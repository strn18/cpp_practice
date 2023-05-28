#include <iostream>
#include <cmath>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;

  cin >> n >> m;

  int count2 = 0, count5 = 0;

  for(int i=1; pow(2, i)<=n; i++){
    int cur = pow(2, i);
    count2 += (n/cur) - ((n-m)/cur);
  }

  for(int i=1; pow(5, i)<=n; i++){
    int cur = pow(5, i);
    count5 += (n/cur) - ((n-m)/cur);
  }

  for(int i=1; pow(2, i)<=m; i++){
    int cur = pow(2, i);
    count2 -= (m/cur);
  }

  for(int i=1; pow(5, i)<=m; i++){
    int cur = pow(5, i);
    count5 -= (m/cur);
  }

  cout << min(count2, count5);

  return 0;
}