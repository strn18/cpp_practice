// 수열편집(3. 연결리스트)
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct Node{
  int val;
  struct Node *next;
} Node;

Node *head;

void insert_node(int idx, int num);
void delete_node(int idx);
void change_node(int idx, int num);
void print_node(int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M, L;

    head = NULL;

    cin >> N >> M >> L;

    for(int i=0; i<N; i++){
      int num;
      cin >> num;
      insert_node(i, num);
    }

    for(int i=0; i<M; i++){
      char ch;
      int idx, num;

      cin >> ch;

      if(ch == 'I'){
        cin >> idx >> num;
        insert_node(idx, num);
      }
      else if(ch == 'D'){
        cin >> idx;
        delete_node(idx);
      }
      else{
        cin >> idx >> num;
        change_node(idx, num);
      }
    }

    cout << '#' << t << ' ';
    print_node(L);
    cout << '\n';
  }

  return 0;
}

void insert_node(int idx, int num){
  Node *new_node = (Node*)malloc(sizeof(Node));
  new_node->val = num;

  if(idx == 0){
    new_node->next = head;
    head = new_node;
  }
  else{
    Node *target = head;

    for(int i=1; i<idx; i++)
      target = target->next;
    
    new_node->next = target->next;
    target->next = new_node;
  }
}

void delete_node(int idx){
  Node *temp;

  if(idx == 0){
    temp = head;
    head = head->next;

    free(temp);
  }
  else{
    Node *target = head;

    for(int i=1; i<idx; i++)
      target = target->next;

    temp = target->next;
    target->next = temp->next;
    
    free(temp);
  }
}

void change_node(int idx, int num){
  Node *target = head;

  for(int i=0; i<idx; i++)
    target = target->next;
  
  target->val = num;
}

void print_node(int idx){
  Node *target = head;

  for(int i=0; i<idx && target!=NULL; i++)
    target = target->next;
  
  if(target == NULL) cout << -1;
  else cout << target->val;
}