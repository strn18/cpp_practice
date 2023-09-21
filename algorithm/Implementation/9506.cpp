#include <iostream>
#include <vector>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;

  while(true){
    int divSum = 0;
    vector<int> div;

    cin >> n;

    if(n == -1) break;

    for(int i=1; i<=n/2; i++){
      if(n % i == 0){
        divSum += i;
        div.push_back(i);
      }
    }

    cout << n;

    if(divSum == n){
      cout << " = ";

      for(int i=0; i<div.size()-1; i++)
        cout << div[i] << " + ";

      cout << div.back() << '\n';
    }
    else cout << " is NOT perfect.\n";
  }
  
  return 0;
}