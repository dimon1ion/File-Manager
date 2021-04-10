#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <io.h>
#include <direct.h>
#include <exception>
#include <filesystem>
#include "File.h"
#define Tcolor SetConsoleTextAttribute

namespace fs = std::filesystem;

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;


#pragma region Private metods

void File::Output(string str) {
	int i = 0;
	for (; i < 38 && i < str.length(); i++) {
		cout << str[i];
	}
	if (i == 38) {
		cout << "..";
	}
}

#pragma endregion

#pragma region Constructor & Destructor

File::File(string _address) {
	address = _address;
	colortext = 1;
}

File::~File(){}

#pragma endregion

#pragma region Getters

string File::GetAddress() {
	return address;
}

int File::GetMaxcount() {
	return maxcount;
}

#pragma endregion

#pragma region Public metods

string File::Check(int num, bool dir, bool position, bool checkaddress, bool shortened, string _address) {
	/*num - номер файла\папки, dir - проверка папка или файл по номеру, position - наличие подсказок, checkaddress - проверка адреса на дейсвтительность
	shortened - укороченная версия интерфейса, _address - смена адреса на другой*/
	/*Вывод на консоль названий папок, цвет для файла\папки */
	bool getfile = (num <= 0), colorfol;
	/*Адрес + маска*/
	string path;
	char time[100];
	if (_address.empty()) {
		path = address;
	}
	else {
		path = _address;
	}
	path += "*.*";
	_finddata_t* fileinfo = new _finddata_t;
	long done = _findfirst(path.c_str(), fileinfo);
	int isReadable = done;
	int count = 0; // Счетчик
	/*Хранение имени файла\папки в строке*/
	string str;
	/*Смена позиции курсора по Y, в зависимости количества строк 'Подсказок'*/
	int numpos = 0;
	if (position) { numpos = 17; }
	if (num == 0) {
		SetConsoleCursorPosition(hConsole, { 0, 4 + (SHORT)numpos });
		Tcolor(hConsole, 15);
		cout << "Имя";
		if (shortened) {
			SetConsoleCursorPosition(hConsole, { 45, 4 + (SHORT)numpos });
			cout << "Размер";
			SetConsoleCursorPosition(hConsole, { 75, 4 + (SHORT)numpos });
			cout << "Дата Изменения";
		}
	}
	while (isReadable != -1) {
		count++;
		if (checkaddress) {
			return "";
		}
		str = fileinfo->name;
		if (getfile) {
			ctime_s(time, 100, &fileinfo->time_write);
			colorfol = fileinfo->attrib & _A_SUBDIR;
			if (colorfol) {
				Tcolor(hConsole, 6);
			}
			else {
				Tcolor(hConsole, 5);
			}
			if (num == -1 && count == colortext - 1) { //Закрашивает чернобелым цветом предыдущий ход
				SetConsoleCursorPosition(hConsole, { 0, 5 + (SHORT)numpos + (SHORT)count });
				cout << count << "  ";
				if (shortened) {
					Output(str);
				}
				else {
					cout << str;
				}
				Tcolor(hConsole, 8);
				if (fileinfo->size != 0) {
					if (shortened) {
						SetConsoleCursorPosition(hConsole, { 45 , 5 + (SHORT)numpos + (SHORT)count });
						cout << fileinfo->size << " байтов";
						SetConsoleCursorPosition(hConsole, { 75 , 5 + (SHORT)numpos + (SHORT)count });
						cout << time;
					}
					else {
						cout << "\t\t" << fileinfo->size << " байтов" << "\t\t" << time;
					}
				}
			}
			else if (colortext == count) {
				if (num != -10) {
					if (colorfol) {
						Tcolor(hConsole, 246);
					}
					else {
						Tcolor(hConsole, 245);
					}
				}
				SetConsoleCursorPosition(hConsole, { 0, 5 + (SHORT)numpos + (SHORT)count });
				cout << count << "  ";
				if (shortened) {
					Output(str);
				}
				else {
					cout << str;
				}
				Tcolor(hConsole, 240);
				if (fileinfo->size != 0) {
					if (shortened) {
						SetConsoleCursorPosition(hConsole, { 45 , 5 + (SHORT)numpos + (SHORT)count });
						cout << fileinfo->size << " байтов";
						SetConsoleCursorPosition(hConsole, { 75 , 5 + (SHORT)numpos + (SHORT)count });
						cout << time;
					}
					else {
						cout << "\t\t" << fileinfo->size << " байтов" << "\t\t" << time;
					}
				}
				if (num == -1) { break; }
			}
			else if (num == -2 && count == colortext + 1) { //Закрашивает чернобелым цветом предыдущий ход
				SetConsoleCursorPosition(hConsole, { 0, 5 + (SHORT)numpos + (SHORT)count });
				cout << count << "  ";
				if (shortened) {
					Output(str);
				}
				else {
					cout << str;
				}
				Tcolor(hConsole, 8);
				if (fileinfo->size != 0) {
					if (shortened) {
						SetConsoleCursorPosition(hConsole, { 45 , 5 + (SHORT)numpos + (SHORT)count });
						cout << fileinfo->size << " байтов";
						SetConsoleCursorPosition(hConsole, { 75 , 5 + (SHORT)numpos + (SHORT)count });
						cout << time;
					}
					else {
						cout << "\t\t" << fileinfo->size << " байтов" << "\t\t" << time;
					}
				}
				break;
			}
			else {
				if (num == 0 || num == -10) {
					SetConsoleCursorPosition(hConsole, { 0, 5 + (SHORT)numpos + (SHORT)count });
					cout << count << "  ";
					if (shortened) {
						Output(str);
					}
					else {
						cout << str;
					}
					Tcolor(hConsole, 8);
					if (fileinfo->size != 0) {
						if (shortened) {
							SetConsoleCursorPosition(hConsole, { 45 , 5 + (SHORT)numpos + (SHORT)count });
							cout << fileinfo->size << " байтов";
							SetConsoleCursorPosition(hConsole, { 75 , 5 + (SHORT)numpos + (SHORT)count });
							cout << time;
						}
						else {
							cout << "\t\t" << fileinfo->size << " байтов" << "\t\t" << time;
						}
					}
				}
			}
		}
		else {
			if (num == count) { // Вывод файла или проверка на папку
				if (dir) {
					if (fileinfo->attrib & _A_SUBDIR) {
						_findclose(done);
						delete fileinfo;
						return str;
					}
					return "";
				}
				_findclose(done);
				delete fileinfo;
				return str;
			}
		}
		isReadable = _findnext(done, fileinfo);
	}
	_findclose(done);
	delete fileinfo;
	if (count == 0) {
		return "Error 1234567";
	}
	if (num == 0) {
		SetConsoleCursorPosition(hConsole, { 0, 4 + (SHORT)numpos });
		maxcount = count;
	}
	Tcolor(hConsole, 15);
	return "";
}

