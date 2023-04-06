#include <iostream>
#include <string.h>
using namespace std;
 
// `N × N` chessboard
#define N 8
 

int isSafe(char mat[][N], int r, int c)
{
    
    for (int i = 0; i < r; i++)
    {
        if (mat[i][c] == 'Q') {
            return 0;
        }
    }
 
    
    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
    {
        if (mat[i][j] == 'Q') {
            return 0;
        }
    }
 
    
    for (int i = r, j = c; i >= 0 && j < N; i--, j++)
    {
        if (mat[i][j] == 'Q') {
            return 0;
        }
    }
 
    return 1;
}
int c=0;
void printSolution(char mat[][N])
{
    c++;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) {
            
            cout<<mat[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
 
void nQueen(char mat[][N], int r)
{
    
    if (r == N)
    {
        printSolution(mat);
        return;
    }
 
    
    for (int i = 0; i < N; i++)
    {
        // if no two queens threaten each other
        if (isSafe(mat, r, i))
        {
            // place queen on the current square
            mat[r][i] = 'Q';
 
            // recur for the next row
            nQueen(mat, r + 1);
 
            // backtrack and remove the queen from the current square
            mat[r][i] = '-';
        }
    }
}
 
int main()
{
    
    char mat[N][N];
 
    
    memset(mat, '-', sizeof mat);
 
    nQueen(mat, 0);
    cout<<"\nTotal Solutions : "<<c;
 
    return 0;
}
// Dev Trivedi 21BCE2546