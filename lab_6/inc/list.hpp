#pragma once
#include <iostream>

struct T_List
{
	T_List* next;
	std::string surname;
};

void ADD(T_List* head, std::string surname);
void SEARCH(T_List* head, std::string surname);
void PRINT(T_List* head);
void DELETE(T_List* head);
void CLEAR(T_List* head);
void DUPLICATE(T_List* head);
