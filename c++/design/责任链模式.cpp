/*************************************************************************
    > File Name: test_2.cpp
    > Author: Alice
    > Mail: 2789828898@qq.com
    > Created Time: Mon Jun 27 11:22:52 2022
 ************************************************************************/

#include <cstdio>
#include<iostream>
#include <string>
using namespace std;

class Request
{
private:
	int dayoff;
	string name;
	string reason;
	string leader;

public:
	Request(int dayoff = 0 , string name = "" , string reason = "" , string leader = "")
	:dayoff(dayoff) , name(name) , reason(reason) , leader(leader){}

public:
	string GetName(void)
	{
		return this->name;
	}

    int GetDayOff(void)
	{
		return this->dayoff;
	}

	string GetReason(void)
	{
		return this->reason;
	}
};

class Responsible
{
private:
	string name;
	string title;
	Responsible* next;

protected:
	Responsible(string name = "" , string title = "" , Responsible* next = NULL)
    :name(name) , title(title) , next(next){}

public:
    virtual ~Responsible()
	{
		delete next;
	}

public:
	string GetName(void)
	{
		return this->name;
	}

	string GetTitle(void)
	{
		return this->title;
	}

	void SetNextResponsible(Responsible* next)
	{
		this->next = next;
	}

	Responsible* GetNextResponsible(void)
	{
		return this->next;
	}

    void HandleResquest(Request* request)
	{
		this->HandleRequestImpl(request);
		if(this->next != NULL)
			this->next->HandleResquest(request);
	}

	virtual void HandleRequestImpl(Request* request) = 0;
};

class Person
{
private:
	string name;

public:
	Person(string name = "")
	:name(name){}

public:
	string GetName(void)
	{
		return this->name;
	}

    void SendRequest(Request* request , Responsible* leader)
	{
		cout << this->name << " apply for leave " << request->GetDayOff() << " day, " << "reason for leave: " << request->GetReason() << endl; 
	    if(leader != NULL)
			leader->HandleResquest(request);
	}
};

class Supervisor : public Responsible
{
public:
	Supervisor(string name = "" , Responsible* next = NULL , string title = "Supervisor")
	:Responsible(name , title , next){}

public:
	void HandleRequestImpl(Request* request) override
	{
        if(request->GetDayOff() <= 2)
		    cout << "Agree " << request->GetName() << " leave, Signatory: " << this->GetName() << " " << this->GetTitle() << endl; 
	}
};

class DepartmentManager : public Responsible
{
public:
	DepartmentManager(string name = "" ,  Responsible* next = NULL , string title = "DepartmentManager")
	:Responsible(name , title , next){}

public:
	void HandleRequestImpl(Request* request) override
	{
        if(request->GetDayOff() > 2 && request->GetDayOff() <= 5)
			cout << "Agree " << request->GetName() << " leave, Signatory: " << this->GetName() << " " << this->GetTitle() << endl; 
	}
};

class CEO : public Responsible
{
public:
	CEO(string name = "" , Responsible* next = NULL , string title = "CEO")
	:Responsible(name , title , next){}

public:
	void HandleRequestImpl(Request* request) override
	{
        if(request->GetDayOff() > 5 && request->GetDayOff() <= 22)
			cout << "Agree " << request->GetName() << " leave, Signatory: " << this->GetName() << " " << this->GetTitle() << endl; 
	}
};

class Administrator : public Responsible
{
public:
	Administrator(string name = "" ,  Responsible* next = NULL , string title = "Administrator")
	:Responsible(name , title , next){}

public:
	void HandleRequestImpl(Request* request) override
	{
		cout << request->GetName() << " leave application reviewed, the situation is true, the record has been processed, handler: " << this->GetName() << " " << this->GetTitle() << endl;
	}
};

int main(void)
{
    Responsible* administrator = new Administrator("Alice");
	Responsible* ceo = new CEO("Alien" , administrator);
	Responsible* department_manager = new DepartmentManager("Jacobi" , ceo);
	Responsible* supervisor = new Supervisor("Jack" , department_manager);

	Person* me = new Person("Ish");
	Request* me_request = new Request(5, "Ish", "I'll back home.", "Supervisor");
	me->SendRequest(me_request , supervisor);

	Person* you = new Person("Luci");
	Request* you_request = new Request(2, "Luci", "I am sick.", "DepartmentManager");
    you->SendRequest(you_request , department_manager);

	delete me;
	delete you;
	delete me_request;
	delete you_request;
	delete supervisor;
}
