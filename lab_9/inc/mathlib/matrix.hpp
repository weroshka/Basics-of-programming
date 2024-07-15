#pragma once
#include<iostream>

namespace vk::math
{
	//создали структуру, в к-ю поместили массив
	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	//определение константы

	#define MY_DEBUG

	template <typename T, int N, int M>
	class Matrix
	{
	public:
		// Конструктор
		Matrix()
		{
			//директива
#ifdef MY_DEBUG
			std::cout << "Constructor is working ..." << std::endl;
#endif

			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		//Конструктор, в к-й передали массив по ссылке
		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			std::cout << "Mas constructor " << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}
		// Деструктор
		~Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Destructor is working ..." << std::endl;
#endif
		}

		//Оператор сложения
		template <typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{

#ifdef MY_DEBUG
			std::cout << "Operator + is working ..." << std::endl;
#endif

			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
				{
					T sum = 0;
					sum = m_mat[i][j] + mat.get(i, j);
					tmp.set(i, j, sum);
				}
			return tmp;
		}

		//Оператор вычитания
		template <typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{

#ifdef MY_DEBUG
			std::cout << "Operator - is working ..." << std::endl;
#endif

			Matrix<T, N, M> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
				{
					T razn = 0;
					razn = m_mat[i][j] - mat.get(i, j);
					tmp.set(i, j, razn);
				}
			return tmp;
		}

		// Оператор умножения
		template <typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{

#ifdef MY_DEBUG
			std::cout << "Operator * is working ..." << std::endl;
#endif

			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++)
				{
					T sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(k, j);
					tmp.set(i, j, sum);
				}

			return tmp;

		}

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }


		// Оператор присваивания 
		template <typename T, int N, int M>
		Matrix<T, N, M>& operator = (const Matrix<T, N, M>& mat)
		{

#ifdef MY_DEBUG
			std::cout << "Operator = is working ..." << std::endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);

			return *this;
		}

		// Конструктор копирования 
		Matrix(const Matrix<T, N, M>& mat)
		{

#ifdef MY_DEBUG
			std::cout << "Copy constructor is working ..." << std::endl;
#endif

			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}


		// Вычисление ОПРЕДЕЛИТЕЛЯ матрицы 2*2 или 3*3
		T det() // в качестве аргумента ничего не передаем
		{
			T det = 0;

			if ((m_m == 2) && (m_n == 2))
			{
				det = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];

				return det;
			}

			if ((m_m == 3) && (m_n == 3))
			{
				det = m_mat[0][0] * (m_mat[1][1] * m_mat[2][2] - m_mat[1][2] * m_mat[2][1]) -
					m_mat[0][1] * (m_mat[1][0] * m_mat[2][2] - m_mat[1][2] * m_mat[2][0]) +
					m_mat[0][2] * (m_mat[1][0] * m_mat[2][1] - m_mat[1][1] * m_mat[2][0]);
				return det;
			}

			else
			{
				std::cout << "The operation is (det) not supported " << std::endl;
				return -1;
			}
		}

		// Нахождение обратной матрицы 
		Matrix obr() // в качестве аргумента ничего не передаем
		{
			Matrix tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = 0;
			if ((m_n == 2) && (m_m == 2) && (det() != 0))
			{
				// Обратная матрица - произведение 1/det() на матрицу, элементы которой получаются транспонированием матрицы алгебраич. дополнений исходной матрицы

				tmp.set(0, 0, (m_mat[1][1] / det()));
				tmp.set(0, 1, (-m_mat[0][1] / det()));
				tmp.set(1, 0, (-m_mat[1][0] / det()));
				tmp.set(1, 1, (m_mat[0][0] / det()));
			}

			if ((m_n == 3) && (m_m == 3) && (det() != 0))
			{
				tmp.set(0, 0, ((m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det()));
				tmp.set(0, 1, (-(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det()));
				tmp.set(0, 2, ((m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det()));
				tmp.set(1, 0, (-(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det()));
				tmp.set(1, 1, ((m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det()));
				tmp.set(1, 2, (-(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det()));
				tmp.set(2, 0, ((m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det()));
				tmp.set(2, 1, (-(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det()));
				tmp.set(2, 2, ((m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det()));
			}

			if ((m_n > 3) && (m_m > 3) || (det() == 0))
			{
				std::cout << "The operation (obr) is not supported" << std::endl;
			}

			return tmp;
		}

		// Нахождение траспонированной матрицы 

		Matrix<T, M, N> transp() //в качестве аргумента ничего не передаем
		{

#ifdef MY_DEBUG
			std::cout << "The operation of transposition is working ..." << std::endl;
#endif
			Matrix<T, M, N> tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
				{
					T new_number = 0;
					new_number = m_mat[i][j];
					tmp.set(j, i, new_number); //строки исходной матрицы становятся столбцами новой
				}
			return tmp;
		}

		template <typename T, int N, int M>
		friend std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat);
		template <typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat);

	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	//оператор ввода
	template <typename T, int N, int M>
	std::istream& operator >> (std::istream& in, Matrix<T, N, M>& mat)
	{
		std::cout << "Matrix " << mat.getN() << "x" << mat.getM() << std::endl;
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	//опрератор вывода
	template <typename T, int N, int M>
	std::ostream& operator <<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.getN() << "x" << mat.getM() << std::endl;
		for (int i = 0; i < mat.m_n; i++)
		{
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Matrix_2x2_d = Matrix<double, 2, 2>;
	using Matrix_4x4_d = Matrix<double, 4, 4>;
	using Matrix_5x3_d = Matrix<double, 5, 3 >;
}