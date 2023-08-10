#include <iostream>
#include <algorithm>
#define MAX 8

using namespace std;

int N, M;

int num[MAX];
int choice[MAX];

void solve(int depth, int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> num[i];
  
  sort(num, num+N);

  solve(0, 0);

  return 0;
}

void solve(int depth, int idx){
  if(depth == M){
    for(int i=0; i<M; i++)
      cout << choice[i] << ' ';
    cout << '\n';
    return;
  }

  if(idx >= N) return;

  for(int i=idx; i<N; i++){
    choice[depth] = num[i];
    solve(depth+1, i+1);
  }
}