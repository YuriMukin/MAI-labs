#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct tree
{
	int val;
	struct tree * left;
	struct tree * right;
}node;

void c_tree(node **root, int val)
{
	node *tmp = malloc(sizeof(node));
	tmp->val = val;
	tmp->left = NULL;
	tmp->right = NULL;
	*root = tmp;
}

int checking(node **root, int n)
{
	int chek = 0;
	node *root2 = *root;
	while (1)
	{
		if (n == root2->val)
		{
			chek = 1; break;
		}
		if (n < root2->val)
		{
			if (root2->left == NULL)
				break;
			root2 = root2->left;
		}
		if (n > root2->val)
		{
			if (root2->right == NULL)
				break;
			root2 = root2->right;
		}
	}
	return chek;
}

void p_tree(node *root, int *nod_count, int y)
{
	if (*nod_count < 1)
		printf("\n tree is empty \n");
	else
	{
		if (root == NULL)
			return;
		p_tree(root->right, &*nod_count, y + 1);
		for (int i = 0; i < y; i++)
			printf("    ");
		printf("%d\n", root->val);
		p_tree(root->left, &*nod_count, y + 1);
	}
}

void a_nod(node **root, int val, int *nod_count)
{
	node *root2 = *root;
	node *root3 = NULL;
	node *tmp = malloc(sizeof(node));
	tmp->val = val;
	while (root2 != NULL)
	{
		root3 = root2;
		if (val < root2->val)
			root2 = root2->left;
		else
			root2 = root2->right;
	}
	tmp->left = NULL;
	tmp->right = NULL;
	if (val < root3->val)
		root3->left = tmp;
	else
		root3->right = tmp;
	(*nod_count)++;
}

void nod_add(node **root, int *nod_count)
{
	int nnv;
	printf("\n enter node value: ");
	scanf("%d", &nnv);
	if (*nod_count == 0)
	{
		c_tree(&*root, nnv);
		(*nod_count)++;
	}
	else if (checking(&*root, nnv) == 1)
		printf("\n this value is olready there \n");
	else a_nod(&*root, nnv, &*nod_count);
}

void del_node_bace(node **root,int *nod_count)
{
	int nv;
	if (*nod_count < 2)
		printf("\n tree cannot be deleted!\n");
	else
	{
		printf("\n enter node value: ");
		scanf("%d", &nv);
		if (checking(&*root, nv) == 1) 
		{
			--(*nod_count);
			del_node(&*root, nv);
		}
		else
		{
			printf("\n tree does not contain such a value \n");
		}
	}
}

void del_node(node **root, int val) 
{
	node *l = *root;
	while (l->val != val) 
	{
		if (val < l->val)
			l = l->left;
		else l = l->right;
	}
	if (l->left == NULL && l->right == NULL) 
	{
		node *root2 = *root;
		node *root3 = *root;
		while (1) 
		{
			if (root2->left != NULL)
				if (root2->left->val == val)
					break;
			if (root2->right != NULL)
				if (root2->right->val == val)
					break;
			if (val < root2->val)
				root2 = root2->left;
			else root2 = root2->right;
			root3 = root2;
		}
		if (l == root3->right)
			root3->right = NULL;
		else root3->left = NULL;
		free(l);
	}
	if (l->left == NULL && l->right != NULL) 
	{
		node *root2 = *root;
		node *root3 = *root;
		while (1) 
		{
			if (root2->left != NULL)
				if (root2->left->val == val)
					break;
			if (root2->right != NULL)
				if (root2->right->val == val)
					break;
			if (val < root2->val)
				root2 = root2->left;
			else root2 = root2->right;
			root3 = root2;
		}
		if (l == root3->right) root3->right = l->right;
		else root3->left = l->right;
		free(l);
	}
	if (l->left != NULL && l->right == NULL) 
	{
		node *root2 = *root;
		node *root3 = *root;
		while (1) 
		{
			if (root2->left != NULL)
				if (root2->left->val == val)
					break;
			if (root2->right != NULL)
				if (root2->right->val == val)
					break;
			if (val < root2->val)
				root2 = root2->left;
			else root2 = root2->right;
			root3 = root2;
		}
		if (l == root3->right) root3->right = l->left;
		else root3->left = l->left;
		free(l);
	}
	if (l->left != NULL && l->right != NULL) 
	{
		node *root2 = l;
		while (1) 
		{
			if (root2->right == NULL) 
			{
				root2 = root2->left;
				while (root2->right != NULL)
					root2 = root2->right;
			}
			if (root2->right != NULL) 
			{
				root2 = root2->right;
				while (root2->left != NULL)
					root2 = root2->left;
			}
			break;
		}
		node *root3 = *root;
		node *root4 = *root;
		while (1) 
		{
			if (root3->left != NULL)
				if (root3->left->val == root2->val)
					break;
			if (root3->right != NULL)
				if (root3->right->val == root2->val)
					break;
			if (val < root3->val)
				root3 = root3->left;
			else root3 = root3->right;
			root4 = root3;
		}
		l->val = root2->val;
		if (root4->left->val == root2->val) 
		{
			if (root4->left->left != NULL)
				root4->left = root4->left->right;
			else if (root4->left->right != NULL)
				root4->left = root4->left->right;
			else root4->left = NULL;
		}
		else 
		{
			if (root4->left->right != NULL)
				root4->left = root4->left->right;
			else if (root4->right->right != NULL)
				root4->right = root4->right->right;
			else root4->right = NULL;
		}
		free(root2);
	}
}

void cl_val_bace(node *root, int *nod_count)
{
	int ll = 0, hl = 0, k = 0;
	printf("\n enter interval: ");
	scanf("%d%d", &ll, &hl);
	cl_val(root, &*nod_count, 1, ll, hl, &k);
	printf(" total: %d\n", k);
}

void cl_val(node *root, int *nod_count, int y, int ll, int hl, int *k)
{
	if (*nod_count < 1)
		printf("\n tree is empty \n");
	else
	{
		if (root == NULL)
			return;
		cl_val(root->right, &*nod_count, y + 1, ll, hl, &*k);
		if ((root->right == NULL) && (root->left == NULL) && (root->val <= hl) && (root->val >= ll)) 
		{
			printf(" %d,", root->val);
			(*k)++;
		}
		cl_val(root->left, &*nod_count, y + 1, ll, hl, &*k);
	}
}

void menu(int *act)
{
	int sw = 0;
	while (sw < 1 || sw > 6)
	{
		printf("\n 1. add node \n 2. print tree \n 3. delete node \n 4. chek leaves value \n 5. end work \n choos action : ");
		scanf("%d", &sw);
		if (sw < 1 || sw>5) printf("\n this action dosn'n exist \n");
	}
	*act = sw;
}

int main()
{
	node *root;
	int act = 6, nod_count;
	nod_count = 0;
	while (act != 5)
		switch (act)
		{
		case 1: nod_add(&root, &nod_count); act = 6; break;
		case 2: p_tree(root, &nod_count, 1); act = 6; break;
		case 3: del_node_bace(&root, &nod_count);  act = 6; break;
		case 4: cl_val_bace(root, &nod_count); act = 6; break;
		case 6: menu(&act); break;
		}
}