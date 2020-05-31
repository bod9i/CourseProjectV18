#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include "ApartamentList.h"
#include <Windows.h>
#include <sstream> 

using namespace std;
using namespace list;

bool IsDigit(string item)
{
	bool result = true;
	for (int i = 0; i < item.size(); i++)
	{
		switch (item[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				continue;
			default:
				return false;
		}
	}

	return true;
}

Apartment* initializeItem()
{
	string temp = "";
	Apartment* apart = new Apartment();
	DateTime* date;
	//AddressHouse* address = new AddressHouse();

	while (true)
	{
		cout << endl << "Введите число комнат: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->countRooms;
			break;
		}

		cout << endl << "Введенное значение не является числом!" << endl << endl;
	}

	while (true)
	{
		cout << endl << "Введите площадь: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->area;
			break;
		}

		cout << endl << "Введенное значение не является числом!" << endl << endl;;
	}

	while (true)
	{
		cout << endl << "Введите этаж: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->floor;
			break;
		}

		cout << endl << "Введенное значение не является числом!" << endl << endl;
	}

	cout << endl << "Введите улицу: ";
	cin >> apart->address->street;

	while (true)
	{
		cout << endl << "Введите номер дома: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->address->houseNumber;
			break;
		}

		cout << endl << "Введенное значение не является числом!" << endl << endl;
	}

	cout << endl << "Введите номер дома: ";
	cin >> apart->address->houseNumber;

	cout << endl << "Введите букву дома (не обязательно): ";
	cin >> apart->address->optional;

	auto nado = time(0);
	date = new DateTime(*localtime(&nado));

	delete apart->createdOn;
	apart->createdOn = date;

	apart->createdOn->tm_year += 1900; // спросите у индуса, который написал эту функцию (localtime(*time_t)), какого это нужно делать

	return apart;
}

void print(ApartmentList* list)
{
	cout << " Id\tКомнат\tПлощадь\tЭтаж\tДата создания записи\tАдрес дома" << endl;
 
 	for (int i = 0; i < list->getLength(); i++)
	{
		auto item = list->get(i);
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "  " << item->id << "\t   " << item->countRooms << "\t  " << item->area << "\t " << item->floor << "\t    " << item->createdOn->tm_mday << "." << item->createdOn->tm_mon + 1 << "." << item->createdOn->tm_year << "\t\t" << item->address->street << item->address->houseNumber << item->address->optional << endl;
	}
	cout << "--------------------------------------------------------------------------" << endl << endl;
}

void CLI(ApartmentList* list)
{
	cout << "Для показа возможных операций, введите 'help'" << endl << endl;
	while (true)
	{
		string command;

		cout << "C:\>";
		cin >> command;
		cout << endl;

		if (command == "help")
		{
			cout << "add => добавление єлемента" << endl;
			cout << "update => обновление єлемента" << endl;
			cout << "remove => удаление єлемента" << endl;
			cout << "sort => сортировка элементов по одному из двух, доступных для сортировки полей" << endl;
			cout << "olderYear => получить элементы, которые были созданы в прошлом году" << endl;
			cout << "lessThanFloor => получить элементы, у которых этаж меньше либо равны указаному этажу" << endl;
			cout << "lessThanArea => получить элементы, у которых площадь меньше либо равны указаной площади" << endl;
			cout << "searchByStreet => получить элементы, чье название улицы совпадает с указаным" << endl;
			cout << "countByCountRooms => получить количевство квартир, с указанной кол-вом комнат" << endl;
			cout << "print => получить элементы в исходном порядке" << endl << endl;

			continue;
		}
		else if (command == "add")
		{
			int index = list->getLength();

			list->add(index, initializeItem());

			system("cls");
		}
		else if (command == "update")
		{
			int index;

			cout << "Введите индекс элемента, который хотите обновить: ";
			cin >> index;

			list->update(index, initializeItem());

			system("cls");
		}
		else if (command == "remove")
		{
			int index;

			cout << "Введите индекс элемента, который хотите удалить: ";
			cin >> index;

			list->remove(index);

			system("cls");
		}
		else if (command == "sort")
		{
			cout << "1. По числу комнат" << endl;
			cout << "2. По площади" << endl << endl;

			int choose;
			cout << "Выберите, по какому полю отсоритровать: ";
			cin >> choose;

			system("cls");
			print(list->sort(choose == 1 ? COUNT_ROOMS : AREA));

			continue;
		}
		else if (command == "olderYear")
		{
			system("cls");

			print(list->getOlderThanYear());
			continue;
		}
		else if (command == "lessThanFloor")
		{
			int floor;

			cout << "Введите этаж: ";
			cin >> floor;

			system("cls");

			print(list->getLessOrEqualThanFloor(floor));
			continue;
		}
		else if (command == "lessThanArea")
		{
			double area;

			cout << "Введите площадь: ";
			cin >> area;

			system("cls");

			print(list->getLessOrEqualThanArea(area));
			continue;
		}
		else if (command == "searchByStreet")
		{
			string street;
			
			cout << "Введите улицу: ";	
			cin >> street;

			system("cls");

			print(list->searchByStreet(street));
			continue;
		}
		else if (command == "countByCountRooms")
		{
			int count;
			cout << "Введите кол-во комнат: ";
			cin >> count;

			cout << "Кол-во квартир с указанным количевством комнат: " << list->getCountByRoomCount(count) << endl << endl;
			system("pause");
			system("cls");
		}
		else if (command == "print") 
		{ 
			system("cls"); 
		}
		else 
		{ 
			cout << "Неверно введённая команда" << endl << endl;
			continue;
		}

		print(list);
	}
}

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);

	auto some1 = new Apartment();
	auto some2 = new Apartment();
	auto some3 = new Apartment();

	some1->countRooms = 3;
	some2->countRooms = 1;
	some3->countRooms = 2;

	some1->area = 52;
	some2->area = 26;
	some3->area = 46;

	some1->floor = 1;
	some2->floor = 8;
	some3->floor = 4;

	some1->address = new AddressHouse();
	some2->address = new AddressHouse();
	some3->address = new AddressHouse();

	some1->address->street = "Королёва";
	some2->address->street = "Варненская";
	some3->address->street = "Шклярука";

	some1->address->houseNumber = 78;
	some2->address->houseNumber = 11;
	some3->address->houseNumber = 56;

	some1->address->optional = "A";
	some3->address->optional = "Б";

	DateTime* someDate1 = new DateTime();

	someDate1->tm_year = 2019;
	someDate1->tm_mon = 4;
	someDate1->tm_mday = 21;

	DateTime* someDate2 = new DateTime();

	someDate2->tm_year = 2020;
	someDate2->tm_mon = 4;
	someDate2->tm_mday = 21;

	DateTime* someDate3 = new DateTime();

	someDate3->tm_year = 2020;
	someDate3->tm_mon = 4;
	someDate3->tm_mday = 21;

	some1->createdOn = someDate1;
	some2->createdOn = someDate2;
	some3->createdOn = someDate3;

	ApartmentList* list = new ApartmentList();
	
	list->ApartmentList::add(0, some1);
	list->ApartmentList::add(1, some2);
	list->ApartmentList::add(2, some3);

	print(list);
	CLI(list);
		
	return 0;
}