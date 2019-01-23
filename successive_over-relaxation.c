#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		printf("\nusage:");
		printf("\n./successive_over-relaxation.out <matrix file name> <number of iterations> <relaxation factor>\n");
		return 1;
	}
	FILE *data;
	data = fopen(argv[1], "r");
	int number;
	number = atoi(argv[2]);
	float omega;
	omega = atof(argv[3]);
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
	float *b, *x;
	b = (float *) malloc(n * sizeof(float));
	x = (float *) malloc(n * sizeof(float));
	for(count = 0; count < n; count++)
	{
		fscanf(data, " %f", b + count);
		x[count] = 1;
	}
	int i, j;
	float sum;
	clock_t begin, end;
	begin = clock();
	while(number--)
	{
		for(i = 0; i < n; i++)
		{
			sum = 0;
			for(j = 0; j < n; j++)
			{
				if(j == i)
				{
					continue;
				}
				sum += A[i][j] * x[j];
			}
			x[i] = (1 - omega) * x[i] + omega * (b[i] - sum) / A[i][i];
		}
	}
	for(count = 0; count < n; count++)
	{
		printf("%15f\n", x[count]);
	}
	end = clock();
	printf("time taken = %.0lf us\n", 1e6 * (double) (end - begin) / CLOCKS_PER_SEC);
	return 0;
}
