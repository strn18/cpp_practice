#include <iostream>
#define MAX 131072
#define INF 1000000001

using namespace std;

int leafNum;
int arr[MAX];
int tree[MAX * 2];

void construct(int N);
int find(int L, int R, int nodeNum, int nodeL, int nodeR);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  cin >> N >> M;

  for(int i=1; i<=N; i++){
    cin >> arr[i];
  }

  construct(N);

  for(int i=0; i<M; i++){
    int a, b;

    cin >> a >> b;

    cout << find(a, b, 1, 1, leafNum) << '\n';
  }

  return 0;
}

void construct(int N){
  leafNum = 1;

  while(leafNum < N) leafNum *= 2;

  for(int i = leafNum; i < leafNum + N; i++)
    tree[i] = arr[i-leafNum + 1];
  
  for(int i = leafNum + N; i < leafNum * 2; i++)
    tree[i] = INF;
  
  for(int i = leafNum - 1; i >= 1; i--)
    tree[i] = min(tree[i*2], tree[i*2 + 1]);
}

int find(int L, int R, int nodeNum, int nodeL, int nodeR){
  if(nodeR < L || R < nodeL) return INF;
  if(L <= nodeL && nodeR <= R) return tree[nodeNum];

  int mid = (nodeL + nodeR) / 2;

  return min(find(L, R, nodeNum*2, nodeL, mid), find(L, R, nodeNum*2 + 1, mid + 1, nodeR));
}

/*
기초 세그먼트 트리 문제.
*/