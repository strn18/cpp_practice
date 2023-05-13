#include <iostream>
#include <algorithm>
#define MAX 10000

using namespace std;

int arr[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++){
    int num;

    cin >> num;

    arr[num]++;
  }

  for(int i=1; i<=MAX; i++)
    for(int j=0; j<arr[i]; j++)
      cout << i << '\n';

  return 0;
}