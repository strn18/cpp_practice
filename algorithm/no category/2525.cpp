#include <iostream>

using namespace std;

int main(){
  int H, M, time;

  scanf("%d %d", &H, &M);
  scanf("%d", &time);

  H += time/60;
  M += time%60;

  H += M/60;
  M %= 60;
  H %= 24;

  printf("%d %d", H, M);

  return 0;
}