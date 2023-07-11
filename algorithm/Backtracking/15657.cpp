#include <iostream>
#include <algorithm>
#define MAX 8

using namespace std;

int N, M;
int num[MAX], ans[MAX];

void dfs(int cur, int count);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> num[i];

  sort(num, num+N);

  dfs(0, 0);

  return 0;
}

void dfs(int cur, int count){
  if(count == M){
    for(int i=0; i<M; i++)
      cout << ans[i] << ' ';
    cout << '\n';
    return;
  }

  for(int i=cur; i<N; i++){
    ans[count] = num[i];
    dfs(i, count+1);
  }
}

/*
기초 dfs + 백트래킹 문제. 근데 분류가 백트래킹으로 되어 있어서 그걸로 분류함.
*/