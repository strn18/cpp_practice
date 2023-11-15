#include <iostream>
#define MAX 500000

using namespace std;

int parent[MAX];

int findRoot(int x);
void unionRoot(int x, int y); // x < y

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, ans = 0;

  cin >> n >> m;

  for(int i=0; i<n; i++)
    parent[i] = i;

  for(int i=1; i<=m; i++){
    int a, b;

    cin >> a >> b;

    if(ans == 0 && findRoot(a) == findRoot(b)){
      ans = i;
      break;
    }

    unionRoot(min(a, b), max(a, b));
  }

  cout << ans;

  return 0;
}

int findRoot(int x){
  if(parent[x] == x) return x;
  else return parent[x] = findRoot(parent[x]);
}

void unionRoot(int x, int y){
  int rx = findRoot(x);
  int ry = findRoot(y);

  parent[ry] = rx;
}

/*
시간이 오래 걸려서 왜이러나 싶었는데 29행에서 답을 찾으면 입력 더 이상 안 받고 break하도록 했더니 시간 줄어듦. 
*/