#include <iostream>
#include <fstream>
#include <string>

struct SectionRange
{
	int start{};
	int end{};
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::cout << "Part 1:\n\n";
	int pairCount{};
	while (!input.eof())
	{
		SectionRange assignment1{};
		SectionRange assignment2{};
		std::string str{};

		std::getline(input, str, '-');
		assignment1.start = std::stoi(str);
		std::getline(input, str, ',');
		assignment1.end = std::stoi(str);
		std::getline(input, str, '-');
		assignment2.start = std::stoi(str);
		std::getline(input, str);
		assignment2.end = std::stoi(str);

		bool added{ false };
		if (assignment1.start <= assignment2.start)
			if (assignment1.end >= assignment2.end)
			{
				pairCount++;
				added = true;
			}
		if (!added && assignment1.start >= assignment2.start)
			if (assignment1.end <= assignment2.end)
				pairCount++;
	}
	std::cout << pairCount << '\n';
	input.close();
	input.open("input.txt");
	std::cout << "\nPart 2:\n\n";
	pairCount = 0;
	while (!input.eof())
	{
		SectionRange range1{};
		SectionRange range2{};
		std::string str{};

		std::getline(input, str, '-');
		range1.start = std::stoi(str);
		std::getline(input, str, ',');
		range1.end = std::stoi(str);
		std::getline(input, str, '-');
		range2.start = std::stoi(str);
		std::getline(input, str);
		range2.end = std::stoi(str);

		if (range1.end >= range2.start && range1.start <= range2.end)
			pairCount++;
	}
	std::cout << pairCount << '\n';

	return 0;
}