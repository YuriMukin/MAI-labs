#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define is_operator(c) (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
#define is_ident(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z'))

struct stack_item_string 
{
	char data[40];
	struct stack_item_string* prev;
};

typedef struct
{
	struct stack_item_string* top;
	int size;
}stack_string;

void create_stack_string(stack_string *s) 
{
	s->size = 0;
	s->top = 0;
}

bool empty_stack_string(stack_string* s) 
{
	return s->top == 0;
}

int size_stack_string(stack_string* s) 
{
	return s->size;
}

bool push_in_stack_string(stack_string* s, char* data) 
{
	struct stack_item_string* tmp = malloc(sizeof(struct stack_item_string));
	if (!tmp)
		return false;
	strcpy(tmp->data, data);
	tmp->prev = s->top;
	s->top = tmp;
	s->size++;
	return true;
}

bool pop_from_stack_string(stack_string* s) 
{
	if (!s->size)
		return false;
	struct stack_item_string* tmp = s->top;
	s->top = s->top->prev;
	s->size--;
	free(tmp);
	return true;
}

char* top_stack_string(stack_string* s) 
{
	if (s->top)
		return s->top->data;
}

void destroy_stack_string(stack_string* s) 
{
	while (s->top)
	{
		struct stack_item_string* tmp = s->top;
		s->top = s->top->prev;
		free(tmp);
	}
	s->top = 0;
	s->size = 0;
}

void reverse_stack_string(stack_string *s)
{
	stack_string tmp1;
	stack_string tmp2;
	create_stack_string(&tmp1);
	create_stack_string(&tmp2);
	while (!empty_stack_string(s))
	{
		push_in_stack_string(&tmp1, top_stack_string(s));
		pop_from_stack_string(s);
	}
	while (!empty_stack_string(&tmp1))
	{
		push_in_stack_string(&tmp2, top_stack_string(&tmp1));
		pop_from_stack_string(&tmp1);
	}
	while (!empty_stack_string(&tmp2))
	{
		push_in_stack_string(s, top_stack_string(&tmp2));
		pop_from_stack_string(&tmp2);
	}
	destroy_stack_string(&tmp1);
	destroy_stack_string(&tmp2);
}

void read_frac(char *inp, char *outp, char* *argv, int *si)
{
	char c;
	FILE *in;
	in = fopen(argv[1], "r");
	while ((c = fgetc(in)) != EOF)
	{
		(*si)++;
		*inp = realloc(inp, *si);
		*outp = realloc(outp, *si);
	}
	rewind(in);
	fscanf(in, "%s", inp);
	fclose(in);
	printf("\n you enter: %s\n", inp);
}

int op_preced(const char c)
{
	switch (c)
	{
	case '^':
		return 4;

	case '*':
	case '/':
		return 3;

	case '+':
	case '-':
		return 2;
	}
	return 0;
}

bool op_left_assoc(const char c)
{
	switch (c)
	{
	case '*':
	case '/':
	case '+':
	case '-':
		return true;
	case '^':
		return false;
	}
	return false;
}

unsigned int op_arg_count(const char c)
{
	switch (c)
	{
	case '*':
	case '/':
	case '%':
	case '+':
	case '-':
	case '=':
		return 2;
	case '!':
		return 1;

	default:
		return c - 'A';
	}
	return 0;
}
bool shunting_yard(const char *input, char *output, int si)
{
	const char *strpos = input, *strend = input + strlen(input);
	char c, stack[si], sc, *outpos = output;
	unsigned int sl = 0;
	while (strpos < strend)
	{
		c = *strpos;
		if (c != ' ')
		{
			if (is_ident(c))
			{
				*outpos = c; ++outpos;
			}
			else if (is_operator(c))
			{
				*outpos = ' '; ++outpos;
				while (sl > 0)
				{
					sc = stack[sl - 1];
					if (is_operator(sc) &&
						((op_left_assoc(c) && (op_preced(c) <= op_preced(sc))) ||
						(!op_left_assoc(c) && (op_preced(c) < op_preced(sc)))))
					{
						*outpos = sc; ++outpos;
						sl--;
					}
					else
					{
						break;
					}
				}
				stack[sl] = c;
				++sl;
			}
			else if (c == '(')
			{
				stack[sl] = c;
				++sl;
			}
			else if (c == ')')
			{
				bool pe = false;
				while (sl > 0)
				{
					sc = stack[sl - 1];
					if (sc == '(')
					{
						pe = true;
						break;
					}
					else
					{
						*outpos = sc; ++outpos;
						sl--;
					}
				}
				if (!pe)
				{
					printf("Error: parentheses mismatched\n");
					return false;
				}
				sl--;
			}
			else
			{
				printf("Unknown token %c\n", c);
				return false;
			}
		}
		++strpos;
	}
	while (sl > 0)
	{
		sc = stack[sl - 1];
		if (sc == '(' || sc == ')')
		{
			printf("Error: parentheses mismatched\n");
			return false;
		}
		*outpos = sc; ++outpos;
		--sl;
	}

	*outpos = 0;
	return true;
}

typedef struct tree 
{
	char key[40];
	struct tree* left;
	struct tree* right;
}node;

struct stack_item_node 
{
	node* data;
	struct stack_item_node* prev;
};

typedef struct
{
	struct stack_item_node* top;
	int size;
}stack_node;

void create_stack_node(stack_node *s) 
{
	s->size = 0;
	s->top = NULL;
}

bool empty_stack_node(stack_node *s) 
{
	return s->top == NULL;
}

