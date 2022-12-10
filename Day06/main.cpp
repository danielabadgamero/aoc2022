#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream input{ "input.txt" };
	std::string str{};
	std::getline(input, str);
	std::cout << "Part 1:\n\n";
	for (size_t i{}; i != str.size(); i++)
	{
		bool valid{ true };
		std::string marker{ str.substr(i, 4) };
		for (size_t j{}; j != marker.size(); j++)
		{
			int res{ (int)marker.find(marker[j], j + 1) };
			if (res > 0)
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			std::cout << i + 4 << '\n';
			break;
		}
	}
	input.close();

	input.open("input.txt");
	std::cout << "\nPart 2:\n\n";
	std::getline(input, str);
	for (size_t i{}; i != str.size(); i++)
	{
		bool valid{ true };
		std::string marker{ str.substr(i, 14) };
		for (size_t j{}; j != marker.size(); j++)
		{
			int res{ (int)marker.find(marker[j], j + 1) };
			if (res > 0)
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			std::cout << i + 14 << '\n';
			break;
		}
	}
	input.close();

	return 0;
}