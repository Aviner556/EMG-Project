#pragma once
#include <exception>
#include <stdio.h>

template<typename Type>
class Deque
{
private:
	struct ListNode {
		Type _value;
		struct ListNode* next;
		struct ListNode* prev;
	};
	ListNode* head = nullptr;
	ListNode* tail = head;
	size_t _size = 0;

public:
	Deque() {};
	Deque(const Deque<Type>& other) //copy constructor
	{
		
	};
	~Deque() {};

	void operator = (const Deque<Type>& other) //copy assignments
	{
		
	}; 

	bool isEmpty() const //checks whether the deque is empty
	{
		if (_size == 0) {
			return true;
		}
		return false;
	}; 

	size_t size() const //returns the number of elements in the deque
	{
		return _size;
	};

	void pushFront(const Type& elem)
	{
		ListNode* node = new ListNode;
		if (_size != 0) {
			node->_value = elem;
			node->next = head;
			node->prev = nullptr;
			head->prev = node;
			head = node;
		}
		else {
			node->_value = elem;
			node->next = nullptr;
			head = node;
			tail = node;
		}
		_size++;
	};

	void pushBack(const Type& elem)
	{
		ListNode* node = new ListNode;
		node->_value = elem;
		node->next = nullptr;
		node->prev = tail;
		tail->next = node;
		tail = node;
		_size++;
	};

	Type& front() const //get element at the deque from (position 0)
	{
		if (!(this->isEmpty())) {
			return head->_value;
		}
		throw _EXCEPTION_;
	};

	Type& back() const //get element at the deque back (last element)
	{
		if (!(this->isEmpty())) {
			return tail->_value;
		}
		throw _EXCEPTION_;
	}; 

	void popBack() // extract elements from the deque’s back
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = nullptr;
		_size--;
	};

	void popFront() // extract elements from the deque’s front
	{
		head = head->next;
		delete head->prev;
		head->prev = nullptr;
		_size--;
	};
	
	bool operator == (const Deque<Type>& other) //compares two deques
	{
		if (_size != other._size) {
			return false;
		}
		if (_size == 0) {
			return true;
		}
		ListNode* node = new ListNode;
		ListNode* otherNode = new ListNode;
		node = head;
		otherNode = other.head;
		for (int i = 0; i < _size; i++) {
			if (node->_value != otherNode->_value) {
				return false;
			}
			node = node->next;
			otherNode = otherNode->next;
		}
	}; 

	Type& operator [] (size_t index) //returns the element at position index
	{
		if (_size == 0) {
			printf("empty\n");
			throw _EXCEPTION_;
		}
		if (index >= _size) {
			printf("index out of range");
			throw _EXCEPTION_;
		}
		ListNode * node = new ListNode;
		node = head;
		for (int i = 0; i < index; i++) {
			node = node->next;
		}
		return node->_value;
	}; 
};
