#pragma once
using namespace std;

int *getPrefix(string stringValue)
{
	int stringLength = stringValue.length();
	int *prefixList = new int[stringLength];
	int k = 0;
	prefixList[0] = 0;
	prefixList[1] = 0;
	for (int i = 2; i < stringLength; i++)
	{
		while (k > 0 && stringValue[k + 1] != stringValue[i])
			k = prefixList[k];
		if (stringValue[k + 1] == stringValue[i])
			k++;

		prefixList[i] = k;
	}
	return prefixList;
}

// String numbered from 1 to length() - 1
int getKnuthMorrisPrattPosSolve(string dataString, string findString, int *prefixList)
{
	if (findString.length() > dataString.length())
		return 0;

	int pos = 1;
	int length = 0;
	int stringLength = findString.length() - 1;

	// enough char
	while (pos + stringLength - 1 <= dataString.length() - 1)
	{
		while (length < stringLength && findString[length + 1] == dataString[pos + length])
			length = length + 1;
		if (length == stringLength)
			return pos;

		if (length == 0)
			pos++;
		else
		{
			pos = pos + length - prefixList[length];
			length = prefixList[length];
		}
	}

	return 0;
}

Point getKnuthMorrisPrattPointValue(int w, int h, string *dataHeight, string *dataWidth, string valueString)
{
	int *prefixList = getPrefix(valueString);

	Point solve;
	solve.value = valueString;
	solve.x = 0;
	solve.y = 0;
	solve.direct = "NF";

	for (int i = 0; i < w; i++)
	{
		int pos = getKnuthMorrisPrattPosSolve(dataHeight[i], valueString, prefixList);
		if (pos != 0)
		{
			solve.x = pos;
			solve.y = i + 1;
			solve.direct = "TD";
			return solve;
		}
	}

	for (int i = 0; i < h; i++)
	{
		int pos = getKnuthMorrisPrattPosSolve(dataWidth[i], valueString, prefixList);
		if (pos != 0)
		{
			solve.x = i + 1;
			solve.y = pos;
			solve.direct = "LR";
			return solve;
		}
	}

	delete[] prefixList;
	return solve;
}

void KnuthMorrisPratt(int w, int h, string *dataHeight, string *dataWidth, vector<string> stringList)
{
	vector<Point> solveOfStringList;
	int count = 0;
	for (int i = 0; i < stringList.size(); i++)
	{
		string temp = " " + stringList[i];

		Point solve = getKnuthMorrisPrattPointValue(w, h, dataHeight, dataWidth, temp);
		solve.value = stringList[i];
		if (solve.x != 0 || solve.y != 0)
			count++;
		solveOfStringList.push_back(solve);
	}

	printSolve(count, solveOfStringList);
}