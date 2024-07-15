#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>

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

int main()
{
	std::vector<int> array;
	srand(time(NULL));
	int N = 10000;
	int M = 1000;
	for (int i = 0; i <= N; i++)
		array.push_back(i);

	/*for (int i = 0; i <= 1000; i++)
		std::cout << array[i] << std::endl;*/
	int k; 

	Timer t;
	for (int i = 0; i <= M; i++)
	{
		k = (rand() % 100000) + 1;
		for (int j = 0; j <= N; j++)
		{
			if (array[j] == k)
				std::cout << k << " is found" << std::endl;
		}
		
	}
	
	std::cout << "Time elapsed: " << t.elapsed() << '\n';
	return 0;
}