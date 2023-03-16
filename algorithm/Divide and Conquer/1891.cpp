#include <iostream>
#include <cmath>
#define ll long long
#define MAX 50

using namespace std;

ll R, C;
int d;
int num[MAX];

void find_pos(ll r, ll c, ll len, int depth);
void find_num(ll r, ll c, ll len, int depth);

int main(){
  ll x, y, max_len;

  scanf("%d", &d);
  max_len = pow(2, d);

  for(int i=0; i<d; i++)
    scanf("%1d", &num[i]);
  
  find_pos(0, 0, max_len, 0);

  scanf("%lld %lld", &x, &y);
  R -= y; C += x;

  if(0<=R && R<max_len && 0<=C && C<max_len){
    find_num(R, C, max_len, 0);    
    for(int i=0; i<d; i++)
      printf("%d", num[i]);  
  }
  else
    printf("-1");

  return 0;
}

void find_pos(ll r, ll c, ll len, int depth){
  if(len == 1){
    R = r; C = c;
    return;
  }

  len /= 2;

  if(num[depth] == 1)
    find_pos(r, c+len, len, depth+1);
  else if(num[depth] == 2)
    find_pos(r, c, len, depth+1);
  else if(num[depth] == 3)
    find_pos(r+len, c, len, depth+1);
  else
    find_pos(r+len, c+len, len, depth+1);
}

void find_num(ll r, ll c, ll len, int depth){
  if(len == 1) return;

  len /= 2;

  if(r<len && c>=len)
    num[depth] = 1;
  else if(r<len && c<len)
    num[depth] = 2;
  else if(r>=len && c<len)
    num[depth] = 3;
  else
    num[depth] = 4;
  
  find_num(r%len, c%len, len, depth+1);
}

/*
풀이 방법 자체는 어렵진 않은데, 범위 체크하느라 헷갈렸던 문제. 
1) 사분면 번호를 좌표로 변환하고, 또 반대로 2) 좌표를 사분면 번호로 변환하는 걸 해주면 된다.

나는 우선 1)은 번호의 맨 앞의 수부터 재귀적으로 찾아나가는 방식으로 했다. (r, c)에서 시작하고 변의 길이가 len인 정사각형에서, 구하고 싶은 좌표는
num[depth]사분면에 있으므로, 다시 해당 사분면에 대해서 find_pos를 쳐주었다. 그러다가 len가 1이 되면, 구한 좌표를 R, C에 저장해주고 종료.

그러고 나서, 해당 좌표에 x, y를 잘 더해주고, 그 결과값이 범위((0, 0)부터 ((2^d)-1, (2^d)-1)를 벗어난다면 -1을 출력하고, 그렇지 않으면 그 좌표를
다시 번호로 변환해준다. find_num은 (0, 0)에서 시작하고 변의 길이가 len인 정사각형에서, (r, c)는 몇사분면인지를 찾아 num에 순차적으로 기록한다.
원래는 num에 기록하는게 아니라 직접 그 번호를 구해서 출력했는데, 그렇게 하면 수가 50자리까지 커질 수 있어서 long long을 써도 오버플로우가 난다.
그래서 num에 하나하나 넣어주고 마지막에 다 출력하는 식으로 했다. 

이렇게 풀이를 써놓고 보니까 좀 쉬워보이는데, 풀면서는 좀 헷갈렸다. 자꾸 오버플로우도 나고 해서 원래 int로 했다가 long long으로 많이 바꿈.
*/