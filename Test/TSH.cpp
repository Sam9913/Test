///*This program is an implementaion of the Jacobi iteration method.
//The relation used is X(k+1)=(Diagonal matrix Inverse)(RHS Coefficient-)*(Lower triangle+Upper triangle)X(k))
//*/
//#include <stdio.h>
//#include <omp.h>
//#include <windows.h>
//#include <ctype.h>
//
//#define EPSILON 0.000001
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
//int row = 0, column = 0, matrixSize = 3, navigate;
//
//void multiply(float matrixA[][10], float matrixB[][1])
//{
//	int ctr;
//	//function to perform multiplication
//	for (ctr = 0; ctr < matrixSize; ctr++)
//	{
//		//before every iteration start it will redefine the matrixRes to 0
//		matrixRes[ctr][0] = 0;
//		for (navigate = 0; navigate < matrixSize; navigate++)
//			matrixRes[ctr][0] = matrixRes[ctr][0] + matrixA[ctr][navigate] * matrixB[navigate][0];
//	}
//}
//
//void substraction(float matrixA[][1], float matrixB[][1]) {
//	float(*temp_private)[1];
//
//#pragma omp parallel
//	{
//		const int nthreads = omp_get_num_threads();
//		const int ithread = omp_get_thread_num();
//
//#pragma omp single 
//		{
//			temp_private = new float[10 * nthreads][1];
//			for (int i = 0; i < (10 * nthreads); i++) 
//				temp_private[i][0] = 0;
//		}
//#pragma omp for
//		for (int n = 0; n < 10; ++n)
//		{
//			for (int row = 0; row <= n; ++row) {
//				temp_private[ithread * 10 + n][0] = matrixA[row][0] - matrixB[row][0];
//			}
//		}
//#pragma omp for
//		for (int i = 0; i < 10; i++) {
//			for (int t = 0; t <= i; t++) {
//				temp[i][0] = temp_private[10 * ithread + i][0];
//			}
//		}
//	}
//
//	delete[] temp_private;
//}
//
//int main()
//{
//	float(*temp_private)[1];
//
//#pragma omp parallel
//	{
//		const int nthreads = omp_get_num_threads();
//		const int ithread = omp_get_thread_num();
//
//#pragma omp single 
//		{
//			temp_private = new float[10 * nthreads][1];
//			for (int i = 0; i < (10 * nthreads); i++)
//				temp_private[i][0] = 0;
//		}
//	}
//
//	for (int i = 0; i < 10; i++) {
//		printf("%d : %f \n",i, temp_private[i][0]);
//	}
//}