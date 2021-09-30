#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <queue>
#include <utility>

using namespace std;

char** map;
int N, M;
int** breakWall;
int cnt;

namespace BFS { int*** visited; }

pair <int, int> p1;
/*
void allocArr(int** arr)
{
	arr = new int* [N];
	for (int i = 0; i < N; i++) {
		arr[i] = new int[M];
		memset(arr[i], 0, sizeof(int) * M);
	}
}
*/


int doBFS(int v1, int v2)
{

	pair<pair <int, int>, int> cur;

	// 위, 밑, 왼, 오
	int _x[4] = { -1, 1, 0, 0 };
	int _y[4] = { 0, 0, -1, 1 };
	int n_x, n_y;
	int bw = 1; // 벽을 부쉈는지 여부

//	breakWall = new int* [N];
//	for (int i = 0; i < N; i++) {
//		breakWall[i] = new int[M];
//		memset(breakWall[i], 0, sizeof(int) * M);
//	}

	cnt = 1;

	BFS::visited[v1][v2][1] = 1;

	queue<pair<pair<int, int>, int > > q; // 안쪽 pair : 좌표, 바깥쪽 pair : 좌표, 벽부순여부
 // make_pakr : 두개를 페어로 하겠다...

	q.push({ {0,0} , 1 });

	while (!q.empty()) {
		cur = q.front();
		q.pop();

		if (cur.first.first == N - 1 && cur.first.second == M - 1)
			return BFS::visited[cur.first.first][cur.first.second][cur.second];

		for (int i = 0; i < 4; i++)
		{
			n_x = cur.first.first + _x[i]; // 주변 x
			n_y = cur.first.second + _y[i]; // 주변 y
			bw = cur.second;


			if (n_x < 0 || n_x >= N || n_y < 0 || n_y >= M) // 범위 밖
				continue;

			// 벽을 안 부쉈고(bw), 다음 경로가 0이고, 방문하지 않음
			if (map[n_x][n_y] == '0'  && BFS::visited[n_x][n_y][bw] == 0)
			{
				//bw = map[n_x][n_y] - '0';
				BFS::visited[n_x][n_y][bw] = BFS::visited[cur.first.first][cur.first.second][bw] + 1; // cnt
				q.push(make_pair(make_pair(n_x, n_y), bw));
			}

			//벽을 한번 부술거임! 다음 경로가 1임. 방문하지 않음.
			else if (map[n_x][n_y] == '1' && BFS::visited[n_x][n_y][bw] == 0 && bw == 1)
			{
				BFS::visited[n_x][n_y][bw-1] = BFS::visited[cur.first.first][cur.first.second][bw] + 1;
				q.push(make_pair(make_pair(n_x, n_y), bw-1));
			}

		}
/*
		for (int i = 1; i < ::N + 1; i++) {
			if (map[cur.first][cur.second] == '0' && BFS::visited[i] == 0)
			{
				if(//다음이 1이고, breakWall ==0 )
				BFS::visited[i] = 1;
				cnt++;
				cout << i << " ";
				q.push(i);
			}
		}*/
	}

	return -1;
}

void printMap()
{

	for (int i = 0; i < ::N; i++) {
		for (int j = 0; j < ::M; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
}

int main()
{

	cin >> ::N >> ::M;
	int N = ::N;
	int M = ::M;

	map = new char* [N + 1];
	for (int i = 0; i < N + 1; i++) {
		map[i] = new char[M + 1];
		memset(map[i], '0', sizeof(char) * (M + 1)); //문자열이니까 NULL값 들어갈 1을 추가해줘야함.
	}

	char buff[1000];

	for (int i = 0; i < N; i++) {
		cin >> buff;
		strcpy(map[i], buff);
	}

	BFS::visited = new int** [N];
	for (int i = 0; i < N; i++) {
		BFS::visited[i] = new int*[M];
		memset(BFS::visited[i], 0, sizeof(int) * M);
		for (int j = 0; j < M; j++) {
			BFS::visited[i][j] = new int[2];
			memset(BFS::visited[i][j], 0, sizeof(int) * 2);
		}
	}

	cout << doBFS(0, 0);


	for (int i = 0; i < N; i++) {
		delete[] map[i];
		for (int j = 0; j < M; j++) {
			delete[] BFS::visited[i][j];
		}
		delete[] BFS::visited[i];
	}

	delete[] map; // 할당 공간 반환
//	delete[] DFS::visited;
	delete[] BFS::visited;
	delete[] breakWall;

	return 0;

}
