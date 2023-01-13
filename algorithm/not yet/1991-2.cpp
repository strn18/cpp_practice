/*
#include <iostream>

using namespace std;

char tree[26][2];
char temp;

void Pre(char node);
void In(char node);
void Post(char node);

int main(){
  int N;
  cin >> N;

  for(int i=0; i<N; i++){
    cin >> temp;
    cin >> tree[temp-'A'][0] >> tree[temp-'A'][1];
  }

  Pre('A');
  cout << endl;
  In('A');
  cout << endl;
  Post('A');
  cout << endl;
}

void Pre(char node){
  if(node == '.')
    return;
  cout << node;
  Pre(tree[node-'A'][0]);
  Pre(tree[node-'A'][1]);
}

void In(char node){
  if(node == '.')
    return;
  In(tree[node-'A'][0]);
  cout << node;
  In(tree[node-'A'][1]);
}

void Post(char node){
  if(node == '.')
    return;
  Post(tree[node-'A'][0]);
  Post(tree[node-'A'][1]);
  cout << node;
}

7576에 이어서 세 번째로 다시 풀어본 문젠데 어려운 건 딱히 없었다. 다만 자식 노드가 없는 경우(.) 관련해서 코드가 좀 더 간결해진듯
*/