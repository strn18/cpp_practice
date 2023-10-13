#include <iostream>
#define ll long long

using namespace std;

int gcd(ll a, ll b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll A, B;
  int ans;

  cin >> A >> B;

  ans = gcd(min(A, B), max(A, B));

  while(ans--)
    cout << 1;

  return 0;
}

int gcd(ll a, ll b){
  if(b % a == 0) return a;
  else return gcd(b % a, a);
}

/*
1의 개수로 숫자가 표현되어 있지만 잘 생각해보면 그냥 유클리드 호제법으로 gcd 구하면 된다. 
*/