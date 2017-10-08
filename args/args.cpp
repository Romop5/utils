#include "args.h"
#include <regex>
#include <iostream>
Arguments::Arguments()
{
	this->argumentPrecedence = OPTIONAL;
}
void Arguments::first(argType type)
{
	this->argumentPrecedence = type;
}


void Arguments::addFixed(std::string name, std::string format)
{
	this->fixedArguments.push_back(std::make_pair(name,format));
}

void Arguments::addOpt(std::string name, std::string shortKey, bool hasParam, std::string format)
{
	auto pair = std::make_pair(name,hasParam);
	this->options[shortKey] = pair;
}
	
void Arguments::addLongOpt(std::string name, std::string key, std::string shortKey, bool hasParam, std::string format)
{
	this->addOpt(name,key,hasParam,format);
	this->addOpt(name,shortKey,hasParam,format);
}

int Arguments::parse(int argc, char** argv)
{
	for(int i = 0; i < argc; ++i)
		std::cout << argv[i] << std::endl;

	// Skip program name
	char ** argumentPointer = argv+1;
	
	enum automata{STEP_FIXED, STEP_OPTIONAL, STEP_END} state;

	state = STEP_OPTIONAL;
	if(this->argumentPrecedence == FIXED)
		state = STEP_FIXED;

	while(state != STEP_END)
	{
		switch(state)
		{
			case STEP_FIXED:
			for(auto &fixedArg: this->fixedArguments)
			{
				// expected fixed, got optional ?
				if(*argumentPointer == NULL || *argumentPointer[0] == '-')
				{
					errorMessage = std::string("Expected fixed argument '")+fixedArg.first+"'";
					return ARGUMENT_INVALID_FORMAT;
				}
				if(!hasFormat(fixedArg.second,*argumentPointer))
				{
					errorMessage = std::string("Format mismatch for '")+fixedArg.first+"'";
					return ARGUMENT_INVALID_FORMAT;
				}
				this->arguments[fixedArg.first] = *argumentPointer;
				argumentPointer++;
			}
			state = STEP_END;
			if(this->argumentPrecedence == FIXED)
				state = STEP_OPTIONAL;
			break;

			case STEP_OPTIONAL:
			while(*argumentPointer != NULL)
			{
				if(*argumentPointer[0] == '-')
				{

					char* omitMinus = (*argumentPointer)+1;
					if((*argumentPointer)[1] == '-')
						omitMinus = (*argumentPointer)+2;
					char* param = *(argumentPointer+1);
					if(hasOption(omitMinus))
					{
						auto val = &arguments[getOptionName(omitMinus)];
						if(hasOptionParam(omitMinus))
						{
							// expected param
							if(param == NULL)
							{
								errorMessage = std::string("Expected param for option -")+omitMinus;
								return ARGUMENT_INVALID_FORMAT;
							}

							*val = param;
							++argumentPointer;
						}
						else
							*val = "";
					} else {
						errorMessage = std::string("Non-defined option '")+omitMinus+"'";
						return ARGUMENT_INVALID_FORMAT;
					}
					argumentPointer++;
					continue;
				}
				break;
			}
			if(*argumentPointer != NULL)
			{
				// FIXED arguments went first, optionals were
				// supposed to end command-line
				if(this->argumentPrecedence == FIXED)
				{
					errorMessage = "Expected any optional argument";
					return ARGUMENT_INVALID_FORMAT;
				}
				else {
					state = STEP_FIXED;
					break;
				}
			} else {
				state = STEP_END;
				if(this->argumentPrecedence == OPTIONAL)
					state = STEP_FIXED;
			}
		}
	}
	if(*argumentPointer != NULL)
	{
		errorMessage = std::string("Expected no argument, got '")+*argumentPointer;
		return ARGUMENT_INVALID_FORMAT;
	}
	return OK;
}



bool Arguments::hasFormat(std::string format, std::string testedWord)
{
	std::cout << "Comparing " << format << " and " << testedWord << std::endl;
	// TODO:compare
	std::regex re = std::regex(format);
	std::smatch result;
	return std::regex_match(testedWord,result, re);
}


bool Arguments::hasOption(std::string option)
{
	return (this->options.find(option) != this->options.end());
}

bool Arguments::hasOptionParam(std::string longOpt)
{
	auto it = this->options.find(longOpt);
	if(it != this->options.end())
	{
		return it->second.second == true;
	}
	return false;
}

std::string Arguments::getOptionName(std::string opt)
{	
	auto it = this->options.find(opt);
	if(it != this->options.end())
	{
		return it->second.first;
	}
	return "";
}

std::string Arguments::operator[](std::string argument)
{
	return this->arguments[argument];
}


bool Arguments::hasArgument(std::string name)
{

	auto it = this->arguments.find(name);
	return (it != this->arguments.end());
}


bool Arguments::allowRedefinition(bool allow)
{
	this->isRedefinitionAllowed = allow;
}
