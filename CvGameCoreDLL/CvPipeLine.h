#pragma once
#ifndef CVPIPELINE_H_
#define CVPIPELINE_H_

#include <vector>
#include <queue>
#include "FProfiler.h"
#include "CvRandom.h"

#define BOOST_THREAD_NO_LIB
#define BOOST_THREAD_USE_LIB
#include  <boost/thread/thread.hpp>

class CvPipeline;
class CvPipelineStage;

typedef enum
{
	WORKITEM_STATE_NONE = -1,
	WORKITEM_STATE_QUEUED,
	WORKITEM_STATE_PROCESSING,
} PipelineWorkItemState;

// A pipeline work item - this records the state of the work item as it flows through
// the pipeline. Appropriate subclasses should be defined for concrete items, sufficient
// to record their state changes as they flow through the pipeline stages
class CvPipelineWorkItem
{
	friend CvPipeline;
	friend CvPipelineStage;

public:
	CvPipelineWorkItem();
	virtual ~CvPipelineWorkItem();

	// Get the priority of this item (determines dequeue order at each stage and may return different values
	// at different stages if necessary). Must be deterministic based on item state however to avoid OOS issues.
	// In cases where requeueing may result in different states the priority used should be related to the item
	// identifier (e.g. - city id) to ensure deterministic processing order in synchronous stages
	virtual int GetPriority(void) const = 0;
	// Provide a unique identifying name (used in rand logging to identify the stream)
	virtual const CvWString GetName(void) const = 0;

	// Requeue the work item to the last non-synchronous stage not yet completed
	// This is intended for use with optimistic locking systems to handle a lock failure
	// down-stream of the pipeline stage that took the lock
	void	Requeue(void);
	// Abandon a work item
	void	Abandon(void);
	// Note that processing has completed (for the current pipeline stage) on this work item
	void	Complete(int iKey);
	// Get a queuiong key - this should be queried before processing and passed to Complete() on completion
	int		GetKey(void) const;

	// Initialize the seed to use in the item's sync rand
	void	SetRandSeed(unsigned long ulSeed);
	// A synchronous random number, which is OOS safe even in multi-threaded pipeline usage. Always
	// use this in pipeline stage processing rather than the regular synced random number generator
	int		GetSyncRand(int iNum, const char* pszLog);
	// Get the current work flow state of this item
	PipelineWorkItemState	GetState(void) const { return m_state; }
protected:
	void					SetState(PipelineWorkItemState state) { m_state = state; m_iQueueingKey++; }

protected:
	CvPipelineStage*	m_currentStage;
	CvPipeline*			m_pipeline;
	CvRandom			m_sorenRand;
private:
	PipelineWorkItemState	m_state;
	int					m_iQueueingKey;
};

// Class representing a processing stage in a pipeline. A Stage may be synchronous or
// asynchronous. A synchronous stage will not begin executing until all work flow items
// have been completely processed up to the end of the previous stage, whereas an asynchronous
// one will process items as soon as they are queued
// A stage may have multiple threads allocated to its processing if desired
// Define appropriate subclasses of this class to provide the processing
class CvPipelineStage
{
	friend CvPipeline;
	friend CvPipelineWorkItem;
public:
	CvPipelineStage(const char* name, bool bSynchronous);
	virtual ~CvPipelineStage();

	// Queue a work item into the stage
	void	EnqueueWorkItem(CvPipelineWorkItem* item);

	// Process a work item
	virtual void ProcessWorkItem(CvPipelineWorkItem* item) = 0;

protected:
	void	NotePorcessed(CvPipelineWorkItem* item);
	void	Stall(void);
	int		GetNumUnprocessedItems(void) const;
	bool	IsSynchronous(void) const { return m_bSynchronous; }
	// Commence processing of queued work items
	void	Begin(void);
	// Complete processing - will synchronously wait for all work items to complete
	bool	End(void);
	// Explicit manipulators for the work counter - used to make sequences where items move
	// between stages thread safe by incrementing the target stage's count before dequeueing
	// from the source stage
	inline void IncrementWorkCount() { InterlockedIncrement(&m_iNumItemsRemaining); }
	inline void DecrementWorkCount() { InterlockedDecrement(&m_iNumItemsRemaining); }
private:
	void	DrainQueue(void);

protected:
	// Next stage in the overall pipeline
	CvPipelineStage* m_nextStage;
	CvPipelineStage* m_prevStage;
private:
	class CvPipelineWorkItemComparer
	{
	public:
		CvPipelineWorkItemComparer() {}
		bool operator() (CvPipelineWorkItem* const& lhs, CvPipelineWorkItem* const& rhs) const
		{
			return lhs->GetPriority() < rhs->GetPriority();
		}
	};
	// Queue of work remaining items to be processed
	std::priority_queue<CvPipelineWorkItem*, std::vector<CvPipelineWorkItem*>, CvPipelineWorkItemComparer> m_queue;
	volatile LONG	m_iNumItemsRemaining;
	volatile LONG	m_iNumItemsQueued;
	CRITICAL_SECTION m_csQueueAccessSection;
	const char*	m_szName;
	bool	m_bSynchronous;
	bool	m_bStalled;
};

// A work flow pipeline the processes work items through multiple pipeline processing stages
class CvPipeline
{
	friend CvPipelineWorkItem;

public:
	CvPipeline(int iMaxThreads);
	virtual ~CvPipeline();

	// Add a stage to the pipeline. Must occur before the pipeline's Begin() is called
	// Note - a stage is assumed to be owned by the pipeline once added, and will be deleted
	// by it when it is finished with it. FUTRUE - encapsulate better within a stage factory
	void	AddStage(CvPipelineStage* stage);
	// Queue a work item to be processed by the pipeline
	void	EnqueueWorkItem(CvPipelineWorkItem* item);
	// Commence processing of queued work items
	void	Begin(void);
	// Complete processing - will synchronously wait for all work items to complete
	void	End(void);

protected:
	void	CompleteItem(CvPipelineWorkItem* item);
	void	RequeueItem(CvPipelineWorkItem* item);
public:
	void	DoDrainThread(void);	// Needs to be public for accessibility from thread function

private:
	CvPipelineStage*	m_firstStage;
	CvPipelineStage*	m_lastStage;
	std::vector<boost::thread*> m_threads;
	int					m_iMaxThreads;
	volatile bool		m_bRunning;
};

// A no-op synchronous stage is often useful to provide a synchronization point to ensure
// all previous pipeline stages are complete for earlier stages before the next (async) stage begins
// this class serves that purpose
class CvPipelineSyncPointStage : public CvPipelineStage
{
public:
	CvPipelineSyncPointStage(const char* name) : CvPipelineStage(name, true) {}

	virtual ~CvPipelineSyncPointStage() {}

	virtual void ProcessWorkItem(CvPipelineWorkItem* item)
	{
		item->Complete((item->GetKey());
	}
};

#endif