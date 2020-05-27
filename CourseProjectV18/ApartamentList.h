#pragma once

#include "List.h"

using namespace std;

namespace list
{
	typedef tm DateTime;
	typedef struct
	{
		int countRooms = 0;
		double area = 0;
		int floor = -1;
		DateTime CreatedOn;
		//AddressHouse addres;
	} Apartment;

	typedef struct
	{
		string street;
		int houseNumber = 0;
		char optional = 'æ';
	} AddressHouse;

	enum SortingField
	{
		COUNT_ROOMS = 10,
		AREA = 20
	};

	class ApartamentList : List<Apartment>
	{
		public:
			ApartamentList sort(SortingField field);
			ApartamentList getOlderThanYear();
			ApartamentList getLessOrEqualThanFloor(int floor);
			ApartamentList getLessOrEqualThanArea(double area);
			ApartamentList searchByStreet(string street);

			int getCountByRoomCount(int count);
	};

	int ApartamentList::getCountByRoomCount(int count)
	{
		int x = 0;
		for (int i = 0; i < size; i++)
		{
			if (get(i)->countRooms == count)
			{
				x++;
			}
		}

		return x;
	}
}