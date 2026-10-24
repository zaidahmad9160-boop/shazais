#include <stdio.h>

#define MAX 10

void inputMatrix(int a[MAX][MAX], int r, int c);
void displayMatrix(int a[MAX][MAX], int r, int c);
void addMatrix(int a[MAX][MAX], int b[MAX][MAX], int r, int c);
void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX],
                    int r1, int c1, int c2);
void transposeMatrix(int a[MAX][MAX], int r, int c);

int main()
{
    int a[MAX][MAX], b[MAX][MAX];
    int r1, c1, r2, c2;

    printf("Enter rows and columns of Matrix A: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter elements of Matrix A:\n");
    inputMatrix(a, r1, c1);

    printf("Enter rows and columns of Matrix B: ");
    scanf("%d %d", &r2, &c2);

    printf("Enter elements of Matrix B:\n");
    inputMatrix(b, r2, c2);

    printf("\nMatrix A:\n");
    displayMatrix(a, r1, c1);

    printf("\nMatrix B:\n");
    displayMatrix(b, r2, c2);

    if (r1 == r2 && c1 == c2)
    {
        printf("\nMatrix Addition:\n");
        addMatrix(a, b, r1, c1);
    }
    else
    {
        printf("\nAddition is not possible.\n");
    }

    if (c1 == r2)
    {
        printf("\nMatrix Multiplication:\n");
        multiplyMatrix(a, b, r1, c1, c2);
    }
    else
    {
        printf("\nMultiplication is not possible.\n");
    }

    printf("\nTranspose of Matrix A:\n");
    transposeMatrix(a, r1, c1);

    return 0;
}

void inputMatrix(int a[MAX][MAX], int r, int c)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

void displayMatrix(int a[MAX][MAX], int r, int c)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void addMatrix(int a[MAX][MAX], int b[MAX][MAX],
               int r, int c)
{
    int i, j;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            printf("%d ", a[i][j] + b[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX],
                    int r1, int c1, int c2)
{
    int i, j, k, sum;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            sum = 0;

            for (k = 0; k < c1; k++)
            {
                sum += a[i][k] * b[k][j];
            }

            printf("%d ", sum);
        }
        printf("\n");
    }
}

void transposeMatrix(int a[MAX][MAX], int r, int c)
{
    int i, j;

    for (j = 0; j < c; j++)
    {
        for (i = 0; i < r; i++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
