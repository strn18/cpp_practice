#include <iostream>
#include <stack>
#define MAX 500000
#define INF 100000001

using namespace std;

int height[MAX+1] = {INF};
int ans[MAX+1];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  stack<pair<int, int>> st;

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> height[i];

  for(int i=N; i>=0; i--){
    while(!st.empty() && height[i]>st.top().second){
      ans[st.top().first] = i;
      st.pop();
    }

    st.push({i, height[i]});
  }

  for(int i=1; i<=N; i++)
    cout << ans[i] << ' ';

  return 0;
}

/*
17298이랑 거의 유사한 문제. 그때는 다른 방식으로 풀었는데 이번 꺼는 그 문제 스택으로 풀었던 풀이가 기억나서 스택으로 좀 짧게 풀었음.

주어진 수를 오른쪽 부터 스택에 넣으면서, 스택의 top에 지금 수보다 작은 수가 있으면 계속 pop을 해주고, pop된 그 수에 해당하는 탑은 지금 수에
해당하는 탑에 레이저가 닿는다는 것을 표시해주면 됨. 그래서 pair를 썼고, {인덱스, 탑 높이}이다. 그런 다음 ans를 다시 왼쪽부터 출력해주면 됨.
*/