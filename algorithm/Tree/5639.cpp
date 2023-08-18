#include <iostream>
#define MAX 10000

using namespace std;

typedef struct{
  int val, left_idx, right_idx;
} info;

info node[MAX];
int node_count = 0;

void add_node(int idx, int val);
void post_order(int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int num;

  cin >> num;

  node[node_count++] = {num, -1, -1};

  while(cin >> num)
    add_node(0, num);

  post_order(0);

  return 0;
}

void add_node(int idx, int val){
  if(val < node[idx].val){
    if(node[idx].left_idx == -1){
      node[idx].left_idx = node_count;
      node[node_count++] = {val, -1, -1};
    }
    else add_node(node[idx].left_idx, val);
  }
  else{
    if(node[idx].right_idx == -1){
      node[idx].right_idx = node_count;
      node[node_count++] = {val, -1, -1};
    }
    else add_node(node[idx].right_idx, val);
  }
}

void post_order(int idx){
  if(node[idx].left_idx != -1) post_order(node[idx].left_idx);

  if(node[idx].right_idx != -1) post_order(node[idx].right_idx);

  cout << node[idx].val << '\n';
}

/*
우선, while(cin >> num) 이거를 배웠음. 주어지는 입력이, 몇 개인지(가령 숫자가 주어진다면 몇 개의 수가 주어지는지) 모를 때, 
while(cin >> num) 이렇게 한다면, EOF를 받을 때까지 num에 입력을 받게 되고, EOF에 도달한다면 while문을 탈출하게 된다.
https://velog.io/@c-jeongyyun/CPP-EOF-%ED%8C%90%EB%8B%A8%ED%95%98%EA%B8%B0 여기 참고.

그리고 나는 이 문제를 풀 때, 노드 정보를 나타내는 구조체를 만들어서, 특정 노드의 left, right child의 인덱스 기입하고, ... 하는 식으로 
풀었는데, https://ongveloper.tistory.com/295 여기를 보니까 더 간단한 풀이가 있었다. 자세한 건 링크 참조.
*/