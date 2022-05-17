#ifndef RB_TREE_REALISATION


#include <iostream>
#include <stdexcept>
#include "QueueForRBtree.h"
#include "StackForRBtree.h"
#include "IteratorForRBTree.h"
#include "Node_List.h"
#pragma once
using namespace std;

template <class typeKey, class typeValue>
class RBTree {

	class  RBTree_node {
	public:
		bool red;
		typeKey* key;
		typeValue* value;

		RBTree_node* left_Element, * parent_of_Element, * right_Element;



		RBTree_node(RBTree_node* parent_of_Element) : parent_of_Element(parent_of_Element), left_Element(nullptr), right_Element(nullptr), key(nullptr), value(nullptr) {}
		RBTree_node(typeKey* key, typeValue* value, RBTree_node* parent_of_Element = nullptr) : parent_of_Element(parent_of_Element),
			left_Element(nullptr),
			right_Element(nullptr),
			red(1),
			key(key),
			value(value) {}
		~RBTree_node()
		{
			if (key != nullptr) delete key;
			if (value != nullptr) delete value;
		}



	};



public:
	RBTree_node* root;

	RBTree() { // create blank list
		this->root = nullptr;
	}



	void LeftRotate(RBTree_node* ElementX) {

		RBTree_node* ElementY = ElementX->right_Element;

		if (ElementY->left_Element->key != NULL) {
			ElementX->right_Element = ElementY->left_Element;
			ElementX->right_Element->parent_of_Element = ElementX;
		}
		if (ElementX->parent_of_Element->key == NULL) {
			this->root = ElementY;
		}
		else {
			if (ElementX->parent_of_Element->left_Element->key == ElementX->key) {

				ElementX->parent_of_Element->left_Element->key = ElementY->key;
			}
			else {
				ElementX->parent_of_Element->right_Element->key = ElementY->key;
			}

		}
		ElementY->parent_of_Element = ElementX->parent_of_Element;
		ElementY->left_Element = ElementX;
		ElementX->parent_of_Element->key = ElementY->key;
	}

	void RightRotate(RBTree_node* ElementY) {

		RBTree_node* ElementX = ElementY->left_Element;

		if (ElementX->right_Element->key != NULL) {

			ElementY->left_Element = ElementX->right_Element;
			ElementY->left_Element->parent_of_Element = ElementY;
		}

		if (ElementY->parent_of_Element->key == NULL) {
			this->root = ElementX;
		}
		else {
			if (ElementY->parent_of_Element->right_Element == ElementY) {

				ElementY->parent_of_Element->right_Element = ElementX;

			}
			else {
				ElementY->parent_of_Element->left_Element = ElementX;
			}

		}
		ElementX->parent_of_Element = ElementY->parent_of_Element;
		ElementX->right_Element = ElementY;
		ElementY->parent_of_Element = ElementX;

	}

	void RecoverForInsert(RBTree_node* newNode) {

		RBTree_node* p = newNode->parent_of_Element;
		RBTree_node* gp = newNode->parent_of_Element->parent_of_Element;

		while (newNode->parent_of_Element != nullptr && newNode->parent_of_Element->red == 1)
		{
			p = newNode->parent_of_Element;
			gp = p->parent_of_Element;
			//if (gp == nullptr) { };
			if (p == gp->left_Element)
			{
				if (gp->right_Element->red == 1)// 1
				{
					gp->right_Element->red = 0;
					gp->left_Element->red = 0;
					gp->red = 1;
					newNode = gp;
				}
				else if (p->right_Element == newNode)
				{
					newNode = p;
					LeftRotate(newNode);
				}
				else
				{
					p->red = 0;
					gp->red = 0;
					RightRotate(gp);
				}
			}

			if (p == gp->right_Element)
			{

				if (gp->left_Element->red == 1)
				{
					gp->right_Element->red = 0;
					gp->left_Element->red = 0;
					gp->red = 1;
					newNode = gp;
				}
				else
				{
					newNode = p;
					RightRotate(newNode);
					p->red = 0;
					gp->red = 1;
					LeftRotate(gp);
				}
			}
		}
		root->red = 0;

	}

