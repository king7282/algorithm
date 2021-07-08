#include <stdio.h>
#include <algorithm>
#include <vector>

struct node {
	int num, left, right;

	node(int num, int left, int right) : num(num), left(left), right(right) {}
};

std::vector<node> nodeList;
int root = -1;

int insert_tree(int cur, int num) {
	if (cur == -1) {
		nodeList.push_back(node(num, -1, -1));

		return nodeList.size() - 1;
	}

	if (nodeList[cur].num < num)
		nodeList[cur].right = insert_tree(nodeList[cur].right, num);
	else
		nodeList[cur].left = insert_tree(nodeList[cur].left, num);
	
	return cur;
}

void trace(int cur) {
	if (cur == -1)
		return;

	trace(nodeList[cur].left);
	trace(nodeList[cur].right);
	printf("%d\n", nodeList[cur].num);
}

int main(void) {
	int input;

	while ((scanf("%d", &input)) > 0) {
		root = insert_tree(root, input);
	}

	trace(root);
}
