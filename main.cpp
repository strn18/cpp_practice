#include <iostream>
#define PLATE 30000
#define SUSHI 3000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, d, k, c;

  int types = 0, maxTypes = 0;
  int belt[PLATE], eat[SUSHI+1] = {0};

  cin >> N >> d >> k >> c;

  for(int i=0; i<N; i++)
    cin >> belt[i];
  
  for(int i=0; i<k; i++){
    if((eat[belt[i]]++) == 0)
      types++;
  }

  if(eat[c] == 0) maxTypes = max(maxTypes, types + 1);
  else maxTypes = max(maxTypes, types);

  int start = 0, end = k-1;

  while(start != N-1){
    if((--eat[belt[start]]) == 0)
      types--;
    if((eat[belt[(end+1)%N]]++) == 0)
      types++;
    
    if(eat[c] == 0) maxTypes = max(maxTypes, types + 1);
    else maxTypes = max(maxTypes, types);

    start = (start+1) % N;
    end = (end+1) % N;
  }
  
  cout << maxTypes;

  return 0;
}