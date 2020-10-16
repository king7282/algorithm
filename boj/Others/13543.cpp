#include <stdio.h>
#include <algorithm>
#include <cassert>
#include <climits>

unsigned combination[11][11];

struct SplayTree {
	struct node {
		node *l, *r, *p;
		long long key;
		int cnt, lazy;
		unsigned sum[11], value, k;
	};

	node *tree;

	void Rotate(node *x) {
		node *p = x->p, *tmp;

		if (p->l == x) {
			p->l = tmp = x->r;
			x->r = p;
		}
		else {
			p->r = tmp = x->l;
			x->l = p;
		}

		x->p = p->p;
		p->p = x;
		if (tmp != NULL)
			tmp->p = p;

		if (x->p == NULL)
			tree = x;
		else {
			if (p == x->p->l)
				x->p->l = x;
			else
				x->p->r = x;
		}
		Update(p);
		Update(x);
	}

	void Splay(node *x) {
		while (x->p != NULL) {
			node *p = x->p;
			node *g = p->p;
			if (g != NULL) {
				if ((x == p->l && p == g->l) || (x == p->r && p == g->r))
					Rotate(p);
				else
					Rotate(x);
			}
			Rotate(x);
		}
	}

	void Insert(long long key, unsigned value, unsigned k) {
		node *p = tree;
		node *x = new node();
		x->key = key; x->value = value; x->k = k;
		x->l = x->r = NULL;
		if (p == NULL) {
			tree = x;
			x->p = NULL;
			return;
		}

		while (1) {
			Lazy(p);
			if (key == p->key)
				return;

			if (key < p->key) {
				if (p->l == NULL) {
					p->l = x;
					x->p = p;
					break;
				}
				p = p->l;
			}
			else {
				if (p->r == NULL) {
					p->r = x;
					x->p = p;
					break;
				}
				p = p->r;
			}
		}
		Splay(x);
	}

	bool Find(long long key) {
		node *p = tree;

		if (p == NULL)
			return false;

		while (1) {
			Lazy(p);
			if (p->key == key)
				break;

			if (key < p->key) {
				if (p->l == NULL)
					break;
				p = p->l;
			}
			else {
				if (p->r == NULL)
					break;
				p = p->r;
			}
		}

		Splay(p);
		return p->key == key;
	}

	void Delete(long long key) {
		if (!Find(key))
			return;

		node *p = tree;
		Lazy(p);
		if (p->l != NULL && p->r != NULL) {
			tree = p->l;
			tree->p = NULL;

			node *x = tree;
			while (x->r != NULL) {
				Lazy(x);
				x = x->r;
			}
			Lazy(x);

			x->r = p->r;
			p->r->p = x;
			Splay(x);
		}
		else if (p->l != NULL) {
			tree = p->l;
			tree->p = NULL;
		}
		else if (p->r != NULL) {
			tree = p->r;
			tree->p = NULL;
		}
		else {
			tree = NULL;
		}
		
		delete p;
	}

	void Update(node *x) {
		x->cnt = 1;
		unsigned tmp = 1;
		for (int i = 0; i <= 10; i++) {
			x->sum[i] = x->value * tmp;
			tmp = tmp * x->k;
		}

		if (x->l != NULL) {
			x->cnt += x->l->cnt;
			for(int i = 0; i <= 10; i++)
				x->sum[i] += x->l->sum[i];
		}
		if (x->r != NULL) {
			x->cnt += x->r->cnt;
			for(int i = 0; i <= 10; i++)
				x->sum[i] += x->r->sum[i];
		}
	}

	void kth_element(int k) {
		node *x = tree;
		Lazy(x);

		while (1) {
			while (x->l != NULL && x->l->cnt > k) {
				x = x->l;
				Lazy(x);
			}

			if (x->l != NULL) k -= x->l->cnt;
			if (k == 0)
				break;
			k--;
			x = x->r;
			Lazy(x);
		}
		Splay(x);
	}

	void Delete_k(int k) {
		kth_element(k);

		Delete(tree->key);
	}

	void Change(int i, unsigned z) {
		kth_element(i);
		unsigned num = 1;
		for (int a = 0; a <= 10; a++) {
			tree->sum[a] -= tree->value * num;
			tree->sum[a] += z * num;
			num = num * (unsigned)(tree->k);
		}
		tree->value = z;
	}

