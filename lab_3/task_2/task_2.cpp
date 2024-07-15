#include <iostream>
#include <math.h> //для пользования log(x)= ln(x)

double equation(double x)
{
	return log(x) - 1;
}

double Bisection(double a, double b, double e)
{
	double fa = equation(a);

	while (1)
	{
		double x = (a + b) / 2;
		
		if (abs(a - b) < e) 
			return x;
		
		else if (equation(x) * fa > 0) 
			a = x;
		
		else 
			b = x;
	}
}

int main()
{
	double a = 0; // т.к. по ОДЗ x > 0
	double b = DBL_MAX;
	double e = 1e-4;

	double x = Bisection(a, b, e);
	std::cout << x;
	return 0;
}