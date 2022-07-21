#pragma once
using namespace std;

int getBruteForcePosSolve(string dataString, string findString) {
	for (int i = 1; i <= dataString.length() - findString.length() + 1; i++) {
		bool isTrue = true;
		for (int j = 1; j < findString.length(); j++) {
			if (findString[j] != dataString[i + j - 1]) {
				isTrue = false;
				break;
			}
		}

		if (isTrue) return i;
	}

	return 0;
}

Point getBruteForcePointValue(int w, int h, string* dataHeight, string* dataWidth, string valueString) {
	Point solve;
	solve.value = valueString;
	solve.x = 0;
	solve.y = 0;
	solve.direct = "NF";

	for (int i = 0; i < w; i++) {
		int pos = getBruteForcePosSolve(dataHeight[i], valueString);
		if (pos != 0) {
			solve.x = pos;
			solve.y = i + 1;
			solve.direct = "TD";
			return solve;
		}
	}

	for (int i = 0; i < h; i++) {
		int pos = getBruteForcePosSolve(dataWidth[i], valueString);
		if (pos != 0) {
			solve.x = i + 1;
			solve.y = pos;
			solve.direct = "LR";
			return solve;
		}
	}
	return solve;
}

void BruteForce(int w, int h, string* dataHeight, string* dataWidth, vector <string> stringList) {
	vector <Point> solveOfStringList;
	int count = 0;
	for (int i = 0; i < stringList.size(); i++) {
		string temp = " " + stringList[i];
		Point solve = getBruteForcePointValue(w, h, dataHeight, dataWidth, temp);
		solve.value = stringList[i];
		if (solve.x != 0 || solve.y != 0) count++;
		solveOfStringList.push_back(solve);
	}

	printSolve(count, solveOfStringList);
}