	void RecoverForRemove(RBTree_node* newNode)
	{
		RBTree_node* x = newNode;
		RBTree_node* w;

		while (x != root, x->parent_of_Element != nullptr && x->red != 0)
		{
			if (x->parent_of_Element->left_Element == x)
			{
				w = x->parent_of_Element->right_Element;
				if (w->red == 1)
				{
					w->red = 0;
					x->parent_of_Element->red = 1;
					LeftRotate(x->parent_of_Element);
					w = x->parent_of_Element->right_Element;
				}
				else if (w->left_Element->red == 0 && w->right_Element->red == 0)
				{
					w->red = 1;
					x = x->parent_of_Element;
				}
				else if (w->right_Element->red == 0)
				{
					w->left_Element->red = 0;
					w->red = 0;
					RightRotate(w);
					w = x->parent_of_Element->right_Element;
				}
				else
				{
					w->red = (x->parent_of_Element->red);
					x->parent_of_Element->red = 0;
					w->right_Element->red = 0;
					LeftRotate(x->parent_of_Element);
					x = root;
				}
			}
			else
			{
				w = x->parent_of_Element->left_Element;
				if (w->red == 1)
				{
					w->red = 0;
					x->parent_of_Element->red = 1;
					RightRotate(x->parent_of_Element);
					w = x->parent_of_Element->left_Element;
				}
				else if (w->left_Element->red == 0 && w->right_Element->red == 0)
				{
					w->red = 1;
					x = x->parent_of_Element;
				}
				else if (w->left_Element->red == 0)
				{
					w->right_Element->red = 0;
					w->red = 1;
					LeftRotate(w);
					w = x->parent_of_Element->left_Element;
				}
				else
				{
					w->red = (x->parent_of_Element->red);
					x->parent_of_Element->red = 0;
					w->left_Element->red = 0;
					RightRotate(x->parent_of_Element);
					x = root;
				}
			}
			x->red = 0;
		}
	}

	RBTree_node& FindTreeNode(typeKey data)
	{
		RBTree_node* cur = root;
		while (cur != NULL)
		{
			if (*(cur->key) == data) return *cur;
			cur = (data > *(cur->key)) ? cur->right_Element : cur->left_Element;
		}

	}

	Node_List<RBTree_node*>* DFT()
	{
		RBTree_node* cur = root;
		Stack<RBTree_node*> stack;
		Node_List<RBTree_node*>* result = new Node_List<RBTree_node*>;
		while (cur != NULL)
		{
			result->PushBack(cur);
			if (cur->right_Element != nullptr) stack.Push(cur->right_Element);
			if (cur->left_Element != nullptr) cur = cur->left_Element;
			else
			{
				if (stack.head != nullptr)
				{
					cur = (RBTree_node*)stack.GetData(0);
					stack.Pop();
				}
				else cur = nullptr;
			}
		}
		return result;
	}

	typeValue Find(typeKey data)
	{
		RBTree_node* cur = root;
		while (cur != nullptr)
		{
			if (*(cur->key) == data) return *(cur->value);

			if (data > *(cur->key)) {
				cur = cur->right_Element;
			}
			else {
				cur = cur->left_Element;
			}
		}
	}

	void insert(typeKey key, typeValue val)
	{
		if (root == nullptr)
		{
			delete root;
			root = new RBTree_node(new typeKey(key), new typeValue(val));
			root->red = 0;
			root->right_Element = nullptr;
			root->left_Element = nullptr;
		}
		else
		{

			RBTree_node* cur = root;

			while ((cur->right_Element != nullptr) && (cur->left_Element != nullptr))
			{
				if (key > *(cur->key)) {
					cur = cur->right_Element;
				}
				else
					cur = cur->left_Element;
			}
			RBTree_node* newNode = new RBTree_node(new typeKey(key), new typeValue(val));
			newNode->parent_of_Element = cur;
			if (key > *(newNode->parent_of_Element->key)) {
				newNode->parent_of_Element->right_Element = newNode;
			}
			else newNode->parent_of_Element->left_Element = newNode;
			newNode->red = 1;
			RecoverForInsert(newNode);
		}
	}

	void remove(typeKey key)
	{
		RBTree_node* nodeToBeDeleted = &FindTreeNode(key);
		RBTree_node* x = nullptr;

		bool originalColor = nodeToBeDeleted->red;//2

		if (nodeToBeDeleted->left_Element == nullptr)//3
		{
			delete nodeToBeDeleted->left_Element;
			x = nodeToBeDeleted->right_Element;

			if (nodeToBeDeleted->parent_of_Element != nullptr) {
				if (nodeToBeDeleted->parent_of_Element->right_Element == nodeToBeDeleted)
				{
					nodeToBeDeleted->parent_of_Element->right_Element = x;
				}
				else nodeToBeDeleted->parent_of_Element->left_Element = x;
				if (x != nullptr) { x->parent_of_Element = nodeToBeDeleted->parent_of_Element; }
			}
			else {
				nodeToBeDeleted = nodeToBeDeleted->right_Element;


			}


		}
		else if (nodeToBeDeleted->right_Element == NULL)//4
		{
			delete nodeToBeDeleted->right_Element;
			x = nodeToBeDeleted->left_Element;
			if (nodeToBeDeleted->parent_of_Element->right_Element == nodeToBeDeleted)
			{
				nodeToBeDeleted->parent_of_Element->right_Element = x;
			}
			else nodeToBeDeleted->parent_of_Element->left_Element = x;
			if (x != nullptr) { x->parent_of_Element = nodeToBeDeleted->parent_of_Element; }
		}
		else//5
		{
			RBTree_node* y = nodeToBeDeleted->right_Element;
			while (y->left_Element != NULL) y = y->left_Element;//a
			originalColor = y->red;//b
			y->right_Element;//â
			if (y->parent_of_Element == nodeToBeDeleted)//ã
			{
				y = x->parent_of_Element;
			}
			else//ä
			{
				if (y->parent_of_Element->right_Element == y)
				{
					y->parent_of_Element->right_Element = x;
				}
				else y->parent_of_Element->left_Element = x;
			}
			if (nodeToBeDeleted->parent_of_Element->right_Element == nodeToBeDeleted)
			{
				nodeToBeDeleted->parent_of_Element->right_Element = y;
			}
			else nodeToBeDeleted->parent_of_Element->left_Element = y;//å
			if (y != nullptr) { y->parent_of_Element = nodeToBeDeleted->parent_of_Element; }

			y->red = originalColor;//æ
		}


		if (originalColor == 0) RecoverForRemove(nodeToBeDeleted);
		delete nodeToBeDeleted;
	}

