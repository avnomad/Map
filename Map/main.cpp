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

#include <cstring>
using std::strlen;

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
	{																							// ...run that block
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


double f(int x)
{
	return 1.5*x;
}

vector<double> g(const vector<double> &in)
{
	return vector<double>();
}

int h(char *s)
{
	return strlen(s);
}

int main()
{
	wcout << std::boolalpha;

	const unsigned size = 7;
	vector<double> vd(size);
	vector<int> vi(size);
	vector<double> vd2(size);
	vector<vector<int>> vvi(size,vector<int>(size));
	vector<vector<double>> vvd(size,vector<double>(size));

	wcout << "vi->vd\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vi.begin(),vi.end(),vd.begin(),f,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vi.begin(),vi.end(),vd.begin(),f,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vvi->vvd\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvi.begin(),vvi.end(),vvd.begin(),f,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvi.begin(),vvi.end(),vvd.begin(),f,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vd->vd\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vd.begin(),vd.end(),vd.begin(),f,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vd.begin(),vd.end(),vd.begin(),f,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vd->vi\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vd.begin(),vd.end(),vi.begin(),f,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vd.begin(),vd.end(),vi.begin(),f,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vvd->vvi\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvd.begin(),vvd.end(),vvi.begin(),f,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvd.begin(),vvd.end(),vvi.begin(),f,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vvd->vvd g\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvd.begin(),vvd.end(),vvd.begin(),g,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvd.begin(),vvd.end(),vvd.begin(),g,dummy))>::value << endl;
	wcout << "\n";
	wcout << "vi->vi h\n";
	wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vi.begin(),vi.end(),vi.begin(),h,dummy))>::value << endl;
	wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vi.begin(),vi.end(),vi.begin(),h,dummy))>::value << endl;
	wcout << "\n";
	//map(vi.begin(),vi.end(),vi.begin(),h);
	//*vi.begin() = h(*vi.begin());
	system("pause");
	return 0;
} // end function main
