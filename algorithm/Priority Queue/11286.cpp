#include <iostream>
#include <queue>
#include <cstdlib>

using namespace std;

struct compare{
  bool operator()(int a, int b){
    if(abs(a) != abs(b))
      return abs(a) > abs(b);
    else
      return a > b;
  }
};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  priority_queue<int, vector<int>, compare> pq;

  cin >> N;

  while(N--){
    int x;

    cin >> x;

    if(x==0){
      if(pq.empty()) cout << 0;
      else{
        cout << pq.top();
        pq.pop();
      }
      cout << '\n';
    }
    else
      pq.push(x);
  }

  return 0;
}

/*
쉬운 pq 문제인데, 정렬 기준을 위해 compare 구조체 재정의 어쩌고 하는 게 기억 안 나서 좀 찾아봤던 문제..

https://jioneprogstdy.tistory.com/82 여기랑 
https://codingdog.tistory.com/entry/c-priority-queue-%EC%98%88%EC%A0%9C
-compare-%EA%B5%AC%EC%A1%B0%EC%B2%B4%EB%A7%8C-%EC%9E%98-%EC%A0%95%EC%9D%98%ED%95%A9%EC%8B%9C%EB%8B%A4
여기에 잘 나와있음. 

sort 함수에서 정렬 기준 재정의를 하려면
bool compare(int a, int b){
    어쩌고 저쩌고
}
이런 형식인데, 

pq에서는
struct compare{
    bool operator()(int a, int b){
        어쩌고 저쩌고
    }
};
와 같이 compare 구조체를 재정의해야 한다. 

그리고 또 주의할 점은, sort랑 기준이 반대임.
가령 sort에서는 52행 부분에 return a < b; 이렇게 하면 오름차순으로 정렬되는데,
pq에서는 57행 부분에 return a < b; 이렇게 하면 내림차순으로 정렬된다. 사실 엄밀히 말하면 내림차순은 아니고, 최댓값이 맨 위(pq의 top)에 온다.
greater나 less를 쓸 때도 마찬가지임.
*/