#include <iostream>
#include <fstream>

enum class Shape
{
	rock = 1,
	paper = 2,
	scissors = 3
};

enum class Outcome
{
	lost = 0,
	draw = 3,
	won = 6
};

struct ShapePair
{
	Shape opponent{};
	Shape player{};
};

Outcome calculateOutcome(ShapePair pair)
{
	if (pair.opponent == pair.player && (int)pair.opponent != 0)
		return Outcome::draw;
	bool won{};
	switch (pair.opponent)
	{
	case Shape::rock:
		won = (pair.player == Shape::paper);
		break;
	case Shape::paper:
		won = (pair.player == Shape::scissors);
		break;
	case Shape::scissors:
		won = (pair.player == Shape::rock);
		break;
	}
	if (won)
		return Outcome::won;
	else
		return Outcome::lost;
}

Shape chooseShape(Shape opponent, Outcome outcome)
{
	switch (outcome)
	{
	case Outcome::draw:
		return opponent;
	case Outcome::won:
		switch (opponent)
		{
		case Shape::rock:
			return Shape::paper;
		case Shape::paper:
			return Shape::scissors;
		case Shape::scissors:
			return Shape::rock;
		}
	case Outcome::lost:
		switch (opponent)
		{
		case Shape::rock:
			return Shape::scissors;
		case Shape::paper:
			return Shape::rock;
		case Shape::scissors:
			return Shape::paper;
		}
	}
	return (Shape)0;
}

int main()
{
	std::ifstream input{ "input.txt" };
	
	std::cout << "Part 1:\n\n";
	int score{};

	while (!input.eof())
	{
		ShapePair shapePair{};
		char c{};
		input >> c;
		switch (c)
		{
		case 'A':
			shapePair.opponent = Shape::rock;
			break;
		case 'B':
			shapePair.opponent = Shape::paper;
			break;
		case 'C':
			shapePair.opponent = Shape::scissors;
			break;
		}
		input >> c;
		switch (c)
		{
		case 'X':
			shapePair.player = Shape::rock;
			break;
		case 'Y':
			shapePair.player = Shape::paper;
			break;
		case 'Z':
			shapePair.player = Shape::scissors;
			break;
		}
		score += (int)shapePair.player;
		score += (int)calculateOutcome(shapePair);
	}
	std::cout << score << '\n';
	input.close();

	std::cout << "\nPart 2:\n\n";
	input.open("input.txt");
	score = 0;

	while (!input.eof())
	{
		Shape opponentShape{};
		Outcome desiredOutcome{};
		char c{};
		input >> c;
		switch (c)
		{
		case 'A':
			opponentShape = Shape::rock;
			break;
		case 'B':
			opponentShape = Shape::paper;
			break;
		case 'C':
			opponentShape = Shape::scissors;
			break;
		}
		input >> c;
		switch (c)
		{
		case 'X':
			desiredOutcome = Outcome::lost;
			break;
		case 'Y':
			desiredOutcome = Outcome::draw;
			break;
		case 'Z':
			desiredOutcome = Outcome::won;
			break;
		}
		score += (int)desiredOutcome;
		score += (int)chooseShape(opponentShape, desiredOutcome);
	}
	std::cout << score << '\n';
	input.close();

	return 0;
}