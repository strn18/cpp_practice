#include <iostream>
#define MAX 11
#define INF 2100000000

using namespace std;

int N, max_val = -INF, min_val = INF;
int num[MAX], oper[4];

void choose(int val, int depth);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> num[i];
  
  for(int i=0; i<4; i++)
    cin >> oper[i];
  
  choose(num[0], 0);

  cout << max_val << '\n' << min_val;

  return 0;
}

void choose(int val, int depth){
  int next;

  if(depth == N-1){
    max_val = max(max_val, val);
    min_val = min(min_val, val);
    return;
  }

  for(int i=0; i<4; i++){
    if(oper[i] == 0) continue;

    oper[i]--;
    
    if(i==0) next = val + num[depth+1];
    else if(i==1) next = val - num[depth+1];
    else if(i==2) next = val * num[depth+1];
    else next = val / num[depth+1];

    choose(next, depth+1);

    oper[i]++;
  }
}