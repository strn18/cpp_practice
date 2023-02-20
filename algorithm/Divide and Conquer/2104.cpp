#include <iostream>
#include <algorithm>
#define MAX 100000

using namespace std;

int arr[MAX];

long long max_point(int start, int end);

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    scanf("%d", &arr[i]);
  
  printf("%lld", max_point(0, N-1));

  return 0;
}

long long max_point(int start, int end){
  if(start == end) return arr[start]*arr[start];

  int mid = (start+end)/2;
  long long result = max(max_point(start, mid), max_point(mid+1, end));

  int left = mid, right = mid, minimum = arr[mid];
  long long count = arr[mid];
  result = max(result, count*minimum);
  
  while(start < left || right < end){
    if((start != left) && (right == end || arr[left-1] > arr[right+1])){
      left--;
      minimum = min(minimum, arr[left]);
      count += arr[left];
    }
    else{
      right++;
      minimum = min(minimum, arr[right]);
      count += arr[right];
    }
    result = max(result, count*minimum);
  }

  return result;
}

/*
마지막에 막혔던 분할정복 문제.. [start, end]의 구간에서 최대 점수를 구할 때, 중간의 mid를 기준으로 반으로 나눠서, [start, mid]의 최댓값과
[mid+1, end]의 최댓값을 비교해서 더 큰 값을 찾아야한다는 것은 알았다. 하지만, 그 둘 외에도 또다른 요소가 있었는데, 처음에는 [start, mid]에서
최댓값을 가지는 구간을 [left_i, left_j]라 하고, [mid+1, end]에서는 [right_i, right_j]라고 잡았을 때, [left_i, right_j]의 점수가 바로 그거인 줄
알았다. 다시 말해, [left_i, left_j]의 점수(최댓값 말고, 점수), [right_i, right_j]의 점수, [left_i, right_j]의 점수. 이 세 가지 중에서 최댓값이
[start, end]의 최댓값이라고 생각했다. 

그래서 그걸 구하기 위해, (i, j, 점수)를 갖는 구조체인 sub를 정의하고, [start, mid] 구간에서의 최댓값 정보를 sub left에, [mid+1, end]의 정보를
sub right에 담고, [left_i, right_j]의 점수는 long long mid_points에 담았다(sub형 함수인 max_point에서). 그런 다음, left.points(점수), 
right.점수, mid_points 이 세 개를 비교하여, left.점수가 최대면 left를 리턴하고, right가 최대면 right, mid_points가 최대면
{left.i, right.j, mid_points}를 리턴했다. 즉, 결국 sub max_point(int start, int end) 는 [start, end] 구간의 최댓값 정보를 sub 타입의 형태
(i, j, 점수)로 리턴하는 것이다.

이렇게 해서 제출했는데, 몇 프로 맞더니 틀렸다고 떴다. 가령 2 2 2 2 4 2 2 의 배열이 있을 때, 위의 방식대로면 2 2 2 2 / 4 2 2 로 쪼갠다. 이때
왼쪽 부분의 max_point, 즉 max_point(0, 3)은 {0, 3, 16}을 리턴하고, 오른쪽 부분은 {4, 4, 16}을 리턴한다. 왜냐? 오른쪽 부분은 다시 4 2 / 2 로
쪼개지는데, 여기서 왼쪽은 4만 고를 것이고, 오른쪽은 2만 고른다. 이 둘을 합치면? 왼쪽의 4를 골랐을 때 점수는 16, 오른쪽의 2를 골랐을 때는 4, 
4부터 2까지 다 골랐을 때([left_i, right_j]의 점수)는 16으로, 최댓값은 16인데, 위의 방식대로면 왼쪽이 먼저니까 왼쪽의 4를 고른 걸 리턴하게 됨.
그래서 오른쪽 부분은 {4, 4, 16}을 리턴하게 되는 것임. 이렇게 되면, 2 2 2 2 에서는 모두 고르고, 4 2 2 에서는 4만 고른 상태이다. 이 상태에서 
둘을 다시 병합하면, 2 2 2 2와 4를 모두 고른 24가 정답이 된다. 하지만 실제로는? 2 2 2 2 4 2 2를 모두 고른 32가 정답이다.

이 문제를 해결하기 위해, 왼쪽이 먼저(left.점수가 최대면 left를 리턴하는 것을 제일 먼저 하는 것)가 아니라, 중간을 먼저 하는 방식으로 바꿔서
제출해봤는데, 좀 더 맞는가 싶더니 틀렸다.

이리저리 고민하다가, 반례를 또 찾았다. 입력이
36
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4 4
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4 4
일 때, 위의 방식대로면 답은 32이다. 중간의 4 4부터, 끝의 4 4까지 모두 고르는 것이다. 하지만 실제로 답은, 수를 모두 고른 48이다. 왜 이렇게
되냐면, 왼쪽의 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 4 4 에서 최대는 4 4를 골랐을 때이다. 오른쪽도 마찬가지. 근데, 둘을 합치면 왼쪽이나, 오른쪽이나,
중간(mid_points)이 모두 아니라, 아예 다른 경우(모든 수 고르기)가 답이 되어버린다. 이를 해결하기 위해, mid_points를 구하는 방식을 좀 바꿨다.
우선 위의 방식의 mid_points를 구한 후, 좌우로 확장해나가면서, mid_points를 고를 때의 최솟값(minimum) 이상의 값을 보면 계속 좌우로 확장하고,
더 작은 값을 보면 그만 확장한다. 즉, mid_points에서부터 점수를 최대한 늘리도록 확장하는 것이다(minimum 미만의 값을 고르면 값이 줄어들게 되므로,
미만의 값을 보면 그만 확장함).

이렇게 해서 또 제출했는데, 또 좀 더 맞는가 싶더니 틀림. 그래서 고민하다가, 결국 https://blog.naver.com/kks227/220776241154 여기서 힌트를
봤다. 힌트를 보니까, 링크에서 설명했던 히스토그램 문제 방식과 거의 유사했음. 우선 왼쪽 오른쪽 값을 구하는 것(51, 52행)은 맞았다. 근데 
중간에서부터의 값을 구하는 것은 유사했으나 틀렸다.. 링크의 설명대로라면, 중간부터 확장하는 건 맞는데, 나처럼 minimum보다 작은 값을 봤다고 확장을
멈추는 게 아니라, 일단 확장은 계속 하면서 최댓값을 갱신해야 한다. 즉, minimum보다 작은 값을 봐서 지금 당장은 값이 줄어들 수 있으나, 그 방향으로
계속 확장하면서 값이 커져서 왼쪽 오른쪽 값보다 커질 수 있어서 그런듯.

그리고 풀이가 그렇게 된 이상, 왼쪽 오른쪽 값을 구할 때 각각의 i, j값은 필요가 없다(점수(=최댓값)만 필요). 그래서 구조체 부분 지우고, 링크의
히스토그램 문제 풀이 코드와 유사한 방식으로 풀어서 제출했더니 맞았다.

거의 다 갔는데 아깝다..
*/