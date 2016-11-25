#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const string MSA = "msa.txt";

int main()
{
	vector<string> sequence;
	string line, symbols="";
	ifstream input;
	int row_count = 0;

	input.open(MSA);

	if (input.fail())
	{
		cout << "Failed to open " << MSA << endl;
		return -1;
	}

	//Get each sequence and store it in vector. Also get unique symbols in a string.
	while (getline(input, line))
	{
		for (int i = 0; i < line.length(); i++)
		{
			if (symbols.find(line[i]) == string::npos && line[i] != '-')
			{
				symbols += line[i];
			}
		}
		sequence.push_back(line);
		row_count++;
	}

	//Column length
	int column_count = sequence[0].length();

	//Sort the symbols
	sort(symbols.begin(), symbols.end());

	//Check if column is match or insert state
	
	string match_state = "";
	string insert_state = "";

	for (int i = 0; i < column_count; i++)
	{	
		int gaps = 0;

		for (int j = 0; j < row_count; j++)
		{
			if (sequence[j][i] == '-')
			{
				gaps++;
			}
		}

		if (gaps > row_count/2)
		{
			insert_state += to_string(i+1) + ", ";
		}
		else
		{
			match_state += to_string(i+1) + ", ";
		}
		
	}

	insert_state.erase(insert_state.end()-2);
	match_state.erase(match_state.end() - 2);

	cout << "Columns corresponding to MATCH states: " << match_state << endl;
	cout << endl;
	cout << "Columns corresponding to INSERT states: " << insert_state << endl;
	cout << endl;
	
	//Calculation of emission probabilities
	vector<int> count(symbols.length(), 0);

	for (int i = 0; i < column_count; i++)
	{
		int gaps = 0;
		for (int j = 0; j < row_count; j++)
		{	
			if (sequence[j][i] == '-')
			{
				gaps++;
				continue;
			}
			for (int k = 0; k < symbols.length(); k++)
			{
				if (symbols[k] == sequence[j][i])
				{
					count[k]++;
					break;
				}
			}
		}

		if (gaps > row_count / 2)
		{
			continue;
		} 
		else {
			cout << "Column " << i << " : ";
			for (int k = 0; k < symbols.length(); k++)
			{
				int num = count[k] + 1;
				cout << "E(" <<symbols[k] <<") = " << num << " / " << (row_count - gaps) + symbols.length() << " ";
				if (k % 5 == 0 && k != 0)
				{
					cout << endl <<"\t";
				}
			}
		}
		cout << endl << endl;
		fill(count.begin(), count.end(), 0);
	}

	return 1;
}

