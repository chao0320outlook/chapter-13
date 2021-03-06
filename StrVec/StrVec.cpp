// StrVec.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class StrVec
{
public:
	StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}
	StrVec(initializer_list<string>lst);
	StrVec(const StrVec&);
	//移动构造函数  noexcept不抛出异常
	StrVec(StrVec &&s) noexcept :
		elements(s.elements), first_free(s.first_free), cap(s.cap)
	{
		//使析构函数安全
		s.elements = s.first_free = s.cap=nullptr;
	}

	StrVec &operator= (StrVec&&) noexcept;

	StrVec &operator= (const StrVec&);
	~StrVec() { free(); }

	void push_back(const string&);
	size_t size() const { return first_free - elements;}
	size_t capacity()const { return cap - elements; }
	string *begin() const { return elements; }
	string *end() const { return first_free; }

private:
	allocator<string> alloc;            //分配元素
	string *elements;    //数组首元素指针
	string *first_free;  //数组第一个空闲元素指针
	string *cap;  //数组尾后元素指针

	void chk_n_alloc() 
	{ if(size()==capacity()) reallocate();}
	pair<string*, string*>alloc_n_copy(const string* ,const string*);
	void free();
	void reallocate();
};

StrVec::StrVec(initializer_list<string> lst)
{
	auto newdata = alloc_n_copy(lst.begin(), lst.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

void StrVec::push_back(const string& s)
{
	chk_n_alloc();   //确保空间足够
	alloc.construct(first_free++, s);
}

pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e)
{
	auto data = alloc.allocate(e - b);
	return { data,uninitialized_copy(b,e,data) };
}

void StrVec::free()
{
	if (elements)
	{
		//逆序销毁元素
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);   
		for_each (elements, first_free, [this](string &rhs) { alloc.destroy(&rhs); });
		alloc.deallocate(elements, cap - elements);       //释放内存空间
	}
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec & StrVec::operator=(StrVec &&rhs) noexcept
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

StrVec & StrVec::operator=(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;

	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));

	auto newcapacity = size() ? 2 * size() : 1;

	auto first = alloc.allocate(newcapacity);
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);

	free();

	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

//使用移动迭代器实现
void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;

	auto first = alloc.allocate(newcapacity);
	auto last = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), first);

	free();

	elements = first;
	first_free = last;
	cap = elements + newcapacity;
}



int main()
{
	initializer_list<string> vec{"adasdad","asdsasd"};
	for (auto &i : vec)
	{
		cout << i << endl;
	}
    
	StrVec vec_1(vec);
	vec_1.push_back("love");
	cout << endl;
	for (auto &i : vec_1)
	{
		cout << i << endl;
	}

	int secs = 300;                                  //延时300s的程序
	clock_t delay = secs * CLOCKS_PER_SEC;           //总延时
	clock_t start = clock();                         //开始时间
	while (clock() - start < delay);                 //时间差大于总延时 跳出循环

	return 0;

}

