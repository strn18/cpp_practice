#include <iostream>
#include <algorithm>
#define MAX 1000

using namespace std;

int main(){
  int N, P[MAX];
  int count = 0;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    scanf("%d", &P[i]);

  sort(P, P+N);

  for(int i=0; i<N; i++)
    for(int j=0; j<=i; j++)
      count += P[j];
  
  printf("%d", count);

  return 0;
}