#include <iostream>
#include <map>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, X;
  map<int, int> m; // {key값, depth}
  long long C = 0;

  cin >> N;

  m.insert({0, 0});
  m.insert({N+1, 0});

  for(int i=0; i<N; i++){
    int depth;

    cin >> X;

    map<int, int>:: iterator higher_min = m.lower_bound(X);
    map<int, int>:: iterator lower_max = higher_min;
    lower_max--;

    depth = max(higher_min->second, lower_max->second)+1;

    m.insert({X, depth});
    C += depth-1;

    cout << C << '\n';
  }

  return 0;
}

/*
걍 BST에 insert 연산만 구현하면 되는 쉬운 문제인 줄 알았는데, 삽입하는 노드의 수가 최대 30만 개라서, 만약 편향된 형태로 트리가 구성된다면,
일반 BST 방식으로 그대로 풀었을 때 O(N^2)으로 시간초과가 난다. 그래서 아니 레드블랙트리 같은 걸 구현하라는 건가? 했으나 그러면 문제에서 주어진
수도코드랑 insert 방식이 달라지니까 그건 아닐 것 같았고, 고민하다가 걍 https://everenew.tistory.com/102 여기서 살짝 힌트를 봄.

중요한 건 map 자료구조의 사용이었다. map에 대한 대략적인 설명은 https://blockdmask.tistory.com/87 여기를 참고함.
map은 레드블랙트리로 구현된 자료구조로, 탐색 연산이 반드시 O(logN)임을 보장함. 근데 여기서 의문점이 들 수 있다. 아니 map으로 주어진 BST를
구현한다고 하면, 레드블랙트리로 구현되니까 문제에 주어진 insert랑 방식이 달라져서 C값도 다르게 나오는 거 아님? 맞다. 그래서 map으로 BST를
구현하는 게 아니라, map에는 주어지는 노드들의 값을 담기만 하고, 어떠한 노드를 O(logN)으로 탐색하는 용도로만 사용할 것임.

뭔 소리냐면, map을 <int, int> type으로 만든다. 이때, first는 key값(데이터들 대소비교를 통해 레드블랙트리를 구성할 수 있게 하는 key값. 문제에서
주어지는 X값을 이 key값으로 사용할 것임)이고, second는 각 데이터를 문제에서 주어진 insert로 BST를 구성한다고 가정할 때, 그 데이터의 depth를
의미한다. 왜 depth값을 쓰느냐? 수도코드 insert(X, N)을 실행했다고 할 때, C값을 얼마나 증가시키는가? 는 X를 BST에 넣었을 때 위치하게 되는 곳의
depth는 얼마인가?와 관련이 있음. 가령,
 2
1 3
이렇게 BST가 있다고 하자. root node의 depth는 1이라고 치자. 왜 0으로 안 했는지는 이따 설명함. 이때 insert(4)를 한다면? 
C는 2만큼 증가시키게 되고, 실행 결과 BST는
 2
1 3
   4
가 되는데, 이때 4의 depth는 3인데, 3에서 1을 뺀 2가 C의 증가값과 일치함.

다시 말해, BST에 X를 삽입했을 때 X의 depth 값을 구하면 C의 증가값을 구할 수 있는 것임.

그러면 그건 어떻게 구할까? 결론부터 말하면, map에 넣은 값들 중에서, "key값이 X보다 작지만 최대인 노드" 와 "key값이 X보다 크지만 최소인 노드"를
찾으면 됨. 왜냐? 우선 전자를 W, 후자를 Y라고 하자. BST에 X를 넣었을 때, X는 반드시 W의 right node거나 Y의 left node가 된다. 왜인지는 BST
그리면서 잘 생각해보면 됨. 그러므로, X의 depth는 W의 depth+1 or Y의 depth+1 인 것이다. 위의 링크(https://everenew.tistory.com/102)에 설명이
잘 나와있다. max(W의 depth, Y의 depth)+1을 하면 X의 depth를 구할 수 있으니까, 그 값-1만큼 C를 증가시켜주면 된다. 

근데 왜 루트 노드의 depth를 1로 했냐면, W나 Y가 없는 경우(X가 최솟값 or 최댓값인 경우)를 피하기 위해, key값이 각각 0과 N+1이고 depth값은 0인 
애들을 먼저 집어넣었기 때문임(16, 17행). 그래서 얘네들 depth값이 0이니까 처음으로 들어오는 노드 X의 depth는 1부터 시작하게 됨.

그럼 이제 W랑 Y는 어떻게 구하느냐? map 자료구조에 내장된 lower_bound로 구했다. lower_bound(X)는 X 이상인 값들 중 최솟값을 구한다. 즉 Y라고 할
수 있음. 그러면 W는 어떻게 구할까? Y의 바로 왼쪽에 있는 놈이 W임. 왜냐? map 자료구조(레드블랙트리)에서는, 오름차순으로 정렬되어있음. 즉
m.begin()부터 m.end()까지 돈다고 하면, 1, 2, 3, ... 이런 식으로 오름차순으로 뽑히는 거임. 그렇기 때문에, Y의 바로 전 원소가 바로 W에 해당한다.

이를 이용하여 24, 25행에서 Y와 W를 구하고, 위에서 말한 거 잘 구현하면 된다.

https://velog.io/@doontagi/C-map-%ED%81%B4%EB%9E%98%EC%8A%A4%EC%99%80-upperbound-lowerbound-%EB%A9%94%EC%84%9C%EB%93%9C
lower_bound와 upper_bound는 여기를 참고했음.

설명이 좀 복잡한데, 쉽게 말하자면 내가 구하고 싶은 것은 C의 증가값인데, 그 값은 주어진 수도 코드에 따라 insert(X)를 했을 때, X가 BST의 몇
depth에 위치하는지를 구하면 구할 수 있음. 근데 그렇다고 주어진 수도 코드로 구성되는 BST를 직접 구현하려 하면 시간초과가 나니까, 대신에 
map 자료구조를 사용하고, 데이터로 depth(BST로 구성한다고 쳤을 때 그 노드의 depth값)를 가지게 한다. 그러면, map에서 어떤 노드를 찾는 거는
O(logN)이면 찾으니까, 쉽게 어떤 노드의 depth를 찾을 수 있고, 이번 노드 X의 depth도 구할 수 있게 되어 C의 증가값을 구할 수 있게 된다.
*/