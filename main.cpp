#include <iostream>
#include <queue>
#include <string>
#define MAX 10000

using namespace std;

int D(int n);
int S(int n);
int L(int n);
int R(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int A, B;
    bool visited[MAX];
    queue<pair<int, string>> Q;

    cin >> A >> B;

    for(int i=0; i<MAX; i++)
      visited[i] = false;

    Q.push({A, ""});
    visited[A] = true;

    while(true){
      pair<int, string> cur = Q.front();
      Q.pop();

      if(cur.first == B){
        cout << cur.second << '\n';
        break;
      }

      int d = D(cur.first);
      int s = S(cur.first);
      int l = L(cur.first);
      int r = R(cur.first);

      if(!visited[d]){
        Q.push({d, cur.second+"D"});
        visited[d] = true;
      }
      if(!visited[s]){
        Q.push({s, cur.second+"S"});
        visited[s] = true;
      }
      if(!visited[l]){
        Q.push({l, cur.second+"L"});
        visited[l] = true;
      }
      if(!visited[r]){
        Q.push({r, cur.second+"R"});
        visited[r] = true;
      }
    }
  }

  return 0;
}

int D(int n){
  return (n*2) % MAX;
}

int S(int n){
  if(n == 0) return MAX-1;
  else return n-1;
}

int L(int n){
  n *= 10;
  n += (n/MAX);
  return n%MAX;
}

int R(int n){
  n += (n%10)*MAX;
  return n/10;
}

// #define MAX 100

// bool adj[MAX][MAX];
// bool visited[MAX];

// void dfs_init(int N, int path[100][2])
// {
//   for(int i=1; i<MAX; i++){
//     for(int j=1; j<MAX; j++)
//       adj[i][j] = false;
//     visited[i] = false;
//   }

//   for(int i=0; i<N-1; i++)
//     adj[path[i][0]][path[i][1]] = true;
// }

// int dfs(int n)
// {
//   int st[MAX];
//   int top = -1;

//   st[++top] = n;

//   while(top != -1){
//     int cur = st[top--];
//     visited[cur] = true;

//     if(cur > n) return cur;

//     for(int i=1; i<MAX; i++)
//       if(adj[cur][i] && !visited[i])
//         st[++top] = i;
//   }

//   return -1;
// }