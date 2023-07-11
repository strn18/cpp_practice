#include <stdio.h>
#define MAX 400
#define INF 2100000000

int dist[MAX+1][MAX+1];

int main(void)
{
	int test_case;
	int T;

	setbuf(stdout, NULL);
	scanf("%d", &T);
    
	for (test_case = 1; test_case <= T; ++test_case)
	{
        int N, M, ans = INF;
        int X, Y, C;

        scanf("%d %d", &N, &M);

        for(int i=1; i<=N; i++)
            for(int j=1; j<=N; j++)
                dist[i][j] = INF;

        for(int i=0; i<M; i++){
            scanf("%d %d %d", &X, &Y, &C);
            dist[X][Y] = C;
        }

        // 플로이드 와샬 사용
        for(int k=1; k<=N; k++){
            for(int i=1; i<=N; i++){
                if(dist[i][k] == INF) continue;

                for(int j=1; j<=N; j++){
                    if(dist[k][j] == INF) continue;

                    if(dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }

        for(int i=1; i<=N; i++)
            if(dist[i][i] < ans) ans = dist[i][i];

        printf("#%d %d\n", test_case, (ans == INF ? -1 : ans));
	}
	return 0;
}

// 하계 대학생 S/W 알고리즘 특강 사전문제 1번(17675. 민석이의 마니또)