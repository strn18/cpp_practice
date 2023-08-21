#include <iostream>
#include <vector>
#define MAX 1000000

using namespace std;

bool isPrime[MAX+1];
vector<int> primeNum;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for(int i=2; i<=MAX; i++)
    isPrime[i] = true;

  for(int i=2; i<=MAX; i++){
    if(!isPrime[i]) continue;

    primeNum.push_back(i);
    
    for(int j=2; i*j<=MAX; j++)
      isPrime[i*j] = false;
  }

  while(true){
    int n;
    bool found = false;

    cin >> n;

    if(n == 0) break;

    for(int i=0; i<primeNum.size()/2; i++){
      if(isPrime[n-primeNum[i]]){
        cout << n << " = " << primeNum[i] << " + " << n-primeNum[i] << '\n';
        found = true;
        break;
      }
    }

    if(!found)
      cout << "Goldbach's conjecture is wrong.\n";
  }

  return 0;
}

/*
에라토스테네스의 체 이용.
*/