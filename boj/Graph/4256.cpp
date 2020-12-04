#include <stdio.h>
#include <algorithm>

struct node {
	int left, right;
};

node tree[1010];
int preorder[1010], inorder[1010];
int cur;

int make_tree(int s, int e) {
	if (s > e)
		return -1;

	int index = -1, node = preorder[cur];
	for (int i = s; i <= e; i++) {
		if (inorder[i] == node)
			index = i;
	}

	if (index == -1)
		return -1;

	cur++;
	tree[node].left = make_tree(s, index - 1);
	tree[node].right = make_tree(index + 1, e);

	return node;
}

void post_order(int node) {
	if (tree[node].left != -1)
		post_order(tree[node].left);
	if (tree[node].right != -1)
		post_order(tree[node].right);
	printf("%d ", node);
}

int main(void) {
	int test;
	scanf("%d", &test);

	for (int t = 0; t < test; t++) {
		int n;
		scanf("%d", &n);

		for (int i = 1; i <= n; i++)
			tree[i].left = tree[i].right = -1;

		for (int i = 1; i <= n; i++)
			scanf("%d", preorder + i);

		for (int i = 1; i <= n; i++)
			scanf("%d", inorder + i);

		cur = 1;
		make_tree(1, n);

		post_order(preorder[1]);
		printf("\n");
	}
}