#include <iostream>
#include <algorithm>
#include <string>
#define MAX 100000

using namespace std;

pair<int, string> arr[MAX];

bool compare(pair<int, string> a, pair<int, string> b){
  return a.first < b.first;
}

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d", &arr[i].first);
    cin >> arr[i].second;
  }

  stable_sort(arr, arr+N, compare);
  
  for(int i=0; i<N; i++){
    printf("%d ", arr[i].first);
    cout << arr[i].second << '\n';
  }

  return 0;
}

/*
쉬운 문제지만, stable_sort라는 걸 배웠다. 

나이가 다르면 나이 순으로 오름차순 정렬하고, 나이가 같으면 입력 받은 순으로 오름차순 정렬이다. 즉 나이가 같다면 순서는 그대로 둔다.

처음에는 이를 위해, sort에 넣어 줄 compare 함수에서, 나이가 같으면 true를 리턴하도록 했다. 왜 그렇게 했냐면, true가 리턴되면 두 원소의 순서를
바꾸지 않고 그대로 두는 줄 알았고, 그래서 나이가 같으면 순서를 안 건들게 되는 줄 알았음. 근데 돌려보니까 순서가 바뀐다. 그래서 혹시나 해서 true
말고 false를 리턴하게 했더니 안 건들길래, 제출했더니 틀렸다. 고민을 좀 하다가, 그냥 입력받은 순서를 의미하는 변수를 구조체(원래 풀이에서는 
구조체 썼었음) 안에 하나 더 정의했고, 나이가 같으면 그 변수 순으로 오름차순 정렬시켰다. 그랬더니 맞았음.

다른 풀이 찾아보니까, algorithm 헤더에 안정 정렬(두 원소의 우선순위가 같으면, 기존의 순서가 보장)을 하는 함수인 stable_sort가 있었다. 그냥
sort 함수는 불안정 정렬하는 함수였음. 그래서 틀렸던 것.

stable_sort 함수를 쓰고, 구조체도 없애고 그냥 pair 형으로 바꿔서 제출했다. 맞았음.
*/