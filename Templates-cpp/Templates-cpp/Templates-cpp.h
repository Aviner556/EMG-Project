#pragma once

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
	ListNode* tail = nullptr;

public:
	Deque() {};
	Deque(const Deque<Type>& other) {};
	~Deque() {};
};
