#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Tree
{
	int height{};
	bool visible{ false };
	int scenicScore{};
};

int checkVisibleTop(std::vector<std::vector<Tree>>* forest, int x, int y)
{
	int height{ forest->at(y).at(x).height };
	
	if (y > 0)
		for (int i{ y - 1 }; i >= 0; i--)
			if (height <= forest->at(i).at(x).height) return y - i;

	forest->at(y).at(x).visible = true;

	return y;
}

int checkVisibleBottom(std::vector<std::vector<Tree>>* forest, int x, int y)
{
	int height{ forest->at(y).at(x).height };
	
	if (y < forest->size() - 1)
		for (int i{ y + 1 }; i != forest->size(); i++)
			if (height <= forest->at(i).at(x).height) return i - y;


	forest->at(y).at(x).visible = true;

	return (int)forest->size() - (y + 1);
}

int checkVisibleLeft(std::vector<std::vector<Tree>>* forest, int x, int y)
{
	int height{ forest->at(y).at(x).height };
	
	if (x > 0)
		for (int i{ x - 1 }; i >= 0; i--)
			if (height <= forest->at(y).at(i).height) return x - i;

	forest->at(y).at(x).visible = true;

	return x;
}

int checkVisibleRight(std::vector<std::vector<Tree>>* forest, int x, int y)
{

	int height{ forest->at(y).at(x).height };
	
	if (x < forest->size() - 1)
		for (int i{ x + 1 }; i != forest->size(); i++)
			if (height <= forest->at(y).at(i).height) return i - x;

	forest->at(y).at(x).visible = true;

	return (int)forest->size() - (x + 1);
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	std::vector<std::vector<Tree>> forest{};
	std::cout << "Part 1:\n\n";
	while (!input.eof())
	{
		forest.push_back({});
		std::getline(input, line);
		for (char c : line)
			forest.back().push_back({ (int)c - 48 });
	}

	for (int y{}; y != forest.size(); y++)
		for (int x{}; x != forest.at(y).size(); x++)
		{
			int dTop{ checkVisibleTop(&forest, x, y) };
			int dBottom{ checkVisibleBottom(&forest, x, y) };
			int dLeft{ checkVisibleLeft(&forest, x, y) };
			int dRight{ checkVisibleRight(&forest, x, y) };
			forest.at(y).at(x).scenicScore = dTop * dBottom * dLeft * dRight;
		}

	int visibleCount{};
	for (std::vector<Tree> trees : forest)
		for (Tree tree : trees)
			if (tree.visible)
				visibleCount++;
	std::cout << visibleCount << '\n';

	std::cout << "\nPart 2:\n\n";
	int maxScore{};
	for (std::vector<Tree> trees : forest)
		for (Tree tree : trees)
			if (tree.scenicScore > maxScore)
				maxScore = tree.scenicScore;
	std::cout << maxScore << '\n';

	return 0;
}