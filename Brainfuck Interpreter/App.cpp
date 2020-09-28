#include "App.h"

#include <iomanip>
#include <vector>
#include <fstream>

#include <iostream>

namespace BFI
{
	App::App(const std::string& path)
		: path{ path }, tape{ nullptr }
	{
		loadFile();
		tape = new std::uint_fast8_t[tapeSize]();
	}

	App::~App()
	{
		programCounter = nullptr;
		tapeIndex = nullptr;
		delete tape;
		tape = nullptr;
	}

	void App::loadFile()
	{
		std::ifstream input(path, std::ios::binary);
		code = std::vector<char>(std::istreambuf_iterator<char>(input), {});
	}

	void App::run()
	{
		programCounter = code.data();
		tapeIndex = tape;

		while (programCounter - 1 != &code[code.size() - 1])
		{
			switch (*programCounter)
			{
			case '>':
				++tapeIndex;
				break;

			case '<':
				--tapeIndex;
				break;

			case '+':
				++(*tapeIndex);
				break;

			case '-':
				--(*tapeIndex);
				break;

			case '[':
				if (*tapeIndex == 0)
				{
					programCounter = getNextMatchingIndex(programCounter + 1);
				}
				else
				{
					loopBeginings.push(programCounter);
				}
				break;

			case ']':
				if (*tapeIndex != 0)
				{
					programCounter = loopBeginings.top();
				}
				else
				{
					loopBeginings.pop();
				}
				break;

			case ',':
				*tapeIndex = getchar();
				break;

			case '.':
				putchar(*tapeIndex);
				break;
			}

			++programCounter;
		}
	}

	char* App::getNextMatchingIndex(char* index)
	{
		std::int_fast32_t encounters{ 0 };

		for (auto* i{ index }; i <= &code[code.size() - 1]; ++i)
		{
			if (*i == '[')
			{
				++encounters;
			}

			if (*i == ']')
			{
				if (encounters == 0)
				{
					return i;
				}
				else
				{
					--encounters;
				}
			}
		}

		return nullptr;
	}
}