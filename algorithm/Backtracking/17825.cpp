#include <iostream>

using namespace std;

int ans = -1, total = 0;
int nums[10], piece[4];

typedef struct{int point, red, blue, occupied;}info;
info board[33];

void update(int depth);
int move_piece(int idx, int n);
void initialize_board(void);

int main(){
  for(int i=0; i<10; i++)
    scanf("%d", &nums[i]);
  
  initialize_board();
  update(0);
  printf("%d", ans);

  return 0;
}

void update(int depth){
  if(depth == 10){
    ans = max(ans, total);
    return;
  }
  for(int i=0; i<4; i++){
    if(piece[i] == 32) continue;

    int ori_pos = piece[i];
    int points = move_piece(i, nums[depth]);
    board[ori_pos].occupied = 0;

    if(points != -1){
      total += points;
      board[piece[i]].occupied = 1;
      update(depth+1);
      total -= points;
      board[piece[i]].occupied = 0;
    }
    piece[i] = ori_pos;
    board[ori_pos].occupied = 1;
  }
}
int move_piece(int idx, int n){
  for(int moved=0; moved<n; moved++){
    if(moved)
      piece[idx] = board[piece[idx]].red;
    else
      piece[idx] = board[piece[idx]].blue;
  }
  if(piece[idx] == 32 || !board[piece[idx]].occupied)
    return board[piece[idx]].point;
  else
    return -1;
}
void initialize_board(void){
  for(int i=0; i<33; i++){
    if(i==5){
      board[i].red = 6;
      board[i].blue = 20;
      board[i].point = 10;
    }
    else if(i==10){
      board[i].red = 11;
      board[i].blue = 23;
      board[i].point = 20;
    }
    else if(i==15){
      board[i].red = 16;
      board[i].blue = 25;
      board[i].point = 30;
    }
    else if(i==19){
      board[i].red = 31;
      board[i].blue = 31;
      board[i].point = 38;
    }
    else if(i==20||i==21||i==23||i==25){
      board[i].red = i+1;
      board[i].blue = i+1;
      board[i].point = 13+(i-20)*3;
    }
    else if(i==22){
      board[i].red = 28;
      board[i].blue = 28;
      board[i].point = 19;
    }
    else if(i==24){
      board[i].red = 28;
      board[i].blue = 28;
      board[i].point = 24;
    }
    else if(i==26){
      board[i].red = 27;
      board[i].blue = 27;
      board[i].point = 27;
    }
    else if(i==27){
      board[i].red = 28;
      board[i].blue = 28;
      board[i].point = 26;
    }
    else if(28<=i && i<=31){
      board[i].red = i+1;
      board[i].blue = i+1;
      board[i].point = 25+(i-28)*5;
    }
    else if(i==32){
      board[i].red = 32;
      board[i].blue = 32;
      board[i].point = 0;
    }
    else{
      board[i].red = i+1;
      board[i].blue = i+1;
      board[i].point = i*2;
    }
    board[i].occupied = 0;
  }
}

/*
굉장히 귀찮았지만 크게 어렵지는 않았던 백트래킹 문제.
처음 움직일 때 blue로 가고 그 다음부터는 red로 가는 식으로 짜서, 보드의 칸에 점수, red, blue, 그리고 다른 말이 위치해있는지 표시하는 occupied에
대한 정보를 넣는 info 구조체를 선언해서 board를 만들었다. 문제에 주어진 정보를 board에 넣는 게 굉장히 귀찮았지만(initialize_board 함수) 그거 빼면
그냥 n번째로 주사위에서 나올 수를 4가지 말에 차례로 적용시키면서 dfs로 짜면 크게 어려움은 없었다. 물론 이렇게 하면 중복되는 경우가 나오겠지만,
어차피 주사위에서 나올 수는 10가지 뿐이라 4^10 = 약 백만 정도라서 상관 없었다.
나는 move_piece에서 idx번 말을 하나하나 옮겨놓고, update에서 만약 말을 옮길 수 있는 경우(points != 1) 옮긴 자리에 그대로 두고 (occupied = 1) 
update를 한 후 다시 원래 자리로 옮겨놓는 식으로 했는데, 다른 풀이를 보니 말을 최종적으로 옮길 자리를 따로 기록해두고, 만약 거기로 옮길 수 있으면
그제서야 옮긴 후 update하고 다시 원래 자리로 옮기는 식으로 했다. https://haejun0317.tistory.com/163 이게 좀 더 깔끔한 것 같긴 하네.

*/