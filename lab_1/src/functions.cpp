#include <iostream>
#include <functions.hpp>

namespace standart
{
	void Input(int& n, int mas[20000])
	{
		std::cout << "n = ";
		std::cin >> n;
		std::cout << "Input ";
		for (int i = 0; i < n; i++)
			std::cin >> mas[i];
	}

	bool isEven(int x)
	{
		if (x % 2 == 0)
			return true;

		return false;
	}

	void Output(int n, int mas[20000])
	{
		std::cout << "Output ";
		for (int i = 0; i < n; i++)
			std::cout << mas[i] << " ";
	}
}