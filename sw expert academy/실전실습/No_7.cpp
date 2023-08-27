#include <vector>
#define MAX 1048576 // 100만 이상인 첫 2의 제곱수
#define INF 2100000000
#define MOD 1000000

using namespace std;

int colSize, leafNum; // 격자판의 열의 개수, 리프 노드의 개수
long long blockNum; // 블록의 총 개수(사라진 블록들도 포함)

pair<int, int> tree[MAX * 2]; // {최솟값, 최댓값}
int lazy[MAX * 2];

void construct(int N){
  leafNum = 1;
  blockNum = 0;

  while(leafNum < N) leafNum *= 2;

  for(int i = 1; i < leafNum + N; i++){ // internal nodes와, colSize개의 리프 노드 값에 초깃값인 0 대입.
    tree[i].first = 0;
    tree[i].second = 0;
    
    lazy[i] = 0;
  }

  for(int i = leafNum + N; i < leafNum * 2; i++){ // 나머지 더미 리프 노드에는 {INF, 0}을 넣어 최솟값/최댓값 찾기를 방해하지 않도록 함.
    tree[i].first = INF;
    tree[i].second = 0;
    
    lazy[i] = 0;
  }
}

void propagate(int nodeNum){
  if(lazy[nodeNum] == 0) return;

  if(nodeNum < leafNum){ // 리프 노드가 아니라면 자식에게 전파
    lazy[nodeNum*2] += lazy[nodeNum];
    lazy[nodeNum*2 + 1] += lazy[nodeNum];
  }

  tree[nodeNum].first += lazy[nodeNum];
  tree[nodeNum].second += lazy[nodeNum];

  lazy[nodeNum] = 0;
}

void add(int L, int R, int val, int nodeNum, int nodeL, int nodeR){
  propagate(nodeNum);

  if(nodeR < L || R < nodeL) return;
  if(L <= nodeL && nodeR <= R){ // 만약 nodeNum의 범위가 [L, R]에 다 들어온다면? nodeNum 범위의 최솟값, 최댓값은 반드시 + val만큼 갱신됨.
    lazy[nodeNum] += val;
    propagate(nodeNum);
    return;
  }

  int mid = (nodeL + nodeR) / 2; // 그렇지 않다면, 자식 노드로 재귀를 쳐준다.

  add(L, R, val, nodeNum*2, nodeL, mid);
  add(L, R, val, nodeNum*2 + 1, mid + 1, nodeR);

  tree[nodeNum].first = min(tree[nodeNum*2].first, tree[nodeNum*2 + 1].first); // 그런 다음, 갱신된 자식 노드들의 값으로 자신의 값을 갱신.
  tree[nodeNum].second = max(tree[nodeNum*2].second, tree[nodeNum*2 + 1].second);
}

pair<int, int> find(void){
  propagate(1);

  return {tree[1].first, tree[1].second};
}

struct Result{
  int top;
  int count;
};

void init(int C)
{
  colSize = C;
  blockNum = 0;

  construct(C);
}

Result dropBlocks(int mCol, int mHeight, int mLength)
{
  add(mCol + 1, mCol + mLength, mHeight, 1, 1, colSize); // 1번째 ~ colSize번째 리프 노드만 본다. 그 다음 노드들은 필요 x.

  Result ret;

  pair<int, int> result = find();

  ret.top = result.second - result.first; // 남은 블록의 높이 = 그동안 쌓인 블록(사라진 것도 포함)들의 최대 높이 - 최소 높이
  
  blockNum += (mHeight * mLength); // 블록 개수 갱신
  ret.count = (blockNum - ((long long)result.first * colSize)) % MOD; // 총 블록 개수 - 사라진 블록

  return ret;
}

/*
너무 어려워서 해설 참조하면서 풀었던 문제. https://blog.naver.com/kks227/220824350353 여기도 참고했음. 
일반 세그먼트 트리의 변형으로, 레이지 프로퍼게이션(Lazy Propagation)이라는 개념이 사용되었다.

해설이랑 블로그 글 보면서 대충 섞어가면서 내 스타일대로 짜봤다. 우선 해설과 다른 점은, 해설 코드에서는 add를 해준 다음에, 놓여있는 
블록들 중 최소 높이를 구하고, 그걸 이용해서 -그 높이 만큼 add를 다시 해줘서 블록이 터져서 사라지는 걸 직접 코드에 구현해놨다. 
나는 그 대신에, 터져서 사라지게 하지 않고 그냥 남겨놨음. 즉, 내 코드에서는 최소 높이가 2, 최대 높이가 5라면 실제로 남아 있는 블록의 
높이는 3이고, 2행 만큼의 블록들은 터져서 사라진 것이다. 해설 코드에서는 add를 한 후 최소 높이가 2가 되었다면 add(..., -2)를 해줘서 
사라진 만큼 값을 줄여주는 방식이었다.

이걸 이용해서, 남은 블록의 개수를 구하는 부분(98행)도 좀 다르게 짰다.

그리고 그동안 풀었던 일반 세그먼트 트리와 다르게, 89행에서 특정 범위에 add를 해줄 때, nodeNum 노드가 가리키는 범위인 nodeL, nodeR에서, 
nodeR로 원래 leafNum을 주곤 했었는데 여기서는 colSize를 줬다. 딱 필요한 부분(실제로 값이 존재하는 부분. 더미 리프 노드 부분 전까지.)을 
범위로 잡아서 add를 해줬음. 이걸 안 하니깐 값이 틀리게 나왔다. 사실 잘 이해는 안 가는데 일단 그렇게 짰음.

나머지 자세한 풀이는 해설이랑 블로그 글 참조.
*/