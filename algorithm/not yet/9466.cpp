/*
#include <iostream>
#include <vector>

#define MAX 100000

using namespace std;

vector<int> choice(MAX+1), visit(MAX+1); // choice[i]는 i번 학생이 선택한 학생 번호, visit[i]는 i번 학생을 탐색했는지 여부
int cnt, n; // cnt는 팀에 속하는 학생의 수
void dfs(int cur); // cur는 현재 탐색중인 학생 번호

int main(){
  int T;
  cin >> T;

  while(T--){
    cin >> n;
    for(int i=1; i<=n; i++)
      cin >> choice[i];

    cnt = 0;
    fill_n(&visit[1], n, 0); // 1~n번 학생의 visit 정보를 0으로 초기화
    //fill(visit.begin(), visit.end(), 0); // 스터디 영상에서 썼던 방법. 이거는 그냥 모든 visit을 0으로 초기화함

    for(int i=1; i<=n; i++)
      if(!visit[i])
        dfs(i); // i번 학생을 탐색 안 했으면 탐색한다.

    cout << n-cnt << endl;
  }

  return 0;
}

void dfs(int cur){
  visit[cur] = 1; // 현재 cur번 학생 탐색 중임을 의미.
  int next = choice[cur]; // next는 cur번 학생이 선택한 학생 번호

  if(!visit[next])
    dfs(next);
  else if(visit[next]==1){ // next번 학생이 탐색 중이라면, 사이클이 만들어진 것임.
    cnt++; // cur번 학생을 센다
    for(int i=next; i!=cur; i=choice[i]) // 사이클을 돌며, cur번 학생으로 돌아오기 전까지 학생들의 수를 센다
      cnt++;
  }
  visit[cur] = 2; // cur번 학생 탐색 완전 끝.
}

알고리즘 스터디 2주차에서 DFS 배우면서 소개되었던 문제. 문제 풀 때 처음에는 다음과 같은 방식으로 풀었다. 
i번 학생의 선택을 따라가다가 이미 선택된 학생을 선택하게 되었을 때, 그게 자신(i번 학생)이라면 자신은 팀에 속한 학생인 것이고, 자신이 아니라면 팀에 속하지 않은 학생이 된다. 이 과정을 i는 1부터 n까지 반복한다면 1~n번 학생이 팀에 속했는지 안 속했는지 구할 수 있다. (밑에 코드 있음)
int dfs(int cur, vector<int> *adj, bool *visit);

int main() {
  int T, n, temp;
  int total = 0;

  scanf("%d", &T);
  for(int i=0; i<T; i++){
    scanf("%d", &n);
    vector<int> adj[n+1];
    
    for(int j=1; j<=n; j++){
      scanf("%d", &temp);
      adj[j].push_back(temp);
    }

    for(int j=1; j<=n; j++){
      bool visit[n+1];
      std::fill_n(visit+1, n, false);
      if(dfs(j, adj, visit)!=j)
        total += 1;
    }

    printf("%d\n", total);
    total = 0;
  }

  return 0;
}

int dfs(int cur, vector<int> *adj, bool *visit){
  if(visit[cur])
    return cur;
  visit[cur] = true;
  return dfs(adj[cur][0], adj, visit);
}
사실 이렇게 풀면서 adj, visit을 main 함수 안에서 선언하는 바람에 dfs에 인자로 넘겨줘야하는 귀찮은 일이 생겼는데, 그건 c++ 벡터를 처음 다루는 바람에 몰라서 그랬던 거니까 넘어가고...
제일 큰 문제는 시간초과가 난다는 것임. 아마 70행에서 visit 배열에 false를 다 채우는 과정(i번 학생 팀 소속 여부를 구한 후, i+1번 학생 팀 소속 여부 구할 때 visit 값을 리셋하는 과정)이 있는데, visit 배열의 길이는 n이고 이걸 n번 반복하니 O(n^2)라서 당연히 시간초과가 나는 것일듯.

사실 시간초과 난다는 문제 빼면 풀이 방식이 꽤 간단하고 간결해서 이게 답일 줄 알았는데.. 아니었다. 중요한 건 시간초과가 안 나게 하기 위해 visit 배열을 n번 리셋하는 일이 없게 한 번에 탐색해야 한다는 것. 즉, 한번 탐색한 학생은 다시 탐색하지 않는 것. 이걸 아는 게 중요했던 것 같다.

이거 말고 특이사항으로는 fill이랑 fill_n 함수인데, 둘다 std에 있는 거라고 생각했는데 fill_n이 algorithm 라이브러리에도 있다고 함. 질문 올려도 답이 안 달려서 뭐가뭔지 잘 모르겠다.. 일단 그냥 써보는 걸로.
*/