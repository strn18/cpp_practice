#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int points = 0, winnerNum = 0, winnerPoint = 0;

  for(int i=1; i<=5; i++){
    points = 0;

    for(int j=1; j<=4; j++){
      int p;
      cin >> p;
      points += p;
    }

    if(points > winnerPoint){
      winnerNum = i;
      winnerPoint = points;
    }
  }

  cout << winnerNum << ' ' << winnerPoint;

  return 0;
}