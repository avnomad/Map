#include <iostream>
using std::wcout;
using std::wcin;
using std::endl;

#include <cstdlib>
using std::system;

#include <type_traits>
using std::true_type;
using std::false_type;
using std::integral_constant;
using std::is_same;
using std::is_convertible;

#include <vector>
using std::vector;
using std::begin;
using std::end;

#include <list>
using std::list;


class Dummy{} dummy;
template<typename T> struct Workaround : T {};

template<typename IIter, typename OIter, typename Func>
auto checkBaseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f, Dummy &dummy)->
	decltype(inBegin != inEnd,*outBegin = f(*inBegin),++inBegin,++outBegin,true_type());

template<typename IIter, typename OIter, typename Func>
auto checkBaseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f, const Dummy &dummy)->false_type;

template<typename IIter, typename OIter, typename Func>
auto checkRecursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f, Dummy &dummy)->
	decltype(inBegin != inEnd,begin(*inBegin),end(*inBegin),begin(*outBegin),++inBegin,++outBegin,true_type());
		// chech whether is_same<decltype(begin(*inBegin)),decltype(end(*inBegin))> ?
template<typename IIter, typename OIter, typename Func>
auto checkRecursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f, const Dummy &dummy)->false_type;


template<typename IIter, typename OIter, typename Func>
void map(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
{
	if(Workaround<decltype(checkBaseCase(inBegin,inEnd,outBegin,f,dummy))>::value)	// if this block of code would be semantically correct...
	{																				// ...run this block
		while(inBegin != inEnd)
		{
			*outBegin = f(*inBegin);
			++inBegin;
			++outBegin;
		} // end while
	}
	else if(Workaround<decltype(checkRecursiveStep(inBegin,inEnd,outBegin,f,dummy))>::value)	// if that block of code would be semantically correct...
	{			// ...run that block
		//using std::begin;
		//using std::end;

		while(inBegin != inEnd)
		{
			map(begin(*inBegin),end(*inBegin),begin(*outBegin),f);
			++inBegin;
			++outBegin;
		} // end while
	} // end if

	static_assert(!Workaround<decltype(checkBaseCase(inBegin,inEnd,outBegin,f,dummy))>::value
		&& !Workaround<decltype(checkRecursiveStep(inBegin,inEnd,outBegin,f,dummy))>::value,
			"Neither the base case nor the recursive step of map can be applied to this combination of iterators and function");
} // end function map


int main()
{
	wcout << std::boolalpha;




	system("pause");
	return 0;
} // end function main
