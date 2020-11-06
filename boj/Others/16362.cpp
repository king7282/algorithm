#include <cstdio>
#include <vector>

std::vector<char> input;
int result = 0, num = 0;

void func(void) {
	int cnt = 0;
	while (num < input.size() && input[num] != ')') {
		if (input[num] == '(') {
			num++;
			func();
			if (result == 1)
				return;
			if (num >= input.size() || input[num] == ')')
				break;
		}

		if (input[num] == '+' || input[num] == '-' || input[num] == '*' || input[num] == '/' || input[num] == '%')
			cnt++;
		num++;
	}
	if (cnt != 1) {
		result = 1;
		return;
	}
	num++;
}

int main(void) {
	while (1) {
		char c;
		scanf("%c", &c);
		if (c == '\n')
			break;
		if (c == ' ')
			continue;
		input.push_back(c);
	}

	if (input.size() % 2 == 0) {
		printf("error\n");
		return 0;
	}
	int cnt = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '(')
			cnt++;
		else if (input[i] == ')')
			cnt--;

		if (cnt < 0)
			result = 2;
	}

	if (cnt != 0)
		result = 2;

	for (int i = 1; i < input.size() && result != 2; i++) {
		if (input[i - 1] == '(' && input[i] == ')')
			result = 2;
		if (input[i - 1] == '(' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '(' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '(' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '(' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '(' && input[i] == '%')
			result = 2;

		if (input[i - 1] == ')' && input[i] == '(')
			result = 2;
		if (input[i - 1] == ')' && 'a' <= input[i] && input[i] <= 'z')
			result = 2;


		if (input[i - 1] == '+' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '+' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '+' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '+' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '+' && input[i] == '%')
			result = 2;
		if (input[i - 1] == '+' && input[i] == ')')
			result = 2;

		if (input[i - 1] == '-' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '-' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '-' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '-' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '-' && input[i] == '%')
			result = 2;
		if (input[i - 1] == '-' && input[i] == ')')
			result = 2;

		if (input[i - 1] == '*' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '*' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '*' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '*' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '*' && input[i] == '%')
			result = 2;
		if (input[i - 1] == '*' && input[i] == ')')
			result = 2;

		if (input[i - 1] == '/' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '/' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '/' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '/' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '/' && input[i] == '%')
			result = 2;
		if (input[i - 1] == '/' && input[i] == ')')
			result = 2;

		if (input[i - 1] == '%' && input[i] == '+')
			result = 2;
		if (input[i - 1] == '%' && input[i] == '-')
			result = 2;
		if (input[i - 1] == '%' && input[i] == '*')
			result = 2;
		if (input[i - 1] == '%' && input[i] == '/')
			result = 2;
		if (input[i - 1] == '%' && input[i] == '%')
			result = 2;
		if (input[i - 1] == '%' && input[i] == ')')
			result = 2;

		if ('a' <= input[i - 1] && input[i - 1] <= 'z' && 'a' <= input[i] && input[i] <= 'z')
			result = 2;
		if ('a' <= input[i - 1] && input[i - 1] <= 'z' && input[i] == '(')
			result = 2;

	}

	if (result == 2) {
		printf("error\n");
	}
	else {
		func();

		if (result == 0)
			printf("proper\n");
		else if (result == 1)
			printf("improper\n");
	}
}