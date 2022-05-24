#ifndef NODELIST
#pragma once
#include <iostream>
#include "IteratorForRBTree.h"
#include <string>
using namespace std;


template <class T>
class Node_List
{
public:
	class Node
	{
	public:
		friend class ListIterator;

		Node(T value, Node* next, Node* prev)
		{
			this->next = next;
			this->prev = prev;
			this->value = value;
		}

		Node(T value) : Node(value, nullptr, nullptr) {}

		~Node() {};

		Node* next;
		Node* prev;
		T value;
	};

	Node* last;

	int size;

	Node* head;

	Node_List()
	{
		head = nullptr;
		last = nullptr;
		size = 0;
	}

	Node_List(const Node_List& list) : Node_List()
	{
		Node* current = list.head;

		while (current != nullptr)
		{
			this->PushBack(current->value);
			current = current->next;
		}
	}

	Node_List<T>& operator=(Node_List<T> list)
	{
		this->head = list.head;
		list.head = nullptr;
		this->last = list.last;
		list.last = nullptr;
		this->size = list.size;
		return *this;
	}

	~Node_List()
	{
		while (!isEmpty())
			pop_back();
	}

	T getHead()
	{
		return this->head->value;
	}

	void PushBack(T elem)
	{
		size++;

		Node* newElem = new Node(elem, nullptr, last);
		if (isEmpty())
		{
			head = newElem;
		}
		else
		{
			last->next = newElem;
		}
		last = newElem;
	}

	void push_front(T elem)
	{
		size++;

		Node* newElem = new Node(elem, head, nullptr);;
		if (isEmpty())
		{
			last = newElem;
		}
		else
		{
			head->prev = newElem;
		}
		head = newElem;
	}

	void pop_back()
	{
		if (isEmpty())
		{
			throw invalid_argument("Nothin to pop");
		}
		else if (head->next == nullptr)
		{
			size = 0;
			pop_only();
		}
		else
		{
			size--;
			Node* currNode = last->prev;
			delete last;
			last = currNode;
			currNode->next = nullptr;
		}
	}

	void pop_front()
	{
		if (isEmpty())
		{
			throw invalid_argument("Nothin to pop");
		}
		else if (head->next == nullptr)
		{
			size = 0;
			pop_only();
		}
		else
		{
			size--;
			Node* currNode = head->next;
			delete head;
			head = currNode;
			currNode->prev = nullptr;
		}
	}

	void clear()
	{
		size = 0;
		this->~Node_List();
		return;
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	class ListIterator : public Iterator<T>
	{

	public:
		friend class Node_List;

		Node* current;

		ListIterator(Node_List<T>* list)
		{
			current = list->head;
		}

		~ListIterator()
		{
		}

		bool has_next()
		{
			return current != nullptr;
		}

		T next()
		{
			T temp = current->value;
			current = current->next;
			return temp;
		}
	};

	ListIterator* create_iterator()
	{
		ListIterator* iter = new ListIterator(this);
		return iter;
	}
private:
	void pop_only()
	{
		delete head;
		head = nullptr;
		last = nullptr;
	}
};


template <typename T1, typename T2>
struct Pair
{
public:
	T1 first;
	T2 second;

	Pair(const T1& first, const T2& second)
	{
		this->first = first;
		this->second = second;
	}

	Pair(const Pair& pair)
	{
		this->first = pair.first;
		this->second = pair.second;
	}

	Pair() { }

	~Pair() { }
};

template <typename T1, typename T2>
Pair<T1, T2> makepair(const T1& first, const T2& second)
{
	return Pair<T1, T2>(first, second);
}

#endif // !NODELIST
