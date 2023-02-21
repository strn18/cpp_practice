#include <iostream>
#include <algorithm>
#define MAX 100000

using namespace std;

int H[MAX];

int largest(int start, int end);

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    scanf("%d", &H[i]);
  
  printf("%d", largest(0, N-1));

  return 0;
}

int largest(int start, int end){
  if(start == end) return H[start];

  int mid = (start+end)/2;
  int result = max(largest(start, mid), largest(mid+1, end));

  int left = mid, right = mid;
  int bottom_count = 1, lowest_height = H[mid];

  result = max(result, bottom_count * lowest_height);

  while(start < left || right < end){
    if( (start < left) && (right == end || H[left-1] > H[right+1]) ){
      left--;
      lowest_height = min(lowest_height, H[left]);
    }
    else{
      right++;
      lowest_height = min(lowest_height, H[right]);
    }

    result = max(result, (++bottom_count) * lowest_height);
  }

  return result;
}

/*
2104랑 거의 똑같았던 분할정복 문제. largest 함수는 start부터 end까지의 히스토그램에서 가장 큰 직사각형의 넓이를 구해서 반환한다.

2104의 풀이와 마찬가지로, 기저 조건일 때를 제외하면 세 가지를 비교해서 최댓값을 반환한다. 1) start와 end의 중간을 mid라고 잡았을 때,
largest(start, mid)의 값(mid 기준 왼쪽 히스토그램에서 가장 큰 직사각형의 넓이). 2) largest(mid+1, end)의 값(오른쪽). 3) mid부터 시작해서,
직사각형을 좌우로 확장하면서, 가장 클 때의 넓이. 1)과 2)는 27행에서처럼, 단순히 재귀 방식으로 구해주면 된다. 3)은 2104에서의 풀이와 거의
유사하게, mid에서 시작하면서 밑변의 길이인 bottom_count와 가장 작은 높이인 lowest_height를 갱신해나가면서, bottom_count * lowest_height로
직사각형의 넓이를 구하면서 최댓값을 찾는다. 이때 좌우로 확장하는 건, 좌 우의 높이 중 큰 쪽을 우선으로 확장한다(35행). 그러다가 left와 right가
각각 start와 end에 다다르면 끝낸다. 

35행의 조건문을 좀 더 설명하자면, 우선 (start < left) 이거는, left가 아직 start에 도달하지 않았을 때만 left를 왼쪽으로 확장할 수 있으므로, 
and를 중간에 두고 넣었다(left가 start에 도달했다면, 반드시 right를 확장해야함). 그리고 (right == end || H[left-1] > H[right+1]) 이거는, 
우선 right == end를 만족한다면, 방금 설명한 거랑 반대로, right가 end에 도달한 거니까 반드시 left를 확장해햐한다. 그리고 그것도 만족하지 않을 때, 
즉 left와 right가 모두 start와 end에 도달하지 않았다면, 왼쪽과 오른쪽 중 높이가 높은 쪽으로 확장한다. 즉 H[left-1]이 더 크다면 left를 확장하고,
아니라면 else문을 통해 right를 확장한다.
*/