#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void phase_1(char *input)
{
	int res;

	res = strcmp(input, "Public speaking is very easy.");
	if (res != 0)
		explode_bomb();
	return;
}

void phase_2(char *input)
{
	int numbers[6];
	read_six_numbers(input, numbers);

	if (numbers[0] != 1)
		explode_bomb();

	for (int i = 1; i < 6; i++)
		if (numbers[i] != numbers[i - 1] * (i + 1))
			explode_bomb();
}

void phase_3(char *input)
{
	int input_case;
	char input_char;
	int input_num;
	char expected_char;
	int expected_num;

	if (sscanf(input, "%d %c %d", (int *)&input_case, &input_char, &input_num) < 3)
		explode_bomb();

	switch (input_case)
	{
	case 0:
		expected_char = 'q';
		expected_num = 777;
		break;
	case 1:
		expected_char = 'b';
		expected_num = 214;
		break;
	case 2:
		expected_char = 'b';
		expected_num = 755;
		break;
	case 3:
		expected_char = 'k';
		expected_num = 251;
		break;
	case 4:
		expected_char = 'o';
		expected_num = 160;
		break;
	case 5:
		expected_char = 't';
		expected_num = 458;
		break;
	case 6:
		expected_char = 'v';
		expected_num = 780;
		break;
	case 7:
		expected_char = 'b';
		expected_num = 524;
		break;
	default:
		explode_bomb();
	}
	if (expected_num != input_num || expected_char != input_char)
		explode_bomb();
	return;
}

int fibonacci(int input)
{
	if (input <= 1)
		return 1;
	else
		return fibonacci(input - 1) + fibonacci(input - 2);
}

void phase_4(char *input)
{
	int num;

	if (sscanf(input, "%d", &num) != 1 || num <= 0)
		explode_bomb();

	if (fibonacci(num) != 55)
		explode_bomb();
}

void phase_5(char *input)
{
	if (strlen(input) != 6)
		explode_bomb();

	char transformed[7] = {0};
	char lookup_table[] = "isrveawhobpnutfg";

	for (int i = 0; i < 6; i++)
	{
		char character = input[i];
		transformed[i] = lookup_table[character & 0xf];
	}

	if (strcmp(transformed, "giants") != 0)
		explode_bomb();
}

const Node node1 = {253, 1, &node2}, node2 = {725, 2, &node3}, node3 = {301, 3, &node4},
		   node4 = {997, 4, &node5}, node5 = {212, 5, &node6}, node6 = {432, 6, NULL};

typedef struct Node
{
	int value;
	int index;
	struct Node *next;
} Node;

void phase_6(char *inputString)
{
	int inputNumbers[6];
	Node *nodeArray[6];
	Node *firstNode;
	Node *currentNode;
	Node *nextNode;

	read_six_numbers(inputString, inputNumbers);
	for (int i = 0; i < 6; i++)
	{
		if (inputNumbers[i] > 6)
			explode_bomb();

		for (int j = i + 1; j < 6; j++)
			if (inputNumbers[i] == inputNumbers[j])
				explode_bomb();
	}

	for (int i = 0; i < 6; i++)
	{
		currentNode = &node1;
		for (int j = 1; j < inputNumbers[i]; j++)
			currentNode = currentNode->next;
		nodeArray[i] = currentNode;
	}

	currentNode = nodeArray[0];
	firstNode = currentNode;
	for (int i = 1; i < 6; i++)
	{
		nextNode = nodeArray[i];
		currentNode->next = nextNode;
		currentNode = nextNode;
	}

	currentNode = firstNode;
	for (int i = 0; i < 5; i++)
	{
		if (currentNode->value > currentNode->next->value)
			explode_bomb();
		currentNode = currentNode->next;
	}
	return;
}

int num_input_strings = 0;
char input_strings[1600];

typedef struct nNode
{
	int value;
	struct nNode *left;
	struct nNode *right;
} nNode;

const nNode n1 = {36, &n21, &n22},
			n21 = {8, &n31, &n32}, n22 = {50, &n33, &n34},
			n31 = {6, &n41, &n42}, n32 = {22, &n43, &n44}, n33 = {45, &n45, &n46}, n34 = {107, &n47, &n48},
			n41 = {1, NULL, NULL}, n42 = {15, NULL, NULL}, n43 = {20, NULL, NULL}, n44 = {35, NULL, NULL}, n45 = {40, NULL, NULL}, n46 = {47, NULL, NULL}, n47 = {99, NULL, NULL}, n48 = {1001, NULL, NULL};

int fun7(nNode *n, int input)
{
	if (n == NULL)
		return -1;

	if (input < n->value)
		return 2 * fun7(n->left, input);
	else if (input > n->value)
		return 2 * fun7(n->right, input) + 1;
	else
		return 0;
}

int secret_phase()
{
	int input = strtol(read_line(), NULL, 10);

	if (input > 1001)
		explode_bomb();

	if (fun7(&n1, input) != 7)
		explode_bomb();

	printf("Wow! You've defused the secret stage!\n");
	phase_defused();

	return 0;
}

void phase_defused(void)
{
	int scanResult;
	int numberInput;
	char inputString[80];

	if (num_input_strings == 6)
	{
		if (sscanf(input_strings + 240, "%d %s", &numberInput, inputString) == 2)
		{
			if (strcmp(inputString, "austinpowers") == 0)
			{
				printf("Curses, you\'ve found the secret phase!\n");
				printf("But finding it and solving it are quite different...\n");
				secret_phase();
			}
		}
		printf("Congratulations! You\'ve defused the bomb!\n");
	}
	return;
}

int main(int argc, char *argv[])
{
	FILE *infile;

	if (argc == 1)
		infile = stdin;
	else if (argc == 2)
	{
		infile = fopen(argv[1], "r");
		if (infile == NULL)
			printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]), exit(8);
	}
	else
		printf("Usage: %s [<input_file>]\n", argv[0]), exit(8);

	initialize_bomb();
	printf("Welcome this is my little bomb !!!! You have 6 stages with\n");
	printf("only one life good luck !! Have a nice day!\n");

	char *line = read_line();
	phase_1(line);
	phase_defused();
	printf("Phase 1 defused. How about the next one?\n");

	line = read_line();
	phase_2(line);
	phase_defused();
	printf("That\'s number 2.  Keep going!\n");

	line = read_line();
	phase_3(line);
	phase_defused();
	printf("Halfway there!\n");

	line = read_line();
	phase_4(line);
	phase_defused();
	printf("So you got that one.  Try this one.\n");

	line = read_line();
	phase_5(line);
	phase_defused();
	printf("Good work!  On to the next...\n");

	line = read_line();
	phase_6(line);
	phase_defused();
	return 0;
}