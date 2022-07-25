/*************************************************************************
    > File Name: test.cpp
    > Author: Alice
    > Mail: 2789828898@qq.com
    > Created Time: Thu Jun 30 12:14:40 2022
 ************************************************************************/

#include <cstdio>
#include<iostream>
#include <string>
using namespace std;

class ZIP
{
public:
	void Compress(string src_file_path , string dsc_file_path)
	{
		cout << "ZIP模块正在进行" << src_file_path << "文件的压缩..."<< endl;
		cout << "文件压缩成功,已保存至"<< dsc_file_path << endl;
	}

	void DeCompress(string src_file_path , string dsc_file_path)
	{
		cout << "ZIP模块正在进行" << src_file_path << "文件的解压缩..."<< endl;
		cout << "文件解压缩成功,已保存至"<< dsc_file_path << endl;
	}
};

class RAR
{
public:
	void Compress(string src_file_path , string dsc_file_path)
	{
		cout << "RAR模块正在进行" << src_file_path << "文件的压缩..."<< endl;
		cout << "文件压缩成功,已保存至"<< dsc_file_path << endl;
	}

	void DeCompress(string src_file_path , string dsc_file_path)
	{
		cout << "RAR模块正在进行" << src_file_path << "文件的解压缩..."<< endl;
		cout << "文件解压缩成功,已保存至"<< dsc_file_path << endl;
	}
};

class QZ
{
public:
	void Compress(string src_file_path , string dsc_file_path)
	{
		cout << "7Z模块正在进行" << src_file_path << "文件的压缩..."<< endl;
		cout << "文件压缩成功,已保存至"<< dsc_file_path << endl;
	}

	void DeCompress(string src_file_path , string dsc_file_path)
	{
		cout << "7Z模块正在进行" << src_file_path << "文件的解压缩..."<< endl;
		cout << "文件解压缩成功,已保存至"<< dsc_file_path << endl;
	}
};

class Appearance
{
private:
	ZIP* zip;
	RAR* rar;
	QZ* qz;

public:
	Appearance(ZIP* zip = new ZIP , RAR* rar = new RAR , QZ* qz = new QZ)
	:zip(zip), rar(rar), qz(qz){}

	~Appearance()
	{
		delete zip;
		delete rar;
		delete qz;
	}

public:
	void Compress(string src_file_path, string dsc_file_path, string type)
	{
		if(type == "ZIP")
			zip->Compress(src_file_path, dsc_file_path);
		else if(type == "RAR")
			rar->Compress(src_file_path, dsc_file_path);
		else if(type == "7Z")
			qz->Compress(src_file_path, dsc_file_path);
	}

	void DeCompress(string src_file_path, string dsc_file_path, string type)
	{
		if(type == "ZIP")
			zip->DeCompress(src_file_path, dsc_file_path);
		else if(type == "RAR")
			rar->DeCompress(src_file_path, dsc_file_path);
		else if(type == "7Z")
			qz->DeCompress(src_file_path, dsc_file_path);
	}
};

int main(void)
{
	Appearance jarvis = Appearance();
	jarvis.Compress("love", "./", "ZIP");
	jarvis.Compress("Joy", "../", "RAR");
	jarvis.Compress("Peace", "./book", "7Z");
	cout << "===============" << endl;
	jarvis.DeCompress("love", "./", "ZIP");
	jarvis.DeCompress("Joy", "../", "RAR");
	jarvis.DeCompress("Peace", "./book", "7Z");
    return 0;
}
