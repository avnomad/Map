#include <iostream>
using std::wcout;
using std::wcin;
using std::endl;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <cstdlib>
using std::system;

#include <vector>
using std::vector;


#include <list>
using std::list;

#include <cstring>
using std::strlen;

#include "map.h"

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


const unsigned size = 7;
const unsigned rows = 3;
vector<double> vd(size);
vector<int> vi(size);
//vector<double> vd2(size);
vector<vector<int>> vvi(rows,vector<int>(size));
vector<vector<double>> vvd(rows,vector<double>(size));

void printAll()
{
	wcout << "------------------------------------------\n";
	for(auto i = 0u ; i < vd.size() ; i++)
		wcout << setw(6) << vd[i];
	wcout << "\n\n";

	for(auto i = 0u ; i < vi.size() ; i++)
		wcout << setw(6) << vi[i];
	wcout << "\n\n";

	for(auto i = 0u ; i < vvi.size() ; i++)
	{
		for(auto j = 0u ; j < vvi[i].size() ; j++)
			wcout << setw(6) << vvi[i][j];
		wcout << "\n";
	} // end for
	wcout << "\n\n";

	for(auto i = 0u ; i < vvd.size() ; i++)
	{
		for(auto j = 0u ; j < vvd[i].size() ; j++)
			wcout << setw(6) << vvd[i][j];
		wcout << "\n";
	} // end for
	wcout << "\n\n";
} // end printAll


int main()
{
	wcout << std::boolalpha << setprecision(1) << std::fixed;


	// initializations
	for(auto i = 0u ; i < vd.size() ; i++)
		vd[i] = i*1.1;

	for(auto i = 0u ; i < vi.size() ; i++)
		vi[i] = i;
	
	for(auto i = 0u ; i < vvi.size() ; i++)
		for(auto j = 0u ; j < vvi[i].size() ; j++)
			vvi[i][j] = i*vvi.size()+j;

	for(auto i = 0u ; i < vvd.size() ; i++)
		for(auto j = 0u ; j < vvd[i].size() ; j++)
			vvd[i][j] = (i*vvd.size()+j)*1.1;

	printAll();

	wcout << "vi->vd f\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vi.begin(),vi.end(),vd.begin(),f,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vi.begin(),vi.end(),vd.begin(),f,dummy))>::value << endl;
	map(vi.begin(),vi.end(),vd.begin(),f);
	printAll();
	wcout << "\n";
	wcout << "vvi->vvd f\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvi.begin(),vvi.end(),vvd.begin(),f,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvi.begin(),vvi.end(),vvd.begin(),f,dummy))>::value << endl;
	map(vvi.begin(),vvi.end(),vvd.begin(),f);
	printAll();
	wcout << "\n";
	wcout << "vd->vd f\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vd.begin(),vd.end(),vd.begin(),f,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vd.begin(),vd.end(),vd.begin(),f,dummy))>::value << endl;
	map(vd.begin(),vd.end(),vd.begin(),f);
	printAll();
	wcout << "\n";
	wcout << "vd->vi f\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vd.begin(),vd.end(),vi.begin(),f,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vd.begin(),vd.end(),vi.begin(),f,dummy))>::value << endl;
	map(vd.begin(),vd.end(),vi.begin(),f);
	printAll();
	wcout << "\n";
	wcout << "vvd->vvi f\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvd.begin(),vvd.end(),vvi.begin(),f,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvd.begin(),vvd.end(),vvi.begin(),f,dummy))>::value << endl;
	map(vvd.begin(),vvd.end(),vvi.begin(),f);
	printAll();
	wcout << "\n";
	wcout << "vvd->vvd g\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vvd.begin(),vvd.end(),vvd.begin(),g,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vvd.begin(),vvd.end(),vvd.begin(),g,dummy))>::value << endl;
	map(vvd.begin(),vvd.end(),vvd.begin(),g);
	printAll();
	wcout << "\n";
	wcout << "vi->vi h\n";
	//wcout << "checkBaseCase: " << Workaround<decltype(checkBaseCase(vi.begin(),vi.end(),vi.begin(),h,dummy))>::value << endl;
	//wcout << "checkRecursiveStep: " << Workaround<decltype(checkRecursiveStep(vi.begin(),vi.end(),vi.begin(),h,dummy))>::value << endl;
	//map(vi.begin(),vi.end(),vi.begin(),h);
	//printAll();
	wcout << "\n";
	//map(vi.begin(),vi.end(),vi.begin(),h);	// error: static assertion failed
	//map(vvi.begin(),vvi.end(),vvi.begin(),h);	// error: static assertion failed
	//map(vvi.begin(),vvi.end(),vi.begin(),f);	// error: static assertion failed
	//map(vi.begin(),vi.end(),vvi.begin(),f);	// error: static assertion failed
	//*vi.begin() = h(*vi.begin());
	system("pause");
	return 0;
} // end function main
