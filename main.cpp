#include <iostream>
#include <vector>
#define MAX 4000000

using namespace std;

bool not_prime[MAX+1] = {false};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;
  vector<int> prime = {0}; // prime[1]: 1번째 소수(2)
  vector<long long> p_sum = {0}; // p_sum[i]: 1~i번째 소수의 합

  cin >> N;

  for(int i=2; i<=N; i++){
    if(!not_prime[i]){
      prime.push_back(i);

      for(int j=2; i*j<=N; j++)
        not_prime[i*j] = true;
    }
  }

  for(int i=1; i<prime.size(); i++)
    p_sum.push_back(p_sum[i-1]+prime[i]);

  int s = 1, e = 1;

  while(s<=e){
    long long sum = p_sum[e]-p_sum[s-1];

    if(sum == N) count++;

    if(sum > N || e == prime.size()-1) s++;
    else e++;
  }

  cout << count;

  return 0;
}