#include <stdio.h>
#define MAX 200000

typedef struct{int val, pos;} largest;

largest row[MAX+1], col[MAX+1]; // 각각 {어떠한 행의 최댓값, 그 칸의 열값}, {어떠한 열의 최댓값, 그 칸의 행값}

int main(void)
{
	int test_case;
	int T;
    
	setbuf(stdout, NULL);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
        int N, M, Q, num;
        int total = 0;

        scanf("%d %d %d", &N, &M, &Q);

        if(N <= M){ // N행, M열이 있다고 본다.
            for(int i=1; i<=N; i++)
                row[i].val = 0;
            for(int i=1; i<=M; i++)
                col[i].val = 0;

            for(int i=1; i<=N; i++){
                for(int j=1; j<=M; j++){
                    scanf("%d", &num);

                    if(num > row[i].val){
                        row[i].val = num;
                        row[i].pos = j;
                    }
                    if(num > col[j].val){
                        col[j].val = num;
                        col[j].pos = i;
                    }
                }
            }
        }
        else{ // N열, M행이 있다고 본다.
            for(int i=1; i<=M; i++)
                row[i].val = 0;
            for(int i=1; i<=N; i++)
                col[i].val = 0;

            for(int i=1; i<=N; i++){
                for(int j=1; j<=M; j++){
                    scanf("%d", &num);

                    if(num > row[j].val){
                        row[j].val = num;
                        row[j].pos = i;
                    }
                    if(num > col[i].val){
                        col[i].val = num;
                        col[i].pos = j;
                    }
                }
            }
        }

        while(Q--){
            int r, c, x;

            if(N <= M) scanf("%d %d %d", &r, &c, &x);
            else scanf("%d %d %d", &c, &r, &x);

            if(x > row[r].val){
                row[r].val = x;
                row[r].pos = c;
            }
            if(x > col[c].val){
                col[c].val = x;
                col[c].pos = r;
            }

            if(N <= M){
                for(int i=1; i<=N; i++)
                    if(row[i].val == col[row[i].pos].val) total++; // 어떠한 행의 최댓값 칸이 그 열에서도 최댓값이라면, 안전한 셀이다.
            }
            else{
                for(int i=1; i<=M; i++)
                    if(row[i].val == col[row[i].pos].val) total++;
            }
        }

        printf("#%d %d\n", test_case, total);
	}
	return 0;
}

// 하계 대학생 S/W 알고리즘 특강 사전문제 2번(17670. 부자의 꿈)