#ifndef MAP_H
#define MAP_H

#include <type_traits>
#include <iterator>

namespace Check
{
	using std::begin;
	using std::end;

	class Dummy{} dummy;
	template<typename T> struct Workaround : T {};

	template<typename IIter, typename OIter, typename Func>
	auto baseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f, Dummy &dummy)->
		decltype(inBegin != inEnd,*outBegin = f(*inBegin),++inBegin,++outBegin,std::true_type());

	template<typename IIter, typename OIter, typename Func>
	auto baseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f, const Dummy &dummy)->std::false_type;

	template<typename IIter, typename OIter, typename Func>
	auto recursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f, Dummy &dummy)->
		decltype(inBegin != inEnd,begin(*inBegin),end(*inBegin),begin(*outBegin),++inBegin,++outBegin,std::true_type());
			// chech whether is_same<decltype(begin(*inBegin)),decltype(end(*inBegin))> ?
	template<typename IIter, typename OIter, typename Func>
	auto recursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f, const Dummy &dummy)->std::false_type;
}; // end namespace Check

template<typename IIter, typename OIter, typename Func>
void map(IIter inBegin, IIter inEnd, OIter outBegin, Func f);

template<bool active> struct Map;

template<>
struct Map<true>
{
	template<typename IIter, typename OIter, typename Func>
	static void mapBaseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
	{
		while(inBegin != inEnd)
		{
			*outBegin = f(*inBegin);
			++inBegin;
			++outBegin;
		} // end while
	} // end function mapBaseCase


	template<typename IIter, typename OIter, typename Func>
	static void mapRecursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
	{
		using std::begin;
		using std::end;

		while(inBegin != inEnd)
		{
			map(begin(*inBegin),end(*inBegin),begin(*outBegin),f);
			++inBegin;
			++outBegin;
		} // end while
	} // end function mapRecursiveStep
}; // end struct Map

template<>
struct Map<false>
{
	template<typename IIter, typename OIter, typename Func>
	static void mapBaseCase(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
	{
		// do nothing
	} // end function mapBaseCase

	template<typename IIter, typename OIter, typename Func>
	static void mapRecursiveStep(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
	{
		// do nothing
	} // end function mapRecursiveStep
}; // end struct Map



template<typename IIter, typename OIter, typename Func>
void map(IIter inBegin, IIter inEnd, OIter outBegin, Func f)
{
	Map<Check::Workaround<decltype(Check::baseCase(inBegin,inEnd,outBegin,f,Check::dummy))>::value>
		::mapBaseCase(inBegin,inEnd,outBegin,f);
	Map<!Check::Workaround<decltype(Check::baseCase(inBegin,inEnd,outBegin,f,Check::dummy))>::value
		&& Check::Workaround<decltype(Check::recursiveStep(inBegin,inEnd,outBegin,f,Check::dummy))>::value>
			::mapRecursiveStep(inBegin,inEnd,outBegin,f);
	static_assert(Check::Workaround<decltype(Check::baseCase(inBegin,inEnd,outBegin,f,Check::dummy))>::value
		|| Check::Workaround<decltype(Check::recursiveStep(inBegin,inEnd,outBegin,f,Check::dummy))>::value,
			"Neither the base case nor the recursive step of map can be applied to this combination of iterators and function");
} // end function map

#endif // MAP_H