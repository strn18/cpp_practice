// 15963. [Pro] 최대최소값 찾기
#include <algorithm>
#define MAX_BUCKET_SIZE 448
#define INF 2100000000

using namespace std;

typedef struct bucket{
  int len, minVal, maxVal;
  int arr[MAX_BUCKET_SIZE];
  bucket *prev, *next;

  void init(bucket *prevBucket, bucket *lastBucket){
    len = 0;
    minVal = INF;
    maxVal = -INF;
    prev = prevBucket;
    next = lastBucket;
  }

  void pushBack(int val){
    arr[len++] = val;
    minVal = min(minVal, val);
    maxVal = max(maxVal, val);
  }

  void recalculate(void){
    minVal = INF;
    maxVal = -INF;

    for(int i=0; i<len; i++){
      minVal = min(minVal, arr[i]);
      maxVal = max(maxVal, arr[i]);
    }
  }
} bucket;

bucket b[MAX_BUCKET_SIZE];
bucket first, last;
int lastIdx;

void add(int M, int mValue[]){
  if(last.prev == &first){
    b[++lastIdx].init(&first, &last);
    first.next = &b[lastIdx];
    last.prev = &b[lastIdx];
  }

  for(int i=0; i<M; i++){
    if(last.prev->len == MAX_BUCKET_SIZE){
      b[++lastIdx].init(last.prev, &last);
      last.prev->next = &b[lastIdx];
      last.prev = &b[lastIdx];
    }
    last.prev->pushBack(mValue[i]);
  }
}

void init(int N, int mValue[]){
  lastIdx = 0;
  b[0].init(&first, &last);
  first.next = &b[0];
  last.prev = &b[0];

  add(N, mValue);
}

void erase(int mFrom, int mTo){
  int skipCount = 0;
  int deleteCount = mTo-mFrom+1;

  bucket *cur = first.next;

  while(skipCount + cur->len < mFrom){
    skipCount += cur->len;
    cur = cur->next;
  }

  int targetIdx = mFrom-skipCount-1;

  while((cur != &last) && (deleteCount != 0)){
    if(targetIdx + deleteCount >= cur->len){
      deleteCount -= (cur->len - targetIdx);
      cur->len = targetIdx;

      if(targetIdx == 0){
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
      }
      else cur->recalculate();
      
      cur = cur->next;
      targetIdx = 0;
    }
    else{
      for(int i=targetIdx+deleteCount; i<cur->len; i++)
        cur->arr[i-deleteCount] = cur->arr[i];
      cur->len -= deleteCount;
      cur->recalculate();
      return;
    }
  }
}

int find(int K){
  int minVal = INF;
  int maxVal = -INF;

  bucket *cur = last.prev;

  while(K > 0){
    if(cur->len <= K){
      minVal = min(minVal, cur->minVal);
      maxVal = max(maxVal, cur->maxVal);
      K -= cur->len;
      cur = cur->prev;
    }
    else{
      for(int i=1; i<=K; i++){
        minVal = min(minVal, cur->arr[cur->len - i]);
        maxVal = max(maxVal, cur->arr[cur->len - i]);
      }
      break;
    }
  }

  return maxVal - minVal;
}

/*
세그먼트 트리로 푸는 건줄 알았는데 아무리 생각해봐도 계속 시간초과가 날 것 같아서 고민하다가 풀이를 참고함.

풀이를 보니깐 세그먼트 트리가 아니라 무슨 버켓? 이런 개념을 사용했다.
자세한 건 풀이 참조. erase 함수만 내멋대로 짰고 나머지는 풀이와 거의 비슷함.
*/