#include <iostream>
#include <functions.hpp>
#include <chrono> 

int main()
{
	int n;
	int mas[20000];
	standart::Input(n, mas);
	


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
	

	Timer t;

	int i = 0;
	while (i < n)
	{
		if (standart::isEven(mas[i]))
		{
			for (int k = n - 1; k >= i; k--)
			{
				mas[k + 1] = mas[k];

			}
			n++;
			i++;
		}
		i++;
	}

	std::cout << "Time elapsed: " << t.elapsed() << '\n';


	standart::Output(n, mas);

	return 0;
}

	

