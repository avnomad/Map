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


class Dummy{};


template<typename T>
struct Test : T
{
	static_assert(is_same<T,true_type>::value || is_same<T,false_type>::value,"T is neither true_type nor false_type");
};

template<typename B,typename T>
struct Propagate : B
{
	static_assert(is_same<B,true_type>::value || is_same<B,false_type>::value,"B is neither true_type nor false_type");
};


template<typename Iter>
auto fun(Iter inBegin,       Dummy &dummy)->decltype(*begin(*inBegin),true)
{return true;}
template<typename Iter>
auto fun(Iter inBegin, const Dummy &dummy)->bool
{return false;}


int main()
{
	Dummy dummy;
	wcout << std::boolalpha;

	vector<double> vd;
	vector<vector<double>> vvd;


	wcout << fun(begin(vd),dummy) << endl;
	wcout << fun(begin(vvd),dummy) << endl;

	system("pause");
	return 0;
} // end function main
