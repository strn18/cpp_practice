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