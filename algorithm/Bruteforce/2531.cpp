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

/*
그냥 브루트포스로 풀면 된다. 그리고 투포인터도 사용함. 
접시0 접시1 ... 접시N-1 이렇게 있으면(원형이라고 가정), 처음에는 접시0부터 연속으로 k개를 집는다. 그리고 그 k개를 먹었을 때의 
가짓수를 types에 넣어준다(24행까지). 참고로 이걸 할 때 eat 배열을 쓴다. eat[i]: 종류가 i인 초밥(i번 초밥)을 먹은 개수이다. 

그런 다음 26, 27행은 그냥 쿠폰으로 한 종류 더 먹어서 types+1로 최댓값을 갱신할지, 쿠폰 써도 똑같아서 types로 갱신할지 정하는 그거다. 

31행부터 투 포인터로 브루트포스를 돌려준다. 접시a ~ 접시b를 연속해서 먹었을 때, a가 start이고 b가 end이다. 이후 start++, end++을 
반복해주면서(이때 나누기 연산 유의) types를 갱신해주고 그걸로 답을 갱신해주면 끝이다. 
*/