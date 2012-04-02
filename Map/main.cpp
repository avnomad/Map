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

class Dummy{};


bool fun(const Dummy &dummy)
{
	return false;
} // end function fun


bool fun(Dummy &dummy)
{
	return true;
} // end function fun


template<typename T>
struct Test : T
{
	static_assert(is_same<T,true_type>::value || is_same<T,false_type>::value,"T is neither true_type nor false_type");
};


int main()
{
	wcout << std::boolalpha;
	Test<true_type> t;

	wcout << t.value << endl;

	wcout << fun(Dummy()) << endl;
	system("pause");
	return 0;
} // end function main
