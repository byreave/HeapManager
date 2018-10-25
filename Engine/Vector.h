#pragma once
namespace Engine {
	template <typename T>
	class Node
	{
	public:
		Node(const T & val) { _val = val; }
		~Node() { delete _val; }
		Node<T> * & next() { return _next; }
		T & val() { return _val; }
	private:
		T _val;
		Node<T> * _next;
	};

	template <typename T>
	class Vector
	{
	public:
		Vector();
		~Vector();
		void push(const T & val);
		void pop();
		void clear();
		T & operator[](const unsigned int index);
		bool removeAt(const unsigned int index);
	private:
		Node<T> * head;
		Node<T> * tail;
	};

}
#include <assert.h>

template <typename T>
Engine::Vector<T>::Vector()
{
	head = tail = nullptr;
}

template<typename T>
Engine::Vector<T>::~Vector()
{
	Node<T> * cur = head;
	while (nullptr != cur)
	{
		head = head->next();
		delete cur;
		cur = head;
	}
	head = nullptr;
}

template<typename T>
void Engine::Vector<T>::push(const T & val)
{
	if (nullptr == head)
	{
		head = new Node<T>(val);
		tail = head;
	}
	else
	{
		while (tail->next() != nullptr)
			tail = tail->next();
		tail->next() = new Node<T>(val);
		tail = tail->next();
	}
}

template<typename T>
void Engine::Vector<T>::pop()
{
	Node<T> * cur = head;
	if (cur == tail)//only one element
	{
		delete tail;
		head = tail = nullptr;
		return;
	}
	while (cur->next() != tail)
	{
		cur = cur->next();
	}
	delete tail;
	tail = cur;
}

template<typename T>
void Engine::Vector<T>::clear()
{
	Node<T> * cur = head;
	while (nullptr != cur)
	{
		head = head->next();
		delete cur;
		cur = head;
	}
	head = nullptr;
}

template<typename T>
T & Engine::Vector<T>::operator[](const unsigned int index)
{
	Node<T> * cur = head;
	unsigned int ind = index;
	while (ind-- > 0)
	{
		//add assert
		assert(cur != nullptr);
		cur = cur->next();
	}
	return cur->val();
}

template<typename T>
bool Engine::Vector<T>::removeAt(const unsigned int index)
{
	Node<T> * cur = head;
	int tmpInd = index;
	if (index == 0)
	{
		head = cur->next();
		if (head == nullptr)
			tail = nullptr;
		delete cur;
		cur = nullptr;
	}
	while (tmpInd-- > 1)
	{
		//add assert
		assert(cur != nullptr);
		cur = cur->next();
	}
	//add assert
	assert(cur->next() != nullptr);
	if (cur->next() == tail)
	{
		tail = cur;
	}
	delete cur->next();
	cur->next() = nullptr;
	return false;
}

//template class Engine::Vector<int>;
