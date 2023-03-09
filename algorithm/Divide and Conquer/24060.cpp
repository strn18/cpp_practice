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

/*
기초 병합정렬 문제. 알고리즘 분류는 다른 걸로 되어있긴 한데, 어쨌든 병합정렬 이용 문제니깐 걍 분할 정복에 넣었다.
문제에 주어진 병합정렬 코드를 그대로 이용하고, merge 과정에서 오름차순으로 temp에 넣어놓은 수를 52행에서 A에 다시 넣어주는 과정에서 K번째로 넣는
수를 찾아서 출력하면 된다. 만약 정렬이 다 끝났는데 K가 여전히 양수라면, A에 넣는 횟수가 K보다 적다는 뜻이므로 -1을 출력한다.
*/