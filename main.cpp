#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "base.h"
#include "BruteForce.h"
#include "RabinKarp.h"
#include "KnuthMorrisPratt.h"
using namespace std;

int main() {
	int w, h;
	char** dataTable;
	vector <string> stringList;

	stringList = readData("input.txt", w, h, dataTable);
	//array data up to down
	string* dataHeight = new string[w];
	getDataHeight(dataTable, w, h, dataHeight);

	//array data left to right
	string* dataWidth = new string[h];
	getDataWidth(dataTable, w, h, dataWidth);

	//Algorithm Brute-Force
	//BruteForce(w, h, dataHeight, dataWidth, stringList);
	//Algorithm Rabin-Karp
	KabinKarp(w, h, dataHeight, dataWidth, stringList);
	//Algorithm Knuth-Morris-Pratt
	//KnuthMorrisPratt(w, h, dataHeight, dataWidth, stringList);

	return 0;
}