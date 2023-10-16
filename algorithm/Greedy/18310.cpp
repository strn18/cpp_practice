#include <iostream>
#define ll long long
#define MAX 100000

using namespace std;

int houses[MAX+1];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  ll ansDist; int ansPos;
  int maxPos = 0, leftCount = 0, rightCount = 0; ll totalDist = 0;

  cin >> N;

  for(int i=0; i<N; i++){
    int pos;

    cin >> pos;

    maxPos = max(maxPos, pos);

    houses[pos]++;
    totalDist += pos;
  }

  rightCount = N;

  ansDist = totalDist;
  ansPos = 0;

  for(int i=1; i<=maxPos; i++){
    totalDist += leftCount;
    totalDist -= rightCount;

    leftCount += houses[i];
    rightCount -= houses[i];

    if(totalDist < ansDist){
      ansDist = totalDist;
      ansPos = i;
    }
  }

  cout << ansPos;

  return 0;
}

/*
모든 위치에서, 모든 집들에 대한 거리를 합치는 코드를 짜면 시간초과가 난다. 그래서 나는, 이런 방법을 떠올림. 위치 i일 때 거리의 총합이 
totalDist라고 하자. 이때, 위치 i+1이 됐을 때 거리의 총합은? 
totalDist + 위치 i일 때 왼쪽(또는 위치 i 포함)에 있던 집들의 개수 - 위치 i일 때 오른쪽에 있던 집들의 개수
이다. 이를 이용해서 O(N)으로 짰음.

근데 풀이 보니까 그냥 개쉽게 푸는 방법이 있었다. 모든 위치값을 오름차순으로 정렬하고, 가장 중앙에 있는 원소의 위치값이 답임. 
그걸로 푼 게 두번째 풀이. 왜인지는 https://blog.naver.com/PostView.naver?blogId=jinhan814&logNo=222534711709&parentCategoryNo=&categoryNo=11&viewDate=&isShowPopularPosts=false&from=postView
여기 참조. 
*/