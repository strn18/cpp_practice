#include <iostream>
#include <vector>

using namespace std;

vector<int> people;

void kill(int K, int start);

int main(){
  int N, K;

  scanf("%d %d", &N, &K);

  for(int i=1; i<=N; i++)
    people.push_back(i);
  
  printf("<");
  kill(K, 0);
  printf(">");

  return 0;
}

void kill(int K, int start){
  int target = (start+K-1)%people.size();

  printf("%d", people[target]);
  people.erase(people.begin()+target);

  if(people.empty()) return;

  printf(", ");
  kill(K, target%people.size());
}