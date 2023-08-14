#include <iostream>
#include <vector>
#define MAX 50

using namespace std;

typedef struct{
  vector<int> child;
  bool valid;
} info;

info node[MAX];

void make_invalid(int num);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, target, ans = 0;

  cin >> N;

  for(int i=0; i<N; i++){
    node[i].child = vector<int>();
    node[i].valid = true;
  }

  for(int i=0; i<N; i++){
    int p;

    cin >> p;

    if(p != -1) node[p].child.push_back(i);
  }

  cin >> target;

  make_invalid(target);

  for(int i=0; i<N; i++)
    if(node[i].valid && node[i].child.size() == 0) ans++;
  
  for(int i=0; i<N; i++)
    if(node[i].child.size() == 1 && node[i].child[0] == target) ans++;

  cout << ans;

  return 0;
}

void make_invalid(int num){
  node[num].valid = false;

  for(int i=0; i<node[num].child.size(); i++)
    make_invalid(node[num].child[i]);
}

/*
첫 풀이는 잘못 풀었는데 맞았다... 이진트리라고 생각하고 left, right 자식을 두는 구조체를 만들어서 풀었는데 다 풀고 다른 풀이 보니깐 이진트리가 
아니었음. 그래서 수정함.

우선 어떤 노드의 자식을 벡터에 저장한다. 그런 다음, 삭제할 노드를 받아 dfs로 그 후손 노드들까지 모두 삭제(valid 값이 false)해준다. 
그런 다음, 모든 노드(0 ~ N-1번)를 돌면서, valid하고 child가 0개라면 ans++ 해준다. 그런데 이때, 딱 한가지를 더 고려해야 함. 만약 삭제한 노드의 
부모 노드가, 자식이 딱 하나(삭제한 노드)였다면? 해당 부모 노드는 이제 리프 노드가 된다. 그걸 찾아보고 있으면 ans++ 해주면 된다(45행).
그러면 삭제한 노드의 부모 노드가 자식이 두 개 이상이라면? 노드를 삭제해도 어차피 자식이 하나 이상 남으니까 알 바 아니다.
*/