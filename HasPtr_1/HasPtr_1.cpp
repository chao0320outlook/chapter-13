// HasPtr_1.cpp: 定义控制台应用程序的入口点。
// 使用原始指针

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

class HasPtr_1
{
	friend void swap(HasPtr_1&, HasPtr_1&);
	friend bool operator<(const HasPtr_1& s1, const HasPtr_1& s2);
	friend void show(vector<HasPtr_1>& vec);
public:
	//默认构造函数
	HasPtr_1( const string &s =string() ):
		ps( new string (s) ), i(0) {}

	//复制构造函数
	HasPtr_1(const HasPtr_1 &p):
		ps(new string( *(p.ps) ) ),i(p.i) {}

	//复制赋值运算符
	HasPtr_1& operator=(const HasPtr_1 &);

	//析构函数
	~HasPtr_1() { delete ps; }

	string show()
	{
		return *ps;
	};
private:
	string *ps;
	int i;
};

HasPtr_1 & HasPtr_1::operator=(const HasPtr_1 &rhs)
{
	//先复制右侧运算对象，防止自赋操作
	auto newp = new string(*rhs.ps); //复制底层string
	delete ps;                       //释放旧内存
	
	ps = newp;
	i = rhs.i;
	return *this;
}


void swap(HasPtr_1 &a, HasPtr_1 &b)
{
	using std::swap;
	swap(a.ps, b.ps);
	swap(a.i, b.i);
	cout << "--------"<<endl;
}

bool operator<(const HasPtr_1 & s1, const HasPtr_1 & s2)
{
	cout << "定义的 Operator< 被调用" << endl;
	return *s1.ps < *s2.ps;

}

void show(vector<HasPtr_1>& vec)
{
	auto it1 = vec.begin();
	for (it1; it1 != vec.end(); ++it1)
	{
		cout << *(it1->ps) << endl;
	}

}

int main()
{
	HasPtr_1 a1("c"), a2("b"), a3("a");

	cout << a1.show() << endl;
	cout << a2.show() << endl;
	swap(a1, a2);
	cout << a1.show() << endl;
	cout << a2.show() << endl;

	cout << max(a1.show(),a2.show()) << endl;

	vector<HasPtr_1> vec1;
	vec1.push_back(a1);
	vec1.push_back(a2);
	vec1.push_back(a3);

	sort(vec1.begin(), vec1.end());
	show(vec1);

	int secs = 300;                                  //延时120s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环


	return 0;
}

