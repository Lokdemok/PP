// Task1Var2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "MatrixSuccessively.h"
#include "MatrixParallel.h"
#include "RangeForMatrix.h"
#include <ctime>



using namespace std;

void Output(Matrix const &matrix)
{
	for (auto row : matrix)
	{
		for (auto column : row)
		{
			std::cout << " " << column;
		}
		std::cout << std::endl;
	}
}

int main(int argc, char * argv[])
{
	vector<vector<float>> matrix1;
	vector<vector<float>> matrix2;
	MatrixData matrixData;
	size_t threadsCount = 1;
	cout << "Inverse Matrix Parallel" << endl;
	unsigned int  start_time = clock();
	CMatrixInverseParallel matrixInverseParallel(threadsCount, matrixData);
	matrix1 = matrixInverseParallel.GetInverseMatrix();
	Output(matrix1);
	unsigned int end_time = clock();
	unsigned int  search_time = end_time - start_time;
	cout << "time proccess Parallel: " << float(search_time) / 1000 << endl;
	cout << "Inverse Matrix Successivel" << endl;
	start_time = clock();
	CMatrixInverseSuccessively matrixInverseSuccessively(matrixData.basicMatrix);
	matrix2 = matrixInverseSuccessively.GetInverseMatrix();
	Output(matrix2);
	end_time = clock();
	search_time = end_time - start_time;
	cout << "time proccess Successively: " << float(search_time) / 1000 << endl << endl << endl;
	return 0;
}

