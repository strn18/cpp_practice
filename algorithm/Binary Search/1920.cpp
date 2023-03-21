#include <iostream>
#include <algorithm>
#define MAX 100000

using namespace std;

int arr[MAX];

bool binary_search(int left, int right, int num);

int main(){
  int N, M, num;

  scanf("%d", &N);

  for(int i=0; i<N; i++)
    scanf("%d", &arr[i]);
  
  sort(arr, arr+N);

  scanf("%d", &M);
  for(int i=0; i<M; i++){
    scanf("%d", &num);
    printf("%d\n", binary_search(0, N-1, num) ? 1 : 0);
  }

  return 0;
}

bool binary_search(int left, int right, int num){
  if(left == right) return arr[left] == num;

  int mid = (left+right)/2;

  if(num == arr[mid]) return true;
  else if(num < arr[mid]) return binary_search(left, mid, num);
  else return binary_search(mid+1, right, num);
}

/*
걍 이진탐색 문제. 22행에 M을 N이라고 써서 한 번 틀림.
*/