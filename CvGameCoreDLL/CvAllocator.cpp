#include "CvGameCoreDLL.h"
#include "CvAllocator.h"

CvAllocator::CvAllocator(void)
{
	m_heap = NULL;
}

CvAllocator::~CvAllocator(void)
{
	clearAll();
}

void CvAllocator::clearAll(void)
{
	if (m_heap != NULL)
	{
		HeapDestroy(m_heap);
		m_heap = NULL;
	}
}

void * CvAllocator::allocate(size_t size)
{
	if (m_heap == NULL)
	{
		m_heap = HeapCreate(0, 1024 * 1024 * 5, 0);
	}
	return HeapAlloc(m_heap, 0, size);
}

void CvAllocator::deAllocate(void * ptr)
{
	if (m_heap != NULL)
	{
		HeapFree(m_heap, 0, ptr);
	}
}
