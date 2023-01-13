/*
#include <iostream>

using namespace std;

int N;
char tree[26][2]; // tree[i][j]는 i번째 알파벳(0-base)의 왼쪽(j=0)/오른쪽(j=1) 자식임

void preOrder(int index); // 전위 순회
void inOrder(int index); // 중위 순회
void postOrder(int index); // 후위 순회

int main(){
  char temp;
  
  cin >> N;
  for(int i=0; i<N; i++){
    cin >> temp;
    cin >> tree[temp-65][0] >> tree[temp-65][1]; // 왼쪽, 오른쪽 자식 기록하기
  }

  preOrder(0);
  cout << endl;
  inOrder(0);
  cout << endl;
  postOrder(0);
  
  return 0;
}

void preOrder(int index){
  char left = tree[index][0], right = tree[index][1];
  
  printf("%c", index+65); // 현재 노드 출력하고
  
  if(left != '.')
    preOrder(left-65); // 왼쪽 자식을 전위 순회

  if(right != '.')
    preOrder(right-65); // 오른쪽 자식을 전위 순회
}

void inOrder(int index){
  char left = tree[index][0], right = tree[index][1];

  if(left != '.')
    inOrder(left-65); // 왼쪽 자식을 중위 순회하고

  printf("%c", index+65); // 현재 노드 출력

  if(right != '.')
    inOrder(right-65); // 오른쪽 자식을 중위 순회
}

void postOrder(int index){
  char left = tree[index][0], right = tree[index][1];

  if(left != '.')
    postOrder(left-65); // 왼쪽 자식을 후위 순회하고

  if(right != '.')
    postOrder(right-65); // 오른쪽 자식을 후위 순회

  printf("%c", index+65); // 끝으로 현재 노드 출력
}
*/