#include <iostream>
#include <string>
#include <vector>
#include <code.hpp>

int main()
{
	std::vector<CodeGenerator*> lang_code;

	CodeGenerator* code1 = codeFactory(language::JAVA);
	lang_code.push_back(code1);

	CodeGenerator* code2 = codeFactory(language::PHP);
	lang_code.push_back(code2);

	CodeGenerator* code3 = codeFactory(language::C_PLUS_PLUS);
	lang_code.push_back(code3);

	for (int i = 0; i < lang_code.size(); i++)
	{
		lang_code[i]->generateCode();
		std::cout << std::endl;
	}

	for (int i = 0; i < lang_code.size(); i++)
		delete lang_code[i];


	return 0;

}