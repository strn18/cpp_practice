#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int piece[6], num[6] = {1, 1, 2, 2, 2, 8};

  for(int i=0; i<6; i++)
    cin >> piece[i];
  
  for(int i=0; i<6; i++)
    cout << num[i] - piece[i] << ' ';

  return 0;
}