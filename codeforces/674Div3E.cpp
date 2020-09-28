#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <limits.h>
 
struct dinic {
	struct edge {
		long long to, cap, rev;
		edge(long long to, long long cap, long long rev) : to(to), cap(cap), rev(rev) {}
	};
 
	std::vector<edge> adj[2010]; // 첫번째 to, 두번째 capacity
	long long level[2010];
	long long iter[2010];
 
	void add_edge(long long from, long long to, long long capacity) {
		adj[from].push_back(edge(to, capacity, adj[to].size()));
		adj[to].push_back(edge(from, 0, adj[from].size() - 1));
	}
 
	void bfs(int start) {
		memset(level, -1, sizeof(level));
 
		level[start] = 0;
		std::queue<int> qu;
		qu.push(start);
		while (!qu.empty()) {
			int f = qu.front();
			qu.pop();
 
			for (int i = 0; i < adj[f].size(); i++) {
				if (adj[f][i].cap > 0 && level[adj[f][i].to] < 0) {
					level[adj[f][i].to] = level[f] + 1;
					qu.push(adj[f][i].to);
				}
			}
		}
	}
 
	long long dfs(int num, int finish, long long cap) {
		if (num == finish) return cap;
		for (long long &i = iter[num]; i < adj[num].size(); i++) {
			if (adj[num][i].cap > 0 && level[num] < level[adj[num][i].to]) {
				int d = dfs(adj[num][i].to, finish, std::min(cap, adj[num][i].cap));
				if (d > 0) {
					adj[num][i].cap -= d;
					adj[adj[num][i].to][adj[num][i].rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}
 
	long long max_flow(int start, int finish) {
		long long result = 0;
		while (1) {
			bfs(start);
			if (level[finish] == -1)
				return result;
			memset(iter, 0, sizeof(iter));
			long long tmp;
			while ((tmp = dfs(start, finish, INT_MAX / 2)) > 0)
				result += tmp;
		}
	}
};
 
 
int main(void) {
	long long n;
	scanf("%I64d", &n);
 
	long long A[3], B[3];
	scanf("%I64d %I64d %I64d", A, A + 1, A + 2);
	scanf("%I64d %I64d %I64d", B, B + 1, B + 2);
 
	int source = 0, sink = 7;
 
	dinic flow;
 
	flow.add_edge(source, 1, A[0]);
	flow.add_edge(source, 2, A[1]);
	flow.add_edge(source, 3, A[2]);
 
	flow.add_edge(4, sink, B[0]);
	flow.add_edge(5, sink, B[1]);
	flow.add_edge(6, sink, B[2]);
 
	flow.add_edge(1, 4, INT_MAX / 2);
	flow.add_edge(1, 6, INT_MAX / 2);
	flow.add_edge(2, 5, INT_MAX / 2);
	flow.add_edge(2, 4, INT_MAX / 2);
	flow.add_edge(3, 5, INT_MAX / 2);
	flow.add_edge(3, 6, INT_MAX / 2);
 
	printf("%I64d %I64d\n", n - flow.max_flow(source, sink), std::min(A[0], B[1]) + std::min(A[1], B[2]) + std::min(A[2], B[0]));
}