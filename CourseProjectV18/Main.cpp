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

	some1->countRooms = 5;
	some2->countRooms = 3;
	some3->countRooms = 5;

	some1->area = 5.2;
	some2->area = 7;
	some3->area = 5.2;

	some1->address->street = new string("abc");
	some2->address->street = new string("abc");
	some3->address->street = new string("abs");

	ApartamentList* list = new ApartamentList();
	
	list->add(0, some1);
	list->add(1, some2);
	list->add(2, some3);

	int nado = list->getCountByRoomCount(5);

	auto nado1 = list->searchByStreet("abc");
	auto nado2 = list->getLessOrEqualThanArea(5.2);

	return 0;
}