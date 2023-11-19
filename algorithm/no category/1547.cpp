#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int M;
  bool cup[3] = {true, false, false};

  cin >> M;

  while(M--){
    int a, b;

    cin >> a >> b;

    a--; b--;

    if(cup[a] || cup[b]){
      cup[a] = !cup[a];
      cup[b] = !cup[b];
    }
  }

  for(int i=0; i<3; i++)
    if(cup[i]) cout << i+1;

  return 0;
}