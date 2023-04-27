#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int a, b;

  cin >> a >> b;

  int small = min(a, b);
  int G, L;

  for(int i=1; i<=small; i++)
    if(a%i==0 && b%i==0)
      G = i;
      
  L = (a*b)/G;

  cout << G << '\n' << L;

  return 0;
}

/*
두 수의 최대공약수 & 최소공배수 구하는 문제. 처음에는 최소공배수 구할 때 그냥 min(a, b)부터 1씩 증가시키면서 찾았지만, 
https://www.acmicpc.net/source/59958092 이 풀이를 보니깐 최소공배수 = 두 수의 곲 / 최대공약수 였음. 그거대로 바꾸니까 시간 줄었다.
*/