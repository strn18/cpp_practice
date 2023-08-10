#include <iostream>
#define MAX 50

using namespace std;

void quick_sort(int arr[], int p, int r, bool asc);
int pivot_pos(int arr[], int p, int r, bool asc);
void swap(int *a, int *b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, total = 0;
  int A[MAX], B[MAX];

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> A[i];
  for(int i=0; i<N; i++)
    cin >> B[i];

  quick_sort(A, 0, N-1, true);
  quick_sort(B, 0, N-1, false);

  for(int i=0; i<N; i++)
    total += A[i]*B[i];

  cout << total;

  return 0;
}

void quick_sort(int arr[], int p, int r, bool asc){
  if(p<r){
    int q = pivot_pos(arr, p, r, asc);
    
    quick_sort(arr, p, q-1, asc);
    quick_sort(arr, q+1, r, asc);
  }
}

int pivot_pos(int arr[], int p, int r, bool asc){
  int pivot = r, left = p-1;

  for(int i=p; i<r; i++){
    if(asc ? arr[i] < arr[pivot] : arr[i] > arr[pivot]){
      swap(&arr[left+1], &arr[i]);
      left++;
    }
  }

  swap(&arr[left+1], &arr[pivot]);

  return left+1;
}


void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
쉬운 정렬 문제지만 퀵 정렬을 직접 구현해봄.
*/