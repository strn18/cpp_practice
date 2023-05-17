#include <iostream>
#include <queue>
#define MAX 1000
#define ll long long

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  ll total = 0;
  priority_queue<ll, vector<ll>, greater<ll>> pq;

  cin >> n >> m;

  for(int i=0; i<n; i++){
    int num;

    cin >> num;

    pq.push(num);
  }

  for(int i=0; i<m; i++){
    ll a = pq.top(); pq.pop();
    ll b = pq.top(); pq.pop();
    pq.push(a+b); pq.push(a+b);
  }
  
  while(!pq.empty()){
    total += pq.top();
    pq.pop();
  }

  cout << total;

  return 0;
}

/*
기초적인 pq 문제. 오버플로우만 조심하면 됨.
*/