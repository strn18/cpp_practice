#include <iostream>
#include <algorithm>
#define MAX 100000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, x, count = 0;
  int arr[MAX];

  cin >> n;

  for(int i=0; i<n; i++)
    cin >> arr[i];

  sort(arr, arr + n);

  cin >> x;

  int i = 0, j = n-1;

  while(i < j){
    int sum = arr[i] + arr[j];

    if(sum == x){
      ++count;
      ++i;
      --j;
    }
    else if(sum < x){
      ++i;
    }
    else{
      --j;
    }
  }
  
  cout << count;
  
  return 0;
}

/*
처음에는 unordered_set 써서, 어떤 수가 있는지 기록해두고, 어떠한 수 a를 보고 있을 때, x-a가 set에 있는지 확인하는 식으로 했다.

근데 풀고 다른 풀이 찾아보니까, 투포인터로 풀 수 있어서 그렇게 풀었다. 수열을 정렬해놓고 투포인터를 쓰는데, 이때 포인터가 하나는 앞, 하나는 
뒤에서 시작하는 것에 유의.
*/