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