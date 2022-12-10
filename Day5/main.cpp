#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

std::stack<char> reverseStack(std::stack<char>* stack)
{
	std::stack<char> newStack{};
	while (stack->size() > 0)
	{
		newStack.push(stack->top());
		stack->pop();
	}
	return newStack;
}

struct Action
{
	int origin{};
	int destination{};
	int count{};
};

Action parseAction(std::string line)
{
	Action action{};
	
	size_t moveStart{ line.find("e ") + 2 };
	size_t moveEnd{ line.find(" f") - 1 };
	action.count = std::stoi(line.substr(moveStart, moveEnd));

	size_t fromStart{ line.find("m ") + 2 };
	size_t fromEnd{ line.find(" t") - 1 };
	action.origin = std::stoi(line.substr(fromStart, fromEnd));

	size_t toStart{ line.find("o ") + 2 };
	size_t toEnd{ line.size() - 1 };
	action.destination = std::stoi(line.substr(toStart, toEnd));

	return action;
}

struct Instructions
{
	std::vector<std::stack<char>> stacks{};
	std::vector<Action> actions{};
};

Instructions parseInput(std::ifstream* input)
{
	std::vector<std::stack<char>> stacks(9);
	std::vector<Action> actions{};
	bool readingStacks{ true };
	int targetStack{};
	std::stack<bool> whitespaces{};
	while (!input->eof())
	{
		std::string line{};
		if (readingStacks)
		{
			std::getline(*input, line, ' ');
			if (line.empty())
			{
				whitespaces.push(true);
				if (whitespaces.size() == 4)
				{
					targetStack++;
					while (whitespaces.size() > 0)
						whitespaces.pop();
				}
			}
			else if (line == "\n")
			{
				targetStack = 0;
				while (whitespaces.size() > 1)
					whitespaces.pop();
			}
			else if (line == "1")
			{
				readingStacks = false;
				for (size_t i{}; i != stacks.size(); i++)
					stacks[i] = reverseStack(&stacks[i]);
				continue;
			}
			else
			{
				std::erase(line, '[');
				std::erase(line, ']');

				int newLine{ static_cast<int>(line.find('\n')) };
				if (newLine > 0)
				{
					stacks[targetStack].push(line[0]);
					targetStack = 0;
					if (line.size() == 3)
					{
						stacks[targetStack].push(line[2]);
						targetStack++;
					}
					whitespaces.push(true);
					continue;
				}
				else
				{
					stacks[targetStack].push(line[0]);
				}

				targetStack++;
			}
		}
		else
		{
			std::getline(*input, line);
			if (line == "  2   3   4   5   6   7   8   9 " || line.empty())
				continue;
			else
				actions.push_back(parseAction(line));
		}
	}

	return { stacks, actions };
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::cout << "Part 1:\n\n";
	Instructions instructions{ parseInput(&input) };

	for (size_t i{}; i != instructions.actions.size(); i++)
		while (instructions.actions[i].count > 0)
		{
			instructions.actions[i].count--;
			instructions.stacks[instructions.actions[i].destination - 1].push(instructions.stacks[instructions.actions[i].origin - 1].top());
			instructions.stacks[instructions.actions[i].origin - 1].pop();
		}

	for (std::stack<char> stack : instructions.stacks)
		std::cout << stack.top();
	std::cout << '\n';
	input.close();

	input.open("input.txt");
	std::cout << "\nPart 2:\n\n";
	instructions = parseInput(&input);

	for (Action action : instructions.actions)
	{
		std::stack<char> tempStack{};
		for (int i{}; i != action.count; i++)
		{
			tempStack.push(instructions.stacks[action.origin - 1].top());
			instructions.stacks[action.origin - 1].pop();
		}
		for (int i{}; i != action.count; i++)
		{
			instructions.stacks[action.destination - 1].push(tempStack.top());
			tempStack.pop();
		}
	}
	for (std::stack<char> stack : instructions.stacks)
		std::cout << stack.top();
	std::cout << '\n';

	input.close();

	return 0;
}