int size_stack_node(stack_node *s) 
{
	return s->size;
}

bool push_in_stack_node(stack_node* s, node *data) 
{
	struct stack_item_node* tmp = malloc(sizeof(struct stack_item_node));
	if (!tmp)
		return false;
	tmp->data = data;
	tmp->prev = s->top;
	s->top = tmp;
	s->size++;
	return true;
}
bool pop_from_stack_node(stack_node* s) 
{
	if (!s->size)
		return false;
	struct stack_item_node* tmp = s->top;
	s->top = s->top->prev;
	s->size--;
	free(tmp);
	return true;
}
node* top_stack_node(stack_node *s) 
{
	if (s->top)
		return s->top->data;
	else
		return NULL;
}
void destroy_stack_node(stack_node* s) 
{
	while (s->top)
	{
		struct stack_item_node* tmp = s->top;
		s->top = s->top->prev;
		free(tmp);
	}
	s->top = NULL;
	s->size = 0;
}
node* string_to_node(char *s) 
{
	node* tmp = (node*)malloc(sizeof(node));
	strcpy(tmp->key, s);
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
node* string_to_tree(stack_string *input) 
{
	stack_node tree;
	node* tmp = (node*)malloc(sizeof(node));
	create_stack_node(&tree);
	while (!empty_stack_string(input))
	{
		if (atoi(top_stack_string(input)) != 0)
			push_in_stack_node(&tree, string_to_node(top_stack_string(input)));
		else
		{
			tmp = string_to_node(top_stack_string(input));
			tmp->right = top_stack_node(&tree);
			pop_from_stack_node(&tree);
			tmp->left = top_stack_node(&tree);
			pop_from_stack_node(&tree);
			push_in_stack_node(&tree, tmp);
		}
		pop_from_stack_string(input);
	}
	tmp = top_stack_node(&tree);
	destroy_stack_node(&tree);
	return tmp;
}

void tree_print(node* tree, int y) 
{
	if (tree)
	{
		tree_print(tree->right, y + 1);
		for (int i = 0; i < y; i++)
			printf("    ");
		printf("%s\n", tree->key);
		tree_print(tree->left, y + 1);
	}
}

void menu(int *act)
{
	int sw = 0;
	while (sw < 1 || sw > 6)
	{
		printf("\n 1. read input \n 2. convert from infix to postfix \n 3. rewrite to tree \n 4. perform the conversion \n 5. end work \n choos action : ");
		scanf("%d", &sw);
		if (sw < 1 || sw>6) printf("\n this action dosn'n exist \n");
	}
	*act = sw;
}

void len_to_st(char *output, stack_string *s)
{
	char tmp[40];
	int i = 0;
	tmp[0] = 0;
	while (output[i] != '\0') 
	{
		if (is_ident(output[i])) 
		{
			sprintf(tmp, "%s%c", tmp, output[i]);
		}
		else if (is_operator(output[i]))
		{
			if (atoi(tmp) != 0)
				push_in_stack_string(&*s, tmp);
			tmp[0] = 0;
			sprintf(tmp, "%s%c", tmp, output[i]);
			push_in_stack_string(&*s, tmp);
			tmp[0] = 0;
		}
		else if (output[i] = ' ' && atoi(tmp) != 0)
		{
			push_in_stack_string(&*s, tmp);
			tmp[0] = 0;
		}
		i++;
	}
}

void inf_to_post(char *input, char *output, int si, stack_string *s)
{
	if (shunting_yard(input, output, si))
	{
		printf("\n postfix form: %s\n", output);
		len_to_st(output, s);
		reverse_stack_string(s);
	}
}

void simplific(node *tree, int *count)
{
	if (tree == NULL)
		return;
		if (strcmp(tree->key, "/") == 0 && strcmp(tree->right->key, "/") == 0)
		{
			printf("yes\n");
			node* tmp = (node*)malloc(sizeof(node));
			tmp->left=tree->left;
			tmp->key[0]='*';
			tmp->right=tree->right->right;
			tree->left=tmp;
			tree->right=tree->right->left;
		}
	simplific(tree->right, count);
}


int pr_int(char c)
{
	switch (c)
	{
	case '-': case '+': return 1;
	case '*': case '/': case '^': return 2;
	}
}

void print_infix(node* tree, int priority_node)
{
	if (priority_node == 2)
		printf("(");
	if (tree->left)
	{
		if (!tree->left->left && !tree->left->right)
			print_infix(tree->left, 1);
		else
			print_infix(tree->left, pr_int(tree->key[0]));
	}
	printf("%s", tree->key);
	if (tree->right)
	{
		if (!tree->right->left && !tree->right->right)
			print_infix(tree->right, 1);
		else
			print_infix(tree->right, pr_int(tree->key[0]));
	}
	if (priority_node == 2)
		printf(")");
}

int main(int argc, char* argv[])
{
	int act = 1, si = 1, count = 0;
	char *inp = malloc(si), *outp = malloc(si);
	node* tree = (node*)malloc(sizeof(node));
	stack_string input;
	create_stack_string (&input);
	while (act != 5)
		switch (act)
		{
		case 1: read_frac(inp, outp, argv, &si); act = 6; break;
		case 2: inf_to_post(inp, outp, si, &input); act = 6; break;
		case 3: tree = string_to_tree(&input); destroy_stack_string(&input); tree_print(tree, 0); act = 6; break;
		case 4: simplific(tree, &count); tree_print(tree, 0); printf("\n"); print_infix(tree, 1); act = 6; break;
		case 6: menu(&act); break;
		}
}