#include <iostream>
#include <algorithm>
#define MAX 5000000

using namespace std;

int arr[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  cin >> N >> K;

  for(int i=0; i<N; i++)
    cin >> arr[i];
  
  sort(arr, arr + N);

  cout << arr[K-1];

  return 0;
}