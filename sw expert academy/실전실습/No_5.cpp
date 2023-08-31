// 17694. [Pro] 개발협업도구
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#define LMT 50

using namespace std;

typedef struct{
  string content;
  int created, edited;
} file_info;

typedef struct{
  string parent;
  vector<string> child; // 자식 노드들(추가한 순)
  
  unordered_map<string, file_info> files; // 노드가 가진 파일들
  priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> oldest; // {파일 생성 시각, 파일 이름}
  // 노드의 파일이 50개 초과일 때, 가장 생성 시각이 이른 파일을 제거하기 위해 사용. 걔는 oldest에서 pop 해주고, files에서도 erase 해준다.
} branch_info;

unordered_map<string, branch_info> b;

void init() {
  b = unordered_map<string, branch_info>();
	b["root"] = branch_info();
}

void create(int mTime, char mBranch[], char mFile[], char mData[]) {
  if(b[mBranch].oldest.size() == LMT){ // 파일을 추가하려는데 이미 50개라면, 가장 생성 시각이 이른 파일을 제거
    string s = b[mBranch].oldest.top().second;

    b[mBranch].files.erase(s);
    b[mBranch].oldest.pop();
  }

	b[mBranch].files[mFile] = {mData, mTime, mTime};
  b[mBranch].oldest.push({mTime, mFile});
}

void edit(int mTime, char mBranch[], char mFile[], char mData[]) {
	b[mBranch].files[mFile].content = mData;
	b[mBranch].files[mFile].edited = mTime;
}

void branch(int mTime, char mBranch[], char mChild[]) {
  b[mChild] = branch_info();

  b[mChild].parent = mBranch;
  b[mChild].files = b[mBranch].files;
  b[mChild].oldest = b[mBranch].oldest;

  b[mBranch].child.push_back(mChild);
}

void merge_to_me(string mBranch){ // mBranch의 자식들을 mBranch에게 병합하고, mBranch의 파일이 50개 이하가 되도록 줄인다.
  if(b[mBranch].child.empty()) return; // 리프 노드라면, 이미 위의 상태를 만족하므로 리턴.

  for(int i=0; i<b[mBranch].child.size(); i++){
    string c = b[mBranch].child[i];

    merge_to_me(c); // 먼저 자식에게 이 함수를 재귀 쳐줌.

    for(auto s: b[c].files){ // 그런 다음, 자식의 파일을 mBranch의 파일에 넣는다. 
      if(b[mBranch].files.count(s.first) == 0){ // mBranch에 없는 파일이면 바로 넣는다.
        b[mBranch].files[s.first] = s.second;
        b[mBranch].oldest.push({s.second.created, s.first});
      }
      else if(b[mBranch].files[s.first].created == s.second.created){ // 있는 파일이면, 최근에 수정된 놈을 남긴다.
        if(b[mBranch].files[s.first].edited < s.second.edited)
          b[mBranch].files[s.first] = s.second;
      }
    }

    b.erase(c); // 자식은 이제 사라짐(mBranch에게 병합되니까)

    while(b[mBranch].files.size() > LMT){ // 그런 다음, mBranch의 파일이 50개 이하가 되도록 한다.
      string s = b[mBranch].oldest.top().second;
    
      b[mBranch].files.erase(s);
      b[mBranch].oldest.pop();
    }
  }
}

void merge(int mTime, char mBranch[]) { // mBranch를 그 부모에게 병합해야 한다.
  string p = b[mBranch].parent;

  merge_to_me(mBranch); // 먼저 mBranch의 자식들을 mBranch에게 병합시킨다.

  for(auto s: b[mBranch].files){ // 이제 mBranch를 부모에게 병합해야 하므로, 파일을 옮긴다(여기부터는 65행과 동일)
    if(b[p].files.count(s.first) == 0){
      b[p].files[s.first] = s.second;
      b[p].oldest.push({s.second.created, s.first});
    }
    else if(b[p].files[s.first].created == s.second.created){
      if(b[p].files[s.first].edited < s.second.edited)
        b[p].files[s.first] = s.second;
    }
  }

  b.erase(mBranch);

  while(b[p].files.size() > LMT){
    string s = b[p].oldest.top().second;
    
    b[p].files.erase(s);
    b[p].oldest.pop();
  }

  for(int i=0; i<b[p].child.size(); i++){ // 이제 p는 mBranch를 자식으로 갖지 않으므로, child에서 지워줌.
    if(b[p].child[i] == mBranch){
      b[p].child.erase(b[p].child.begin() + i);
      break;
    }
  }
}

int readfile(int mTime, char mBranch[], char mFile[], char retString[]) {
  string str = b[mBranch].files[mFile].content;

  for(int i=0; i<str.size(); i++)
    retString[i] = str[i];
    
  retString[str.size()] = '\0'; // 끝에 널 문자 넣어야 함!!

	return str.size();
}

/*
거의 다 풀었는데(테케 25개 중 반 정도는 맞고 반은 틀리는 상태), merge하는 부분에서 틀린 게 있었던 문제...

문제에서 주어진 병합 과정은 다음과 같았다. 노드 A, B, C, D가 있다고 하자. 이때, 자식 관계는 A - B - (C, D) 즉
  A
  |
  B
 / \
C   D
이런 상태라고 하자. 이때, merge(B)를 한다면? 우선 B를 A에 병합시키기 전에, C와 D를 B에 병합시켜야 한다. 근데 이때, 
C와 D의 파일을 B에 먼저 다 때려박고, B의 파일이 50개 초과면 50개로 줄이는 게 아니라,
C의 파일을 B에 때려박고, B의 파일이 50개 초과면 50개로 줄이고, D의 파일을 B에 때려박고, B의 파일이 50개 초과면 50개로 줄여야 한다.
즉, 어떠한 노드의 자식 노드들을 그 노드에게 다 병합할 때, 자식 노드들의 파일들을 그 노드에게 다 넣고(물론 중복은 제외하고, 같은 파일이면 
수정 시각이 늦은 놈을 남김), 마지막에 그 노드의 파일을 최대 50개로 줄이는 게 아니라, 
한 자식 노드의 파일들을 그 노드에게 넣고, 그 노드의 파일을 최대 50개로 줄이고, 그 다음 자식 노드의 파일들을 그 노드에게 넣고, ... 
이렇게 해야 한다는 것.

사실 이걸 눈치챈 다음에도, 아니 어차피 결과적으로는 똑같지 않나? 싶었는데, 아무리 찾아봐도 다른 오류는 안 보여서, 저 순서에 맞게 코드를 
바꿨더니 맞았다...
*/