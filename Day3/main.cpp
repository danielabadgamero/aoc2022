#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int getItemTypePriority(char c)
{
	if (c < 'a')
		return static_cast<int>(c) - 38;
	else
		return static_cast<int>(c) - 96;
}

int getRepeatedItemPriority(std::string rucksack)
{
	for (int i{}; i != (int)rucksack.size() / 2; i++)
		for (int j{ (int)rucksack.size() / 2 }; j != rucksack.size(); j++)
			if (rucksack[i] == rucksack[j])
				return getItemTypePriority(rucksack[i]);
	return 0;
}

int getGroupBadgePriority(std::vector<std::string>* group)
{
	for (char c : group->at(0))
		for (char d : group->at(1))
			if (c == d)
				for (char e : group->at(2))
					if (d == e)
						return getItemTypePriority(c);
	return 0;
}

int main()
{
	std::ifstream input{ "input.txt" };

	std::cout << "Part 1:\n\n";
	int priorities{};
	while (!input.eof())
	{
		std::string rucksack{};
		std::getline(input, rucksack);
		priorities += getRepeatedItemPriority(rucksack);
	}
	std::cout << priorities << '\n';
	input.close();

	std::cout << "\nPart 2:\n\n";
	input.open("input.txt");
	priorities = 0;
	while (!input.eof())
	{
		std::vector<std::string> group(3);
		for (int i{}; i != 3; i++)
			std::getline(input, group.at(i));
		priorities += getGroupBadgePriority(&group);
	}
	std::cout << priorities << '\n';
	input.close();

	return 0;
}