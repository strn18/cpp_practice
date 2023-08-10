#include <iostream>

using namespace std;

int insertion_sort(int A[], int N, int K){
  int count = 0;

  for(int i=1; i<N; i++){
    int loc = i-1;
    int newItem = A[i];

    while(0<=loc && newItem<A[loc]){
      A[loc+1] = A[loc];
      if(++count == K) return A[loc+1];

      loc--;
    }
    if(loc+1 != i){
      A[loc+1] = newItem;
      if(++count == K) return A[loc+1];
    }
  }

  return -1;
}

int main(){
  int N, K, ans;
  int arr[10000];

  scanf("%d %d", &N, &K);
  for(int i=0; i<N; i++){
    scanf("%d", &arr[i]);
  }

  ans = insertion_sort(arr, N, K);
  
  printf("%d", ans);

  return 0;
}