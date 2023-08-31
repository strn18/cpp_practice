// 17697. [Pro] 공지방송
#include <vector>
#include <unordered_map>
#include <cstring>
#define MAX 86400

using namespace std;

unordered_map<int, pair<int, int>> time; // time[i] = {a, b}라면, a시에 출근하여 b시(정시)에 퇴근함.
int inPerson[MAX + 1]; // inPerson[i]: i시간이 됐을 때 출근하는 사람 수
int outPerson[MAX + 1]; // outPerson[i]: i시간이 됐을 때 퇴근하는 사람 수

void init() {
  time.clear();

	return;
}

int add(int mId, int mStart, int mEnd) {
  time[mId] = {mStart, mEnd + 1}; // [mStart, mEnd + 1)까지 회사에 있는 것이므로, time의 정의에 맞게 변형해서 넣음.

	return time.size();
}

int remove(int mId) {
  time.erase(mId);

	return time.size();
}

int announce(int mDuration, int M) {
  int count = 0;

  memset(inPerson, 0, sizeof(inPerson));
  memset(outPerson, 0, sizeof(outPerson));

  for(auto t: time){
    int start = t.second.first;
    int end = t.second.second;

    if(end - start >= mDuration){
      inPerson[start]++;
      outPerson[end - mDuration]++; // 왜 이렇게 하는지는 해설 참조. 
      // 대충 설명하자면, [start, end-mDuration) 동안만 회사에 있고, 대신 공지방송을 0(mDuration-mDuration)시간 동안만 한다고 생각하는 것임.
    }
  }

  for(int i=0; i<=MAX; i++){
    count += inPerson[i];
    if(count >= M) return i;
    count -= outPerson[i];
  }

	return -1;
}