	void clear()
	{
		RBTree_node* cur = root, * tmp;

		if (cur != nullptr) {
			while ((cur->left_Element != nullptr) && (cur->right_Element != nullptr))
			{
				if (cur->left_Element != nullptr) cur = cur->left_Element;

			}
			while (cur != root)
			{
				tmp = cur;
				if (cur->parent_of_Element->right_Element != nullptr) {

					delete cur->parent_of_Element->right_Element;
				}
				delete cur;
				cur = tmp->parent_of_Element;
			}
			while ((cur->left_Element != nullptr) && (cur->right_Element != nullptr))
			{
				if (cur->right_Element != nullptr) cur = cur->right_Element;

			}
			while (cur != root)
			{
				tmp = cur;
				if (cur->parent_of_Element->left_Element != nullptr) {

					delete cur->parent_of_Element->left_Element;
				}
				delete cur;
				cur = tmp->parent_of_Element;
			}

		}


		cur = nullptr;
		root = cur;

	}

	Node_List<typeKey>* get_keys()
	{
		Node_List<RBTree_node*>* list = DFT();
		Node_List<typeKey>* keysList = new Node_List<typeKey>;
		while (list->head != nullptr)
		{
			keysList->PushBack(typeKey(*((RBTree_node*)list->head->data)->key));
			list->PopFront();
		}
		return keysList;
	}

	Node_List<typeValue>* get_values()
	{
		Node_List<RBTree_node*>* list = DFT();
		Node_List<typeValue>* valuesList = new Node_List<typeValue>;
		while (list->head != nullptr)
		{
			valuesList->PushBack(typeValue(*((RBTree_node*)list->head->data)->value));
			list->PopFront();
		}
		return valuesList;
	}


	friend ostream& operator<<(ostream& out, RBTree< typeKey, typeValue>& RBTree)
	{
		Node_List<RBTree_node*>* list = RBTree.DFT();
		out << &list;
		return out;
	}

	void Print() {
		cout << *this->get_keys();
		cout << *this->get_values();

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
Pair<T1, T2> makepair(T1 first, T2 second)
{
	return Pair<T1, T2>(first, second);
}



template <class T1, class T2>
class Map
{
private:
	RBTree<T1, T2>* rbtree;
public:
	int size;

	Map()
	{
		size = 0;
		rbtree = new RBTree<T1, T2>();
	}

	~Map()
	{
		delete rbtree;
	}

	void Insert(const T1& key, const T2& data)
	{
		rbtree->Insert(key, data);
		size++;
	}

	void Add(const T1& key, const T2& data)
	{
		rbtree->Add(key, data);
	}

	void Delete(T1 key)
	{
		rbtree->Delete(key);
		size--;
	}

	T2 Find(T1 key)
	{
		return rbtree->FindData(key);
	}

	Node_List<T1>* FindKeysByData(T2 data)
	{
		auto itr = this->create_iterator();

		Node_List<T1>* foundkeys = new Node_List<T1>();

		while (itr->has_next())
		{
			Pair<T1, T2> pair = itr->next();
			if (pair.second == data)
			{
				foundkeys->PushBack(pair.first);
			}
		}
		return foundkeys;
	}

	void Clear()
	{
		delete rbtree;
		rbtree = new RBTree<T1, T2>();
		size = 0;
	}

	class MapIterator : public Iterator<Pair<T1, T2>>
	{
	public:
		friend class Map;

		Iterator<Pair<T1, T2>>* treeiter;

		MapIterator(RBTree<T1, T2>* rbtree)
		{
			treeiter = rbtree->create_iterator();
		}

		~MapIterator()
		{
			delete treeiter;
		}

		bool has_next()
		{
			return treeiter->has_next();
		}

		Pair<T1, T2> next()
		{
			return treeiter->next();
		}
	};

	MapIterator* create_iterator()
	{
		return new MapIterator(rbtree);
	}
};
#endif


