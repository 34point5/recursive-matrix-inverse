#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// sorry, no comments
// the only important thing to know is the formula
// look up 'recursive inversion'
// you have to know nothing more

float ***partition_square_matrix(float **M, int n)
{
	n >>= 1;
	float ***P;
	P = (float ***) malloc(4 * sizeof(float **));
	int count, track;
	for(count = 0; count < 4; count++)
	{
		P[count] = (float **) malloc(n * sizeof(float *));
		for(track = 0; track < n; track++)
		{
			P[count][track] = (float *) malloc(n * sizeof(float));
		}
	}
	for(count = 0; count < n; count++)
	{
		for(track = 0; track < n; track++)
		{
			P[0][count][track] = M[count][track];
			P[1][count][track] = M[count][track + n];
			P[2][count][track] = M[count + n][track];
			P[3][count][track] = M[count + n][track + n];
		}
	}
	return P;
}

float **multiply_square_matrices(float **K, float **L, int n)
{
	int x, y, count;
	float **Z;
	Z = (float **) malloc(n * sizeof(float *));
	for(count = 0; count < n; count++)
	{
		Z[count] = (float *) malloc(n * sizeof(float));
	}
	for(x = 0; x < n; x++)
	{
		for(y = 0; y < n; y++)
		{
			Z[x][y] = 0;
			for(count = 0; count < n; count++)
			{
				Z[x][y] += K[x][count] * L[count][y];
			}
		}
	}
	return Z;
}

float **add_square_matrices(float **K, float **L, int n)
{
	int x, y, count;
	float **Z;
	Z = (float **) malloc(n * sizeof(float *));
	for(count = 0; count < n; count++)
	{
		Z[count] = (float *) malloc(n * sizeof(float));
	}
	for(x = 0; x < n; x++)
	{
		for(y = 0; y < n; y++)
		{
			Z[x][y] = K[x][y] + L[x][y];
		}
	}
	return Z;
}

float **subtract_square_matrices(float **K, float **L, int n)
{
	int x, y, count;
	float **Z;
	Z = (float **) malloc(n * sizeof(float *));
	for(count = 0; count < n; count++)
	{
		Z[count] = (float *) malloc(n * sizeof(float));
	}
	for(x = 0; x < n; x++)
	{
		for(y = 0; y < n; y++)
		{
			Z[x][y] = K[x][y] - L[x][y];
		}
	}
	return Z;
}

float **negate_square_matrix(float **M, int n)
{
	int x, y, count;
	float **Z;
	Z = (float **) malloc(n * sizeof(float *));
	for(count = 0; count < n; count++)
	{
		Z[count] = (float *) malloc(n * sizeof(float));
	}
	for(x = 0; x < n; x++)
	{
		for(y = 0; y < n; y++)
		{
			Z[x][y] = -M[x][y];
		}
	}
	return Z;
}

float **invert_square_matrix(float **M, int n)
{
	float **M_inverse;
	M_inverse = (float **) malloc(n * sizeof(float *));
	int count, track;
	for(count = 0; count < n; count++)
	{
		M_inverse[count] = (float *) malloc(n * sizeof(float));
	}
	if(n == 2)
	{
		float determinant;
		determinant = M[0][0] * M[1][1] - M[0][1] * M[1][0];
		M_inverse[0][0] = M[1][1] / determinant;
		M_inverse[0][1] = -M[0][1] / determinant;
		M_inverse[1][0] = -M[1][0] / determinant;
		M_inverse[1][1] = M[0][0] / determinant;
		return M_inverse;
	}
	n >>= 1;
	float ***P;
	P = (float ***) malloc(4 * sizeof(float **));
	for(count = 0; count < 4; count++)
	{
		P[count] = (float **) malloc(n * sizeof(float *));
		for(track = 0; track < n; track++)
		{
			P[count][track] = (float *) malloc(n * sizeof(float));
		}
	}
	P = partition_square_matrix(M, n << 1);
	float ***Q;
	Q = (float ***) malloc(4 * sizeof(float **));
	for(count = 0; count < 4; count++)
	{
		Q[count] = (float **) malloc(n * sizeof(float *));
		for(track = 0; track < n; track++)
		{
			Q[count][track] = (float *) malloc(n * sizeof(float));
		}
	}
	Q[3] = invert_square_matrix(subtract_square_matrices(P[3], multiply_square_matrices(Q[3] = multiply_square_matrices(P[2], invert_square_matrix(P[0], n), n), P[1], n), n), n);
	Q[1] = negate_square_matrix(multiply_square_matrices(invert_square_matrix(P[0], n), multiply_square_matrices(P[1], Q[3], n), n), n);
	Q[2] = negate_square_matrix(multiply_square_matrices(multiply_square_matrices(Q[3], P[2], n), invert_square_matrix(P[0], n), n), n);
	Q[0] = subtract_square_matrices(invert_square_matrix(P[0], n), multiply_square_matrices(multiply_square_matrices(Q[1], P[2], n), invert_square_matrix(P[0], n), n), n);
	for(count = 0; count < n; count++)
	{
		for(track = 0; track < n; track++)
		{
			M_inverse[count][track] = Q[0][count][track];
			M_inverse[count][track + n] = Q[1][count][track];
			M_inverse[count + n][track] = Q[2][count][track];
			M_inverse[count + n][track + n] = Q[3][count][track];
		}
	}
	return M_inverse;
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("\nusage:");
		printf("\n./inversion_by_partition.out <matrix file name>\n");
		return 1;
	}
	FILE *data;
	data = fopen(argv[1], "r");
	int n;
	fscanf(data, " %d", &n);
	float **M;
	M = (float **) malloc(n * sizeof(float *));
	int count, track;
	for(count = 0; count < n; count++)
	{
		M[count] = (float *) malloc(n * sizeof(float));
	}
	int row, column;
	for(row = 0; row < n; row++)
	{
		for(column = 0; column < n; column++)
		{
			fscanf(data, " %f", *(M + row) + column);
		}
	}
	float *b;
	b = (float *) malloc(n * sizeof(float));
	for(count = 0; count < n; count++)
	{
		fscanf(data, " %f", b + count);
	}
	float **M_inverse;
	M_inverse = (float **) malloc(n * sizeof(float *));
	for(count = 0; count < n; count++)
	{
		M_inverse[count] = (float *) malloc(n * sizeof(float));
	}
	float *x;
	x = (float *) malloc(n * sizeof(float));
	clock_t begin, end;
	begin = clock();
	M_inverse = invert_square_matrix(M, n);
	for(count = 0; count < n; count++)
	{
		x[count] = 0;
		for(track = 0; track < n; track++)
		{
			x[count] += M_inverse[count][track] * b[track];
		}
		printf("%15f\n", x[count]);
	}
	end = clock();
	printf("time taken = %.0lf us\n", 1e6 * (double) (end - begin) / CLOCKS_PER_SEC);
	return 0;
}
