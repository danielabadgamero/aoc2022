#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

struct Rope
{
	struct Knot
	{
		int x{};
		int y{};

		bool operator== (Knot B)
		{
			return ((x == B.x) && (y == B.y));
		}
	};

	struct Head
	{
		int x{};
		int y{};
	};

	Head head{};
	std::vector<Knot> knots{};
};

void moveHead(Rope::Head* head, char direction)
{
	switch (direction)
	{
	case 'U':
		head->y++;
		return;
	case 'R':
		head->x++;
		return;
	case 'D':
		head->y--;
		return;
	case 'L':
		head->x--;
		return;
	}
}

bool moveKnot(std::vector<Rope::Knot>* tailHistory, Rope::Knot* knot, int x, int y, int knotIndex, int tailIndex)
{
	int distance{ (int)std::sqrt(std::pow(knot->x - x, 2) + std::pow(knot->y - y, 2))};
	if (distance > 1)
	{
		if (knot->x < x)
			knot->x++;
		else if (knot->x > x)
			knot->x--;

		if (knot->y < y)
			knot->y++;
		else if (knot->y > y)
			knot->y--;
	}
	if (knotIndex == tailIndex)
	{
		bool exists{ false };
		for (int i{}; i != tailHistory->size(); i++)
			if (*knot == tailHistory->at(i))
			{
				exists = true;
				break;
			}
		if (!exists)
			tailHistory->push_back(*knot);
	}
	return (distance > 1);
}

int main()
{
	std::ifstream input{ "input.txt" };
	Rope rope{};
	rope.knots.resize(1);
	std::cout << "Part 1:\n\n";
	std::vector<Rope::Knot> tailHistory{};
	while (!input.eof())
	{
		char direction{};
		int steps{};
		input >> direction;
		input >> steps;

		for (int i{}; i != steps; i++)
		{
			moveHead(&rope.head, direction);
			moveKnot(&tailHistory, &rope.knots.at(0), rope.head.x, rope.head.y, 0, 0);
		}
	}
	std::cout << tailHistory.size() << '\n';
	input.close();

	input.open("input.txt");
	std::cout << "\nPart 2:\n\n";
	tailHistory.clear();
	rope.knots.clear();
	rope.head = { 0, 0 };
	rope.knots.resize(9);
	int line{};
	while (!input.eof())
	{
		char direction{};
		int steps{};
		input >> direction;
		input >> steps;
		line++;
		for (int i{}; i != steps; i++)
		{
			moveHead(&rope.head, direction);
			for (int j{}; j != (int)rope.knots.size(); j++)
			{
				if (j == 0)
				{
					if (!moveKnot(&tailHistory, &rope.knots.at(j), rope.head.x, rope.head.y, j, 8))
						break;
				}
				else
					if (!moveKnot(&tailHistory, &rope.knots.at(j), rope.knots.at(j - 1).x, rope.knots.at(j - 1).y, j, 8))
						break;
			}
		}
	}
	std::cout << tailHistory.size() << '\n';

	return 0;
}