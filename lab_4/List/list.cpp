#include <iostream>
#include <ctime>
#include <chrono>

class Timer
{
private:
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

struct T_List
{
	T_List* next;
	int age;
};

void ADD(T_List* head, int age)
{
	T_List* p = new T_List;
	p->age = age;
	p->next = head->next;
	head->next = p;
}

void PRINT(T_List* head)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		std::cout << p->age << std::endl;
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

bool FIND_k(T_List* head, int k)
{
	T_List* p = head->next;
	while (p != nullptr)
	{
		if (p->age == k)
			return true;
		p = p->next;
	}
}

int main()
{
	T_List* head = new T_List;
	head->next = nullptr;
	int k;
	int M = 1000;
	int N = 10000;
	for (int i = 0; i <= N; i++)
		ADD(head, i);
	
	srand(time(NULL));

	Timer t; 
	for (int i = 0; i <= M; i++)
	{
		k = (rand() % 100000) + 1; 
		
		if (FIND_k(head, k))
			std::cout << k << " is found" << std::endl;
	}

	std::cout << "Time elapsed: " << t.elapsed() << '\n';
	CLEAR(head);

	delete head;
	return 0;
}