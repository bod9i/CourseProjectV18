#pragma once

#include "List.h"

using namespace std;

namespace list
{
	typedef struct addressHouse
	{
		string* street;
		int houseNumber;
		char optional = 'æ';
	} AddressHouse;

	typedef tm DateTime;
	typedef struct apartment
	{
		int countRooms = 0;
		double area = 0;
		int floor = -1;
		DateTime* createdOn;
		AddressHouse* address;

		~apartment()
		{
			delete createdOn;
			delete address;
		}

		apartment()
		{
			address = new AddressHouse();
			createdOn = new DateTime();
		}
	} Apartment;

	enum SortingField
	{
		COUNT_ROOMS = 10,
		AREA = 20
	};

	class ApartamentList : public List<Apartment>
	{
		public:
			ApartamentList* sort(SortingField field);
			ApartamentList* getOlderThanYear();
			ApartamentList* getLessOrEqualThanFloor(int floor);
			ApartamentList* getLessOrEqualThanArea(double area);
			ApartamentList* searchByStreet(string street);

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

	ApartamentList* ApartamentList::searchByStreet(string street)
	{
		ApartamentList* result = new ApartamentList();
		int j = 0;

		for (int i = 0; i < size; i++)
		{
			auto temp = get(i);
			
			if (*temp->address->street == street)
			{
				result->add(j++, temp);
			}
		}

		return result;
	}

	ApartamentList* ApartamentList::getLessOrEqualThanArea(double area)
	{
		ApartamentList* result = new ApartamentList();
		int j = 0;

		for (int i = 0; i < size; i++)
		{
			auto temp = get(i);

			if (temp->area <= area)
			{
				result->add(j++, temp);
			}
		}

		return result;
	}

	ApartamentList* ApartamentList::getLessOrEqualThanFloor(int floor)
	{
		ApartamentList* result = new ApartamentList();
		int j = 0;

		for (int i = 0; i < size; i++)
		{
			auto temp = get(i);

			if (temp->floor <= floor)
			{
				result->add(j++, temp);
			}
		}

		return result;
	}

	ApartamentList* ApartamentList::getOlderThanYear()
	{
		ApartamentList* result = new ApartamentList();
		int j = 0;

		for (int i = 0; i < size; i++)
		{
			auto nado = time(0);
			auto temp = get(i);
			auto localTime = localtime(&nado);

			if (temp->createdOn->tm_year < localTime->tm_year)
			{
				result->add(j++, temp);
			}
		}

		return result;
	}
}