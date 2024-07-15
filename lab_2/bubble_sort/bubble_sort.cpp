#include <iostream>
#include <ctime>
#include <chrono>

void BubbleSort(int mas[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if ((mas[i]) >= (mas[i - 1]))
			continue;
		int j = i - 1;
		while ((j >= 0) && ((mas[j]) > mas[j + 1]))
		{
			std::swap(mas[j], mas[j + 1]);
			j = j - 1;
		}
	}
}

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
	int n;
	std::cout << "Enter n = ";
	std::cin >> n;
	
	//Создание массива рандомных чисел
	int* mas = new int[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		//Заполнение массива числами от 1 до 100
		mas[i] = (rand() % 100) + 1;
	}

	// Выводим массив до сортировки
	std::cout << "You entered ";
	for (int i = 0; i < n; i++)
	{
		std::cout << mas[i] << "  ";
	}
	std::cout << std::endl;

	std::cout << "Bubble sort began... " << std::endl;
	
	Timer t;
	
	BubbleSort(mas, n);

	std::cout << "Time elapsed: " << t.elapsed() << '\n';

	std::cout << "Sorted array is  ";
	
	/*for (int i = 0; i < n; i++)
	{
		std::cout << mas[i] << " ";
	}*/

	//Удаление динамического массива
	delete[] mas; 

	return 0;
}