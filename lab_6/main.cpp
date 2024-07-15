#include <iostream>
#include <fstream>
#include "inc/list.hpp"


int main()
{
	T_List* head = new T_List;
	head->next = nullptr;

	std::ifstream in("input.txt");
	std::string c;

	while (in>>c)
	{
		ADD(head, c);
	}
	
	SEARCH(head, "Popov");
	DUPLICATE(head);
	DELETE(head);
	PRINT(head);
	CLEAR(head);

	delete head;
	return 0;
}
