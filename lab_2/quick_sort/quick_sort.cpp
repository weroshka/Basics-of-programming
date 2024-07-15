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

void QuickSort(int a, int b, int mas[])
{
	if (a >= b)
		return;
	
	int m = ((rand()*rand()) % (b - a + 1)) + a; //медиана 3-х

	int k = mas[m];
	int l = a - 1;
	int r = b + 1;

	while (1)
	{
		do
			l++;
		while (mas[l] < k);
		
		do
			r--;
		while (mas[r] > k);

		if (l >= r)
			break;

		std::swap(mas[l], mas[r]);
	}
	r = l;
	l = l - 1;
	QuickSort(a, l, mas);
	QuickSort(r, b, mas);
}

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

	int begin = 0;
	int end = n - 1;

	std::cout << "Quick sort began... " << std::endl;

	Timer t;
	QuickSort(begin, end, mas);
	std::cout << "Time elapsed: " << t.elapsed() << '\n';

	/*for (int i = 0; i < n; i++)
		std::cout << mas[i] << " ";*/

	//Удаление динамического массива
	delete[] mas;

	return 0;
}