#include <iostream>
#include <vector>
#define MAX 50

using namespace std;

int parent[MAX+1];

void union_root(int x, int y);
int find_root(int x); // root가 0이면 진실을 아는 사람임

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, T, count = 0;
  vector<int> party[MAX];

  cin >> N >> M >> T;

  for(int i=1; i<=N; i++)
    parent[i] = i;
  
  for(int i=0; i<T; i++){
    int num;
    cin >> num;
    parent[num] = 0;
  }

  for(int i=0; i<M; i++){
    int n;
    cin >> n;

    for(int j=0; j<n; j++){
      int num;
      cin >> num;
      party[i].push_back(num);
    }

    for(int j=1; j<party[i].size(); j++)
      union_root(party[i][j-1], party[i][j]);
  }

  for(int i=0; i<M; i++)
    if(find_root(party[i][0]) != 0) count++;

  cout << count;

  return 0;
}

void union_root(int x, int y){
  int rx = find_root(x);
  int ry = find_root(y);

  if(rx < ry) parent[ry] = rx;
  else parent[rx] = ry;
}

int find_root(int x){
  if(parent[x] == x) return x;

  return parent[x] = find_root(parent[x]);
}

/*
분리 집합 태그 보고 들어온 문제였는데, 문제 좀 읽어보니 "여기에 왜 유니온 파인드를 쓰지?"라는 생각이 들었음. 

어차피 N, M이 모두 최대 50이니까, 그냥 모든 파티의 모든 구성원들 다 돌아보면서, 만약 한 명이라도 진실을 아는 사람일 경우 그 파티의 모든 
구성원들을 진실을 아는 사람으로 만들어줌. 만약 그 파티의 모든 사람들이 진실을 모르는 사람일 경우, 그 파티에는 거짓말을 할 수 있음. 
이렇게 모든 파티를 다 도는 걸 반복해서, 모든 파티의 상태(거짓말을 할 수 있다/없다)가 변화가 없을 경우, 반복을 끝내고 정답을 출력한다.

이런 방식으로 풀었는데 맞았다(첫번째 제출). 근데 왜 유니온 파인드 문제였는지 궁금해서 https://hagisilecoding.tistory.com/133 여기를
참고했는데, 내가 처음에 한 생각이 약간 틀렸다는 걸 알게 됨. 

나는 처음에 "어차피 모든 파티 도는 걸 여러 번 해야할 것 같은데, 거기서 굳이 유니온 파인드 쓰느니 그냥 bool 배열 써서(위의 방식처럼)
푸는 게 빠르지 않을까?" 싶었는데, 블로그 풀이 잘 읽어보니깐 유니온 파인드를 쓸 경우 모든 파티 돌아보는 걸 한 번만 해도 답을 구할 수 있다.

어떠한 파티의 구성원들에 대해, 둘씩 묶어 union을 계속 해준다(40행). 이렇게 하면, 그 파티의 구성원들은 공통한 root를 가지게 됨. 이때, root가
0일 경우 진실을 아는 것이고 0이 아니면 모르는 것임. 이걸 모든 파티에 대해서 한 번만 해주면(이때, 진실을 원래 알고 있던 사람의 root값은 이미
0으로 되어 있음), 각 파티의 구성원들이 진실을 아는지 모르는지 바로 구할 수 있다.

예를 들어, {1, 2}, {2, 3}, {3, 4}라는 파티가 있고, 4가 진실을 안다고 하자. 위의 과정을 1~2번째 파티에 대해서 해주면, 1 2 3은 모두 root로
1을 가진다. 여기까지는 1 2 3 모두 진실을 모르는 상태임. 근데 3번째 파티에 대해서 해주게 되면, 4의 root는 0이므로 3과 union 해주었을 때 3도
root가 0이 됨. 즉, 3의 원래 root였던 1의 root가 0이 되는 것이므로, 1 2 3 모두 root가 0이 된다. 

이처럼, 유니온 파인드를 쓸 경우 모든 파티를 도는 것을 한 번만 해줘도 답을 구할 수 있었음. 블로그 풀이랑 다른 점으로는, 블로그에서는 마지막 부분
(여기서는 44행)에서 각 파티의 모든 구성원들의 root를 다 체크해줬는데, 잘 생각해보니깐 굳이 그럴 필요가 없어보였음. 어차피 각 구성원들은 공통의
root를 가지니깐 한 명만 확인하면 되는 것 같아보여서, 그렇게 하고 제출했더니 맞았다.
*/