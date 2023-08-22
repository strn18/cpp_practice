#include <iostream>

using namespace std;

bool isStar(int H, int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  if(N == 3){
    cout << "  *  \n";
    cout << " * * \n";
    cout << "*****\n";
  }
  else{
    for(int i=0; i<N; i++){
      for(int j=0; j<2*N-1; j++)
        cout << (isStar(N, i, j) ? '*' : ' ');

      cout << '\n';
    }
  }

  return 0;
}

bool isStar(int H, int r, int c){
  if(H == 3){
    if(r == 1 && c == 2) return false;
    else return true;
  }

  if(H-1 - r <= c && c < H + r){
    if(r < H/2) return isStar(H/2, r, c - (H/2));

    if(r <= c && c < 2*H-1 - r) return false;
    else return isStar(H/2, r % (H/2), c % H);
  }
  else return false;
}