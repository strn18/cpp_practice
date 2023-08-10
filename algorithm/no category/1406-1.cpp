#include <iostream>
#include <string>

using namespace std;

typedef struct node{
  char ch;
  struct node *prev, *next;
} node;

node *head, *tail;

void add_node(node *cur, char ch); // cur 노드의 이전에 넣기
void del_node(node *cur); // cur 노드의 이전 노드 삭제

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string str;
  int M;

  head = new node;
  tail = new node;

  head->ch = '?';
  head->prev = nullptr;
  head->next = tail;

  tail->ch = '!';
  tail->prev = head;
  tail->next = nullptr;

  cin >> str;

  node *cur = tail;
  
  for(int i=0; i<str.size(); i++)
    add_node(cur, str[i]);

  cin >> M;

  while(M--){
    string choice;

    cin >> choice;

    if(choice == "L"){
      if(cur->prev != head) cur = cur->prev;
    }
    else if(choice == "D"){
      if(cur != tail) cur = cur->next;
    }
    else if(choice == "B"){
      del_node(cur);
    }
    else{
      string ch;
      cin >> ch;
      add_node(cur, ch[0]);
    }
  }

  cur = head->next;

  while(cur != tail){
    cout << cur->ch;
    cur = cur->next;
  }

  return 0;
}

void add_node(node *cur, char ch){
  node *new_node = new node;

  new_node->ch = ch;
  new_node->prev = cur->prev;
  new_node->next = cur;

  (cur->prev)->next = new_node;

  cur->prev = new_node;
}

void del_node(node *cur){
  if(cur->prev == head) return;

  node *target = cur->prev;

  cur->prev = target->prev;
  (target->prev)->next = cur;

  delete target;
}

/*
링크드 리스트 구현해서 풀었음. malloc 말고 new로 동적할당 하는 거 처음 써봤다. 근데 풀고나서 찾아보니깐 스택으로 푸는 더 쉬운 풀이가 있는 것 
같아서 그걸로도 풀어봄.
*/