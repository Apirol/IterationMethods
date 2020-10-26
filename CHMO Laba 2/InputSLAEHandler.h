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

	pair <int, int> InputSize()
	{
		pair <int, int> sizes;
		ifstream fin;
		fin.open(fileNameSize + ".txt");

		fin >> sizes.first;
		fin >> sizes.second;

		return sizes;
	}

	vector <vector <real>> InputMatrix(int sizeMatrix, int diagAmount)
	{
		vector<vector <real>> A(sizeMatrix);
		ifstream fin;
		fin.open(fileNameA + ".txt");

		for (int i = 0; i < sizeMatrix; i++)
		{
			A[i].resize(diagAmount);
			for (int j = 0; j < diagAmount ; j++)
				fin >> A[i][j];
		}

		fin.close();

		return A;
	}

	vector <int> InputVectorI(int diagAmount)
	{
		vector <int> I(diagAmount);
		ifstream fin;
		fin.open(fileNameI + ".txt");

		for (int i = 0; i < diagAmount; i++)
			fin >> I[i];

		fin.close();

		return I;
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