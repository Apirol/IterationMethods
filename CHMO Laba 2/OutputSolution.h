#pragma once
#include <iostream>
#include <fstream>
#include <vector>


class OutputSolution
{
private:
	string filename;

public:

	OutputSolution(string filename)
	{
		this->filename = filename;
	}

	void ReportSolution(JakobiMethod method) 
	{
		ofstream fout;
		fout.open(filename + ".txt");
		real wMax = method.FindMinW();
		real w = 0;

		while (w + 0.1 < wMax)
		{
			ReportForCurrentW(method, &fout, w);
			w += 0.1;


		}

		while (w < wMax)
		{
			ReportForCurrentW(method, &fout, w);
			w += 0.01;
		}
	};

	void ReportForCurrentW(JakobiMethod method, ofstream *fout, real w)
	{
		int k = method.Solution(w);
		vector<real> x_prec(method.slae.sizeMatrix);

		for (int i = 0; i < method.slae.sizeMatrix; i++)
			x_prec[i] = i + 1;

		*fout << setprecision(2) << fixed;

		*fout << "w = " << w << endl;
		*fout << "x: " << endl;

		*fout << setprecision(10) << scientific;

		for (int i = 0; i < method.slae.sizeMatrix; i++)
			*fout << method.slae.X[i] << endl;

		*fout << "x* - x: " << endl;
		for (int i = 0; i < method.slae.sizeMatrix; i++)
			*fout << x_prec[i] - method.slae.X[i] << endl;

		*fout << "vA = " << method.slae.Norm(method.slae.X - x_prec) / method.slae.Norm(x_prec) / method.Inconspicuous(method.slae.X) << endl;
		*fout << "k = " << k << endl << endl;
	}
};