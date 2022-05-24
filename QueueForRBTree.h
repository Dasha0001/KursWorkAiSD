#ifndef QUEUEFORRBTREE
#pragma once
#include "NodeList.h"

template <class T>
class Queue
{
private:
	class Node
	{
	public:
		Node(T data)
		{
			this->data = data;
			this->prev = nullptr;
		}

		T data;

		Node* prev;
	};

	Node* head;

	Node* last;

public:
	Queue()
	{
		head = nullptr;
		last = nullptr;
	}

	~Queue()
	{
		while (!isEmpty())
		{
			pop();
		}
	}

	void pop()
	{
		if (isEmpty())
		{
			throw out_of_range("Queue is empty!");
		}
		else
		{
			Node* temp = head;
			head = head->prev;
			delete temp;
		}
	}

	void Push(T data)
	{
		Node* newNode = new Node(data);
		if (isEmpty())
		{
			head = newNode;
			last = newNode;
		}
		else
		{
			last->prev = newNode;
			last = newNode;
		}
	}

	bool isEmpty()
	{
		return head == nullptr;
	}

	T front()
	{
		if (isEmpty())
		{
			throw out_of_range("Queue is empty");
		}
		else
		{
			return head->data;
		}
	}

	T back()
	{
		if (isEmpty())
		{
			throw out_of_range("Queue is empty");
		}
		else
		{
			return last->data;
		}
	}
};

#endif // !QUEUEFORRBTREE
