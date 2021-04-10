#pragma once
#include <string>

using std::string;

extern HANDLE hConsole; // Глобальная переменная для редактирования текста и координат курсора
extern CONSOLE_CURSOR_INFO structCursorInfo; // Глобальная переменная для включение и отключения видимости курсора

class File {
private:
	string address; // Адрес
	int maxcount; // Максимальное количество файлов/папок в папке

	/*Ограничения названия в режиме красивого интерфейса*/
	void Output(string str);
public:
	int colortext; // Номер выделенного файла

	/*Конструктор*/
	File(string _address);
	/*Получить адрес*/
	string GetAddress();
	/*Получить максимальное количество файлов и папок*/
	int GetMaxcount();
	/*Вывод на консоль названий папок\файлов по адресу. Получение название папки\файла по номеру расположения. Проверка адреса на действительность.
	Проверка на наличие папки по номеру расположения*/
	string Check(int num = 0, bool dir = false, bool position = false, bool checkaddress = false, bool shortened = false, string _address = "");
	/*Смена адреса на выбранную папку*/
	int Enter(int num);
	/*Смена адреса на предыдущую папку*/
	int Back();
	/*Смена имени у папки\файла*/
	void Rename();
	/*Создание папки\файла*/
	void New();
	/*Проверка на удаление папки\файла. Удаление файла*/
	void Remove();
	/*Удаление папки и ее содержимого*/
	bool RemoveFoulder(string address);
	/*Смена адреса на дефолтный. Смена и проверка адреса введенного пользователем*/
	void EnterAddress(bool def);
	/*Поиск по маске в папках*/
	bool Find(string path, string mask, string address);
	/*Высчитывание размера папки*/
	long long SizeFolder(string address);
	/*Копирование папки и ее содержимого*/
	bool CopyFolder(string startAd, string endAd);
	/*Деструктор*/
	~File();
};