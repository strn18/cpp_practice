#include <iostream>
#include <vector>
#define MAX 40000

using namespace std;

int main(){
  int nw, nm; // 추의 개수, 구슬의 개수
  int w[30], m; // 추의 무게, 구슬의 무게
  bool visited[MAX+1] = {false};
  vector<int> able;

  scanf("%d", &nw);
  for(int i=0; i<nw; i++){
    scanf("%d", &w[i]);
    
    vector<int> temp;
    if(!visited[w[i]]){
      temp.push_back(w[i]);
      visited[w[i]] = true;
    }
    for(int j=0; j<able.size(); j++){
      if(!visited[able[j]+w[i]]){
        temp.push_back(able[j]+w[i]);
        visited[able[j]+w[i]] = true;
      }

      if(able[j]>w[i]){
        if(!visited[able[j]-w[i]]){
          temp.push_back(able[j]-w[i]);
          visited[able[j]-w[i]] = true;
        }
      }
      
      else if(w[i]>able[j]){
        if(!visited[w[i]-able[j]]){
          temp.push_back(w[i]-able[j]);
          visited[w[i]-able[j]] = true;
        }
      }
    }

    for(int j=0; j<temp.size(); j++)
      able.push_back(temp[j]);
  }

  scanf("%d", &nm);
  for(int i=0; i<nm; i++){
    scanf("%d", &m);

    if(visited[m])
      printf("Y ");
    else
      printf("N ");
  }

  return 0;
}

/*
어렵지는 않았던 dp문제. 측정할 수 있는 무게의 집합을 able이라고 했을 때, 어떠한 추 w[i]로 able을 갱신해주고 싶다면, able의 원소를 a라고 했을 때,
모든 a에 대해서 a+w[i], a-w[i], w[i]-a 이 세 가지를 새로 able에 넣어주면 된다(이미 able에 있거나, 음수가 되는 경우는 당연히 제외). 그리고 w[i]도
똑같이 넣어주면 된다. 이 작업을 모든 w[i]에 대해서 행해주면 된다. 

이거를 떠올리는 거는 딱히 어렵지 않았고, 구현하는 것도 able을 벡터로 두고, 어떤 값이 이미 able에 있는지 없는지 판단하기 위해 int 배열인 checked를
사용했다. 파이썬에서 세트같은거 썼으면 편했겠지만, c++엔 없으니깐 O(1)로 바로 체크하기 위해 썼음(안 쓰면 벡터를 매번 돌아야 함).
그리고 w[i]를 통해 able에 새로이 넣어준 값을 w[i]로 중복으로 또 써버리면 안 되니까(able에 1이 있고 w[i]가 4여서 5를 새로이 넣어줬을 때, 뒤에서 그
5를 보고 또 9를 넣어버리면 안 되니까), temp 벡터에 우선 넣어두고 다 끝난 후 able에 넣어주었다.
그리고 vscode에서는 배열 인덱스가 음수여도 프로그램 안 끊기고 그냥 넘어가면서 실행이 돼서 확인을 못 했는데, 백준에 제출하니깐 out of bounds 에러가
났다. 29, 36행에서 음수가 되어서 배열 인덱스가 음수가 떠서 그런듯. 이후 지금 코드처럼 if문을 추가해서 음수일 때는 배열 들어가지 않게 했다.

고친 다음에 코드 제출하니까 맞았다. 근데 다른 사람들 코드를 보니까, 나랑 다르게 풀었음. https://yabmoons.tistory.com/105 여기 코드 보니까
마치 dfs처럼 1) 구슬 없는 쪽에 추 올리기 2) 추 안 올리기 3) 구슬 쪽에 추 올리기. 이 세 가지 경우를 depth가 1~nw(추의 개수)일 때(모든 추에 대해서)
재귀적으로 실행하는 방식이었음. 이것도 간결하고 좋은 것 같다.
*/