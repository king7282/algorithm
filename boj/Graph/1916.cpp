#include <stdio.h>
#include <vector>
#include <queue>
#include <string.h>

struct node {
    int x, weight;
    node(int x, int weight) : x(x), weight(weight) {}
};

bool operator<(node a, node b) {
    return a.weight > b.weight;
}

int visit[1010];
std::vector<std::pair<int, int> > adj[1010];
std::priority_queue<node> qu;

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({ b, c });
	}
	int s, e;
	scanf("%d %d", &s, &e);
	
	memset(visit, 0x7f, sizeof(visit));
	visit[s] = 0;
    qu.push({s, visit[s]});
    
	while (!qu.empty()) {
		auto top = qu.top();
		qu.pop();
        if(top.weight != visit[top.x])
            continue;
        
		for (int i = 0; i < adj[top.x].size(); i++)
			if (visit[adj[top.x][i].first] > visit[top.x] + adj[top.x][i].second) {
				visit[adj[top.x][i].first] = visit[top.x] + adj[top.x][i].second;
				qu.push({adj[top.x][i].first, visit[adj[top.x][i].first]});
			}
	}

	printf("%d\n", visit[e]);
}