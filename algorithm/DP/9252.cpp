#include <iostream>
#include <string>
#include <stack>
#define MAX 1000

using namespace std;

int dp[MAX+1][MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string A, B;
  stack<char> ans;

  cin >> A;
  cin >> B;

  for(int i=1; i<=A.size(); i++){
    for(int j=1; j<=B.size(); j++){
      if(A[i-1] == B[j-1]) dp[i][j] = dp[i-1][j-1] + 1; // i, j는 1-based이고 A, B는 0-based이기에 변환.
      else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
  }

  int i = A.size(), j = B.size();

  while(i >= 1 && j >= 1){
    if(dp[i][j] == dp[i-1][j]) i = i-1;
    else if(dp[i][j] == dp[i][j-1]) j = j-1;
    else{
      ans.push(A[i-1]); // i, j는 1-based이고 A, B는 0-based이기에 변환.
      i = i-1;
      j = j-1;
    }
  }

  cout << ans.size() << '\n';

  while(!ans.empty()){
    cout << ans.top();
    ans.pop();
  }

  return 0;
}

/*
9251이랑 거의 비슷하지만, LCS를 직접 출력해야한다는 점이 다르다.

알고리즘 수업 시간에 배운대로, 우하단에서 시작해서, 지나온 길을 역으로 밟아가면 된다. 이때, 인덱스 i와 j는 혼동을 피하기 위해 1-based로 했는데 
문자열 A, B는 0-based로 참조해야 해서, 22행과 33행에서 인덱스값-1을 해줘서 변환해준 것에 유의.
*/