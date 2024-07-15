#include <iostream>
#include <ctime>
#include <chrono>

void QuickSort(int a, int b, int mas[])
{
	if (a >= b)
		return;

	int m = ((rand() * rand()) % (b - a + 1)) + a; 

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


int Search(int mas[], int start, int end, int k)
{
	if (k < mas[start])
		return -1;

	if (k == mas[start])
		return 1;

	if (k > mas[end])
		return -1;

	int a = start;
	int b = end - 1;

	while (a + 1 < b)
	{
		int c;
		c = (a + b) / 2;

		if (k > mas[c])
			a = c;

		else
			b = c;
	}

	if (mas[b] == k)
		return b;

	else
		return -1;

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
		mas[i] = (rand() % N)+1;
	}

	int begin = 0;
	int the_end = N - 1;
	QuickSort(begin, the_end, mas);

	int key = (rand() % N)+1;
	std::cout << "Key is " << key << std::endl;

	std::cout << "SEARCH began... " << std::endl;

	Timer t;

	for (int i = 0; i < M; i++)
		Search(mas, 0, N - 1, key);

	std::cout << "Time elapsed: " << t.elapsed() << '\n';

	//Удаление динамического массива
	delete[] mas;

	return 0;
}
