/*This program is an implementaion of the Jacobi iteration method.
The relation used is X(k+1)=(Diagonal matrix Inverse)(RHS Coefficient-)*(Lower triangle+Upper triangle)X(k))
*/
#include <stdio.h>
#include <omp.h>
#include <windows.h>
#include <ctype.h>

#define EPSILON 0.000001

char label[3] = { 'x','y','z' };
float coeff[10][10];
float Dinv[10][10];
float approx[10][1];
float temp[10][1];
float tempApprox[10][1];
float R[10][10];//declare the relevant matrices
float matrixRes[10][1];
float b[10][1];
int row = 0, column = 0, matrixSize = 3, navigate;

void multiply(float matrixA[][10], float matrixB[][1])
{
	float(*temp_private)[1];

#pragma omp parallel
	{
		const int nthreads = omp_get_num_threads();

#pragma omp single 
		{
			temp_private = new float[10 * nthreads][1];
			for (int i = 0; i < (10 * nthreads); i++)
				temp_private[i][0] = 0;
		}
	}

#pragma omp for
	for (int pointer = 0; pointer < matrixSize; ++pointer) {
		for (navigate = 0; navigate < matrixSize; navigate++)
			temp_private[pointer][0] += matrixA[pointer][navigate] * matrixB[navigate][0];
	}

#pragma omp critical
	{
		for (int n = 0; n < 10; ++n) {
			matrixRes[n][0] = temp_private[n][0];
		}
	}
}

int main()
{
	bool inputType1 = true, inputType2 = true;
	/*Color code
			0 = Black       8 = Gray
			1 = Blue        9 = Light Blue
			2 = Green       A = Light Green
			3 = Aqua        B = Light Aqua
			4 = Red         C = Light Red
			5 = Purple      D = Light Purple
			6 = Yellow      E = Light Yellow
			7 = White       F = Bright White*/
	system("color f8");

	printf("\t=======================================\n");
	printf("\t||     Jacobi Iteration Calculator    ||\n");
	printf("\t=======================================\n");

	printf("Enter the coefficent matrix\n");

	for (row = 0; row < matrixSize; row++) {
		for (column = 0; column < matrixSize; column++) {
			if (scanf_s("%f", &coeff[row][column]) != 1) {
				inputType1 = false;
				break;
			}
		}
	}

	if (inputType1) {
		for (row = 0; row < matrixSize; row++)
			approx[row][0] = 0;

		printf("Enter the RHS coefficient\n");

		for (row = 0; row < matrixSize; row++) {
			if (scanf_s("%f", &b[row][0]) != 1) {
				inputType2 = false;
				break;
			}
			else if (b[row][0] == 0) {
				inputType2 = false;
				break;
			}
		}

		if (inputType2) {
			double start_time = omp_get_wtime();

			//calculating the diagonal inverse matrix make all other entries as zero except Diagonal entries 
			//whose resciprocal stored
			for (row = 0; row < matrixSize; row++)
			{
				for (column = 0; column < matrixSize; column++)
				{
					if (row == column)
						Dinv[row][column] = 1 / coeff[row][column];
					else
						Dinv[row][column] = 0;
				}
			}

			//calculating the R matrix L+U
			for (row = 0; row < matrixSize; row++)
			{
				for (column = 0; column < matrixSize; column++)
				{
					if (row == column)
						R[row][column] = 0;
					else
						R[row][column] = coeff[row][column];
				}
			}

			int ctr = 1;
			int octr;
			int sameAmount = 0;

			//to check whether the current iteration same as the last iteration
			for (; sameAmount < 6; ctr++)
			{
				for (octr = 0; octr < matrixSize; octr++) {
					if (tempApprox[octr][0] - approx[octr][0] < EPSILON && ctr != 1) {
						sameAmount++;
					}
					tempApprox[octr][0] = matrixRes[octr][0];
				}

				//If only two of the answers are same, then reset it to 0
				if (sameAmount < 3) {
					sameAmount = 0;
				}

				//multiply L+U and the approximation
				multiply(R, approx);

				//calculate the matrix(b-Rx) and store it to temp
#pragma omp for schedule (guided, 8)
				for (row = 0; row < matrixSize; row++)
					temp[row][0] = b[row][0] - matrixRes[row][0];

				//multiply D inverse and (b-Rx)
				multiply(Dinv, temp);

				//store matrixRes value in the next approximation
#pragma omp for schedule (guided, 8)
				for (octr = 0; octr < matrixSize; octr++)
					approx[octr][0] = matrixRes[octr][0];

				//display the value after the pass
				printf("The value after iteration %d is\n", ctr);
				for (row = 0; row < matrixSize; row++) {
					printf("%c : %.3f\n", label[row], approx[row][0]);
				}
			}

			double end_time = omp_get_wtime();
			//print time used
			printf("Time used (seconds) : %f", end_time - start_time);
		}
		else {
			system("color fc");
			printf("\n\t----------You have entered invalid input.----------\n\n");
			printf("\tPossible problems: \n");
			printf("\t1. You are not entering numeric number. \n");
			printf("\t2. 0 is not suggested to be used as RHS coefficient. \n\n");
			printf("\t   ----------Please try again later.----------\n");
		}
	}
	else {
		system("color fc");
		printf("\n\t----------You have entered invalid input.----------\n\n");
		printf("\tPossible problems: \n");
		printf("\t1. You are not entering numeric number. \n\n");
		printf("\t   ----------Please try again later.----------\n");
	}
}