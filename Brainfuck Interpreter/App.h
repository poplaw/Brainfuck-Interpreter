#pragma once

#include <string>
#include <array>
#include <cstdint>
#include <memory>
#include <stack>
#include <vector>

namespace BFI
{
	class App
	{
	private:
		static const std::uint_fast16_t tapeSize{ 30000 };

		std::string path;
		std::vector<char> code;
		char* programCounter{ nullptr };

		std::uint_fast8_t* tape{ nullptr };
		std::uint_fast8_t* tapeIndex { nullptr };

		std::stack<char*> loopBeginings;

		char* getNextMatchingIndex(char* index);
		void loadFile();

	public:
		App(const std::string& path);
		~App();
		void run(); 
	};
}