int File::Enter(int num) {
	string str = Check(num, true);
	if (!str.empty()) {
		if (str == ".") {
			return -1;
		}
		else if (str == "..") {
			Back();
			return 0;
		}
		address += str + '\\';
		ofstream out("Address.txt");
		out << address;
		out.close();
		colortext = 1;
		system("cls");
		return 0;
	}
	return -1;
}

int File::Back() {
	string str = address;
	str.pop_back();
	if (str[str.length() - 1] == ':') {
		return -1;
	}
	for (int i = str.length() - 1, j = str.find_last_of("\\"); j < i; i--) {
		str.pop_back();
	}
	address = str;
	ofstream out("Address.txt");
	out << address;
	out.close();
	system("cls");
	colortext = 1;
	return 0;
}

void File::Rename() {
	string old = address + Check(colortext);
	string nev = address;
	string tmp;
	system("cls");
	cout << "Введите новое название файла/папки: ";
	SetConsoleCursorPosition(hConsole, { 0, 2 });
	cout << "Уже существующие файлы\\папки:\n";
	Check(0);
	SetConsoleCursorPosition(hConsole, { 36, 0 });
	Tcolor(hConsole, 10);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
	getline(cin, tmp);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
	nev.append(tmp);
	if (rename(old.c_str(), nev.c_str()) != 0) {
		Tcolor(hConsole, 4);
		cout << "Error...";
	}
	else {
		cout << "Complete...";
	}
	Sleep(500);
	colortext = 1;
}

