#include <iostream>
#include <ctime>
#include <chrono>

class Timer
{
private:
	// Псевдонимы типов используются для удобного доступа к вложенным типам
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


int main()
{
	int N;
	std::cout << "Enter N = ";
	std::cin >> N;

	int M;
	std::cout << "Enter M = ";
	std::cin >> M;

	//Создание массива рандомных чисел
	int* mas = new int[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		//Заполнение массива числами от 1 до N-1
		mas[i] = (rand() % N) + 1;;
	}

	int key = (rand() % N) + 1;
	std::cout << "Key is " << key << std::endl;

	std::cout << "Operation began... " << std::endl;

	Timer t;

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (mas[j] == key)
			{
				std::cout << "Exists!" << std::endl;
				break;
			}
		}
	}
	std::cout << "Time elapsed: " << t.elapsed() << '\n';

	//Удаление динамического массива
	delete[] mas;

	return 0;
}



