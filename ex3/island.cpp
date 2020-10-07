#include <bits/stdc++.h>
using namespace std;
#define m 5
#define n 5

int reachable(int arr[][n], int i, int j, bool visited[][n])
{
    return (i >= 0) && (i < m) &&
           (j >= 0) && (j < n) &&
           (arr[i][j] && !visited[i][j]);
}

void adjislands(int arr[][n], int i, int j, bool visited[][n])
{
    int rowchange[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colchange[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    visited[i][j] = true;

    for (int k = 0; k < 8; k++)
        if (reachable(arr, i + rowchange[k], j + colchange[k], visited))
            adjislands(arr, i + rowchange[k], j + colchange[k], visited);
}

int island(int arr[][n])
{
    bool visited[m][n];
    memset(visited, 0, sizeof(visited));
    int count = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] && !visited[i][j])
            {
                count++;
                adjislands(arr, i, j, visited);
            }
    return count;
}

int main()
{
    int arr[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> arr[i][j];
    cout << endl
         << island(arr) << endl;
    return 0;
}