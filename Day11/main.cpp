#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

enum Operation
{
	addition,
	multiplication
};

class Monkey
{
private:
	std::list<long long int> items{};
	Operation operation{};
	long long int factor{};
	long long int testDivisible{};
	int destinationMonkey[2]{};
	long long int inspectedItems{};

public:
	long long int getTestDiv()
	{
		return testDivisible;
	}

	Monkey(std::string startingItemsStr, std::string operationStr, std::string testStr, std::string trueStr, std::string falseStr)
	{
		std::string nums{ startingItemsStr.substr(18) };
		std::string op{ operationStr.substr(23) };
		std::string test{ testStr.substr(21) };
		std::string destTrue{ trueStr.substr(29) };
		std::string destFalse{ falseStr.substr(30) };

		for (int i{}; i < nums.size() - 1; i += 2)
			if (nums.at(i) != ',')
				items.push_back(static_cast<long long>(std::stol(nums.substr(i, 2))));
		operation = static_cast<Operation>(op.at(0) == '*');
		if (op.substr(2).at(0) == 'o')
			factor = -1;
		else
			factor = std::stol(op.substr(2));
		testDivisible = std::stol(test);
		destinationMonkey[true] = std::stoi(destTrue);
		destinationMonkey[false] = std::stoi(destFalse);
	}

	long long int getNumItems()
	{
		return static_cast<long long int>(items.size());
	}

	bool inspectItem(bool divide)
	{
		switch (operation)
		{
		case addition:
			items.front() += factor;
			break;
		case multiplication:
			if (factor == -1)
				items.front() *= items.front();
			else
				items.front() *= factor;
			break;
		}
		if (divide)
			items.front() /= 3;
		return (items.front() % testDivisible == 0);
	}

	long long int getInspectedItems()
	{
		return inspectedItems;
	}

	void addItem(long long int item)
	{
		items.push_back(item);
	}

	void throwItem(bool dest, std::vector<Monkey>* monkies)
	{
		int reduceWorryLevel{ 1 };
		for (int i{}; i != monkies->size(); i++)
			reduceWorryLevel *= (int)monkies->at(i).getTestDiv();
		items.front() %= reduceWorryLevel;
		monkies->at(destinationMonkey[dest]).addItem(items.front());
		items.pop_front();
	}

	void addInspectedItems(long long int n)
	{
		inspectedItems += n;
	}
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::vector<Monkey> monkies{};
	
	std::cout << "\nPart 1:\n\n";
	while (!input.eof())
	{
		std::vector<std::string> lines(1);
		std::getline(input, lines[0]);
		while (!lines.back().empty())
		{
			lines.push_back("");
			std::getline(input, lines.back());
		}
		monkies.push_back({ lines[1], lines[2], lines[3], lines[4], lines[5] });
	}
	input.close();

	for (int round{}; round != 20; round++)
		for (Monkey& monkey : monkies)
		{
			monkey.addInspectedItems(monkey.getNumItems());
			while (monkey.getNumItems() > 0)
				monkey.throwItem(monkey.inspectItem(true), &monkies);
		}
	std::vector<long long int> inspectedItems{};
	for (Monkey monkey : monkies)
		inspectedItems.push_back(monkey.getInspectedItems());
	std::sort(inspectedItems.rbegin(), inspectedItems.rend());
	std::cout << inspectedItems[0] * inspectedItems[1] << '\n';

	std::cout << "\nPart 2:\n\n";
	monkies.clear();
	inspectedItems.clear();
	input.open("input.txt");
	while (!input.eof())
	{
		std::vector<std::string> lines(1);
		std::getline(input, lines[0]);
		while (!lines.back().empty())
		{
			lines.push_back("");
			std::getline(input, lines.back());
		}
		monkies.push_back({ lines[1], lines[2], lines[3], lines[4], lines[5] });
	}
	input.close();

	for (int round{}; round != 10000; round++)
		for (Monkey& monkey : monkies)
		{
			monkey.addInspectedItems(monkey.getNumItems());
			while (monkey.getNumItems() > 0)
				monkey.throwItem(monkey.inspectItem(false), &monkies);
		}
	for (Monkey monkey : monkies)
		inspectedItems.push_back(monkey.getInspectedItems());

	std::sort(inspectedItems.rbegin(), inspectedItems.rend());
	std::cout << inspectedItems[0] * inspectedItems[1] << '\n';

	return 0;
}