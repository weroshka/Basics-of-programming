#include <iostream>
#include <inc/pointers.hpp>

int main()
{
	auto Stavitskaia{ std::make_shared<Teacher>("Stavitskaya") };
	auto Maklakhova{ std::make_shared<Teacher>("Maklakhova") };
	auto Kutmullaeva{ std::make_shared<Student>("Kurtmullaeva") };
	auto Petrov{ std::make_shared<Student>("Petrov") };

	teacher_student(Stavitskaia, Petrov);
	teacher_student(Maklakhova, Kutmullaeva);

	Stavitskaia->students_of_teacher();
	Maklakhova->students_of_teacher();
}