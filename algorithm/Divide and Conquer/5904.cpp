#include <iostream>
#define MAX 30

using namespace std;

long long moo_len[MAX];

char moo(int k, int n);

int main(){
  int N, K;

  moo_len[0] = 3;
  for(int i=1; i<MAX; i++)
    moo_len[i] = (moo_len[i-1]*2 + (i+3));

  scanf("%d", &N);

  for(int i=0; i<MAX; i++){
    if(N <= moo_len[i]){
      K = i;
      break;
    }
  }

  printf("%c", moo(K, N));

  return 0;
}

char moo(int k, int n){
  if(k==0)
    return (n == 1 ? 'm' : 'o');

  if(n <= moo_len[k-1])
    return moo(k-1, n);
  else if(moo_len[k] - moo_len[k-1] < n)
    return moo(k-1, n - (moo_len[k-1] + (k+3)));
  else
    return (n == moo_len[k-1]+1 ? 'm' : 'o');
}

/*
쉬웠던 분할정복 문제.
우선, 길이가 N 이상이 되는 첫 S(i)를 구한다. 가령 N이 11이면, 길이가 11 이상이 되는 S(i)는 S(2)이므로, i는 2가 된다. 이 과정은, S(i)의
길이를 저장하는 배열인 moo_len를 i=0일 때부터 bottom-up으로 값을 채워준다. 그 다음, 20행에서 찾아준다.

그러고 나서, S(k)의 n번째 글자를 찾아 리턴하는 moo 함수를 사용한다. moo 함수는 만약 k가 0일 경우, n이 1이면 m을, 아니면 o를 리턴한다.
k가 0이 아닌 경우에는, 만약 n번째 글자가 S(k)의 왼쪽 부분(S(k-1)에 해당하는 부분)에 있으면(35행), k-1에 대해서 moo 함수를 다시 실행한다.
만약 오른쪽 부분에 있으면(37행), 마찬가지로 k-1에 대해서 실행하는데, 이때 n 값은 S(k-1)에 맞게 줄여준다.
만약 중간 부분(m과 k+2개의 o로 만든 부분)에 있으면, 위치에 따라 m 또는 o를 리턴한다.

n값을 잘 조정해주는 것만 신경쓰면 어렵지 않았음.
*/