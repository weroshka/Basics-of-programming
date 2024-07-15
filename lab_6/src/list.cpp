#include "inc/list.hpp"
#include <iostream>

struct T_List;

void ADD(T_List* head, std::string surname)
{
	T_List* p = new T_List;
	p->surname = surname;

	p->next = head->next;
	head->next = p;
}

void PRINT(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->surname << std::endl;
		p = p->next;
	}
}

void SEARCH(T_List* head, std::string surname)
{
	T_List* p = head->next;

	while (p != nullptr)
	{
		if (p->surname == surname)
			std::cout << p->surname << "  found" << std::endl;
		p = p->next;
	}
}

void DELETE(T_List* head)
{
	T_List* tmp;
	T_List* p = head;
	while (p->next != nullptr)
	{
		if (p->next->surname.length() > 6)
		{
			tmp = p->next;
			p->next = p->next->next;
			delete tmp;
		}
		else
			p = p->next;
	}
}

void CLEAR(T_List* head)
{
	T_List* tmp;
	T_List* p = head->next;
	while (p != nullptr)
	{
		tmp = p;
		p = p->next;
		delete tmp;
	}
}

void DUPLICATE(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		if ((p->surname[0] == 'I') || (p->surname[0] == 'A') || (p->surname[0] == 'O'))
		{
			T_List* q = new T_List;
			q->next = p->next;
			p->next = q;
			q->surname = p->surname;
			p = p->next;
		}
		p = p->next;
	}
}