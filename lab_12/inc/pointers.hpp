#pragma once
#include <vector>
#include <memory>

class Teacher;

class Student
{
	std::string st_student;
	std::weak_ptr<Teacher> ptr_teacher;

public:

	Student(const std::string& s_surname) : st_student(s_surname)
	{
		std::cout << "Constructor " << st_student << " worked! " << std::endl;
	}

	~Student()
	{
		std::cout << "Destructor " << st_student << " worked! " << std::endl;
	}

	const std::weak_ptr<Teacher> ptrTeacher() { return ptr_teacher; }
	const std::string student_surname() { return st_student; }
	friend bool teacher_student(std::shared_ptr<Teacher>& teacher, std::shared_ptr<Student>& student);
};

class Teacher
{
	std::string tea_teacher;
	std::vector<std::shared_ptr<Student>> teach_students;

public:

	Teacher(const std::string& t_surname) : tea_teacher(t_surname)
	{
		std::cout << "Constructor " << tea_teacher << " worked! " << std::endl;
	}

	~Teacher()
	{
		std::cout << "Destructor " << tea_teacher << " worked! " << std::endl;
	}

	void add_students(std::shared_ptr<Student> student)
	{
		teach_students.push_back(student);
	}

	void students_of_teacher()
	{
		if (teach_students.size() != 0)
		{
			std::cout << tea_teacher << " has these students: " << std::endl;
			for (auto const& s : teach_students)
				std::cout << s->student_surname() << std::endl;
		}

		else
			std::cout << tea_teacher << " has not students " << std::endl;
	}

	const std::string find_teach_surname() { return tea_teacher; }

	friend bool teacher_student(std::shared_ptr<Teacher>& teacher, std::shared_ptr<Student>& student);
};

bool teacher_student(std::shared_ptr<Teacher>& t_teacher, std::shared_ptr<Student>& s_student)
{
	if (!t_teacher || !s_student)
		return false;

	s_student->ptr_teacher = t_teacher;
	t_teacher->add_students(s_student);

	std::cout << t_teacher->find_teach_surname() << " teaches " << s_student->student_surname() << "\n";

	return true;
}
