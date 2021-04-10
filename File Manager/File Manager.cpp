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

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;

void main() {                               //////////////////////////////////////////////////////////////////////////////////////////////////
	setlocale(LC_ALL, "");
	system("color 05");
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = FALSE; // Отключение видимости курсора
	SetConsoleCursorInfo(hConsole, &structCursorInfo); // Установка параметров курсора

	COORD nullpos = { 0,0 };
	Tcolor(hConsole, 15);

	File* file;
	int write, num = 0;
	/*Показ подсказки, повторный Check, перезапуск программы, наличие копии, наличии вырезки, копирование\вырезка файла, укороченый показ*/
	bool help = false, checkwork = true, restart = false, copy = false, cut = false, foldorfile = false, shortened = true;
	/*Адрес коируемого файла, имя копируемого файла*/
	string copybegin, copyname;
	ifstream takeAddress;
	while (true) {
		takeAddress.open("Address.txt");
		if (takeAddress.is_open()) {
			string address;
			getline(takeAddress, address);
			file = new File{ address };
			takeAddress.close();
			if (file->Check(0, false, false, true) == "Error 1234567" || address.empty()) {
				file->EnterAddress(true);
				continue;
			}
		}
		else {
			takeAddress.close();
			ofstream GiveAddress("Address.txt");
			GiveAddress << "C:\\";
			file = new File{ "C:\\" };
			GiveAddress.close();
		}
		while (true) {
			Tcolor(hConsole, 15);
			if (num == 0) {
				SetConsoleCursorPosition(hConsole, nullpos);
				cout << file->GetAddress() << endl << endl;
				Tcolor(hConsole, 3);
				if (help) {
					/*Подсказка*/
					cout << "Переместить указатель вверх\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '8'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nПереместить указатель вниз\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '2'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nОткрыть папку\t\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "Enter, 6"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВернуться к предыдущей папке\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "Backspace, 4"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nДобавить новую папку\\файл\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '+'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nУдалить папку\\файл\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '-'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nПереименовать папку\\файл\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '/'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nУзнать размер папки\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "Tab"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nСкопировать папку\\файл\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '('; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВырезать папку\\файл\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << ')'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВставить с заменой папку\\файл\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '='; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nНайти по маске папку\\файл\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '.'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВвести свой адрес\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '5'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nПерезапустить программу\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "Del"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nОбновить\t\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << '0'; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВыход из программы\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "Esc"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nВкл\\выкл режим сокращений\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << "*"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 3);
					cout << "\nСкрыть подсказку\t\t"; Tcolor(hConsole, 15); cout << '"'; Tcolor(hConsole, 2); cout << ':'; Tcolor(hConsole, 15); cout << '"';
				}
				else {
					cout << "Открыть подсказку \":\"";
				}
				Tcolor(hConsole, 15);
			}
			if (checkwork) {
				/*Показ названий папок*/
				file->Check(num, false, help, false, shortened);
			}
			else { checkwork = true; }
			write = _getch();
			switch (write) {
			case 56: // '8'
				if (file->colortext > 1) {
					file->colortext--;
				}
				num = -2;
				break;
			case 50: // '2'
				if (file->colortext < file->GetMaxcount()) {
					file->colortext++;
				}
				num = -1;
				break;
			case 13: // 'Enter'
			case 54: // '6'
				num = file->Enter(file->colortext);
				break;
			case 8: // 'Backspace'
			case 52: // '4'
				num = file->Back();
				break;
			case 47: // '/'
				file->Rename();
				num = 0;
				file->colortext = 1;
				system("cls");
				break;
			case 43: // '+'
				file->New();
				num = 0;
				file->colortext = 1;
				system("cls");
				break;
			case 48: // '0'
				num = 0;
				system("cls");
				break;
			case 58: // ':'
				num = 0;
				help = !help;
				system("cls");
				break;
			case 45: // '-'
				file->Remove();
				num = 0;
				file->colortext = 1;
				system("cls");
				break;
			case 53: // '5'
				system("cls");
				file->EnterAddress(false);
				num = 0;
				file->colortext = 1;
				system("cls");
				break;
			case 46: // '.'
			{
				system("cls");
				string path;
				string mask;
				cout << "Введите название файла: \n";
				cout << "Введите маску: ";
				SetConsoleCursorPosition(hConsole, { 24, 0 });
				structCursorInfo.bVisible = TRUE;
				SetConsoleCursorInfo(hConsole, &structCursorInfo);
				getline(cin, path);
				SetConsoleCursorPosition(hConsole, { 15, 1 });
				getline(cin, mask);
				structCursorInfo.bVisible = FALSE;
				SetConsoleCursorInfo(hConsole, &structCursorInfo);
				cout << endl;
				if (file->Find(path, mask, file->GetAddress())) {
					cout << "\n Хотите перейти по адресу к папке?"
						<< "\n1 Да"
						<< "\n  Нет\n";
					write = _getch();
					if (write == 49) { file->EnterAddress(false); }
				}
				else {
					Tcolor(hConsole, 4);
					cout << "Error, not found..";
					Sleep(500);
				}
				system("cls");
				num = 0;
				break;
			}
			case 9: // 'Tab'
			{
				system("cls");
				string str = file->Check(file->colortext, true);
				if (str.empty() || str == ".") {
					Tcolor(hConsole, 4);
					cout << "Папка не найдена";
					Sleep(1000);
					system("cls");
					num = 0;
					break;
				}
				else if (str == "..") {
					string tmp = file->GetAddress();
					int j = tmp.length() - 1;
					tmp[j] = '\0';
					str.clear();
					for (int i = tmp.find_last_of("\\") + 1; i < j; i++) {
						str.push_back(tmp[i]);
					}
					file->Back();
				}
				cout << "Размер папки " << str << " равен = " << file->SizeFolder(file->GetAddress() + str + '\\') << " байтов";
				cout << "\n\nНажмите что-нибудь, чтобы продолжить...";
				write = _getch();
				system("cls");
				num = 0;
				break;
			}
			case 41: // cut ')'
			case 40: // copy '('
				Tcolor(hConsole, 3);
				copyname = file->Check(file->colortext);
				if (copyname == ".") {
					break;
				}
				else if (copyname == "..") {
					string tmp = file->GetAddress();
					int j = tmp.length() - 1;
					tmp[j] = '\0';
					copyname.clear();
					for (int i = tmp.find_last_of("\\") + 1; i < j; i++) {
						copyname.push_back(tmp[i]);
					}
					file->Back();
				}
				copybegin = file->GetAddress() + copyname + '\\';
				if (file->Check(file->colortext, true).empty()) {
					foldorfile = false;
				}
				else {
					foldorfile = true;
				}
				system("cls");
				cout << copyname;
				if (write == 40) {
					copy = true;
					cut = false;
					cout << " скопирован...";
				}
				else {
					cut = true;
					copy = false;
					cout << " вырезан...";
				}
				Sleep(500);
				system("cls");
				num = 0;
				break;
			case 61: // '='
				if (copy || cut) {
					system("cls");
					Tcolor(hConsole, 10);
					if (foldorfile) {
						if (_mkdir((file->GetAddress() + copyname).c_str()) == -1) {
							Tcolor(hConsole, 4);
							cout << "Error...";
						}
						else {
							if (file->CopyFolder(copybegin, file->GetAddress() + copyname + '\\')) {
								if (cut) {
									if (file->RemoveFoulder(copybegin)) {
										copybegin.pop_back();
										if (_rmdir(copybegin.c_str()) == -1) {
											Tcolor(hConsole, 4);
											cout << "Error...";
										}
										else {
											cout << "Complete...";
										}
									}
									else {
										Tcolor(hConsole, 4);
										cout << "Error...";
									}
								}
								else {
									cout << "Complete...";
								}
							}
						}
					}
					else {
						copybegin.pop_back();
						fs::path sourceFile = copybegin;
						fs::path targetParent = file->GetAddress();
						auto target = targetParent / sourceFile.filename();
						try // If you want to avoid exception handling, then use the error code overload of the following functions.
						{
							fs::copy_file(sourceFile, target, fs::copy_options::overwrite_existing);
							if (cut) {
								if (remove(copybegin.c_str()) != 0) {
									Tcolor(hConsole, 4);
									cout << "Error..";
								}
								else {
									cout << "Complete";
								}
							}
							else {
								cout << "Complete...";
							}
						}
						catch (...) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
						{
							Tcolor(hConsole, 4);
							cout << "Error...";
						}
					}
					copy = false;
					cut = false;
					num = 0;
					Sleep(500);
					system("cls");
				}
				break;
			case 42: // '*'
				shortened = !shortened;
				num = 0;
				system("cls");
				break;
			case 224: // 'Del'
				num = 0;
				restart = true;
				system("cls");
				break;
			case 27: // 'Esc'
				system("cls");
				cout << "Спасибо за использование данного проводника :)";
				Sleep(1000);
				return;
			default:
				checkwork = false;
			}
			if (restart) { break; }
		}
		if (restart) { restart = false; continue; }
	}
}