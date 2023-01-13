#include <iostream>

using namespace std;

int N;
int board[100][100];

bool check_num(void);
bool check_row(void);
bool check_col(void);
bool check_dia(void);
bool check_board(void);

int main(){
  scanf("%d", &N);

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &board[i][j]);

  if(check_board())
    printf("TRUE");
  else
    printf("FALSE");  

  return 0;
}

bool check_num(void){
  bool used[10001] = {false};

  for(int r=0; r<N; r++){
    for(int c=0; c<N; c++){
      if(used[board[r][c]])
        return false;
      used[board[r][c]] = true;
    }
  }

  return true;
}

bool check_row(void){
  int sum = N*(N*N+1)/2;
  
  for(int r=0; r<N; r++){
    int count = 0;
    for(int c=0; c<N; c++)
      count += board[r][c];

    if(sum != count)
      return false;
  }

  return true;
}

bool check_col(void){
  int sum = N*(N*N+1)/2;
  
  for(int c=0; c<N; c++){
    int count = 0;
    for(int r=0; r<N; r++)
      count += board[r][c];

    if(sum != count)
      return false;
  }

  return true;
}

bool check_dia(void){
  int sum = N*(N*N+1)/2;
  int r, c, count;

  r=0; c=0; count=0;
  while(r<N){
    count += board[r][c];
    r++; c++;
  }
  if(sum != count)
    return false;
  
  r=0; c=N-1; count=0;
  while(r<N){
    count += board[r][c];
    r++; c--;
  }
  if(sum != count)
    return false;
  
  return true;
}

bool check_board(void){
  if(check_num())
    if(check_row())
      if(check_col())
        if(check_dia())
          return true;

  return false;
}