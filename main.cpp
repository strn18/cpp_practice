#include <iostream>
#define MAX 500000

using namespace std;

int K, A[MAX];

void merge_sort(int p, int r);
void merge(int p, int q, int r);

int main(){
  int N;

  scanf("%d %d", &N, &K);
  for(int i=0; i<N; i++)
    scanf("%d", &A[i]);
  
  merge_sort(0, N-1);

  if(K > 0) printf("-1");

  return 0;
}

void merge_sort(int p, int r){
  if(p < r){
    int q = (p+r)/2;
    merge_sort(p, q);
    merge_sort(q+1, r);
    merge(p, q, r);
  }
}

void merge(int p, int q, int r){
  int i = p, j = q+1, t = 0;
  int temp[MAX];

  while(i<=q && j<=r){
    if(A[i] <= A[j])
      temp[t++] = A[i++];
    else
      temp[t++] = A[j++];
  }

  while(i<=q)
    temp[t++] = A[i++];
  while(j<=r)
    temp[t++] = A[j++];

  i = p, t = 0;
  while(i<=r){
    A[i++] = temp[t++];
    if(!(--K)) printf("%d", temp[t-1]);
  }
}