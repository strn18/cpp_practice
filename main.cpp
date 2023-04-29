#include <iostream>
#define MAX 15

using namespace std;

int N, ans = 0;
int T[MAX+1], P[MAX+1];

void choose(int n, int sum);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> T[i] >> P[i];

  choose(1, 0);

  cout << ans;

  return 0;
}

void choose(int n, int sum){
  if(n > N){
    ans = max(ans, sum);
    return;
  }

  if(n+T[n]-1 <= N) choose(n+T[n], sum+P[n]);
  if(T[n] != 1) choose(n+1, sum);
}