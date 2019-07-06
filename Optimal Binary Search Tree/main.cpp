#include <stdio.h>
#include<stdlib.h>
#include <iostream>

#define NMAX 20
using namespace std;
typedef struct OBST
{
    int KEY;
    struct OBST *left, *right;
}OBST;

double C[NMAX][NMAX]; //cost matrix
double W[NMAX][NMAX]; //weight matrix
int R[NMAX][NMAX]; //root matrix
double p[NMAX]={-99999,0.15,0.10,0.05,0.10,0.20};//{0.04,0.06,0.08,0.02,0.10,0.12,0.14}; //unsuccesful searches
double q[NMAX]={0.05,0.10,0.05,0.05,0.05,0.10};//{0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05}; //frequencies
int NUMBER_OF_KEYS=5; //number of keys in the tree
int KEYS[NMAX]={1,2,3,4,5};
OBST *ROOT;
void COMPUTE_W_C_R() {
    double x;
    double min;
    int i, j, k, h, m;
//Construct weight matrix W
    for (i = 0; i <= NUMBER_OF_KEYS; i++) {
        W[i][i] = q[i];
        //cout<<q[i]<<" "<<W[i][i]<<endl;
        for (j = i + 1; j <= NUMBER_OF_KEYS; j++) {
            W[i][j] = W[i][j - 1] + p[j] + q[j];

            cout<<i<<" "<<j<<W[i][j-1]<<" "<<p[j]<<" "<<q[j]<<endl;
        }
    }
//Construct cost matrix C and root matrix R
    for (i = 0; i <= NUMBER_OF_KEYS; i++)
        C[i][i] = W[i][i];
    for (i = 0; i <= NUMBER_OF_KEYS - 1; i++) {
        j = i + 1;
        C[i][j] = C[i][i] + C[j][j] + W[i][j];
        R[i][j] = j;
    }
    for (h = 2; h <= NUMBER_OF_KEYS; h++){
        for (i = 0; i <= NUMBER_OF_KEYS - h; i++) {
            j = i + h;
            m = R[i][j - 1];
            min = C[i][m - 1] + C[m][j];
            for (k = m + 1; k <= R[i + 1][j]; k++) { //Knuths Improvement      R[i][j-1]<k<R[i+1][j]
                x = C[i][k - 1] + C[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            C[i][j] = W[i][j] + min;
            R[i][j] = m;
        }
}
//Display weight matrix W
    printf("\nThe weight matrix W:\n");
    for(i = 0; i <= NUMBER_OF_KEYS; i++)
    {
        for(j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%f ", W[i][j]);
        printf("\n");
    }
//Display Cost matrix C
    printf("\nThe cost matrix C:\n");
    for(i = 0; i <= NUMBER_OF_KEYS; i++)
    {
        for(j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%f ", C[i][j]);
        printf("\n");
    }
//Display root matrix R
    printf("\nThe root matrix R:\n");
    for(i = 0; i <= NUMBER_OF_KEYS; i++)
    {
        for(j = i; j <= NUMBER_OF_KEYS; j++)
            printf("%d ", R[i][j]);
        printf("\n");
    }
}
//Construct the optimal binary search tree
OBST *CONSTRUCT_OBST(int i, int j)
{
    OBST *p;
    if(i == j)
        p = NULL;
    else
    {
        p = new OBST;
        p->KEY = KEYS[R[i][j]];
        p->left = CONSTRUCT_OBST(i, R[i][j] - 1); //left subtree
        p->right = CONSTRUCT_OBST(R[i][j], j); //right subtree
    }
    return p;
}
//Display the optimal binary search tree
void DISPLAY(OBST *ROOT, int nivel)
{
    int i;
    if(ROOT != 0)
    {
        DISPLAY(ROOT->right, nivel+1);
        for(i = 0; i <= nivel; i++)
            printf(" ");
        printf("%d\n", ROOT->KEY);
        DISPLAY(ROOT->left, nivel + 1);
            }
}
void OPTIMAL_BINARY_SEARCH_TREE()
{
    double average_cost_per_weight;
    COMPUTE_W_C_R();
    printf("C[0] = %f W[0] = %f\n", C[0][NUMBER_OF_KEYS],
           W[0][NUMBER_OF_KEYS]);
    average_cost_per_weight =
            C[0][NUMBER_OF_KEYS]/(double)W[0][NUMBER_OF_KEYS];
    printf("The cost per weight ratio is: %f\n", average_cost_per_weight);
    ROOT = CONSTRUCT_OBST(0, NUMBER_OF_KEYS);
}
int main()
{
    int i, k;
    printf("Input number of keys: ");
    scanf("%d", &NUMBER_OF_KEYS);
    for(i = 1; i <= NUMBER_OF_KEYS; i++)
    {
        printf("key[%d]= ",i);
        scanf("%d", &KEYS[i]);
        printf(" frequency = ");
        scanf("%d",&p[i]);
    }
    for(i = 0; i <= NUMBER_OF_KEYS; i++)
    {
        printf("q[%d] = ", i);
        scanf("%d",&q[i]);
    }
    while(1)
    {
        printf("1.Construct tree\n2.Display tree\n3.Exit\n");
        scanf("%d", &k);
        switch(k)
        {
            case 1:
                OPTIMAL_BINARY_SEARCH_TREE();
                break;
            case 2:
                cout<<"Root :"<<ROOT->KEY<<endl;
                DISPLAY(ROOT, 0);
                break;
            case 3:
                exit(0);
                break;
        }
    }
    system("PAUSE");
}
/*
Input number of keys:6
6
key[1]=1
1
frequency =10
10
key[2]=2
2
frequency =3
3
key[3]=3
3
frequency =9
9
key[4]=4
4
frequency = 2
2
key[5]=5
5
frequency =0
0
key[6]=6
6
frequency =10
10
q[0] =5
5
q[1] =6
6
q[2] =4
4
q[3] =4
4
q[4] =3
3
q[5] =8
8
q[6] =0
0*/
