#include <iostream>
#define MAX 1000000

using namespace std;

int M, N, cookie[MAX];

bool check(int len);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int low = 1, high = 1, ans = 0;

  cin >> M >> N;

  for(int i=0; i<N; i++){
    cin >> cookie[i];
    high = max(high, cookie[i]);
  }

  while(low <= high){
    int mid = (low + high) / 2;

    if(check(mid)){
      ans = mid;
      low = mid + 1;
    }
    else{
      high = mid - 1;
    }
  }

  cout << ans;

  return 0;
}

bool check(int len){
  int count = 0;

  for(int i=0; i<N; i++)
    count += (cookie[i] / len);
  
  return (count >= M ? true : false);
}

/*
그냥 흔한 매개변수 탐색 문제. 탐색 범위는 1 ~ max(L) 이다. 
*/