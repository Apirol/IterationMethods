#pragma once
#include <iostream>
#include <fstream>
#include <vector>

typedef double real;

using namespace std;

class InputSLAEHandler 
{

private:
	string fileNameSize;
	string fileNameI;
	string fileNameA;
	string fileNameB;

public:
	InputSLAEHandler(string fileNameI, string fileNameA, string fileNameSize, string fileNameB)
	{
		this->fileNameI = fileNameI;
		this->fileNameA = fileNameA;
		this->fileNameSize = fileNameSize;
		this->fileNameB = fileNameB;
	}

	vector<int> InputSize()
	{
		vector<int> sizes (3);
		ifstream fin;
		fin.open(fileNameSize + ".txt");

		fin >> sizes[0];
		fin >> sizes[1];
		fin >> sizes[2];

		return sizes;
	}

	void InputMatrix(int sizeMatrix, vector<vector<real>>* Al, vector<vector<real>>* Au, vector<real>* di)
	{
		ifstream fin;
		fin.open(fileNameA + ".txt");

		for (int i = 0; i < sizeMatrix; i++)
		{
			(*Al)[i].resize(3);
			(*Au)[i].resize(3);
			for (int j = 0; j < 7; j++)
				if (j == 3)
					fin >> (*di)[i];
				else if (j < 3)
					fin >> (*Al)[i][j];
				else
					fin >> (*Au)[i][j - 4];
		}
		fin.close();
	}

	vector <real> InputVectorB(int sizeMatrix)
	{
		vector <real> B(sizeMatrix);
		ifstream fin;
		fin.open(fileNameI + ".txt");

		for (int i = 0; i < sizeMatrix; i++)
			fin >> B[i];

		fin.close();

		return B;
	}

};