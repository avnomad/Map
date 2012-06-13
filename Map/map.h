//	Copyright (C) 2008, 2012 Vaptistis Anogeianakis <el05208@mail.ntua.gr>
/*
 *	This file is part of Map.
 *
 *	Map is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Map is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Map.  If not, see <http://www.gnu.org/licenses/>.
 */

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