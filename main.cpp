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