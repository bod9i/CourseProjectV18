#pragma once

#include <iostream>
#include "List.h"

using namespace std;

#ifdef USE_EXPORT_KEYWORD
export
#endif

template <typename T>
class List {

private:
	struct Node {
		Node* next;
		T data;
	};

public:
	//constructer
	List();
	List(const List& aList); //copy constructer for deep copy
	List(Node* head);

	//destructor
	~List();

	//operations
	bool isEmpty();
	int getLength();
	void add(int index, T data);
	void remove(int index);
	void update(int index, T data);
	T get(int index);
	void removeNode(Node* node);
	List<T>* clone() const;
	Node* find(int index);
	T operator[] (int index);

private:
	int size;
	Node* head;
};

template <typename T>
List<T>::~List() {
	while (!isEmpty())
		remove(0);
}

template <typename T>
List<T>::List() {
	size = 0;
	head = NULL;
}

template <typename T>
List<T>::List(Node* aHead) {
	size = 0;
	head = aHead;
	for (Node* cur = head; cur != NULL; cur = cur->next) {
		// cout << cur -> data << endl;
		size++;
	}
}

template <typename T>
List<T>::List(const List& aList) {
	size = aList.size;

	head = new Node;
	head->data = aList.head->data;
	Node* cur = head;

	for (Node* cp_node = aList.head->next; cp_node != NULL; cp_node = cp_node->next) {
		cur->next = new Node;
		cur = cur->next;
		cur->data = cp_node->data;
	}

	cur->next = NULL;
}

template <typename T>
void List<T>::add(int index, T data) {
	if (index < 0) {
		cout << "Negative index" << endl;
		return;
	}
	if (index > size) {
		cout << "Extension is not supported" << endl;
		return;
	}
	//if insert head
	if (index == 0) {
		Node* new_head = new Node;
		new_head->next = NULL;
		new_head->data = data;
		head = new_head;
	}//if insert into middle
	else {
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
	if (size == 0) {
		cout << "No item to remove in list!!" << endl;
		return;
	}
	else if (index >= size || index < 0) {
		cout << "No item with given index!!" << endl;
		return;
	}

	Node* cur;
	//if head ptr
	if (index == 0) {
		cur = head;
		head = head->next;
	}
	else {
		Node* prev = find(index - 1);
		cur = prev->next;
		prev->next = cur->next;
	}
	cur->next = NULL;
	delete cur;
	cur = NULL;
	size--;
}

template<typename T>
void List<T>::update(int index, T data) {
	Node* item = find(index);

	if (item == NULL) {
		cout << "Not found item with this index" << endl;
		return;
	}

	item->data = data;
}
/*
	REMOVE GIVEN NODE FROM THE LIST
*/
template <typename T>
void List<T>::removeNode(Node* node) {
	if (size == 0) {
		cout << "List is empty!!" << endl;
		return;
	}
	if (node->next == NULL) { // if node is the tail
		remove(getLength() - 1);
	}
	else {
		Node* next_node = node->next;
		node->data = next_node->data;
		// remove next_node
		node->next = next_node->next;
		next_node->next = NULL;
		delete next_node;
		next_node = NULL;
	}
	size--;
}

template<typename T>
List<T>* List<T>::clone() const
{
	return new List<T>(*this);
}

template <typename T>
T List<T>::get(int index) {
	if (index > size || index < 0) {
		cout << "Wrong index value!!!" << endl;
		return NULL;
	}
	Node* ptr = find(index);

	return ptr != NULL ? ptr->data : NULL;
}

template <typename T>
typename List<T>::Node* List<T>::find(int index) {
	Node* cur = head;

	if (index > size) return NULL;

	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}
	return cur;
}

template <typename T>
bool List<T>::isEmpty() {
	return (size == 0) ? true : false;
}

template <typename T>
int List<T>::getLength() {
	return size;
}

template <typename T>
T List<T>::operator[](int index) {
	return get(index);
}