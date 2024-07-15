#pragma once
#include <string>

class CodeGenerator
{
public:
	// Constructor 
	CodeGenerator() { };

	// Destructor
	virtual ~CodeGenerator() {};

	//The function which generates code related to specific language
	virtual std::string generateCode() = 0;

protected:

	//The function which adds some stuff in code
	virtual std::string someCodeRelatedThing() = 0;
};

class Java_GC : public CodeGenerator
{
public:

	//Constructor
	Java_GC() : CodeGenerator() {};

	//Destructor 
	virtual ~Java_GC() {};

	std::string generateCode()
	{
		return "proper language" + someCodeRelatedThing();
	}

protected:

	std::string someCodeRelatedThing() override
	{
		return "some JAVA code stuff";
	}
};

class C_PLUS_PLUS_GC : public CodeGenerator
{
public:

	//Constructor
	C_PLUS_PLUS_GC() : CodeGenerator() {};

	//Destructor 
	virtual ~C_PLUS_PLUS_GC() {};

	std::string generateCode()
	{
		return "proper language" + someCodeRelatedThing();
	}

protected:

	std::string someCodeRelatedThing() override
	{
		return "some C_PLUS_PLUS code stuff";
	}

};

class PHP_GC : public CodeGenerator
{
public:

	//Constructor
	PHP_GC() : CodeGenerator() {};

	//Destructor 
	virtual ~PHP_GC() {};

	std::string generateCode()
	{
		return "proper language" + someCodeRelatedThing();
	}

protected:

	std::string someCodeRelatedThing() override
	{
		return "some PHP code stuff";
	}

};


enum class language
{
	JAVA = 0,
	C_PLUS_PLUS = 1,
	PHP = 2
};

//Factory helps to transmit the object (any language) which generates, using the proper constructor
CodeGenerator* codeFactory(enum language _language)
{
	/*switch (_language)
	{
		case language::JAVA: 
			return new Java_GC();
		case language::C_PLUS_PLUS: 
			return new C_PLUS_PLUS_GC();
		case language::PHP: 
			return new PHP_GC();
	}

	throw new std::logic_error("Bad language");*/

	try
	{
		switch (_language)
		{
			case language::JAVA:
				return new Java_GC();
			case language::C_PLUS_PLUS:
				return new C_PLUS_PLUS_GC();
			case language::PHP:
				return new PHP_GC();
		}
		
		throw new std::logic_error("Bad language");
	}
	
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}