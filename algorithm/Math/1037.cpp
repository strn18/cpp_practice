#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int K, num, minimum = 1000001, maximum = 1;

  cin >> K;

  for(int i=0; i<K; i++){
    cin >> num;

    minimum = min(minimum, num);
    maximum = max(maximum, num);
  }

  cout << minimum * maximum;
  
  return 0;
}