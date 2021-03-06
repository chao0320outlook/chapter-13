// chapter 13.36.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#ifndef FOlDER_H
#define FOlDER_H

class Folder
{
public:
	Folder()=default;
	~Folder()=default;
	Folder& operator=(const Folder&);
	Folder(const Folder&) = default;

	void addMsg(Message *m3)//上面需要使用this作为参数,所以这里需要用指针
	{
		messages.insert(m3);
	}
	void remMsg(Message *m4)
	{
		messages.erase(m4);
	}
private:
	set<Message*> messages;//保存Message的指针
};

Folder & Folder::operator=(const Folder &) = default;

#endif FOlDER_H


#ifndef MESSAGE_H//防止头文件重复包含
#define MESSAGE_H

#include <string>
#include <set>
using namespace std;

class Message
{
	friend class Folder;
public:

	Message(const Message& m) :contents(m.contents), folders(m.folders)//拷贝构造函数
	{
		add_to_Folders(m);//拷贝时，将新创建的message的指针添加到每个包含的folder中
	}

	Message& operator=(const Message& mm)//拷贝赋值运算符
	{
		remove_from_Folders();//删除自身
		contents = mm.contents;
		folders = mm.folders;
		add_to_Folders(mm);//将本message传入folder中
		return *this;
	}

	Message(const string &str = "") :contents(str) {}//构造函数
	
	void swap(Message& m1, Message& m2)
	{
		using std::swap;
		//先将每个message从其folders中删除
		for (auto f : m1.folders)
		{
			f->remMsg(this);//所有包含此message的folder进行删除操作
		}
		for (auto f : m2.folders)
		{
			f->remMsg(this);//所有包含此message的folder进行删除操作
		}
		swap(m1.folders, m2.folders);
		swap(m1.contents, m2.contents);
		for (auto f : m1.folders)
		{
			f->addMsg(this);//再进行添加操作
		}
		for (auto f : m2.folders)
		{
			f->addMsg(this);
		}
	}

	~Message()//析构函数
	{
		remove_from_Folders();
	}

	void save(Folder&);
	void remove(Folder&);//对Folder类的操作函数

private:
	string contents;//信息内容
	set<Folder*> folders;//包含本message的folder序列

	void add_to_Folders(const Message&);
	void remove_from_Folders();//从folders中删除本message
};



void Message::save(Folder& f)
{
	folders.insert(&f);//将给定folder加入到我们的folders中
	f.addMsg(this);//将本message添加到给定folder中
}

void Message::remove(Folder& f)
{
	folders.erase(&f);//将给定folder在我们的folders中删除
	f.remMsg(this);//将本message在给定folder中删除
}

void Message::add_to_Folders(const Message& m)
{
	for (auto f : m.folders)
	{
		f->addMsg(this);
	}
}
void Message::remove_from_Folders()
{
	for (auto f : folders)
	{
		f->remMsg(this);//所有包含此message的folder进行删除操作
	}
}

#endif MESSAGE_H




int main()
{
    return 0;
}


