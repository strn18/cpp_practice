#include <iostream>
#define MAX 1048576 // 100만 이상인, 최소의 2의 제곱수.

using namespace std;

int num_size = 1; // N 이상인, 최소의 2의 제곱수. 세그먼트 트리에서 리프 노드의 개수와 같다.

long long node[MAX*2]; // 세그먼트 트리의 노드. 1-based index.
long long num[MAX+1]; // 주어지는 숫자. 1-based index.

void construct(int N); // 세그먼트 트리에 값을 채운다.
long long sum(int L, int R, int node_num, int node_L, int node_R); // [L, R]의 구간합을 구한다. 현재 node_num번 노드를 보고 있으며, 
// 해당 노드는 [node_L, node_R]의 구간합을 값으로 갖는다.
void update(int idx, long long val); // idx번째 숫자를 val로 바꾼다.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M, K;

  cin >> N >> M >> K;

  for(int i=1; i<=N; i++)
    cin >> num[i];

  construct(N);
  
  for(int i=0; i<M+K; i++){
    int a, b;
    long long c;

    cin >> a >> b >> c;

    if(a==1) update(b, c);
    
    else cout << sum(b, c, 1, 1, num_size) << '\n';
  }

  return 0;
}

void construct(int N){
  while(N > num_size) num_size *= 2;

  for(int i=0; i<N; i++)
    node[num_size + i] = num[i+1]; // 우선 세그먼트 트리의 리프 노드에 값을 채운다.
  
  for(int i=num_size-1; i>=1; i--)
    node[i] = node[i*2] + node[i*2 + 1]; // 이후 나머지 노드에 값을 채운다.
}

long long sum(int L, int R, int node_num, int node_L, int node_R){
  if(node_R < L || R < node_L) return 0; // 만약 지금 보는 노드의 범위가 [L, R]을 완전히 벗어났으면 그냥 리턴.
  if(L <= node_L && node_R <= R) return node[node_num]; // 완전히 포함됐으면 지금 노드의 값을 리턴. 

  int mid = (node_L + node_R)/2;

  return sum(L, R, node_num*2, node_L, mid) + sum(L, R, node_num*2 + 1, mid + 1, node_R); // 그렇지 않으면 반으로 나눈다.
}

void update(int idx, long long val){
  int i = num_size + idx-1; // [idx, idx]의 구간합을 값으로 갖는 노드의 인덱스는 i.

  node[i] = val;

  while(i > 1){
    i /= 2;
    node[i] = node[i*2] + node[i*2 + 1]; // 그 조상 노드들의 값도 바꿔주기.
  }
}

/*
처음 풀어본 세그먼트 트리 문제. 자세한 건 https://blog.naver.com/kks227/220791986409 여기 글과 상단 코드의 주석 참조.
*/