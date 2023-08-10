#include <iostream>
#define MAX 1500

using namespace std;

void build_min_heap(int *arr, int size);
void min_heapify(int *arr, int size, int idx);
void swap(int *a, int *b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, temp, heap_size = 0;
  int arr[MAX+1];

  cin >> N;

  for(int i=0; i<N*N; i++){
    cin >> temp;

    if(heap_size == N){
      if(temp > arr[1]){
        arr[1] = temp;
        build_min_heap(arr, heap_size);
      }
    }
    else{
      heap_size++;
      arr[heap_size] = temp;
      build_min_heap(arr, heap_size);
    }
  }

  cout << arr[1];

  return 0;
}

void build_min_heap(int *arr, int size){
  for(int i=size/2; i>=1; i--)
    min_heapify(arr, size, i);
}

void min_heapify(int *arr, int size, int idx){
  int left = idx*2, right = left+1;
  int smallest_idx = idx;

  if(left <= size && arr[left] < arr[smallest_idx])
    smallest_idx = left;
  if(right <= size && arr[right] < arr[smallest_idx])
    smallest_idx = right;

  if(smallest_idx != idx){
    swap(&arr[idx], &arr[smallest_idx]);
    min_heapify(arr, size, smallest_idx);
  }
}

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
우선순위 큐로 푸는 문제인데, 최소 힙을 직접 구현해서 풀어본 풀이.
*/