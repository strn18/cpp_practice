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

/*
어렵지 않은 bfs 문제. https://www.acmicpc.net/problem/1697 이런 거랑 비슷한 류의 문제임.

존재할 수 있는 수의 종류가 10000가지(0~9999) 밖에 안 되기 때문에, 계속 4가지 연산을 적용하면서 bfs를 치다보면 제한 시간 내에 답을 얻을 수 있다.

우선 A를 큐에 넣는다. 이때, 원소 형태는 {수, 그 수를 얻기까지의 명령어들} 형태이다. 그 다음, while문에서 다음의 연산을 반복한다.
1) 큐의 front 꺼내기. 걔의 값이 B라면, second(명령어들) 출력하고 break.
2) B가 아니라면, 그 수로 만들 수 있는 4가지 결과값에 대해서, 각 결과값이 not visited라면 큐에 넣어줌(이때, 방금 사용한 명령어를 더하여).

다 풀고 다른 풀이도 찾아봤는데, https://donggoolosori.github.io/2020/10/05/boj-9019/ 내 풀이랑 거의 비슷했다.
*/