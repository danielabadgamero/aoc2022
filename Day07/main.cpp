#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct File
{
	std::string name{};
	int size{};
};

struct Dir
{
	std::string name{};
	int size{};
	std::vector<File> content_files{};
	std::vector<Dir> content_dirs{};

	Dir* searchDir(std::string targetName, bool checkNested = false)
	{
		for (size_t i{}; i != content_dirs.size(); i++)
		{
			if (content_dirs[i].name == targetName)
				return &content_dirs[i];
			if (checkNested)
			{
				Dir* nestedDir{ content_dirs[i].searchDir(targetName, true) };
				if (nestedDir != nullptr)
					return nestedDir;
			}
		}
		return nullptr;
	}
};

void findSmallDirs(Dir* currentDir, int* totalSize)
{
	for (int i{}; i != currentDir->content_dirs.size(); i++)
	{
		if (currentDir->content_dirs[i].size <= 100000)
			*totalSize += currentDir->content_dirs[i].size;
		findSmallDirs(&currentDir->content_dirs.at(i), totalSize);
	}
}

int findSmallestDir(Dir* currentDir, const int minSize, int smallestSizeSoFar)
{
	int smallest{ smallestSizeSoFar };
	for (int i{}; i != currentDir->content_dirs.size(); i++)
	{
		if (currentDir->content_dirs[i].size >= minSize)
		{
			if (currentDir->content_dirs[i].size < smallest)
				smallest = currentDir->content_dirs[i].size;
			smallest = findSmallestDir(&currentDir->content_dirs[i], minSize, smallest);
		}
	}

	return smallest;
}

void parseFilesystem(std::ifstream* input, Dir* filesystem)
{
	Dir* currentDir{ filesystem };
	std::vector<Dir*> dirPath{};

	while (!input->eof())
	{
		std::string buf{};
		std::getline(*input, buf);
		std::string str{};
		switch (buf[0])
		{
		case '$':
			str = buf.substr(2, 2);
			if (str == "cd")
			{
				std::string dir{ buf.substr(5) };
				if (dir != "..")
				{
					currentDir = currentDir->searchDir(dir);
					if (currentDir == nullptr)
						currentDir = filesystem;
					dirPath.push_back(currentDir);
				}
				else
				{
					dirPath.pop_back();
					currentDir = dirPath.back();
				}
			}
			break;
		case 'd':
			str = buf.substr(4);
			currentDir->content_dirs.push_back({ str });
			break;
		default:
			std::string num{};
			currentDir->content_files.push_back({});
			for (char c : buf)
				if (c <= 57)
					num += c;
				else
					currentDir->content_files.back().name += c;
			currentDir->content_files.back().size = std::stoi(num);
			for (Dir* dir : dirPath)
				dir->size += std::stoi(num);
		}
	}
}

int main()
{
	std::ifstream input{ "input.txt" };
	Dir filesystem{ "/" };
	int totalSize{};
	parseFilesystem(&input, &filesystem);

	findSmallDirs(&filesystem, &totalSize);
	std::cout << totalSize << '\n';
	input.close();

	input.open("input.txt");
	filesystem.size = 0;
	filesystem.content_dirs.clear();
	filesystem.content_files.clear();
	std::cout << "\nPart 2:\n\n";
	parseFilesystem(&input, &filesystem);
	int unusedSpace{ 70000000 - filesystem.size };
	int spaceToFreeUp{ 30000000 - unusedSpace };

	std::cout << findSmallestDir(&filesystem, spaceToFreeUp, filesystem.size) << '\n';

	return 0;
}