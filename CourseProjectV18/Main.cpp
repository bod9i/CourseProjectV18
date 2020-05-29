#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <time.h>
#include "ApartamentList.h"

using namespace std;
using namespace list;

int main()
{
	auto some1 = new Apartment();
	auto some2 = new Apartment();
	auto some3 = new Apartment();

	some1->countRooms = 3;
	some2->countRooms = 1;
	some3->countRooms = 2;

	some1->area = 5.2;
	some2->area = 7;
	some3->area = 3.4;

	some1->address->street = new string("abc");
	some2->address->street = new string("abc");
	some3->address->street = new string("abs");

	ApartmentList* list = new ApartmentList();
	
	list->add(0, some1);
	list->add(1, some2);
	list->add(2, some3);

	int nado = list->getCountByRoomCount(5);

	auto nado1 = list->searchByStreet("abc");
	auto nado2 = list->getLessOrEqualThanArea(5.2);

	auto sortingByArea = list->sort(AREA);
	auto sortingByCountRooms = list->sort(COUNT_ROOMS);

	return 0;
}