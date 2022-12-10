#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};

	std::cout << "Part 1:\n\n";
	int currentInv{};
	int maxInv{};

	while (!input.eof())
	{
		std::getline(input, line);
		if (!line.empty())
			currentInv += std::stoi(line);
		else
		{
			if (currentInv > maxInv)
				maxInv = currentInv;
			currentInv = 0;
		}
	}
	std::cout << maxInv << '\n';
	input.close();


	std::cout << "\nPart 2:\n\n";
	input.open("input.txt");
	std::vector<int> inventories{ 0 };
	
	while (!input.eof())
	{
		std::getline(input, line);
		if (!line.empty())
			inventories.back() += std::stoi(line);
		else
			inventories.push_back(0);
	}
	std::sort(inventories.rbegin(), inventories.rend());
	std::cout << inventories[0] + inventories[1] + inventories[2] << '\n';
	input.close();

	return 0;
}