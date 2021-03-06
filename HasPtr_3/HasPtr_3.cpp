// HasPtr_3.cpp: 定义控制台应用程序的入口点。
// 原始指针加计数

#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class HasPtr_3
{
public:
	//构造函数，初始化相关成员
	HasPtr_3(const string& s) :
		ps(new string(s)), i(0), use(new size_t(1)) {}

	//拷贝构造函数，将引用计数也拷贝过来，并且递增引用计数
	HasPtr_3(const HasPtr_3& p) :
		ps(p.ps), i(p.i), use(p.use) { ++*use; }

	//拷贝赋值运算符
	HasPtr_3& operator= (const HasPtr_3& p1)
	{
		++*p1.use;//首先递增右侧运算符对象的引用计数
		if (--*use == 0)//递减本对象的引用计数，若没有其他用户，则释放本对象的成员
		{
			delete ps;
			delete use;
		}
		ps = p1.ps;//进行拷贝
		use = p1.use;
		i = p1.i;
		return *this;
	}

	//析构函数
	~HasPtr_3()
	{
		if (*use == 0)//引用计数变为0，说明已经没有对象再需要这块内存，进行释放内存操作
		{
			delete ps;
			delete use;
		}
	}

	string show()
	{
		return *ps;
	};
private:
	//定义为指针，是我们想将该string对象保存在动态内存中
	string * ps;
	size_t *use;//将计数器的引用保存
	int i;
};



int main()
{
	HasPtr_3 a1("i love you"), a2("Sorry"), a3 = a1;

	cout << a1.show() << endl;
	cout << a2.show() << endl;
	cout << a3.show() << endl;

	int secs = 300;                                  //延时300s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环

    return 0;
}

