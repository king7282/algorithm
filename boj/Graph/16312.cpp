#include <stdio.h>
#include <vector>
#include <string.h>
#include <queue>
#include <limits.h>
#include <algorithm>

struct dinic {
	struct edge {
		int to, rev;
		long long cap;
		edge(int to, long long cap, int rev) : to(to), cap(cap), rev(rev) {}
	};

	std::vector<edge> adj[2020]; // 첫번째 to, 두번째 capacity
	int level[2020];
	int iter[2020];

	void add_edge(int from, int to, long long capacity) {
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
		for (int &i = iter[num]; i < adj[num].size(); i++) {
			if (adj[num][i].cap > 0 && level[num] < level[adj[num][i].to]) {
				long long d = dfs(adj[num][i].to, finish, std::min(cap, adj[num][i].cap));
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
			while ((tmp = dfs(start, finish, LLONG_MAX / 2)) > 0)
				result += tmp;
		}
	}
};

struct info {
	int next;
	long long weight;
	info(int next, long long weight) : next(next), weight(weight) {}
};

bool operator<(info a, info b) {
	return a.weight > b.weight;
}

std::pair<int, int> flags[100010];
long long visit[100010];
long long input[100010];
std::vector<info> graph[100010];
std::pair<int, int> query[15];
std::priority_queue<info> qu;
std::vector<std::pair<long long, int>> shelter[100010];
int n, m, s;

bool OK(long long num) {
	dinic flow;
	int source = 0, sink = 2010;
	long long sum = 0;

	for (int i = 1; i <= n; i++) {
		flags[i].first = 0;
		flags[i].second = i;
		for (int j = 0; j < shelter[i].size(); j++) {
			if (shelter[i][j].first > num) {
				continue;
			}
			
			flags[i].first += (1 << (shelter[i][j].second));
		}
		sum += input[i];
	}

	for (int i = 1; i <= s; i++) {
		flow.add_edge(source, i, query[i].second);
	}

	std::sort(flags + 1, flags + 1 + n);
	int cnt = s + 1, prev = flags[1].first, start = 1;
	for (int i = 1; i <= n; i++) {
		if (prev != flags[i].first) {
			long long ttmp = 0;
			for (int j = start; j < i; j++) {
				ttmp += input[flags[j].second];
			}
			flow.add_edge(cnt, sink, ttmp);
			for (int j = 1; j <= s; j++) {
				if (((1 << j) & flags[start].first) == 0)
					continue;
				flow.add_edge(j, cnt, LLONG_MAX / 2);
			}
			cnt++;
			start = i;
		}
		prev = flags[i].first;
	}

	long long ttmp = 0;
	for (int j = start; j <= n; j++) {
		ttmp += input[flags[j].second];
	}
	flow.add_edge(cnt, sink, ttmp);
	for (int j = 1; j <= s; j++) {
		if (((1 << j) & flags[start].first) == 0)
			continue;
		flow.add_edge(j, cnt, LLONG_MAX / 2);
	}

	long long tmp = flow.max_flow(source, sink);
	if (tmp >= sum)
		return true;
	return false;
}

int main(void) {
	scanf("%d %d %d", &n, &m, &s);

	for (int i = 1; i <= n; i++)
		scanf("%lld", input + i);

	for (int i = 0; i < m; i++) {
		int a, b;
		long long c;
		scanf("%d %d %lld", &a, &b, &c);
		graph[a].push_back(info(b, c));
		graph[b].push_back(info(a, c));
	}

	long long limits = 0;

	for (int i = 1; i <= s; i++) {
		scanf("%d %d", &query[i].first, &query[i].second);
		qu.push(info(query[i].first, 0));
		memset(visit, 0x7f, sizeof(visit));
		visit[query[i].first] = 0;

		while (!qu.empty()) {
			info top = qu.top();
			qu.pop();

			for (int i = 0; i < graph[top.next].size(); i++) {
				if (visit[graph[top.next][i].next] > top.weight + graph[top.next][i].weight) {
					visit[graph[top.next][i].next] = top.weight + graph[top.next][i].weight;
					qu.push(info(graph[top.next][i].next, visit[graph[top.next][i].next]));
				}
			}
		}

		for (int j = 1; j <= n; j++) {
			shelter[j].push_back(std::make_pair(visit[j], i));
			limits = std::max(limits, visit[j]);
		}
	}

	for (int i = 1; i <= n; i++)
		std::sort(shelter[i].begin(), shelter[i].end());

	long long s = 0, e = limits, r = limits;

	while (s <= e) {
		long long mid = (s + e) / 2;
		if (OK(mid)) {
			r = std::min(r, mid);
			e = mid - 1;
		}
		else
			s = mid + 1;
	}

	printf("%lld\n", r);

}