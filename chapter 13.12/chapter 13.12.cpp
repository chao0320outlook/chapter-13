// chapter 13.12.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>  
#include<string>  
#include<fstream>
#include<list>
#include<vector> 
#include<map>  
#include<set>
#include<cctype>//ctype无法打开，包含tolower()函数和ispunct函数
#include<algorithm>
#include<utility>//保存pair的头文件
#include<memory>
#include <ctime>
using namespace std;

class A
{
public:
	A(int m) :val(m)//默认构造函数
	{
		cout << "默认构造函数" << endl;
	}

	A(const A& a):val(a.val)//复制构造函数
	{
		cout << "复制构造函数" << endl;
	}

	A& operator= (const A& a) //拷贝赋值运算符
	{
		val = a.val;
		cout << "拷贝复制运算符" << endl;
		return *this;
	}

	~A()//析构函数
	{
		cout << "析构函数" << endl;
	}
//private:
	int val;

};

void show1(A& a)
{
	cout << a.val << endl;
}
void show2(A a)
{
	cout << a.val << endl;
}
int main(int argc, char**argv)
{
	//将A的对象当作引用或者非引用传递
	{
		A a(10);
		A b(5);
		A c(2);
		c = a;
		show1(a);
		show2(b);
		show2(c);
		//存放于容器中
		vector<A> m;
		m.push_back(a);                      //向容器中添加已存在变量调用复制构造函数
		//m.push_back(10);
		//动态分配
		A *d = new A(5);
		show2(*d);
		delete d;

	}

	int secs = 300;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环


	return 0;


}

   