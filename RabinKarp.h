#pragma once
using namespace std;

void createBaseList(int w, int h, string* dataHeight, string* dataWidth, long long*& baseList, long long**& hashHeight, long long **& hashWidth) {
	const long long MOD = 1e9 + 7;
	baseList = new long long[max(w, h)+1];

	baseList[0] = 1;
	for (int i = 1; i <= max(w, h); i++) baseList[i] = (baseList[i - 1] * 256) % MOD;

	//creata hash table height
	hashHeight = new long long*[w];
	for (int i = 0; i < w; i++) hashHeight[i] = new long long[dataHeight[i].length()];
	for (int i = 0; i < w; i++) {
		hashHeight[i][0] = 0;
		for (int j = 1; j < dataHeight[i].length(); j++) hashHeight[i][j] = (hashHeight[i][j - 1] * 256 + int(dataHeight[i][j])) % MOD;
	}

	//create hash table width
	hashWidth = new long long* [h];
	for (int i = 0; i < h; i++) hashWidth[i] = new long long[dataWidth[i].length()];
	for (int i = 0; i < h; i++) {
		hashWidth[i][0] = 0;
		for (int j = 1; j < dataWidth[i].length(); j++) hashWidth[i][j] = (hashWidth[i][j - 1] * 256 + int(dataWidth[i][j])) % MOD;
	}
}

long long getHash(string valueString) {
	const long long MOD = 1e9 + 7;
	long long hashValue = 0;
	for (int i = 1; i < valueString.length(); i++) hashValue = (hashValue * 256 + int(valueString[i])) % MOD;

	return hashValue;
}

int getKabinKarpPosSolve(int lengthDataString, long long* hashData, string findString, long long hashFindString, long long* baseList) {
	const long long MOD = 1e9 + 7;
	for (int i = 1; i <= lengthDataString - findString.length() + 1; i++) {
		int posEndFindString = i + findString.length() - 2;
		long long valueHashFromIToEnd = (hashData[posEndFindString] - (hashData[i - 1] * baseList[posEndFindString - i + 1]) + MOD*MOD) % MOD;
		
		if (hashFindString == valueHashFromIToEnd) return i;
	}

	return 0;
}

Point getKabinKarpPointValue(int w, int h, long long** hashHeight, long long** hashWidth, long long* baseList, string valueString) {
	Point solve;
	solve.value = valueString;
	solve.x = 0;
	solve.y = 0;
	solve.direct = "NF";

	long long hashFindString = getHash(valueString);
	for (int i = 0; i < w; i++) {
		int pos = getKabinKarpPosSolve(h + 1, hashHeight[i], valueString, hashFindString, baseList);
		if (pos != 0) {
			solve.x = pos;
			solve.y = i + 1;
			solve.direct = "TD";
			return solve;
		}
	}

	for (int i = 0; i < h; i++) {
		int pos = getKabinKarpPosSolve(w + 1, hashWidth[i], valueString, hashFindString, baseList);
		if (pos != 0) {
			solve.x = i + 1;
			solve.y = pos;
			solve.direct = "LR";
			return solve;
		}
	}
	return solve;
}

void KabinKarp(int w, int h, string* dataHeight, string* dataWidth, vector <string> stringList) {
	vector <Point> solveOfStringList;
	long long* baseList;
	long long** hashHeight;
	long long** hashWidth;
	createBaseList(w, h, dataHeight, dataWidth, baseList, hashHeight, hashWidth);

	int count = 0;
	for (int i = 0; i < stringList.size(); i++) {
		string temp = " " + stringList[i];
		Point solve = getKabinKarpPointValue(w, h, hashHeight, hashWidth, baseList, temp);
		solve.value = stringList[i];
		if (solve.x != 0 || solve.y != 0) count++;
		solveOfStringList.push_back(solve);
	}

	printSolve(count, solveOfStringList);
}