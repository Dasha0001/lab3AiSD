#ifndef QUEUEFORRBTREE
#pragma once
#include "Node_List.h"

template <typename T>
class Queue : public Node_List<T>
{
public:
	Node_List<T>::Clear;

	Node_List<T>::GetSize;

	void PushFront(T element) override
	{
		throw logic_error("Queue structure has no access to execute PushFront");
	}

	Node_List<T>::PushBack;

	void PushIndex(int index, T element) override
	{
		if (index == GetSize()) PushBack(element);
		else throw logic_error("In queue structure pushing index can only be the last one");
		return;
	}

	void Push(T element) override
	{
		PushBack(element);
		return;
	}

	Node_List<T>::PopFront;

	void PopBack() override
	{
		throw logic_error("Queue structure has no access to execute PopBack");
	}

	void PopIndex(int index) override
	{
		if (index == 0) PopFront();
		else throw logic_error("In queue structure popping index can only be zero");
		return;
	}

	void Pop() override
	{
		PopFront();
		return;
	}

	Node_List<T>::GetData;

	Node_List<T>::PrintData;
};

#endif // !QUEUEFORRBTREE
