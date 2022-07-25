/*************************************************************************
    > File Name: test.cpp
    > Author: Alice
    > Mail: 2789828898@qq.com
    > Created Time: Mon Jun 27 13:54:05 2022
 ************************************************************************/

#include<iostream>
#include <string>
using namespace std;

class Subject
{
private:
	string name;

protected:
	Subject(string name = "")
	:name(name){}

public:
	virtual ~Subject()
	{
		cout << "I'm Subect destructor" << endl;
	}

public:
	string GetName(void)
	{
		return this->name;
	}

	virtual void Request(string content) = 0;
};

class ProxySubject : public Subject
{
protected:
	Subject* real_subject;

protected:
	ProxySubject(string name = "" , Subject* real_subject = NULL)
	:Subject(name) , real_subject(real_subject){}

public:
    ~ProxySubject()
	{
		cout << "I'm ProxySubject destructor" << endl;
		delete real_subject;
	}

public:
    void Request(string content)
	{
        this->PreRequest();
		if(real_subject != NULL)
			real_subject->Request(content);
		this->AfterRequest();
	}

	virtual void PreRequest(void) = 0;
	virtual void AfterRequest(void) = 0;
};

class TonyReception : public Subject
{
private:
	string phone;

public:
	TonyReception(string name = "Tony" , string phone = "15537413929")
	:Subject(name) , phone(phone){}

    ~TonyReception()
	{
		cout << "I'm TonyReception destructor" << endl;
	}

public:
	string GetPhone(void)
	{
		return this->phone;
	}

    void Request(string content) override
	{
		cout << "货物主人:" << this->GetName() << "   " << "手机号:" << this->phone << endl;
		cout << "接收到一个包裹，包裹内容: " << content << endl; 
	}
};

class WendyProxy : public ProxySubject
{
public:
	WendyProxy(Subject* real_subject = NULL , string name = "Wendy")
	:ProxySubject(name , real_subject){}

    ~WendyProxy()
	{
		cout << "I'm WendyProxy destructor" << endl;
	}

public:
	void PreRequest(void) override
	{
        cout << "我是" << this->real_subject->GetName() << "的朋友，我来帮他代收快递!"<< endl;
	}

	void AfterRequest(void) override
	{
		cout << "代收人:" << this->GetName() << endl;
	}
};
	

int main(void)
{
	Subject* tony = new TonyReception();
	tony->Request("One piece");

    Subject* wendy = new WendyProxy(tony);
    wendy->Request("One piece");

	delete wendy;
	return 0;
}
