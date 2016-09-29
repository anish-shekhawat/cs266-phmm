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
				cout << num << " / " << (row_count - gaps) + symbols.length() << " - ";
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

Column 0 : 1 / 28 - 1 / 28 - 2 / 28 - 1 / 28 - 5 / 28 - 1 / 28 - 5 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 -

Column 1 : 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 2 / 24 - 1 / 24 - 1 / 24 - 5 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 -

Column 2 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 3 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 2 / 29 - 10 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 5 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 5 / 27 - 7 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 6 : 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 9 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 2 / 28 - 1 / 28 - 1 / 28 - 1 / 28 -

Column 7 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 2 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 6 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 8 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 8 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 9 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 8 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 10 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 5 / 25 - 3 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 11 : 1 / 28 - 2 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 9 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 -

Column 13 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 14 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 7 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 15 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 16 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 17 : 2 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 7 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 -

Column 18 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 5 / 25 - 3 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 19 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 20 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 21 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 22 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 5 / 29 - 1 / 29 - 7 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 23 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 7 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 24 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 25 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 27 : 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 6 / 26 - 1 / 26 - 6 / 26 - 1 / 26 - 1 / 26 - 2 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 -

Column 28 : 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 3 / 26 - 1 / 26 - 6 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 -

Column 29 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 10 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 30 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 7 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 31 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 8 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 32 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 7 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 2 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 33 : 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 6 / 27 - 1 / 27 - 4 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 - 1 / 27 -

Column 34 : 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 2 / 26 - 1 / 26 - 4 / 26 - 1 / 26 - 1 / 26 - 2 / 26 - 1 / 26 - 2 / 26 - 2 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 -

Column 35 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 5 / 25 - 3 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 36 : 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 5 / 26 - 2 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 3 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 -

Column 38 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 39 : 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 40 : 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 2 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 2 / 24 - 2 / 24 - 3 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 - 1 / 24 -

Column 41 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 10 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 2 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 42 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 43 : 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 9 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 2 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 -

Column 44 : 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 4 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 1 / 26 - 5 / 26 - 1 / 26 - 1 / 26 -

Column 45 : 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 2 / 28 - 9 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 - 1 / 28 -

Column 46 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 4 / 25 - 4 / 25 - 1 / 25 -

Column 47 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 4 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 4 / 25 -

Column 48 : 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 3 / 25 - 4 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 2 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 - 1 / 25 -

Column 49 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 50 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 51 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Column 52 : 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 11 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 - 1 / 29 -

Press any key to continue . . .

*/