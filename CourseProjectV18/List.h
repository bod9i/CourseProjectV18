#pragma once

#include <iostream>
#include "List.h"

using namespace std;

namespace list 
{
	template <typename T>
	class List
	{
		protected:
			struct Node {
				Node* next;
				T* data;
			};
			Node* head;
			int size;

		public:
			//constructer
			List();
			List(const List& aList); //copy constructer for deep copy
			List(T* item);

			//destructor
			~List();

			//operations
			bool isEmpty();
			int getLength();
			virtual void add(int index, T* data);
			void remove(int index);
			virtual void update(int index, T* data);
			T* get(int index);
			List<T>* clone() const;
			Node* find(int index);
			T* operator[] (int index);
	};

	template <typename T>
	List<T>::~List()
	{
		while (!isEmpty())
			remove(0);
	}

	template <typename T>
	List<T>::List()
	{
		size = 0;
		head = NULL;
	}

	template <typename T>
	List<T>::List(T* item)
	{
		head = new Node();
		head->data = item;

		size = 0;
		
		for (Node* cur = head; cur != NULL; cur = cur->next)
		{
			// cout << cur -> data << endl;
			size++;
		}
	}

	template <typename T>
	List<T>::List(const List& aList)
	{
		size = aList.size;

		head = new Node;
		head->data = aList.head->data;
		Node* cur = head;

		for (Node* cp_node = aList.head->next; cp_node != NULL; cp_node = cp_node->next)
		{
			cur->next = new Node;
			cur = cur->next;
			cur->data = cp_node->data;
		}

		cur->next = NULL;
	}

	template <typename T>
	void List<T>::add(int index, T* data)
	{
		if (index < 0)
		{
			cout << "Некорректный индекс" << endl;
			return;
		}
		if (index > size)
		{
			cout << "Некорректный индекс" << endl;
			return;
		}
		//if insert head
		if (index == 0)
		{
			Node* new_head = new Node;
			new_head->next = head;
			new_head->data = data;
			head = new_head;
		}//if insert into middle
		else
		{
			Node* prev = find(index - 1);
			Node* node = new Node;
			node->data = data;
			node->next = prev->next;
			prev->next = node;
		}
		size++;
	}

	template <typename T>
	void List<T>::remove(int index) {
		if (size == 0)
		{
			cout << "Список пуст" << endl;
			return;
		}
		else if (index >= size || index < 0)
		{
			cout << "Некорректный индекс" << endl;
			return;
		}

		Node* cur;
		//if head ptr
		if (index == 0)
		{
			cur = head;
			head = head->next;
		}
		else
		{
			Node* prev = find(index - 1);
			cur = prev->next;
			prev->next = cur->next;
		}
		cur->next = NULL;

		delete cur->data;
		delete cur;

		cur = NULL;
		size--;
	}

	template<typename T>
	void List<T>::update(int index, T* data)
	{
		Node* item = find(index);

		if (item == NULL)
		{
			cout << "Элемент с таким id не найден" << endl;
			return;
		}

		delete item->data;
		item->data = data;
	}

	template<typename T>
	List<T>* List<T>::clone() const
	{
		return new List<T>(*this);
	}

	template <typename T>
	T* List<T>::get(int index)
	{
		if (index >= size || index < 0)
		{
			cout << "Некорректный  индекс" << endl;
			return NULL;
		}
		Node* ptr = find(index);

		return ptr != NULL ? ptr->data : NULL;
	}

	template <typename T>
	typename List<T>::Node* List<T>::find(int index)
	{
		Node* cur = head;

		if (index > size) return NULL;

		for (int i = 0; i < index; i++)
		{
			cur = cur->next;
		}

		return cur;
	}

	template <typename T>
	bool List<T>::isEmpty()
	{
		return (size == 0) ? true : false;
	}

	template <typename T>
	int List<T>::getLength()
	{
		return size;
	}

	template <typename T>
	T* List<T>::operator[](int index)
	{
		return get(index);
	}
}