#ifndef NODELIST
#pragma once
#include <iostream>
using namespace std;
#include"IteratorForRBTree.h"

template <typename T>
class Node_List
{
protected:
	struct Node
	{
		Node* previous, * next;
		T data;
		char symbol = '\0';
		int frequency = 0;
		Node(T data, Node* next = nullptr, Node* previous = nullptr) : data(data), previous(previous), next(next) {}
		~Node() {}
	};

public:
	Node* head, * ending;

	Node_List() : head(nullptr), ending(nullptr) {}

	Node_List(const size_t size, T* arr) : head(nullptr), ending(nullptr)
	{
		for (size_t i = 0; i < size; i++) this->PushBack(arr[i]);
	}

	~Node_List()
	{
		if (head != nullptr) Clear();
	}

	friend bool operator==(Node_List<T>& list1, Node_List<T>& list2)
	{
		Node* current1 = list1.head;
		Node* current2 = list2.head;
		while (current1 != nullptr)
		{
			if (current2 != nullptr)
			{
				if (current1->data != current2->data) return false;
			}
			else return false;
			current1 = current1->next;
			current2 = current2->next;
		}
		if (current2 != nullptr) return false;
		return true;
	}

	friend ostream& operator<<(ostream& stream, Node_List<T>& list)
	{
		Node* current = list.head;
		stream << "[";
		while (current != nullptr)
		{
			stream << current->data;
			if (current->next != nullptr) stream << " ";
			current = current->next;
		}
		stream << "]";
		return stream;
	}
	T getHead()
	{
		return this->head->data;
	}
	void Clear()
	{
		if (head == nullptr) throw logic_error("List is already empty");
		while (head != nullptr)
		{
			if (head->next == nullptr) break;
			head = head->next;
			delete head->previous;
		}
		delete head;
	}

	size_t GetSize()
	{
		int size = 0;
		Node* cur = head;
		while (cur != nullptr)
		{
			size++;
			cur = cur->next;
		}
		return size;
	}

	virtual void PushFront(T element)
	{
		Node* newElement = new Node(element, head);
		if (head == nullptr)
		{
			head = newElement;
			ending = head;
		}
		else
		{
			head->previous = newElement;
			head = head->previous;
		}
		return;
	}

	virtual void PushBack(T element)
	{
		Node* newElement = new Node(element, nullptr, ending);
		if (ending == nullptr)
		{
			ending = newElement;
			head = ending;
		}
		else
		{
			ending->next = newElement;
			ending = ending->next;
		}
		return;
	}

	virtual void Push(T element)
	{
		throw logic_error("Push is undefinable, use PushFront/PushBack/PushIndex");
	}

	virtual void PushIndex(int index, T element)
	{
		throw logic_error("Push is undefinable, use PushFront/PushBack/PushIndex");
	}

	virtual void PopFront()
	{
		if (head == nullptr) throw logic_error("List is already empty");
		if (head->next == nullptr)
		{
			delete head;
			head = nullptr;
			ending = nullptr;
		}
		else
		{
			head = head->next;
			delete head->previous;
			head->previous = nullptr;
		}
		return;
	}

	virtual void PopBack()
	{
		if (ending == nullptr) throw logic_error("List is already empty");
		if (ending->previous == nullptr)
		{
			delete ending;
			head = nullptr;
			ending = nullptr;
		}
		else
		{
			ending = ending->previous;
			delete ending->next;
			ending->next = nullptr;
		}
		return;
	}

	virtual void PopIndex(int index)
	{
		const int lastIndex = GetSize() - 1;
		if (index == 0) PopFront();
		else if (index == lastIndex) PopBack();
		else if (index > lastIndex || index < 0) throw out_of_range("Stated index is invalid");
		else
		{
			int currentIndex = 1;
			Node* cur = head->next;
			while (currentIndex != index)
			{
				cur = cur->next;
				currentIndex++;
			}
			Node* next = cur->next, * previous = cur->previous;
			delete cur;
			next->previous = previous;
			previous->next = next;
		}
	}

	virtual void Pop()
	{
		throw logic_error("Push is undefinable, use PopFront/PopBack/PopIndex");
	}

	T& GetData(size_t index)
	{
		Node* current = head;
		size_t i = 0;
		while (current != nullptr)
		{
			if (i == index) return current->data;
			i++;
			current = current->next;
		}
		throw out_of_range("Index is incorrect");
	}

	void PrintData()
	{
		cout << *this;
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
			T temp = current->data;
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
		ending = nullptr;
	}

};


#endif // !NODELIST

