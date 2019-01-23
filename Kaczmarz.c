#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("\nusage:");
		printf("\n./Kaczmarz_Method.out <matrix file name> <number of iterations>\n");
		return 1;
	}
	FILE *data;
	data = fopen(argv[1], "r");
	int number;
	number = atoi(argv[2]);
	int n;
	fscanf(data, " %d", &n);
	float **A;
	A = (float **) malloc(n * sizeof(float *));
	int count, track;
	for(count = 0; count < n; count++)
	{
		A[count] = (float *) malloc(n * sizeof(float));
	}
	int row, column;
	for(row = 0; row < n; row++)
	{
		for(column = 0; column < n; column++)
		{
			fscanf(data, " %f", *(A + row) + column);
		}
	}
	float *b, *x, *y;
	b = (float *) malloc(n * sizeof(float));
	x = (float *) malloc(n * sizeof(float));
	y = (float *) malloc(n * sizeof(float));
	for(count = 0; count < n; count++)
	{
		fscanf(data, " %f", b + count);
		y[count] = 0;
	}
	int i, j, modulus;
	float dot, power;
	track = 0;
	clock_t begin, end;
	begin = clock();
	while(number--)
	{
		modulus = track % n;
		for(count = 0; count < n; count++)
		{
			x[count] = y[count];
		}
		for(i = 0; i < n; i++)
		{
			dot = 0;
			power = 0;
			for(j = 0; j < n; j++)
			{
				dot += A[modulus][j] * x[j];
				power += A[modulus][j] * A[modulus][j];
			}
			y[i] = x[i] + (b[modulus] - dot) * A[modulus][i] / power;
		}
		track++;
	}
	for(count = 0; count < n; count++)
	{
		printf("%15f\n", y[count]);
	}
	end = clock();
	printf("time taken = %.0lf us\n", 1e6 * (double) (end - begin) / CLOCKS_PER_SEC);
	return 0;
}
