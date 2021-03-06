// chapter 13.17.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>  
#include <ctime>
using namespace std;


class A
{
public:
	A()//默认构造函数，14题
	{
		static int val1 = 10;
		val = val1++;
	}
	A(A &a)//自定义版本的拷贝构造函数
	{
		val = a.val + 5;
	}
	int val;
};
void show2(A a)
{
	cout << a.val << endl;
}
void show3(const A& a)
{
	cout << a.val << endl;
}


int main(int argc, char**argv)
{
	A a, b = a, c = b;

	A d, e = d, f = e;
	show2(a);//调用函数时需要拷贝一次
	show2(b);
	show2(c);

	cout << endl;

	show3(d);//这里的调用不需要拷贝构造运算符
	show3(e);
	show3(f);

	int secs = 300;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环


	return 0;
}


