#pragma once 

#include "Common.h"

class CentralCache
{
public:
	static CentralCache* GetInstance()
	{
		return &_inst;
	}

	//从中心缓存获取一定数量的内存给thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t num, size_t byte);

	// 从span链表数组中拿出和bytes相等的span链表
	Span* GetOneSpan(SpanList* spanlist, size_t bytes);

	//将ThreadCache中的内存块归还给CentralCache
	void ReleaseListToSpans(void* start, size_t byte);

private:
	SpanList _spanlist[NLISTS];//中心缓存的span链表的数组，默认大小是	NLISTS : 240

private:
	//构造函数默认化，也就是无参无内容
	CentralCache() = default;
	CentralCache(const CentralCache&) = delete;
	CentralCache& operator=(const CentralCache&) = delete;

	//创建一个对象
	static CentralCache _inst;
};