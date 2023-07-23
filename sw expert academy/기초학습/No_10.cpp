// [S/W 문제해결 기본] 9일차 - 사칙연산(4. 트리)
#include <iostream>
#include <string>
#define MAX 1000

using namespace std;

typedef struct{
  int left, right, val;
  char op;
} node;

node tree[MAX+1];

int str_to_int(string val);
double in_order(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  TC = 10;

  for(int t=1; t<=TC; t++){
    int N, ans;

    cin >> N;

    for(int i=0; i<N; i++){
      int num, left, right;
      string val;

      cin >> num >> val;

      if('0'<=val[0] && val[0]<='9'){
        tree[num].left = -1;
        tree[num].right = -1;
        tree[num].val = str_to_int(val);
      }
      else{
        cin >> left >> right;

        tree[num].left = left;
        tree[num].right = right;
        tree[num].op = val[0];
      }
    }

    ans = in_order(1);

    cout << '#' << t << ' ' << ans << '\n';
  }

  return 0;
}

int str_to_int(string val){
  int result = 0;

  for(int i=0; i<val.size(); i++){
    result *= 10;
    result += val[i]-'0';
  }

  return result;
}

double in_order(int n){
  int left_idx = tree[n].left;
  int right_idx = tree[n].right;

  if(left_idx == -1) return tree[n].val;

  double left_val = in_order(left_idx);
  double right_val = in_order(right_idx);

  if(tree[n].op == '+') return left_val + right_val;
  else if(tree[n].op == '-') return left_val - right_val;
  else if(tree[n].op == '*') return left_val * right_val;
  else return left_val / right_val;

}

/*
드디어 입력이 쫌 정상적인 트리 순회 문제가 나옴. 연산자 노드일 경우 왼쪽과 오른쪽 자식을 모두 입력받고, 숫자 노드일 경우 자식을 입력받지 않는다.
in_order 함수가 해당 서브 트리의 순회 결과값을 가지도록 하면 쉽게 구할 수 있음.
*/