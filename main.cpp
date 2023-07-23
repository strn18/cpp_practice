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