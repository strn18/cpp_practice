#include <iostream>
#define MAX 64

using namespace std;

int arr[MAX][MAX];

void quad(int row, int col, int n);
bool check(int row, int col, int n);

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%1d", &arr[i][j]);
  
  quad(0, 0, N);

  return 0;
}

void quad(int row, int col, int n){
  if(check(row, col, n))
    printf("%d", arr[row][col]);
    
  else{
    printf("(");
    quad(row, col, n/2);
    quad(row, col + n/2, n/2);
    quad(row + n/2, col, n/2);
    quad(row + n/2, col + n/2, n/2);
    printf(")");
  }
}

bool check(int row, int col, int n){
  int num = arr[row][col];

  for(int i=row; i<row+n; i++)
    for(int j=col; j<col+n; j++)
      if(arr[i][j] != num)
        return false;

  return true;
}

/*
쉬웠던 분할정복 문제. 1780과 풀이가 거의 유사함.
*/