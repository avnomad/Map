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


class Dummy{};


//template<typename T>
//struct Test : T
//{
//	static_assert(is_same<T,true_type>::value || is_same<T,false_type>::value,"T is neither true_type nor false_type");
//};

template<typename B,typename T>
struct Propagate : B
{
	static_assert(is_same<B,true_type>::value || is_same<B,false_type>::value,"B is neither true_type nor false_type");
};


template<typename T>
struct Identity : T {};


template<typename Iter>
auto fun(Iter inBegin,       Dummy &dummy)->decltype(*begin(*inBegin),*end(*inBegin),
	integral_constant<unsigned,Identity<decltype(fun(begin(*inBegin),dummy))>::value+1u>());
template<typename Iter>
auto fun(Iter inBegin, const Dummy &dummy)->integral_constant<unsigned,0u>;




template<unsigned n>
void f()
{
	wcout << "some" << endl;
}

template<>
void f<0>()
{
	wcout << "none" << endl;
}


int main()
{
	Dummy dummy;
	wcout << std::boolalpha;

	f<5>();
	f<0>();

	//vector<double> vd;
	//vector<vector<double>> vvd;
	//vector<vector<vector<int>>> vvvi;
	//list<vector<vector<list<unsigned>>>> lvvlu;

	//wcout << Identity<decltype(fun(begin(vd),dummy))>::value << endl;
	//wcout << Identity<decltype(fun(begin(vvd),dummy))>::value << endl;
	//wcout << Identity<decltype(fun(begin(vvvi),dummy))>::value << endl;
	//wcout << Identity<decltype(fun(begin(lvvlu),dummy))>::value << endl;

	//wcout << fun(begin(vd),dummy) << endl;
	//wcout << fun(begin(vvd),dummy) << endl;

	system("pause");
	return 0;
} // end function main
