#pragma once

#ifndef _config_py_2_cpp_h
#define _config_py_2_cpp_h
//
// C libs
//
#include <cmath>

//
//	STL
//
#include <vector>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iterator> // for sum_if

//
//	Boost
//
#include <boost/logic/tribool.hpp>	// for None
#include <boost/array.hpp>	// for array
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <boost/bind.hpp>
#include <boost/assign.hpp>	// for list_of, map_list_of
//#include <boost/lambda/lambda.hpp>
using namespace boost;
using namespace boost::assign;

//
// Typedef
//
typedef std::pair<int, int> coord;

//
//	None, True, False
//

#define None	boost::indeterminate
#define True	true
#define False	false

//
// Operators
//
#define and				 &&
#define or				 ||
#define not				 !

//
// Inner functions
//
#define append				push_back
#define len(x)				((int)x.size())
#define sum(v)				std::accumulate(v.begin(), v.end(), 0L)
#define sum_if(v, fn)		std::accumulate_if(v.begin(), v.end(), 0L, fn)
#define sum_if_lt(v, x)		std::accumulate_if(v.begin(), v.end(), 0L, boost::bind(std::less_equal<int>(), _1, x))
#define sum_if_gt(v, x)		std::accumulate_if(v.begin(), v.end(), 0L, boost::bind(std::greater_equal<int>(), _1, x))

typedef bool (*filter)(int, int);

#pragma pack(push,8)
#pragma warning(push,3)
_STD_BEGIN
template<class _InIt,
	class _Ty,
	class _Fn2> inline
	_Ty accumulate_if(_InIt _First, _InIt _Last, _Ty _Val, _Fn2 _Func)
{	// return sum of _Val and all in [_First, _Last), using _Func
	for (; _First != _Last; ++_First)
		if (_Func(*_First))
			_Val += *_First;
	return (_Val);
}
_STD_END
#pragma warning(pop)
#pragma pack(pop)

//
// Range
//
#define VAL_IN(item,v)		std::count(v.begin(), v.end(), item)
#define MAP_IN(item,m)		m.count(item)
#define INDEX(v, item)		((int)(std::find(v.begin(), v.end(), item) - v.begin()))

//
// Float compare
//
#define EPS 	(1e-8)
#define ZERO(x) (((x)>0?(x):-(x))<EPS)

// For OpenMP
#define CACHE_LINE_LEN	64
#endif