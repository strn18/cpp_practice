#include <iostream>
#include <algorithm>
#define MAX 8

using namespace std;

int N, M;
int num[MAX], choice[MAX];
bool visited[MAX];

void solve(int cur, int count); // 이제 num[cur]를 고를 차례, 지금까지 count개 골랐다.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=0; i<N; i++)
    cin >> num[i];
  
  for(int i=0; i<M; i++)
    choice[i] = -1;

  sort(num, num+N);
  
  for(int i=0; i<N; i++)
    solve(i, 0);

  return 0;
}

void solve(int cur, int count){
  if(choice[count] == num[cur]) return; // 중복된 수열인 경우는 패스

  choice[count++] = num[cur];

  if(count == M){
    for(int i=0; i<M; i++)
      cout << choice[i] << ' ';
    cout << '\n';
    return;
  }

  visited[cur] = true;

  for(int i=0; i<N; i++)
    if(!visited[i])
      solve(i, count);

  choice[count] = -1; // 지금 내 선택의 모든 수열 탐색이 끝났다면, 내 다음 칸은 다시 -1로 초기화해줌
  visited[cur] = false;
}

/*
약간 꼬아놓은 백트래킹 문제. 중복된 수열 출력을 방지하기 위해 34행을 이용했다.
가령, 1 2 3 3 4 가 있을 때, 2개를 고른다고 하자. (1 2), (1 3)을 고른 이후, choice[1]에는 3이 남아있다. 그렇기에 그 다음 중복으로 (1 3)을 
고르지 않게 된다. 그러다가, (1 4)를 고른 다음에는 이제 choice[0]이 1인 solve가 모두 끝나게 되고, 이후 choice[0]이 2인 solve가 시작된다. 이때, 
choice[0]이 1인 solve가 종료되기 전, 51행에서 choice[1]을 -1로 되돌려놓고 간다. 왜냐? 아까 (1 3) 고르면서 choice[1]이 2가 된 건데, 이걸 그대로 
남겨두면 (2 3)을 고르지 못하게 된다. 그렇기에 그걸 -1로 되돌려놓고, choice[0]이 2인 solve가 시작되며 (2 1), (2 3), ... 을 고르게 된다.
*/