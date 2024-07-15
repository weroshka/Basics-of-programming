#pragma once
#include<iostream>

namespace vk::math
{
	//������� ���������, � �-� ��������� ������
	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	//����������� ���������

	#define MY_DEBUG

	template <typename T, int N, int M>
	class Matrix
	{
	public:
		// �����������
		Matrix()
		{
			//���������
#ifdef MY_DEBUG
			std::cout << "Constructor is working ..." << std::endl;
#endif

			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		//�����������, � �-� �������� ������ �� ������
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
		// ����������
		~Matrix()
		{
#ifdef MY_DEBUG
			std::cout << "Destructor is working ..." << std::endl;
#endif
		}

		//�������� ��������
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

		//�������� ���������
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

		// �������� ���������
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


		// �������� ������������ 
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

		// ����������� ����������� 
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


		// ���������� ������������ ������� 2*2 ��� 3*3
		T det() // � �������� ��������� ������ �� ��������
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

		// ���������� �������� ������� 
		Matrix obr() // � �������� ��������� ������ �� ��������
		{
			Matrix tmp;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = 0;
			if ((m_n == 2) && (m_m == 2) && (det() != 0))
			{
				// �������� ������� - ������������ 1/det() �� �������, �������� ������� ���������� ����������������� ������� ���������. ���������� �������� �������

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

		// ���������� ���������������� ������� 

		Matrix<T, M, N> transp() //� �������� ��������� ������ �� ��������
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
					tmp.set(j, i, new_number); //������ �������� ������� ���������� ��������� �����
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

	//�������� �����
	template <typename T, int N, int M>
	std::istream& operator >> (std::istream& in, Matrix<T, N, M>& mat)
	{
		std::cout << "Matrix " << mat.getN() << "x" << mat.getM() << std::endl;
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	//��������� ������
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