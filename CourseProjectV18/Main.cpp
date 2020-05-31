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
		cout << endl << "������� ����� ������: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->countRooms;
			break;
		}

		cout << endl << "��������� �������� �� �������� ������!" << endl;
	}

	while (true)
	{
		cout << endl << "������� �������: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->area;
			break;
		}

		cout << endl << "��������� �������� �� �������� ������!" << endl;;
	}

	while (true)
	{
		cout << endl << "������� ����: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->floor;
			break;
		}

		cout << endl << "��������� �������� �� �������� ������!" << endl;
	}

	cout << endl << "������� �����: ";
	cin >> apart->address->street;

	while (true)
	{
		cout << endl << "������� ����� ����: ";
		cin >> temp;

		if (IsDigit(temp))
		{
			stringstream geek(temp);
			geek >> apart->address->houseNumber;
			break;
		}

		cout << endl << "��������� �������� �� �������� ������!" << endl;
	}

	cout << endl << "������� ����� ���� (�� �����������): ";
	cin >> apart->address->optional;

	cin.clear();

	auto nado = time(0);
	date = new DateTime(*localtime(&nado));

	delete apart->createdOn;
	apart->createdOn = date;

	apart->createdOn->tm_year += 1900; // �������� � ������, ������� ������� ��� ������� (localtime(*time_t)), ������ ��� ����� ������

	return apart;
}

void print(ApartmentList* list)
{
	cout << " Id\t������\t�������\t����\t���� �������� ������\t����� ����" << endl;
 
 	for (int i = 0; i < list->getLength(); i++)
	{
		auto item = list->get(i);
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "  " << item->id << "\t   " << item->countRooms << "\t  " << item->area << "\t " << item->floor << "\t    " << item->createdOn->tm_mday << "." << item->createdOn->tm_mon + 1 << "." << item->createdOn->tm_year << "\t\t" << item->address->street + " " << item->address->houseNumber << item->address->optional << endl;
	}
	cout << "--------------------------------------------------------------------------" << endl << endl;
}

void cli(ApartmentList* list)
{
	string command;
	cout << "��� ������ ��������� ��������, ������� 'help'" << endl << endl;
	while (true)
	{ 
		cin.clear();
		cout << "C:\>";
		cin >> command;
		cout << endl;

		if (command == "help")
		{
			cout << "add => ���������� ��������" << endl;
			cout << "update => ���������� ��������" << endl;
			cout << "remove => �������� ��������" << endl;
			cout << "sort => ���������� ��������� �� ������ �� ����, ��������� ��� ���������� �����" << endl;
			cout << "olderYear => �������� ��������, ������� ���� ������� � ������� ����" << endl;
			cout << "lessThanFloor => �������� ��������, � ������� ���� ������ ���� ����� ��������� �����" << endl;
			cout << "lessThanArea => �������� ��������, � ������� ������� ������ ���� ����� �������� �������" << endl;
			cout << "searchByStreet => �������� ��������, ��� �������� ����� ��������� � ��������" << endl;
			cout << "countByCountRooms => �������� ����������� �������, � ��������� ���-��� ������" << endl;
			cout << "print => �������� �������� � �������� �������" << endl << endl;

			cin.clear();

			continue;
		}
		else if (command == "add")
		{
			int index = list->getLength();

			list->add(index, initializeItem());
			
			cin.clear();
			system("cls");
		}
		else if (command == "update")
		{
			int index;

			cout << "������� ������ ��������, ������� ������ ��������: ";
			cin >> index;

			list->update(index, initializeItem());

			cin.clear();
			system("cls");
		}
		else if (command == "remove")
		{
			int index;

			cout << "������� ������ ��������, ������� ������ �������: ";
			cin >> index;

			list->remove(index);

			cin.clear();
			system("cls");
		}
		else if (command == "sort")
		{
			cout << "1. �� ����� ������" << endl;
			cout << "2. �� �������" << endl << endl;

			int choose;
			cout << "��������, �� ������ ���� �������������: ";
			cin >> choose;

			cin.clear();
			system("cls");
			print(list->sort(choose == 1 ? COUNT_ROOMS : AREA));

			continue;
		}
		else if (command == "olderYear")
		{
			system("cls");

			cin.clear();
			print(list->getOlderThanYear());
			continue;
		}
		else if (command == "lessThanFloor")
		{
			int floor;

			cout << "������� ����: ";
			cin >> floor;

			system("cls");

			cin.clear();
			print(list->getLessOrEqualThanFloor(floor));
			continue;
		}
		else if (command == "lessThanArea")
		{
			double area;

			cout << "������� �������: ";
			cin >> area;

			system("cls");

			cin.clear();
			print(list->getLessOrEqualThanArea(area));
			continue;
		}
		else if (command == "searchByStreet")
		{
			string street;
			
			cout << "������� �����: ";	
			cin >> street;

			system("cls");

			cin.clear();
			print(list->searchByStreet(street));
			continue;
		}
		else if (command == "countByCountRooms")
		{
			int count;
			cout << "������� ���-�� ������: ";
			cin >> count;

			cin.clear();
			cout << "���-�� ������� � ��������� ������������ ������: " << list->getCountByRoomCount(count) << endl << endl;
			system("pause");
			system("cls");
		}
		else if (command == "print") 
		{ 
			cin.clear();
			system("cls"); 
		}
		else 
		{ 
			cin.clear();
			cout << "������� �������� �������" << endl << endl;
			command = "";
			continue;
		}

		command = "";
		print(list);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SetConsoleTitle(TEXT("Apartment list"));

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

	some1->address = new ApartmentAddress();
	some2->address = new ApartmentAddress();
	some3->address = new ApartmentAddress();

	some1->address->street = "�������";
	some2->address->street = "����������";
	some3->address->street = "��������";

	some1->address->houseNumber = 78;
	some2->address->houseNumber = 11;
	some3->address->houseNumber = 56;

	some1->address->optional = "A";
	some3->address->optional = "�";

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
	cli(list);
		
	return 0;
}