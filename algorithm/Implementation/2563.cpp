#include <iostream>
#define MAX 100

using namespace std;

bool is_black[MAX][MAX] = {false};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;

  cin >> N;

  while(N--){
    int r, c;

    cin >> r >> c;

    for(int i=r; i<r+10; i++)
      for(int j=c; j<c+10; j++)
        is_black[i][j] = true;
  }

  for(int i=0; i<MAX; i++)
    for(int j=0; j<MAX; j++)
      if(is_black[i][j]) count++;
  
  cout << count;

  return 0;
}