void File::New() {
	int write;
	system("cls");
	while (true) {
		cout << "Что бы вы хотели создать?"
			<< "\n1 Папка"
			<< "\n2 Файл"
			<< "\n3 Отмена\n";
		write = _getch();
		switch (write) {
		case 49:
		case 50:
		{
			string tmp;
			string str = address;
			system("cls");
			cout << "Введите название";
			if (write == 50) {
				cout << "(без маски): ";
			}
			else {
				cout << ": ";
			}
			SetConsoleCursorPosition(hConsole, { 0, 2 });
			cout << "Уже существующие файлы\\папки:\n";
			Check(-10);
			if (write == 49) {
				SetConsoleCursorPosition(hConsole, { 18, 0 });
			}
			else {
				SetConsoleCursorPosition(hConsole, { 29, 0 });
			}
			Tcolor(hConsole, 10);
			structCursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(hConsole, &structCursorInfo);
			getline(cin, tmp);
			structCursorInfo.bVisible = FALSE;
			SetConsoleCursorInfo(hConsole, &structCursorInfo);
			if (tmp.empty()) {
				Tcolor(hConsole, 4);
				cout << "Error...";
				break;
			}
			str.append(tmp);
			if (write == 50) {
				str += ".txt";
			}
			if (_mkdir(str.c_str()) == -1) {
				Tcolor(hConsole, 4);
				cout << "Error...";
			}
			else {
				cout << "Complete...";
				if (write == 50) {
					try // Отлавливаю момент, если когда я создам папку, и паралельная программа или сверх быстрая рука создаст файл в папке, то выявит код ошибки
					{
						if (_rmdir(str.c_str()) == -1) {
							throw - 1;
						}
					}
					catch (int e)
					{
						system("cls");
						Tcolor(hConsole, 4);
						ofstream out("Error code.txt");
						out << "Error code: -1";
						for (int i = 9; i >= 0; i--) {
							cout << "Error code: " << e << "  " << i;
							SetConsoleCursorPosition(hConsole, { 0, 0 });
							Sleep(1000);
						}
					}
					ofstream out(str.c_str());
					out.close();
				}
			}
			break;
		}
		case 51:
			return;
		default:
			SetConsoleCursorPosition(hConsole, { 0, 0 });
			continue;
		}
		Sleep(500);
		break;
	}
}

void File::Remove() {
	int write;
	system("cls");
	while (true) {
		cout << "Вы уверенны что хотите удалить?"
			<< "\n1 Да"
			<< "\n2 Нет\n";
		write = _getch();
		switch (write) {
		case 49:
		{
			Tcolor(hConsole, 10);
			string str = Check(colortext, true);
			if (str.empty()) {
				str = address + Check(colortext);
				if (remove(str.c_str()) != 0) {
					Tcolor(hConsole, 4);
					cout << "Error...";
				}
				else {
					cout << "Complete...";
				}
			}
			else {
				if (str == ".") {
					return;
				}
				else if (str == "..") {
					string tmp = address;
					int j = tmp.length() - 1;
					tmp[j] = '\0';
					str.clear();
					for (int i = tmp.find_last_of("\\") + 1; i < j; i++) {
						str.push_back(tmp[i]);
					}
					Back();
				}
				RemoveFoulder(address + str + '\\');
				if (_rmdir((address + str).c_str()) == -1) {
					Tcolor(hConsole, 4);
					cout << "Error...";
				}
				else {
					cout << "Complete...";
				}
			}
			break;
		}
		case 50:
			return;
		default:
			SetConsoleCursorPosition(hConsole, { 0, 0 });
			continue;
		}
		Sleep(500);
		break;
	}
}

bool File::RemoveFoulder(string address) {
	bool removeable = true;
	_finddata_t* fileinfo = new _finddata_t;
	long done = _findfirst((address + "*.").c_str(), fileinfo);
	int isReadable = done;
	string tmp;
	for (; isReadable != -1; isReadable = _findnext(done, fileinfo)) {
		tmp = fileinfo->name;
		if (tmp == "." || tmp == "..") {
			continue;
		}
		RemoveFoulder(address + tmp + '\\');
		if (_rmdir((address + tmp + '\\').c_str()) == -1) {
			removeable = false;
		}
	}
	_findclose(done);
	done = _findfirst((address + "*.*").c_str(), fileinfo);
	isReadable = done;
	for (; isReadable != -1; isReadable = _findnext(done, fileinfo)) {
		tmp = fileinfo->name;
		if (tmp == "." || tmp == "..") {
			continue;
		}
		if (remove((address + fileinfo->name).c_str()) != 0) {
			removeable = false;
		}
	}
	_findclose(done);
	delete fileinfo;
	return removeable;
}

