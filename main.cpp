#include <iostream>
#define MAX_N 15
#define MAX_A 1000000

using namespace std;

int N, L, R, X, count = 0;
int A[MAX_N];

void solve(int choice, int start);
bool check(int choice);
int bit_count(int bit);

int main(){
  scanf("%d %d %d %d", &N, &L, &R, &X);
  for(int i=0; i<N; i++)
    scanf("%d", &A[i]);
  
  solve(0, 0);

  printf("%d", count);

  return 0;
}

void solve(int choice, int start){
  if(start == N){
    if(check(choice))
      count++;
    return;
  }

  solve(choice, start+1);
  choice |= (1<<start);
  solve(choice, start+1);
}

bool check(int choice){
  if(bit_count(choice) < 2) return false;

  int sum = 0, hard = 0, easy = MAX_A+1;
  for(int i=0; i<N; i++){
    if((choice>>i) & 1){
      sum += A[i];
      if(A[i] > hard) hard = A[i];
      if(A[i] < easy) easy = A[i];
    }
  }
  
  if(sum<L || sum>R || hard-easy<X) return false;
  return true;
}

int bit_count(int bit){
  if(bit == 0) return 0;
  return bit%2 + bit_count(bit/2);
}