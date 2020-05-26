#include <iostream>
#include <stdlib.h>	/* srand, rand */
#include <map>

using namespace std;
template <typename T>

#pragma region Implementation
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
	T get(int index);
	T extract(int index); /*get the value and remove the node */
	void printList();
	void removeDuplicates();
	void randomIntFill(int item_num, int max);
	void removeNode(Node* node);
	Node* find(int index);
	Node* sumDigitsWithCarry(Node* head1, Node* head2); // given two list of digits sum those lists
							   // like they are natural numbers with given 1o's order
							   // 9 -> 5 + 9 -> 4 = 8 -> 0 -> 1 = 108
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
		cout << "Negative index!!" << endl;
		return;
	}
	if (index > size) {
		cout << "Extension is not supported!!" << endl;
		return;
	}
	//if insert head
	if (index == 0) {
		Node* new_head = new Node;
		new_head->next = head;
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
T List<T> ::extract(int index) {
	if (index < 0 || index >= size) {
		cout << "Wrong index value !!!" << endl;
		return 0;
	}
	Node* node = find(index);
	T ret_data = node->data;
	remove(index);
	node = NULL;
	return ret_data;
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

/*
REMOVE DUPLICATE ENTRIES INPLACE
*/
template <typename T>
void List<T> ::removeDuplicates() {
	if (size < 2)
		return;

	Node* ind = head;
	Node* temp = NULL;
	for (Node* cur = head->next; cur != NULL; cur = cur->next) {
		T value = cur->data;
		temp = head;
		for (temp = head; temp != ind->next; temp = temp->next) {
			if (value == temp->data)
				break;
		}
		if (temp == ind->next) {
			ind = ind->next;
			ind->data = value;
		}
	}
	// remove remaining list 
	while (ind->next != NULL) {
		size--;
		Node* temp = ind->next;
		ind->next = temp->next;
		temp->next = NULL;
		delete temp;
		temp = NULL;
	}
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

/*
	Two list should have same size
*/
template <typename T>
typename List<T>::Node* List<T> ::sumDigitsWithCarry(Node* num1, Node* num2) {
	Node* newHead = new Node;
	Node* newCur = newHead;
	int carry = 0;
	for (Node* cur1 = num1, *cur2 = num2; cur1 != NULL && cur2 != NULL; cur1 = cur1->next, cur2 = cur2->next) {
		int val1 = cur1->data;
		int val2 = cur2->data;
		int sum = val1 + val2;
		int newDig = (sum % 10) + carry;

		newCur->data = newDig;
		newCur->next = new Node;
		newCur = newCur->next;

		carry = (sum / 10) ? 1 : 0;
	}

	if (carry == 1) {
		newCur->data = 1;
		newCur->next = NULL;
	}

	newCur = NULL;
	return newHead;
}


/*
Enter random int values in the range [0, max] to the begining
of the linked list
*/
template <typename T>
void List<T> ::randomIntFill(int item_num, int max) {
	for (int i = 0; i < item_num; i++) {
		int next_val = rand() % max;
		add(0, next_val);
	}
}

template <typename T>
T List<T>::get(int index) {
	if (index > size || index < 0) {
		cout << "Wrong index value!!!" << endl;
		return NULL;
	}
	Node* ptr = find(index);
	return ptr->data;
}

template <typename T>
typename List<T>::Node* List<T>::find(int index) {
	Node* cur = head;
	for (int i = 0; i < index; i++) {
		cur = cur->next;
	}
	return cur;
}

template <typename T>
void List<T>::printList() {
	for (Node* cur = head; cur != NULL; cur = cur->next) {
		cout << cur->data << ' ';
	}
	cout << endl;
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

#pragma endregion

int main()
{
	List<int> list;
	
	int index = 0;
	
	list.add(index++, 1);
	list.add(index++, 2);
	list.add(index++, 3);

	for (int i = 0; i < list.getLength(); i++) 
	{
		cout << list[i] << endl;
	}
}