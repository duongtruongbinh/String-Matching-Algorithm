#pragma once
using namespace std;

struct Point
{
	string value;
	int x, y;
	string direct;
};

vector<string> readData(string fileName, int &w, int &h, char **&arr)
{
	vector<string> str;
	fstream readFile(fileName, ios::in);
	if (!readFile.is_open())
	{
		cout << "Don't open file" << endl;
		return str;
	}

	readFile >> w >> h;
	arr = new char *[h];
	for (int i = 0; i < h; i++)
		arr[i] = new char[w];

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			readFile >> arr[i][j];

	string temp;
	getline(readFile, temp);
	while (!readFile.eof())
	{
		getline(readFile, temp);
		if (temp == "#")
			break;

		str.push_back(temp);
	}
	readFile.close();
	return str;
}

void getDataHeight(char **dataTable, int w, int h, string *dataHeight)
{
	for (int i = 0; i < w; i++)
	{
		string getStringHeight = " ";
		for (int j = 0; j < h; j++)
			getStringHeight = getStringHeight + dataTable[j][i];
		dataHeight[i] = getStringHeight;
	}
}

void getDataWidth(char **dataTable, int w, int h, string *dataWidth)
{
	for (int i = 0; i < h; i++)
	{
		string getStringWidth = " ";
		for (int j = 0; j < w; j++)
			getStringWidth = getStringWidth + dataTable[i][j];
		dataWidth[i] = getStringWidth;
	}
}

void printSolve(int count, vector<Point> solveOfStringList)
{
	cout << count << endl;
	for (int i = 0; i < solveOfStringList.size(); i++)
	{
		cout << solveOfStringList[i].value
			 << " (" << solveOfStringList[i].x
			 << "," << solveOfStringList[i].y
			 << ") " << solveOfStringList[i].direct;
		if (i < solveOfStringList.size() - 1)
			cout << endl;
	}
}