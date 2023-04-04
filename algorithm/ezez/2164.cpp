#include <iostream>
#include <queue>

using namespace std;

int main(){
  int N;
  queue<int> cards;

  scanf("%d", &N);

  for(int i=1; i<=N; i++)
    cards.push(i);

  while(cards.size() > 1){
    cards.pop();
    cards.push(cards.front());
    cards.pop();
  }

  printf("%d", cards.front());

  return 0;
}