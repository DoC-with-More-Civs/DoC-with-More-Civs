#pragma once

#ifndef _CVALLOCATOR_H_
#define _CVALLOCATOR_H_

#include <Windows.h>

// Class to handle long-lived memory allocations, principally intended
// for instances of entity classes like CvUnit, CvCity, etc.
class CvAllocator
{
public:
	CvAllocator(void);
	virtual ~CvAllocator(void);

	void clearAll(void);

	void*	allocate(size_t size);
	void	deAllocate(void* ptr);

private:
	HANDLE	m_heap;
};

#endif