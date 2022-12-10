#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void addIfCycleIncluded(int cycle, int X, int* totalStrength)
{
	switch (cycle)
	{
	case 20: case 60: case 100: case 140: case 180: case 220:
		*totalStrength += cycle * X;
	}
}

void updateSpritePos(std::vector<bool>* spritePos, int X)
{
	for (int i{}; i != spritePos->size(); i++)
		if (i == X - 1 || i == X || i == X + 1)
			spritePos->at(i) = true;
		else
			spritePos->at(i) = false;
}

void drawPixel(std::vector<bool>* spritePos, int cycle)
{
	if (cycle % 40 == 0)
		std::cout << '\n';
	if (spritePos->at((cycle - 1) % 40))
		std::cout << '#';
	else
		std::cout << '.';
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::cout << "Part 1:\n\n";

	int cycle{ 1 };
	int X{ 1 };
	std::string command{};
	int totalStrength{};

	while (!input.eof())
	{
		addIfCycleIncluded(cycle, X, &totalStrength);

		std::getline(input, command);

		int i{ (int)command.find(' ') };
		if (i >= 0)
		{
			cycle++;
			addIfCycleIncluded(cycle, X, &totalStrength);
			X += std::stoi(command.substr(i));
		}

		cycle++;
	}
	std::cout << totalStrength << '\n';
	input.close();
	
	input.open("input.txt");
	std::cout << "\nPart 2:\n\n";

	cycle = 1;
	command.clear();
	X = 1;
	std::vector<bool> spritePos(40);
	std::vector<bool> CRTRow(240);

	while (!input.eof())
	{
		updateSpritePos(&spritePos, X);
		drawPixel(&spritePos, cycle);

		std::getline(input, command);

		int i{ (int)command.find(' ') };
		if (i >= 0)
		{
			cycle++;
			drawPixel(&spritePos, cycle);
			X += std::stoi(command.substr(i));
		}
		cycle++;
	}

	return 0;
}