#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<algorithm>

#define INF 99999999

using namespace std;

int V, E, S;
int N;

pair<int*, int*> answer;
vector<pair<int, int>>* arr;    // 형태가 2차원 배열과 같다...


int doDijkstra(int start, int j);

int main()
{

    cin >> N; // 테스트케이스 개수

    answer.first = new int[N];
    answer.second = new int[N];


    for (int i = 0; i < N; i++) {
        cin >> V >> E >> S;

        arr = new vector<pair<int, int>>[V + 1];

        for (int i = 0; i < E; i++) {
            int from, to, val;
            cin >> to >> from >> val; //그래프 상의 엣지들에 대한 정보를 입력받습니다.
            arr[from].push_back({ to,val });
        }

        doDijkstra(S, i);
    }

}

int doDijkstra(int start, int j)
{

    int* dist = new int[V + 1];    //최단거리를 갱신해주는 배열입니다.
    fill(dist, dist + V + 1, INF);    //먼저 무한대로 전부 초기화를 시켜둡니다.

    priority_queue<pair<int, int>> qu;

    qu.push({ 0,start });    //우선순위 큐에 시작점을 넣어줍니다.
    dist[start] = 0;    //시작점의 최단거리를 갱신합니다.

    while (!qu.empty()) {
        int cost = -qu.top().first;    // cost는 다음 방문할 점의 dist값을 뜻합니다.
        int here = qu.top().second;    // here을 방문할 점의 번호를 뜻합니다.

        qu.pop();

        for (int i = 0; i < arr[here].size(); i++) {
            int next = arr[here][i].first;
            int nextcost = arr[here][i].second;

            if (dist[next] > dist[here] + nextcost) {
                //현재 next에 저장된 dist의값보다 현재의 점을 거쳐서 갈 경우가
                // 거리가 더짧으면 갱신해 주고 큐에 넣습니다.
                dist[next] = dist[here] + nextcost;
                qu.push({ -dist[next],next });
            }
        }

    }

    int cnt = 0;

    for (int i = 1; i <= V; i++) {
        if (dist[i] == INF)
        {
            dist[i] = -1;
        }
        else
        {
            cnt++;
        }
    }

    cout << cnt << " " << *max_element(dist + 1, dist + V + 1) << "\n";

    return 0;
}
