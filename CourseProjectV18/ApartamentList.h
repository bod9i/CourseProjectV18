#pragma once

#include "List.h"

using namespace std;

namespace list
{
	typedef struct addressHouse
	{
		string* street;
		int houseNumber;
		char optional = '�';
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

	class ApartmentList : public List<Apartment>
	{
		public:
			ApartmentList* sort(SortingField field);
			ApartmentList* getOlderThanYear();
			ApartmentList* getLessOrEqualThanFloor(int floor);
			ApartmentList* getLessOrEqualThanArea(double area);
			ApartmentList* searchByStreet(string street);

			int getCountByRoomCount(int count);
	};

	int ApartmentList::getCountByRoomCount(int count)
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

	ApartmentList* ApartmentList::searchByStreet(string street)
	{
		ApartmentList* result = new ApartmentList();
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

	ApartmentList* ApartmentList::getLessOrEqualThanArea(double area)
	{
		ApartmentList* result = new ApartmentList();
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

	ApartmentList* ApartmentList::getLessOrEqualThanFloor(int floor)
	{
		ApartmentList* result = new ApartmentList();
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

	ApartmentList* ApartmentList::getOlderThanYear()
	{
		ApartmentList* result = new ApartmentList();
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

	ApartmentList* ApartmentList::sort(SortingField field)
	{
		auto result = new ApartmentList(*this);

		Node* temp = new Node(); 

		switch (field)
		{
			case COUNT_ROOMS:
				for (int i = 0; i < size - 1; i++)
				{
					for (int j = 0; j < size - i - 1; j++)
					{
						auto current = result->find(j);

						if (current->next == NULL)
						{
							return NULL;
						}

						auto next = result->find(j + 1);

						if (current->data->countRooms > next->data->countRooms)
						{
							temp->data = current->data;
							current->data = next->data;
							next->data = temp->data;
						}
					}
				}

				break;
			case AREA:

				for (int i = 0; i < size - 1; i++)
				{
					for (int j = 0; j < size - i - 1; j++)
					{
						auto current = result->find(j);

						if (current->next == NULL)
						{
							return NULL;
						}

						auto next = result->find(j + 1);

						if (current->data->area > next->data->area)
						{
							temp->data = current->data;
							current->data = next->data;
							next->data = temp->data;
						}
					}
				}
				break;
		}

		return result;
	}
}