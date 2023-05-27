#include <iostream>

using namespace std;

void swap(int *a, int *b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  while(T--){
    int M, N, x, y, high;
    int count = 0;

    cin >> M >> N >> x >> y;

    if(M > N){
      swap(&M, &N);
      swap(&x, &y);
    }

    high = x;

    count += x;
    
    while(high != y){
      high -= (N-M);
      count += M;
      
      if(high <= 0) high += N;

      if(high == x){
        count = -1;
        break;
      }
    }

    cout << count << '\n';
  }

  return 0;
}

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}