	void Add(int l, int r, int z) {
		Interval(l, r);
		node *x = tree->r->l;
		unsigned tmp[11] = { 1, };
		for (int i = 1; i <= 10; i++)
			tmp[i] = tmp[i - 1] * (unsigned)z;
		for (int i = 10; i >= 0; i--) {
			for (int j = 0; j < i; j++) {
				x->sum[i] += combination[i][j] * tmp[i - j] * x->sum[j];
			}
		}

		x->lazy += z;
	}

	void Interval(int l, int r) {
		kth_element(l - 1);

		node *x = tree;
		tree = x->r;
		tree->p = NULL;

		kth_element(r - l + 1);
		x->r = tree;
		tree->p = x;
		tree = x;
	}

	unsigned Sum(int l, int r, int k) {
		Interval(l, r);
		return tree->r->l->sum[k];
	}

	void Lazy(node *x) {
		if (x->lazy == 0)
			return;
		x->k += x->lazy;
		if (x->l != NULL) {
			x->l->lazy += x->lazy;
			unsigned tmp[11] = { 1, };
			for (int i = 1; i <= 10; i++)
				tmp[i] = tmp[i - 1] * (unsigned)x->lazy;

			for (int i = 10; i >= 0; i--) {
				for (int j = 0; j < i; j++) {
					x->l->sum[i] += combination[i][j] * tmp[i - j] * x->l->sum[j];
				}
			}
		}
		if (x->r != NULL) {
			x->r->lazy += x->lazy;
			unsigned tmp[11] = { 1, };
			for (int i = 1; i <= 10; i++)
				tmp[i] = tmp[i - 1] * (unsigned)x->lazy;

			for (int i = 10; i >= 0; i--) {
				for (int j = 0; j < i; j++) {
					x->r->sum[i] += combination[i][j] * tmp[i - j] * x->r->sum[j];
				}
			}
		}
		x->lazy = 0;
	}
};

SplayTree sptree;

int main(void) {
	int n;
	scanf("%d", &n);
	
	combination[0][0] = combination[1][0] = combination[1][1] = 1;
	for (int i = 2; i <= 10; i++) {
		combination[i][0] = 1;
		for (int j = 1; j <= i; j++)
			combination[i][j] = combination[i - 1][j - 1] + combination[i - 1][j];
	}

	sptree.Insert(LLONG_MIN / 2, 0, 0);
	sptree.Insert(LLONG_MAX / 2, 0, 0);
	int cnt = n;
	for (int i = 1; i <= n; i++) {
		unsigned a;
		scanf("%u", &a);

		sptree.Insert(10000000000LL * (i - 1), a, i);
	}
	int q;
	scanf("%d", &q);

	for (int i = 1; i <= q; i++) {
		int a;
		scanf("%d", &a);

		if (a == 1) {
			int b;
			unsigned c;
			scanf("%d %u", &b, &c);
			b++;
			sptree.kth_element(b);
			long long next_key = (sptree.tree)->key;
			sptree.kth_element(b - 1);
			long long prev_key = (sptree.tree)->key;
			long long key = (next_key + prev_key) / 2;

			sptree.Insert(key, c, b);
			cnt++;
			if(b + 1 <= cnt)
				sptree.Add(b + 1, cnt, 1);
		}
		else if (a == 2) {
			int b;
			scanf("%d", &b);
			b++;
			sptree.Delete_k(b);
			cnt--;
			if(b <= cnt)
				sptree.Add(b, cnt, -1);
		}
		else if (a == 3) {
			int b;
			unsigned c;
			scanf("%d %u", &b, &c);
			b++;
			sptree.Change(b, c);
		}
		else {
			int b, c, d;
			scanf("%d %d %d", &b, &c, &d);
			b++;
			c++;
			if (b > c)
				std::swap(b, c);

			unsigned tmp[11] = { 1, };
			unsigned result = 0;
			for (int j = 0; j <= d; j++) {
				if (j > 0)
					tmp[j] = tmp[j - 1] * (unsigned)(-1 * (b - 1));
			}

			for (int j = 0; j <= d; j++)
				result += combination[d][j] * sptree.Sum(b, c, j) * tmp[d - j];

			printf("%u\n", result);
		}
	}

}