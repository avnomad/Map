#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <cstdlib>
using std::system;


template<typename T>
struct Array
{
	T x;
};

template<typename T>
struct Func
{
};

template<typename T>
Array<T> map(Array<T> &a, Func<T> &f)
{
	cout<<"base"<<endl;
	return a;
}

template<typename T,typename E>
Array<T> map(Array<T> &a, Func<E> &f)
{
	cout<<"step"<<endl;
	map(a.x,f);
	return a;
}

int main()
{
	Array<Array<Array<int> > > arr;
	Func<int> func;
	map(arr,func);

	system("pause");
	return 0;
} // end function main
