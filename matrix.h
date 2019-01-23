#include<stdio.h>
#include<stdlib.h>
 
// take input
void read_matrix(float **matrix, int n)
{
    int row, column;
    for(row = 0; row < n; row++)
    {
        for(column = 0; column < n; column++)
        {
            scanf(" %f", *(matrix + row) + column);
        }
    }
    return;
}
 
// display input
void show_matrix(float **matrix, int n)
{
    int row, column;
    for(row = 0; row < n; row++)
    {
        for(column = 0; column < n; column++)
        {
            printf("%8.2f\t", matrix[row][column]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}
 
// calculate by expanding along first row
float calculate_determinant(float **matrix, int n)
{
    if(n == 2)
    {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    int count, flag, row, column;
    float **residue;
    float determinant;
    determinant = 0;
    residue = (float **)malloc((n - 1) * sizeof(float *));
    for(count = 0; count < n - 1; count++)
    {
        residue[count] = (float *)malloc((n - 1) * sizeof(float));
    }
    // 'residue' is the matrix obtained by removing the first row and 'count'th column of 'matrix'
    for(count = 0; count < n; count++)
    {
        for(row = 1; row < n; row++)
        {
            for(column = 0, flag = 0; column < n; column++)
            {
                if(column == count)
                {
                    flag = 1;
                    continue;
                }
                residue[row - 1][column - flag] = matrix[row][column];
            }
        }
        determinant += (1 - 2 * (count % 2)) * matrix[0][count] * calculate_determinant(residue, n - 1);
    }
    free(residue);
    return determinant;
}
 
// calculate cofactor of element matrix[x][y]
float calculate_cofactor(float **matrix, int n, int x, int y)
{
    if(n == 2)
    {
        return (1 - 2 * ((x + y) % 2)) * matrix[1 ^ x][1 ^ y];
    }
    int row, column, row_flag, column_flag;
    float **residue;
    residue = (float **)malloc((n - 1) * sizeof(float *));
    for(row = 0; row < n - 1; row++)
    {
        residue[row] = (float *)malloc((n - 1) * sizeof(float));
    }
    for(row = 0, row_flag = 0; row < n; row++)
    {
        if(row == x)
        {
            row_flag = 1;
            continue;
        }
        for(column = 0, column_flag = 0; column < n; column++)
        {
            if(column == y)
            {
                column_flag = 1;
                continue;
            }
            residue[row - row_flag][column - column_flag] = matrix[row][column];
        }
    }
    return (1 - 2 * ((x + y) % 2)) * calculate_determinant(residue, n - 1);
}
 
// calculate the inverse
float **calculate_inverse(float **matrix, int n)
{
    int row, column;
    float determinant;
    determinant = calculate_determinant(matrix, n);
    float **inverse;
    inverse = (float **)malloc(n * sizeof(float *));
    for(row = 0; row < n; row++)
    {
        inverse[row] = (float *)malloc(n * sizeof(float));
    }
    for(row = 0; row < n; row++)
    {
        for(column = 0; column < n; column++)
        {
            inverse[row][column] = calculate_cofactor(matrix, n, column, row) / determinant;
        }
    }
    return inverse;
}


