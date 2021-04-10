#pragma once
#include <string>

using std::string;

extern HANDLE hConsole; // ���������� ���������� ��� �������������� ������ � ��������� �������
extern CONSOLE_CURSOR_INFO structCursorInfo; // ���������� ���������� ��� ��������� � ���������� ��������� �������

class File {
private:
	string address; // �����
	int maxcount; // ������������ ���������� ������/����� � �����

	/*����������� �������� � ������ ��������� ����������*/
	void Output(string str);
public:
	int colortext; // ����� ����������� �����

	/*�����������*/
	File(string _address);
	/*�������� �����*/
	string GetAddress();
	/*�������� ������������ ���������� ������ � �����*/
	int GetMaxcount();
	/*����� �� ������� �������� �����\������ �� ������. ��������� �������� �����\����� �� ������ ������������. �������� ������ �� ����������������.
	�������� �� ������� ����� �� ������ ������������*/
	string Check(int num = 0, bool dir = false, bool position = false, bool checkaddress = false, bool shortened = false, string _address = "");
	/*����� ������ �� ��������� �����*/
	int Enter(int num);
	/*����� ������ �� ���������� �����*/
	int Back();
	/*����� ����� � �����\�����*/
	void Rename();
	/*�������� �����\�����*/
	void New();
	/*�������� �� �������� �����\�����. �������� �����*/
	void Remove();
	/*�������� ����� � �� �����������*/
	bool RemoveFoulder(string address);
	/*����� ������ �� ���������. ����� � �������� ������ ���������� �������������*/
	void EnterAddress(bool def);
	/*����� �� ����� � ������*/
	bool Find(string path, string mask, string address);
	/*������������ ������� �����*/
	long long SizeFolder(string address);
	/*����������� ����� � �� �����������*/
	bool CopyFolder(string startAd, string endAd);
	/*����������*/
	~File();
};