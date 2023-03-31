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

/*
이상하게 접근해서 은근 어려웠던 실4딱 문제..

처음에는 bool deleted[MAX] = {false}; 이렇게 만들어 놓고, i번째 사람을 kill할 때마다 deleted[i] = true; 이런 식으로 바꿔준 다음,
i는 1~N을 계속 돌면서 deleted가 true면 그냥 continue하고, 아니면 count를 증가시키고.. 이걸 반복하는 방식으로 하려 했다. 그러다가 count가 K와
같아지면 그 사람을 kill하고 다시 이걸 반복하려고 했음. 근데 이렇게 하니까 좀 코드가 복잡했다. 

그래서 그냥 벡터를 쓴 다음, kill한 사람은 erase해주는 방식으로 바꿨다. 이것도 처음에는 벡터의 요소들을 하나한 돌면서 count를 증가시키고 하는
방식으로 하려했는데, 짜다보니까 굳이 하나하나 돌 필요 없이 그냥 start(start번째 사람부터 센다는 뜻)와 K와 people.size(남은 사람들의 수)를
알고 있다면, 몇 번째 사람을 kill해야 하는지 바로 알 수 있을 것 같아서 그 방식으로 바꿨다. 짱구 좀 굴려보니까 26행에 쓴 것처럼 식이 나옴.
0base로 해서, 0번째 사람부터 총 people.size()명의 사람이 있는데, 이때 start번째 사람부터 세서 K번째 사람을 kill하면 된다. 가령, start가 3이고
K가 4라면? 6번째 사람을 kill하면 된다. 그러므로 식은 (start+K-1)이 됨. 근데 이 값이 people.size() 이상이 될 수 있으니, 나머지 연산을 해준다.
가령 총 5명이 있다면? 위의 예시대로면 3 4 0 1 이니까 1번째 사람을 kill한다. 이 1은 곧 아까 6에 %people.size()를 해준 값과 같다. 그래서 식이
저렇게 나옴. 
그 다음은, 그냥 target번째 사람을 벡터에서 빼주면 된다. 그러고 나서 벡터가 비면 끝난 거니까 리턴해주고, 아니면 재귀쳐준다. 이때 target번째 
사람을 죽여서 벡터에서 빼줬으니, 다시 target번째 사람부터 세주는데(원래 target+1번째 였던 사람이 target번째가 된 것), target이 people.size를
넘을 수 있으니 마찬가지로 나머지 연산 해준다.

다른 풀이 보니까, 대부분 큐로 풀었다. 큐의 앞부터 하나하나 세주는데, pop하고 다시 뒤에 push하는 방식으로, 원형 큐같은 느낌임. 이러면 무조건 
큐의 front부터 세면 되어서, 나처럼 start번째 사람부터 세고 그럴 필요가 없다. 좋은듯
*/