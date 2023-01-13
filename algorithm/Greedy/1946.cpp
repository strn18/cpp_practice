#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100000

using namespace std;

typedef struct{int first, second;} grade;

bool Compare_first(grade a, grade b){
    return a.first<b.first;
}
bool Compare_second(grade a, grade b){
    return a.second<b.second;
}

int main(){
  int T, N;
  grade app[MAX];

  scanf("%d", &T);

  while(T--){
    scanf("%d", &N);

    for(int i=0; i<N; i++)
      scanf("%d %d", &app[i].first, &app[i].second);

    sort(app, app+N, Compare_first);
    
    vector<grade> mid;
    mid.push_back(app[0]);
    int top = app[0].second;

    for(int i=1; i<N; i++){
        if(app[i].second < top){
            mid.push_back(app[i]);
            top = app[i].second;
        }
    }

    sort(mid.begin(), mid.end(), Compare_second);

    int total = 1;
    top = mid[0].first;

    for(int i=1; i<mid.size(); i++){
        if(mid[i].first<top){
            total++;
            top = mid[i].first;
        }
    }

    printf("%d\n", total);
  }
  
  return 0;
}

/*
어렵지 않았던 그리디 문제. 지원자 데이터를 (서류심사 성적, 면접 성적)로 뒀을 때, 우선 서류심사 성적 등수 기준 오름차순(1등이 맨 앞에 오도록)으로
정렬한다. 그 다음, 맨 앞 지원자의 면접 성적을 top이라는 int 변수에 넣고, 그 다음 지원자부터 맨 뒤로 가면서, 만약 이번 지원자의 면접 성적이 top보다
떨어진다면 패스하고, 더 높다면 그 지원자를 mid라는 벡터에 넣고, 그 지원자의 면접 성적을 top에 넣는다. 이를 맨 뒤 지원자까지 반복한다.
그 다음, 다시 mid 벡터를 면접 성적 등수 기준 오름차순 정렬하고, 맨 앞 지원자의 서류심사 성적을 top에 넣고, 그 다음 지원자부터 맨 뒤로 가면서, 
만약 이번 지원자의 서류심사 성적이 top보다 낮으면 패스, 높으면 total 값을 1 증가시킨다.
이렇게해서 풀 수 있는 이유는, 서류심사 등수 기준 오름차순 정렬했을 때, '어떠한 지원자'의 성적을 그 위의(서류심사 성적이 높은) 지원자의 성적과 
비교했을 때, 면접 성적이 그 중 한 명보다도 떨어진다면, 자동 탈락임. 왜냐면 그 위의 지원자들은 다 서류심사 성적이 '어떠한 지원자'보다 높은 애들인데,
면접 성적도 높은 애가 있다면 '어떠한 지원자'는 당연히 탈락임. 이를 면접 성적에 대해서도 반복해주면 된다.

근데 다른 사람 풀이를 보면서 알았는데, 그냥 서류심사 기준으로만 한 번 해주면 되고 면접 성적에 대해서는 해 줄 필요가 없음.. 그리고 나처럼 grade형
배열을 쓰지 않고 그냥 int형 배열 arr를 만들어서, arr[i] = j라면, 서류심사 i등의 면접 성적은 j등. 이렇게 두고 푸는 풀이가 있었다. 생각해보면, 
어차피 서류심사든 면접 성적이든 그 값은 1~N으로, 중복이 없다. 그렇기에 그냥 배열 인덱스를 등수로 써먹을 수 있음. 이렇게 하면 정렬해 줄 필요도
없어서 실행 시간이 줄어든다.

그거대로 바꿔서 제출한 결과(두 번째 제출), 메모리와 시간이 많이 줄었음을 확인.
*/