///*This program is an implementaion of the Jacobi iteration method.
//The relation used is X(k+1)=(Diagonal matrix Inverse)(RHS Coefficient-)*(Lower triangle+Upper triangle)X(k))
//*/
//#include <stdio.h>
//#include <omp.h>
//#define EPSILON 0.001
//
//char label[3] = { 'x','y','z' };
//float coeff[10][10];
//float Dinv[10][10];
//float approx[10][1];
//float temp[10][1];
//float tempApprox[10][1];
//float R[10][10];//declare the relevant matrices
//float matrixRes[10][1];
//float b[10][1];
//int row, column, size = 3, navigate;
//
//void multiply(float matrixA[][10], float matrixB[][1])
//{
//	int ctr;
//	//function to perform multiplication
//	for (ctr = 0; ctr < size; ctr++)
//	{
//		//before every iteration start it will redefine the matrixRes to 0
//		matrixRes[ctr][0] = 0;
//		for (navigate = 0; navigate < size; navigate++)
//			matrixRes[ctr][0] = matrixRes[ctr][0] + matrixA[ctr][navigate] * matrixB[navigate][0];
//	}
//}
//
//void substraction(float matrixA[][1], float matrixB[][1]) {
//	for (row = 0; row < size; row++)
//		temp[row][0] = matrixA[row][0] - matrixB[row][0];
//}
//
//int main()
//{
//	printf("Enter the coefficent matrix\n");
//	for (row = 0; row < size; row++)
//		for (column = 0; column < size; column++)
//			scanf_s("%f", &coeff[row][column]);
//	//printf("Enter the first approximation\n");
//	for (row = 0; row < size; row++)
//		approx[row][0] = 0;
//	printf("Enter the RHS coefficient\n");
//	for (row = 0; row < size; row++)
//		scanf_s("%f", &b[row][0]);
//
//	double start_time = omp_get_wtime();
//
//	//calculating the diagonal inverse matrix make all other entries as zero except Diagonal entries 
//	//whose resciprocal stored
//	for (row = 0; row < size; row++)
//		for (column = 0; column < size; column++)
//		{
//			if (row == column)
//				Dinv[row][column] = 1 / coeff[row][column];
//			else
//				Dinv[row][column] = 0;
//		}
//
//	//calculating the R matrix L+U
//	for (row = 0; row < size; row++)
//		for (column = 0; column < size; column++)
//		{
//			if (row == column)
//				R[row][column] = 0;
//			else
//				if (row != column)
//					R[row][column] = coeff[row][column];
//		}
//
//	int ctr = 1;
//	int octr;
//	int sameAmount = 0;
//
//	//to check whether the current iteration same as the last iteration
//	for (; sameAmount < 6; ctr++)
//	{
//		for (octr = 0; octr < size; octr++) {
//			if (tempApprox[octr][0] - approx[octr][0] < EPSILON && ctr != 1) {
//				sameAmount++;
//			}
//			tempApprox[octr][0] = matrixRes[octr][0];
//		}
//
//		//If only two of the answers are same, then reset it to 0
//		if (sameAmount < 3) {
//			sameAmount = 0;
//		}
//
//		//multiply L+U and the approximation
//		multiply(R, approx);
//
//		//calculate the matrix(b-Rx) and store it to temp
//		substraction(b, matrixRes);
//
//		//multiply D inverse and (b-Rx)
//		multiply(Dinv, temp);
//
//		//store matrixRes value in the next approximation
//		for (octr = 0; octr < size; octr++)
//			approx[octr][0] = matrixRes[octr][0];
//
//		//display the value after the pass
//		printf("The value after iteration %d is\n", ctr);
//		for (row = 0; row < size; row++) {
//			printf("%c : %.3f\n", label[row], approx[row][0]);
//		}
//	}
//
//	double end_time = omp_get_wtime();
//	//print time used
//	printf("Time used (seconds) : %f", end_time - start_time);
//
//}