void File::EnterAddress(bool def) {
	int i = 65;
	bool attempt = false;
	bool other = false;
	ofstream Ad;
	while (true) {
		string str;
		if (def) {
			if (other) {
				if (i == 67) { i++; }
				str = i;
				str.append(":\\");
				i++;
			}
			else {
				str = "C:\\";
			}
		}
		else {
			cout << "Введите адрес";
			if (attempt) {
				cout << " (C:\\): ";
			}
			else {
				cout << ": ";
			}
			Tcolor(hConsole, 10);
			structCursorInfo.bVisible = TRUE;
			SetConsoleCursorInfo(hConsole, &structCursorInfo);
			getline(cin, str);
			structCursorInfo.bVisible = FALSE;
			SetConsoleCursorInfo(hConsole, &structCursorInfo);
			if (!str.empty()) {
				if (str[str.length() - 1 != '\\']) { str.push_back('\\'); }
				else {
					for (int i = str.length() - 2; i >= 0; i = str.length() - 2) {
						if (str[i] == '\\') {
							str.pop_back();
							continue;
						}
						break;
					}
				}
			}
			if (str.length() >= 3) {
				Tcolor(hConsole, 4);
				if (str[1] != ':' && str[2] != '\\') {
					cout << "\nError, адрес не был найден...";
					Sleep(1000);
					break;
				}
			}
		}
		if (Check(-1, false, false, true, false, str) == "Error 1234567" || str.empty() || str.length() < 3) {
			other = true;
			attempt = true;
			Tcolor(hConsole, 4);
			if (!def) {
				cout << "\nError, адрес не был найден...";
				Sleep(1000);
				break;
			}
			continue;
		}
		address = str;
		Ad.open("Address.txt");
		Ad << str;
		Ad.close();
		break;
	}
}

bool File::Find(string path, string mask, string address) {
	if (mask.empty()) {
		return false;
	}
	else if (mask[0] != '*') {
		return false;
	}
	else if (mask.length() >= 2) {
		if (mask[1] != '.') { return false; }
	}
	cout << "Поиск..\n\n";
	bool found = false;
	string tmpmask;
	_finddata_t* fileinfo = new _finddata_t;
	long done = _findfirst((address + mask).c_str(), fileinfo);
	if (mask == "*.") {
		tmpmask = "";
	}
	else {
		for (int i = 1, j = mask.length(); i < j; i++) {
			tmpmask.push_back(mask[i]);
		}
	}
	int isReadable = done;
	while (isReadable != -1) {
		if (fileinfo->name == (path + tmpmask)) {
			cout << fileinfo->name << "\t" << address + path + tmpmask << endl;
			found = true;
		}
		isReadable = _findnext(done, fileinfo);
	}
	_findclose(done);
	done = _findfirst((address + "*.").c_str(), fileinfo);
	isReadable = done;
	string tmp;
	for (; isReadable != -1; isReadable = _findnext(done, fileinfo)) {
		tmp = fileinfo->name;
		if (tmp == "." || tmp == "..") {
			continue;
		}
		Find(path, mask, address + tmp + "\\");
	}
	_findclose(done);
	delete fileinfo;
	return found;
}

long long File::SizeFolder(string address) {
	long long size = 0;
	_finddata_t* fileinfo = new _finddata_t;
	long done = _findfirst((address + "*.*").c_str(), fileinfo);
	int isReadable = done;
	while (isReadable != -1) {
		size += fileinfo->size;
		isReadable = _findnext(done, fileinfo);
	}
	_findclose(done);
	done = _findfirst((address + "*.").c_str(), fileinfo);
	isReadable = done;
	string tmp;
	for (; isReadable != -1; isReadable = _findnext(done, fileinfo)) {
		tmp = fileinfo->name;
		if (tmp == "." || tmp == "..") {
			continue;
		}
		size += SizeFolder(address + tmp + '\\');
	}
	_findclose(done);
	delete fileinfo;
	return size;
}

bool File::CopyFolder(string startAd, string endAd) {
	bool copyable = true;
	_finddata_t* fileinfo = new _finddata_t;
	long done = _findfirst((startAd + "*.*").c_str(), fileinfo);
	int isReadable = done;
	string str;
	for (; isReadable != -1; isReadable = _findnext(done, fileinfo)) {
		str = fileinfo->name;
		if (fileinfo->attrib & _A_SUBDIR) {
			if (str == "." || str == "..") {
				continue;
			}
			else if (_mkdir((endAd + fileinfo->name).c_str()) != -1) {
				if (!(CopyFolder(startAd + fileinfo->name + '\\', endAd + fileinfo->name + '\\'))) {
					copyable = false;
				}
			}
			else {
				copyable = false;
			}
		}
		else {
			fs::path sourceFile = startAd + fileinfo->name;
			fs::path targetParent = endAd;
			auto target = targetParent / sourceFile.filename();
			try
			{
				fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
			}
			catch (...)
			{
				copyable = false;
			}
		}
	}
	_findclose(done);
	delete fileinfo;
	return copyable;
}

#pragma endregion