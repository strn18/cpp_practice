#include <iostream>
#define MAX 100

using namespace std;

void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  int basket[MAX+1];

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    basket[i] = i;

  while(M--){
    int i, j;

    cin >> i >> j;
    
    swap(&basket[i], &basket[j]);
  }

  for(int num = 1; num <= N; num++)
    cout << basket[num] << ' ';

  return 0;
}