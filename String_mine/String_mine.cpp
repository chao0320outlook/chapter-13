// String_mine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class String_mine
{
public:
	String_mine() = default;
	String_mine(const char*);

	//c++11 五个复制控制成员
	String_mine(const String_mine&);  //复制构造
	String_mine& operator=(const String_mine&);   //复制赋值运算
	String_mine(String_mine&&rhs)noexcept :elements(rhs.elements), end(rhs.end)  //移动构造
	{
		rhs.elements = rhs.end = nullptr;
		cout << "移动构造函数" << endl;
	}
	String_mine& operator=(String_mine&&)noexcept;  //移动赋值运算
	~String_mine() { free(); }  //析构

private:
	allocator<char> alloc;
	char* elements;
	char* end;

	pair<char*,char*>alloc_n_copy(const char*, const char*);
	void range_initializer(const char*, const char*);
	void free();

};

String_mine::String_mine(const char *s)
{
	auto s1 = const_cast<char*>(s);//转化为非常量的指针
	while (*s1)
	{
		++s1;//使其指向最后一个位置的尾部
	}
	range_initializer(s, s1);
}

String_mine::String_mine(const String_mine &rhs)
{
	range_initializer(rhs.elements, rhs.end);
	cout << "拷贝构造函数" << endl;
}

String_mine & String_mine::operator=(const String_mine &rhs)
{
	auto newstr = alloc_n_copy(rhs.elements, rhs.end);
	free();
	elements = newstr.first;
	end = newstr.second;
	cout << "拷贝赋值运算符" << endl;
	return *this;
}

String_mine & String_mine::operator=(String_mine &&rhs)noexcept
{
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		end = rhs.end;
		rhs.elements = rhs.end = nullptr;//将源对象置为可析构的状态
	}
	cout << "移动赋值运算符" << endl;
	return *this;
	// TODO: 在此处插入 return 语句
}

pair<char*, char*> String_mine::alloc_n_copy(const char *a, const char *b)
{
	auto s1 = alloc.allocate(b - a);             //allocate参数为分配内存的大小
	auto s2 = uninitialized_copy(a, b, s1);     //拷贝赋值，将a到b之间的元素拷贝至s1,返回的是最后一个构造元素之后的位置
	return make_pair(s1, s2);   //返回首尾指针
}

void String_mine::range_initializer(const char *c, const char *d)
{
	auto p = alloc_n_copy(c, d);//拷贝并初始化新的string
	elements = p.first;
	end = p.second;//将新的string的首尾指针赋值
}

void String_mine::free()
{
	if (elements)
	{
		for_each(elements, end, [this](char &rhs) {alloc.destroy(&rhs); });
		alloc.deallocate(elements, end - elements);
	}
}

int main()
{
	vector<String_mine>vec{ "aaaa","bbbb" };
	String_mine str_1("1");
	String_mine str_2("11"), str_3("111"), str_4("1111");

	str_3 = "adssa";     //使用移动赋值
	str_2 = str_1;       //使用复制赋值
	str_3 = std::move(str_4);   //使用移动赋值

	vec.push_back("cccc");  //使用移动构造
	//vec内存不够，寻找新的存储位置时，使用移动构造函数进行移动
	vec.push_back(str_2);   //使用复制构造


	//搞不懂 push_back  没添加一个数都要把所有成员复制一次   暂时理解为每次vector得寻找更大的存储空间
	//cout << "............." << endl;
	//vec.push_back(str_1);                         
	//cout << "............." << endl;
	//vec.push_back(str_2);
	//cout << "............." << endl;
	//vec.push_back(str_3);
	//cout << "............." << endl;
	//vec.push_back(str_4);
	//cout << "............." << endl;
	//vec.push_back(str_4);
	//cout << "............." << endl;
	//vec.push_back(str_4);
	//cout << "............." << endl;
	//vec.push_back(str_4);


	int secs = 300;                                  //延时300s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环

	return 0;
}

