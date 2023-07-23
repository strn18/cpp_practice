// [S/W 문제해결 응용] 3일차 - 공통조상(4. 트리)
#include <iostream>
#include <string>
#define MAX 10000

using namespace std;

typedef struct{
  int left, right, parent;
} node;

node tree[MAX+1];
bool visited[MAX+1];

void init(int V);
int visit_ancestors(int num);
int count_subtree(int num);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int V, E, A, B, common;

    cin >> V >> E >> A >> B;

    init(V);

    for(int i=0; i<E; i++){
      int p, c;

      cin >> p >> c;

      if(tree[p].left == -1) tree[p].left = c;
      else tree[p].right = c;

      tree[c].parent = p;
    }

    visit_ancestors(A);
    common = visit_ancestors(B);

    cout << '#' << t << ' ' << common << ' ' << count_subtree(common) << '\n';
  }

  return 0;
}

void init(int V){
  for(int i=1; i<=V; i++){
    tree[i].left = -1;
    tree[i].right = -1;

    visited[i] = false;
  }
}

int visit_ancestors(int num){
  if(num == 1) return 1;

  if(visited[num]) return num;
  else{
    visited[num] = true;  
    return visit_ancestors(tree[num].parent);
  }
}

int count_subtree(int num){
  if(num == -1) return 0;

  return count_subtree(tree[num].left) + 1 + count_subtree(tree[num].right);
}

/*
낫배드인 문제

어떻게 풀까 하다가 그냥 간단하게 풀기로 함. 두 노드 A, B의 공통 조상을 구하기 위해, 우선 A의 조상을 타고 쭉쭉 올라가면서 visited 표시를 해준다.
그런 다음, B에 대해서도 똑같이 하는데, 그러다가 visited가 true인 놈을 찾으면? 걔가 첫(가장 가까운) 공통 조상이다.

걔를 찾았으면, 그것의 subtree는 그냥 재귀식으로 쉽게 구해주면 된다(72행).
*/