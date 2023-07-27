// [S/W 문제해결 응용] 4일차 - 하나로(5. 그래프)
#include <iostream>
#include <queue>
#include <cmath>
#define MAX 1000

using namespace std;

int X[MAX], Y[MAX];

double length(int a, int b);

int main(){
  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N;
    double E;

    cin >> N;

    for(int i=0; i<N; i++)
      cin >> X[i];
    for(int i=0; i<N; i++)
      cin >> Y[i];

    cin >> E;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    int count = 0;
    double total_cost = 0;
    bool visited[MAX] = {false};

    pq.push({0, 0});

    while(count < N){
      double cost = pq.top().first;
      int num = pq.top().second;

      pq.pop();

      if(visited[num]) continue;

      visited[num] = true;
      count++;
      total_cost += cost;

      for(int i=0; i<N; i++){
        if(visited[i]) continue;

        pq.push({length(num, i), i});
      }
    }

    cout << fixed;
    cout.precision(0);
    cout << '#' << t << ' ' << round(total_cost * E) << '\n';
  }

  return 0;
}

double length(int a, int b){
  return (pow(X[a]-X[b], 2) + pow(Y[a]-Y[b], 2));
}

/*
걍 MST 문제로, 크루스칼/프림 쓰면 되는 문젠데 왜 그래프 강의에 딸려있는지 모르겠네
*/