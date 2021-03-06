// HasPtr_2.cpp: 定义控制台应用程序的入口点。
//使用智能指针

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class HasPtr_2
{
public:
	//默认构造函数
	HasPtr_2(const string &s) :
		ps(make_shared<string>(s)), i(0) {}

	//复制构造函数
	HasPtr_2(const HasPtr_2 &p) :
		ps(make_shared<string>(*(p.ps))), i(p.i) {}

	//复制赋值运算符
	HasPtr_2& operator=(const HasPtr_2 &);

	//析构函数
	~HasPtr_2() { }

	string show()
	{
		return *ps;
	};
private:
	shared_ptr<string> ps;
	int i;
};

HasPtr_2 & HasPtr_2::operator=(const HasPtr_2 &rhs)
{
	ps = make_shared<string>(*rhs.ps);
	i = rhs.i;
	return *this;
}

int main()
{
	HasPtr_2 a1("i love you"), a2("Sorry"),a3=a1;

	cout << a1.show() << endl;
	cout << a2.show() << endl;
	cout << a3.show() << endl;

	int secs = 300;                                  //延时300s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环


	return 0;
}



