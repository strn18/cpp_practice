#include <iostream>
#include <algorithm>
#define MAX 1000000

using namespace std;

int arr[MAX];

int main(){
  int N;

  scanf("%d", &N);

  for(int i=0; i<N; i++)
    scanf("%d", &arr[i]);
  
  sort(arr, arr+N);

  for(int i=0; i<N; i++)
    printf("%d\n", arr[i]);

  return 0;
}