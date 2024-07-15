#include <iostream>
#include "inc/matrix.hpp"
#include <cassert>

using vk::math::Matrix_2x2_d;
using vk::math::Matrix_4x4_d;
using vk::math::Matrix_5x3_d;

int main()
{
	// Тесты

	std::cout << "=== Test 1. Addiction ===" << std::endl;
	{
		Matrix_2x2_d A ({ {
			{1,2},
			{3,4}
		} });

		Matrix_2x2_d B({ {
			{1,2},
			{3,4}
		} });
		auto C = A + B;
		assert(C.get(0, 0) == 2);
		assert(C.get(1, 1) == 8);
	}
	std::cout << "Addiction completed successfully!" << std::endl;

	std::cout << "=== Test 2. Subtraction ===" << std::endl;
	{
		Matrix_2x2_d A({ {
			{1,2},
			{3,4}
		} });

		Matrix_2x2_d B({ {
			{1,2},
			{3,4}
		} });
		auto C = A - B;
		assert(C.get(0, 0) == 0);
		assert(C.get(1, 1) == 0);
	}
	std::cout << "Subtraction completed successfully!" << std::endl;

	std::cout << "=== Test 3. Multiplication ===" << std::endl;
	{
		Matrix_4x4_d A({ {
			{1,2,3,4},
			{1,2,3,4},
			{4,3,2,1},
			{4,3,2,1}
		} });

		Matrix_4x4_d B({ {
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1}
		} });
		auto C = A * B;
		assert(C.get(0, 3) == 10);
		assert(C.get(3, 2) == 10);
	}
	std::cout << "Multiplication completed successfully!" << std::endl;

	std::cout << "=== Test 4. Matrix transposition ===" << std::endl;
	{
		Matrix_5x3_d A({ {
			{1,1,1},
			{2,2,2},
			{3,3,3},
			{4,4,4},
			{5,5,5}
		} });
		A.transp();
		assert(A.transp().get(0, 0) == 1);
		assert(A.transp().get(1, 0) == 1);
		assert(A.transp().get(2, 0) == 1);
		
	}
	std::cout << "Transposition completed successfully!" << std::endl;

	std::cout << "=== Test 5. Determinant ===" << std::endl;
	{
		Matrix_2x2_d A({ {
			{5,6},
			{8,7}
		} });

		A.det();
		assert(A.det() == -13);

		Matrix_4x4_d B({ {
			{1,2,3,4},
			{5,6,7,8},
			{9,10,11,12},
			{13,14,15,16}
		} });

		B.det();
	}
	std::cout << "Determinant was found successfully!" << std::endl;

	std::cout << "=== Test 6. Obr matrix ===" << std::endl;
	{
		Matrix_2x2_d A({ {
			{4,3},
			{2,1}
		} });

		A.obr();
		assert(A.obr().get(1, 0) == 1);
		assert(A.obr().get(1, 1) == -2);
	}
	std::cout << "Obr matrix was found successfully!" << std::endl;
	
	return 0;
}