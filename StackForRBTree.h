#ifndef STACKFORRBTREE
#pragma once
#include "Node_List.h"

template <typename T>
class Stack : public Node_List<T>
{
public:
	Node_List<T>::Clear;

	Node_List<T>::GetSize;

	Node_List<T>::PushFront;

	void PushBack(T element) override
	{
		throw logic_error("Stack structure has no access to execute PushFront");
	}

	void PushIndex(int index, T element) override
	{
		if (index == 0) PushFront(element);
		else throw logic_error("In stack structure pushing index can only be zero");
		return;
	}

	void Push(T element) override
	{
		PushFront(element);
		return;
	}

	Node_List<T>::PopFront;

	void PopBack() override
	{

		throw logic_error("Stack structure has no access to execute PopBack");

	}

	void PopIndex(int index) override
	{
		if (index == 0) PopFront();
		else throw logic_error("In stack structure popping index can only be zero");
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
#endif // !STACKFORRBTREE
