// [S/W 문제해결 기본] 8일차 - 암호문3(3. 연결리스트)
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct crypto{
  int num;
  struct crypto *next;
} crypto;

crypto *head;
int list_size;

void add_list(int idx, int val);
void del_list(int idx);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  TC = 10;

  for(int t=1; t<=TC; t++){
    int N, M;

    cin >> N;

    head = (crypto*)malloc(sizeof(crypto));
    head->next = NULL;

    list_size = 0;

    for(int i=0; i<N; i++){
      int num;

      cin >> num;

      add_list(i, num);
    }

    cin >> M;

    for(int i=0; i<M; i++){
      char ch;
      int x, y, s;

      cin >> ch;

      if(ch == 'I'){
        cin >> x >> y;

        for(int j=0; j<y; j++){
          cin >> s;

          add_list(x+j, s);
        }
      }
      else if(ch == 'D'){
        cin >> x >> y;
        
        for(int j=0; j<y; j++)
          del_list(x);
      }
      else{
        cin >> y;

        for(int j=0; j<y; j++){
          cin >> s;

          add_list(list_size, s);
        }
      }
    }

    cout << '#' << t << ' ';

    crypto *cur = head;

    for(int i=0; i<10; i++){
      cout << cur->num << ' ';
      cur = cur->next;
    }
   
    cout << '\n';
  }

  return 0;
}

void add_list(int idx, int val){
  crypto *new_node = (crypto*)malloc(sizeof(crypto));
  new_node->num = val;

  list_size++;

  if(idx == 0){
    new_node->next = head;
    head = new_node;

    return;
  }

  crypto *target = head;

  for(int i=1; i<idx; i++)
    target = target->next;

  new_node->next = target->next;
  target->next = new_node;
}

void del_list(int idx){
  crypto *target = head;
  crypto *temp;

  list_size--;

  if(idx == 0){
    temp = head;
    head = head->next;

    free(temp);
    return;
  }

  for(int i=1; i<idx; i++)
    target = target->next;

  temp = target->next;
  target->next = temp->next;

  free(temp);
}

/*
준나 귀찮은 문제. 자꾸 런타임에러 떴었는데, 별 문제는 아니었고 그냥 list_size++ or list_size--를 빼먹었다든가, 삽입/삭제 시에 연결을 잘못했다든가
그런 문제였음.
*/