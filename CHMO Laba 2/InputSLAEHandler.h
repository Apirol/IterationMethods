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

	void InputInfo(int* n, int* m, int* k, int* maxiter, real* eps)
	{
		ifstream fin;
		fin.open(fileNameSize + ".txt");

		string s;

		fin >> s >> *n;
		fin >> s >> *m;
		fin >> s >> *k;
		fin >> s >> *maxiter;
		fin >> s >> *eps;
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
		fin.open(fileNameB + ".txt");

		for (int i = 0; i < sizeMatrix; i++)
			fin >> B[i];

		fin.close();

		return B;
	}

};