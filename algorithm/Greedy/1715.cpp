#include <iostream>
#include <queue>

using namespace std;

int main(){
  int N, count = 0;
  priority_queue<int, vector<int>, greater<int>> pq;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    int temp;
    scanf("%d", &temp);
    pq.push(temp);
  }

  while(pq.size() != 1){
    int merge_cost = 0;
    for(int i=0; i<2; i++){
      merge_cost += pq.top();
      pq.pop();
    }
    count += merge_cost;
    pq.push(merge_cost);
  }

  printf("%d", count);

  return 0;  
}

/*
그리디 문제로, 풀이 자체는 쉬웠으나 시간초과 관리(연산 횟수 줄이기)가 관건이었음.

우선 풀이는, 카드 묶음들을 크기 순으로 정렬했을 때, 크기가 가장 작은 두 묶음을 합치는 과정을 계속 반복하면서, 비교 횟수를 갱신해주면 된다.
즉, 카드 묶음이 40, 40, 50, 60, 70 이렇게 있다면, 우선 40과 40을 합쳐서 80을 만든다. 이때 비교횟수는 80이므로 총 비교 횟수는 80이다.
그 다음, 50과 60을 합치고, 총 비교 횟수는 80+110 = 190이다. 그 다음, 카드 묶음이 이제 80, 110, 70이 있으므로 80과 70을 합쳐서 150을
만들고, 총 비교 횟수는 340이다. 마지막으로 150과 110을 합치고, 총 비교 횟수는 600이 된다.

이 방법 떠올리기는 쉬웠기에, 벡터를 이용해서 카드 묶음들을 만들어주고, 가장 적은 두 카드 묶음 합치기 -> 합친 묶음을 올바른 자리에(오름차순이
되도록) 넣어주기. 이 과정을 반복하였다. 이후 제출했는데, 시간초과가 떴다. 사실, 두 카드 묶음을 합치는 과정이 총 N번 정도 발생하고, 
합친 카드 묶음을 다시 올바른 자리에 넣어주는 과정이 총 N번 정도의 연산이 발생하기에 최종적으로 O(N^2)인데 N이 10만이라 시간초과가 발생함..

그래서 어떻게할까 생각하다가, 예전에 파이썬 쓰다가 처음 접한 우선순위 큐를 사용하게 되었음. https://travelbeeee.tistory.com/126 여기 글을
참고했는데, priority_queue가 기본적으로 내림차순 정렬이기에, 오름차순 정렬하려면 priority_queue<int, vector<int>, greater<int>> 이렇게
해야한다고 함. 두 번째 vector<int> 저거는 구현체인데, stl에서 힙을 구현하기 좋은 자료형이면 다 가능하다고 한다. vector를 include하지 않아도 
동작한다(https://jungeu1509.github.io/algorithm/use-priorityqueue/). 그리고 greater<int> 저거는 비교연산자로, algorithm.h의 sort
함수에서 Compare 넣어주는 그거랑 비슷한 역할이다. 근데 따로 함수 정의 안 하고 greater<>, less<> 이렇게 써도 된다는 건 처음 앎.
어쨌든 pq를 써서 거기에 카드 묶음들을 넣어주고, top에 있는 두 요소(가장 적은 두 카드 묶음)를 빼서 합친 값을 count에 더해주고, 합친 값은 다시
pq에 넣어서 정렬해준다. 이 과정을 pq의 요소가 하나가 될 때까지(카드 묶음 병합이 끝날 때까지) 반복하면 된다.

처음 코드에서 합친 카드 묶음을 다시 넣어주는 과정은 O(N)이었다. 정렬된 카드 묶음 N개에 새 카드 묶음을 정렬되도록 넣어야하니깐, 한쪽 끝부터
탐색한다고 쳤을 때 최대 N번 걸린다.
이걸 우선순위 큐로 한다면 O(logN)이다. pq의 완전이진트리에 마지막 요소로 새 카드 묶음을 넣고, 부모 노드와 비교하는 과정을 최대 logN번
하게 되기 때문(밑은 2). https://suyeon96.tistory.com/31 여기에 잘 정리되어있음.
*/