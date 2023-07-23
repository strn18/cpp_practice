// [S/W 문제해결 기본] 9일차 - 중위순회(4. 트리)
#include <iostream>
#include <string>
#define MAX 100

using namespace std;

typedef struct{
  int left, right;
  char ch;
} node;

node tree[MAX+1];

void in_order(int num);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  TC = 10;

  for(int t=1; t<=TC; t++){
    int N;

    cin >> N;

    for(int i=0; i<N; i++){
      int num, left, right;
      char ch, next;

      cin >> num >> ch;
      tree[num].ch = ch;

      next = cin.get();

      if(next == '\n'){
        tree[num].left = -1;
        tree[num].right = -1;
        continue;
      }

      cin >> left;
      tree[num].left = left;

      next = cin.get();

      if(next == '\n'){
        tree[num].right = -1;
        continue;
      }

      cin >> right;
      tree[num].right = right;
    }

    cout << '#' << t << ' ';

    in_order(1);

    cout << '\n';
  }

  return 0;
}

void in_order(int num){
  if(tree[num].left != -1) in_order(tree[num].left);

  cout << tree[num].ch;

  if(tree[num].right != -1) in_order(tree[num].right);
}

/*
진짜 여기는 왜 자꾸 ㅈ같이 만들어둔 문제밖에 없징????? 그냥 중위순회하면 되는 문제인데, 괜히 쓸데없이 까다롭게 해놨다.

두 자식이 모두 주어질 경우 1 A 2 3 이렇게 주어지는데, 왼쪽 자식만 주어지면 1 A 2 이렇게 주어지고, 자식이 없으면 1 A 이렇게만 주어짐.
그렇기 때문에 cin >> num >> ch >> left >> right 이렇게 못 하고, 셋 중에 어느 입력인지를 또 판단해야 됨.

처음에는 한 줄 전체를 string으로 입력받아 그 길이 보고 판단하려 했는데, 생각해보니까 num이 10이나 100이 되면 그때 또 길이가 달라지는 걸
판단해야 해서 안 됨. 그래서 어떻게 할까 하다가 https://luyin.tistory.com/334 여기 보고, cin.get()을 통해 빈 칸 or 개행문자를 입력받아서
판단하기로 함. 우선 num과 ch는 무조건 주어지니 입력받으면 됨. 그런 다음 37행애서 cin.get()으로 문자 하나를 입력받음. 얘가 개행이라면?
입력 끝이므로 continue. 빈 칸이라면? 우선 왼쪽 자식을 입력받고, 똑같이 cin.get()으로 next에 다시 입력받음. 얘가 개행이라면? 입력 끝(왼쪽
자식만 있음)이므로 continue. 빈 칸이라면? 오른쪽 자식도 마저 입력받음.

하여튼 왜 자꾸 쓸데없이 꼬아놓는지 모르겠다. 정작 in_order 함수는 별 것도 아닌데
*/