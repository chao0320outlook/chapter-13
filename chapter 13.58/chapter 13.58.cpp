// chapter 13.58.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;
using std::sort;

class Foo {
public:
	Foo sorted() && ;
	Foo sorted() const&;

private:
	vector<int> data;
};

Foo Foo::sorted() &&
{
	sort(data.begin(), data.end());
	std::cout << "&&" << std::endl; // debug
	return *this;
}

Foo Foo::sorted() const &
{
	//    Foo ret(*this);
	//    sort(ret.data.begin(), ret.data.end());
	//    return ret;

	std::cout << "const &" << std::endl; // debug

	//    Foo ret(*this);
	//    ret.sorted();     //13.56
	//    return ret;

	return Foo(*this).sorted(); //13.57
}

int main()
{
	Foo().sorted(); // call "&&"
	Foo f;
	f.sorted(); // call "const &"
}

