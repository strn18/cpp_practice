#include <iostream>

using namespace std;

int main(){
  int prev, cur;
  bool asc=true, des=true;

  cin >> prev;
  for(int i=1; i<8; i++){
    cin >> cur;
    if(prev<cur)
      des=false;
    else if(prev>cur)
      asc=false;
    prev = cur;
  }
  if(asc)
    cout << "ascending";
  else if(des)
    cout << "descending";
  else
    cout << "mixed";

  return 0;
}