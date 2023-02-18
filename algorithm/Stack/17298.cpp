#include <iostream>
#define MAX 1000000

using namespace std;

int arr[MAX], nge_idx[MAX];

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++)
    scanf("%d", &arr[i]);

  nge_idx[N-1] = -1;
  for(int i=N-2; i>=0; i--){
    int right = i+1;
    
    while(true){
      if(arr[i] < arr[right])
        nge_idx[i] = right;

      else if(arr[i] == arr[right])
        nge_idx[i] = nge_idx[right];

      else{
        if( (nge_idx[right] == -1) || (arr[nge_idx[right]] > arr[i]) )
          nge_idx[i] = nge_idx[right];

        else{
          right = nge_idx[right];
          continue;
        }
      }

      break;
    }
  }

  for(int i=0; i<N; i++)
    printf("%d ", ( (nge_idx[i] == -1) ? -1 : arr[nge_idx[i]]));  
  
  return 0;
}

/*
좀 고민했던 문제. 분류가 애매한데, 다른 풀이들 보니까 스택으로 풀어서 걍 스택으로 함.
어떠한 수열에서, i번째 수보다 오른쪽에 있고 값이 큰 수들 중에서 가장 왼쪽에 있는 수를 찾으면 되는데, 모든 i(1~N)에 대해서 다 구해야 한다.
되게 간단한 문제지만, N이 최대 백만이라서, 오른쪽의 수들을 하나하나 훑는 방식으로 하면 O(N*N)이라서 시간초과가 난다. 그래서 다른 방법을 찾아야 함.

이리저리 고민하다가, NGE(1)부터 찾지 않고, NGE(N)부터 찾는 방식을 생각해봤다.
우선 NGE(N)은 -1이다. 오른쪽에 수가 없으므로. 그렇다면, NGE(N-1)은? 만약 N-1번째 수(num(N-1)이라 하자)가 num(N)보다 작다면, NGE(N-1)은
num(N)이다. 만약 num(N-1) == num(N)이라면? NGE(N-1)과 NGE(N)도 같을 것이다. 만약 num(N-1)이 더 크다면? num(N)보다 오른쪽의 있는 수를 봐야하는데,
없으므로 NGE(N-1)도 -1이다.

이걸 일반화해보자. NGE(i)를 구하고싶다고 하자. 우선 i+1을 right로 잡는다. num(i) <= num(right)인 경우는 위에서 다뤘다. num(i) > num(right)일 때,
NGE(right)가 -1이라면? right보다 오른쪽으로는 num(right)보다 큰 수가 없으므로, num(i)보다 큰 수도 당연히 없다. 그러므로 NGE(i) = -1이다.
만약 NGE(right)가 num(i)보다 크다면? NGE(right)가 NGE(i)가 된다. 그러므로 NGE(i) = NGE(right)이다.
둘 다 아니라면? NGE(right)에 해당하는 수, 즉 num(right)의 NGE 이지만, num(i)보다는 작은 그 녀석을 새로운 right로 삼아서, 위의 과정을 반복해야함.

이 과정이 19행의 while문에 들어가있다. 59행에 해당될 때만 while문을 돌리고, 다른 경우에는 NGE(i)를 찾았으므로 반복하지 않는다.
그리고 nge_idx[i]는 i의 NGE에 해당하는 수의 인덱스이다. 이 값이 -1이면 i의 NGE도 -1(못 찾음)인 것이고, 그렇지 않은 경우 NGE(i)는 
num(nge_idx[i])가 된다.

다른 사람들 풀이 보니까 스택으로 풀었던데, 더 짧고 간결하지만 풀이에 큰 차이는 없어보였다. https://cocoon1787.tistory.com/347
*/