/*
Output:

Columns corresponding to MATCH states: 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53

Columns corresponding to INSERT states: 5, 13, 27, 38, 54, 55

Column 0 : E(0) = 1 / 28 E(1) = 1 / 28 E(2) = 2 / 28 E(4) = 1 / 28 E(A) = 5 / 28 E(B) = 1 / 28
E(C) = 5 / 28 E(D) = 1 / 28 E(E) = 1 / 28 E(F) = 1 / 28 E(L) = 1 / 28
E(M) = 1 / 28 E(N) = 1 / 28 E(P) = 1 / 28 E(Q) = 1 / 28 E(R) = 1 / 28
E(S) = 1 / 28 E(T) = 1 / 28 E(Y) = 1 / 28

Column 1 : E(0) = 1 / 24 E(1) = 1 / 24 E(2) = 1 / 24 E(4) = 1 / 24 E(A) = 2 / 24 E(B) = 1 / 24
E(C) = 1 / 24 E(D) = 5 / 24 E(E) = 1 / 24 E(F) = 1 / 24 E(L) = 1 / 24
E(M) = 1 / 24 E(N) = 1 / 24 E(P) = 1 / 24 E(Q) = 1 / 24 E(R) = 1 / 24
E(S) = 1 / 24 E(T) = 1 / 24 E(Y) = 1 / 24

Column 2 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 3 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 2 / 29 E(B) = 10 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 5 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 5 / 27 E(B) = 7 / 27
E(C) = 1 / 27 E(D) = 1 / 27 E(E) = 1 / 27 E(F) = 1 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 2 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 6 : E(0) = 1 / 28 E(1) = 1 / 28 E(2) = 1 / 28 E(4) = 1 / 28 E(A) = 9 / 28 E(B) = 1 / 28
E(C) = 1 / 28 E(D) = 1 / 28 E(E) = 1 / 28 E(F) = 1 / 28 E(L) = 1 / 28
E(M) = 1 / 28 E(N) = 1 / 28 E(P) = 1 / 28 E(Q) = 1 / 28 E(R) = 2 / 28
E(S) = 1 / 28 E(T) = 1 / 28 E(Y) = 1 / 28

Column 7 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 1 / 25 E(B) = 2 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 6 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 8 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 2 / 27 E(B) = 1 / 27
E(C) = 8 / 27 E(D) = 1 / 27 E(E) = 1 / 27 E(F) = 1 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 1 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 9 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 1 / 27 E(B) = 1 / 27
E(C) = 1 / 27 E(D) = 8 / 27 E(E) = 1 / 27 E(F) = 2 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 1 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 10 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 5 / 25 E(B) = 3 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 11 : E(0) = 1 / 28 E(1) = 2 / 28 E(2) = 1 / 28 E(4) = 1 / 28 E(A) = 1 / 28 E(B) = 9 / 28
E(C) = 1 / 28 E(D) = 1 / 28 E(E) = 1 / 28 E(F) = 1 / 28 E(L) = 1 / 28
E(M) = 1 / 28 E(N) = 1 / 28 E(P) = 1 / 28 E(Q) = 1 / 28 E(R) = 1 / 28
E(S) = 1 / 28 E(T) = 1 / 28 E(Y) = 1 / 28

Column 13 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 2 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 14 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 7 / 25 E(B) = 1 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 15 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 11 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 16 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 17 : E(0) = 2 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 7 / 26 E(B) = 1 / 26
E(C) = 1 / 26 E(D) = 1 / 26 E(E) = 1 / 26 E(F) = 1 / 26 E(L) = 1 / 26
E(M) = 1 / 26 E(N) = 1 / 26 E(P) = 1 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 1 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 18 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 5 / 25 E(B) = 3 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 19 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 11 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 20 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 11 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 21 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 11 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 22 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 5 / 29 E(B) = 1 / 29
E(C) = 7 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 23 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 1 / 25 E(B) = 1 / 25
E(C) = 1 / 25 E(D) = 7 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 24 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 11 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 25 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 11 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 27 : E(0) = 1 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 6 / 26 E(B) = 1 / 26
E(C) = 6 / 26 E(D) = 1 / 26 E(E) = 1 / 26 E(F) = 2 / 26 E(L) = 1 / 26
E(M) = 1 / 26 E(N) = 1 / 26 E(P) = 1 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 1 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 28 : E(0) = 1 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 1 / 26 E(B) = 3 / 26
E(C) = 1 / 26 E(D) = 6 / 26 E(E) = 1 / 26 E(F) = 1 / 26 E(L) = 1 / 26
E(M) = 1 / 26 E(N) = 1 / 26 E(P) = 1 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 1 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 29 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 10 / 29 E(B) = 1 / 29
E(C) = 2 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 30 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 1 / 27 E(B) = 7 / 27
E(C) = 1 / 27 E(D) = 2 / 27 E(E) = 1 / 27 E(F) = 2 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 1 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 31 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 8 / 29 E(B) = 1 / 29
E(C) = 2 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 2 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 2 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 32 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 1 / 27 E(B) = 7 / 27
E(C) = 1 / 27 E(D) = 2 / 27 E(E) = 1 / 27 E(F) = 2 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 1 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 33 : E(0) = 1 / 27 E(1) = 1 / 27 E(2) = 1 / 27 E(4) = 1 / 27 E(A) = 6 / 27 E(B) = 1 / 27
E(C) = 4 / 27 E(D) = 1 / 27 E(E) = 1 / 27 E(F) = 1 / 27 E(L) = 1 / 27
E(M) = 1 / 27 E(N) = 1 / 27 E(P) = 1 / 27 E(Q) = 1 / 27 E(R) = 1 / 27
E(S) = 1 / 27 E(T) = 1 / 27 E(Y) = 1 / 27

Column 34 : E(0) = 1 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 1 / 26 E(B) = 2 / 26
E(C) = 1 / 26 E(D) = 4 / 26 E(E) = 1 / 26 E(F) = 1 / 26 E(L) = 2 / 26
E(M) = 1 / 26 E(N) = 2 / 26 E(P) = 2 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 1 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 35 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 5 / 25 E(B) = 3 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 36 : E(0) = 1 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 5 / 26 E(B) = 2 / 26
E(C) = 1 / 26 E(D) = 1 / 26 E(E) = 1 / 26 E(F) = 1 / 26 E(L) = 3 / 26
E(M) = 1 / 26 E(N) = 1 / 26 E(P) = 1 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 1 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 38 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 11 / 29 E(L) = 2 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 39 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 11 / 29 E(A) = 1 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 40 : E(0) = 1 / 24 E(1) = 1 / 24 E(2) = 1 / 24 E(4) = 1 / 24 E(A) = 1 / 24 E(B) = 2 / 24
E(C) = 1 / 24 E(D) = 1 / 24 E(E) = 1 / 24 E(F) = 1 / 24 E(L) = 2 / 24
E(M) = 2 / 24 E(N) = 3 / 24 E(P) = 1 / 24 E(Q) = 1 / 24 E(R) = 1 / 24
E(S) = 1 / 24 E(T) = 1 / 24 E(Y) = 1 / 24

Column 41 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 10 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 2 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 42 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 1 / 29 E(B) = 11 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 43 : E(0) = 1 / 28 E(1) = 1 / 28 E(2) = 1 / 28 E(4) = 1 / 28 E(A) = 9 / 28 E(B) = 1 / 28
E(C) = 1 / 28 E(D) = 1 / 28 E(E) = 1 / 28 E(F) = 1 / 28 E(L) = 1 / 28
E(M) = 2 / 28 E(N) = 1 / 28 E(P) = 1 / 28 E(Q) = 1 / 28 E(R) = 1 / 28
E(S) = 1 / 28 E(T) = 1 / 28 E(Y) = 1 / 28

Column 44 : E(0) = 1 / 26 E(1) = 1 / 26 E(2) = 1 / 26 E(4) = 1 / 26 E(A) = 1 / 26 E(B) = 1 / 26
E(C) = 1 / 26 E(D) = 1 / 26 E(E) = 1 / 26 E(F) = 4 / 26 E(L) = 1 / 26
E(M) = 1 / 26 E(N) = 1 / 26 E(P) = 1 / 26 E(Q) = 1 / 26 E(R) = 1 / 26
E(S) = 5 / 26 E(T) = 1 / 26 E(Y) = 1 / 26

Column 45 : E(0) = 1 / 28 E(1) = 1 / 28 E(2) = 1 / 28 E(4) = 1 / 28 E(A) = 2 / 28 E(B) = 9 / 28
E(C) = 1 / 28 E(D) = 1 / 28 E(E) = 1 / 28 E(F) = 1 / 28 E(L) = 1 / 28
E(M) = 1 / 28 E(N) = 1 / 28 E(P) = 1 / 28 E(Q) = 1 / 28 E(R) = 1 / 28
E(S) = 1 / 28 E(T) = 1 / 28 E(Y) = 1 / 28

Column 46 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 1 / 25 E(B) = 1 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 4 / 25 E(T) = 4 / 25 E(Y) = 1 / 25

Column 47 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 1 / 25 E(B) = 4 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 1 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 4 / 25

Column 48 : E(0) = 1 / 25 E(1) = 1 / 25 E(2) = 1 / 25 E(4) = 1 / 25 E(A) = 3 / 25 E(B) = 4 / 25
E(C) = 1 / 25 E(D) = 1 / 25 E(E) = 1 / 25 E(F) = 1 / 25 E(L) = 1 / 25
E(M) = 2 / 25 E(N) = 1 / 25 E(P) = 1 / 25 E(Q) = 1 / 25 E(R) = 1 / 25
E(S) = 1 / 25 E(T) = 1 / 25 E(Y) = 1 / 25

Column 49 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 50 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 51 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Column 52 : E(0) = 1 / 29 E(1) = 1 / 29 E(2) = 1 / 29 E(4) = 1 / 29 E(A) = 11 / 29 E(B) = 1 / 29
E(C) = 1 / 29 E(D) = 1 / 29 E(E) = 1 / 29 E(F) = 1 / 29 E(L) = 1 / 29
E(M) = 1 / 29 E(N) = 1 / 29 E(P) = 1 / 29 E(Q) = 1 / 29 E(R) = 1 / 29
E(S) = 1 / 29 E(T) = 1 / 29 E(Y) = 1 / 29

Press any key to continue . . .

*/