#include <iostream>
#include <string.h>
#include <queue>

using namespace std;

int** graph;
int vertex, edge, startV;
namespace BFS { int* visited; }
namespace DFS { int* visited; }

void addEdge(int v1, int v2)
{
	graph[v1][v2] = 1;
	graph[v2][v1] = 1;

	return;
}

void doDFS(int _v)
{
	int v = _v;

	DFS::visited[v] = 1;
	cout << v << " ";

	for (int i = 1; i < ::vertex + 1; i++) {
		if (graph[v][i] == 1 && DFS::visited[i] == 0)
		{
			doDFS(i);
		}
	}

	return;
}

void doBFS(int _v)
{
	int v = _v;
	int cur = 0;

	BFS::visited[v] = 1;
	cout << v << " ";

	queue<int> q;
	q.push(v);

	while (!q.empty()) {
		cur = q.front();
		q.pop();

		for (int i = 1; i < ::vertex + 1; i++) {
			if (graph[cur][i] == 1 && BFS::visited[i] == 0)
			{
				BFS::visited[i] = 1;
				cout << i << " ";
				q.push(i);
			}
		}
	}

	return;
}

int main()
{

	int v1, v2;
	cin >> ::vertex >> ::edge >> ::startV;

	graph = new int* [::vertex + 1];
	for (int i = 0; i < ::vertex + 1; i++) {
		graph[i] = new int[::vertex + 1];
		memset(graph[i], 0, sizeof(int) * (::vertex + 1));
	}

	DFS::visited = new int[::vertex + 1];
	memset(DFS::visited, 0, sizeof(int) * (::vertex + 1));

	BFS::visited = new int[::vertex + 1];
	memset(BFS::visited, 0, sizeof(int) * (::vertex + 1));

	for (int i = 0; i < edge; i++) {
		cin >> v1 >> v2;

		addEdge(v1, v2);
	}

	doDFS(startV);
	cout << endl;
	doBFS(startV);

	for (int i = 0; i < ::vertex + 1;i++) {
		delete[] graph[i];
	}
	delete[] graph; // 할당 공간 반환
	delete[] DFS::visited;
	delete[] BFS::visited;

	return 0;

}
