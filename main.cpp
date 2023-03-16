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