// 기초 Partial Sort 연습(7. Heap)
#define MAX 100000

typedef struct{int uID, income;} info;

info heap[MAX+1];
int heap_size;

void swap(int a, int b){
  info temp = heap[a];
  heap[a] = heap[b];
  heap[b] = temp;
}

void init()
{
  heap_size = 0;
}

void addUser(int uID, int height) 
{
  heap[++heap_size].uID = uID;
  heap[heap_size].income = height;

  int cur = heap_size;

  while(cur != 1){
    int parent = cur/2;

    if(heap[parent].income < heap[cur].income){
      swap(parent, cur);
      cur = parent;
    }
    else break;
  }
}

void max_heapify(int idx){
  int left = idx*2, right = left+1;
  int largest = idx;

  if(left <= heap_size){
    int a = heap[left].income;
    int b = heap[largest].income;

    if(a > b || (a == b && heap[left].uID < heap[largest].uID)) largest = left;
  }

  if(right <= heap_size){
    int a = heap[right].income;
    int b = heap[largest].income;

    if(a > b || (a == b && heap[right].uID < heap[largest].uID)) largest = right;
  }

  if(largest != idx){
    swap(largest, idx);
    max_heapify(largest);
  }
}

int getTop10(int result[10]) 
{
  int count = 0;

  while(heap_size && count < 10){
    result[count++] = heap[1].uID;
    swap(1, heap_size--);
    max_heapify(1);
  }

  for(int i=1; i<=count; i++){
    int cur = (heap_size++) + 1;

    while(cur != 1){
      int parent = cur/2;
      int a = heap[parent].income;
      int b = heap[cur].income;

      if(a < b || (a == b && heap[parent].uID > heap[cur].uID)){
        swap(parent, cur);
        cur = parent;
      }
      else break;
    }
  }

  return count;
}

/*
한 테스트케이스 내에서 getTop10 함수 호출을 여러 번 하게 됨. 즉, 한 테스트케이스 내에서는 힙에 대한 pop이 없어야 한다. 이를 위해, 
getTop10에서 우선 heap_size를 줄이며(최대 10번) top 원소들을 뒤로 몰아넣은 후, 다 끝나고 나면 count를 리턴하기 전에 그걸 다시 힙에 
넣어주는 복구 과정을 추가했다. 그랬더니 맞음.
*/