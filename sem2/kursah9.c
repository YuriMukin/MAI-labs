#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(a, b) ((a > b) - (a < b))

typedef struct 
{
    char keychar;
}t_intchar_key;

typedef struct 
{
    char verse[100];
} t_input;

typedef struct 
{
    t_intchar_key key;
    int index;
} t_table;

void reading(t_table *intab, t_input *inp, int *count)
{
    char filename[15];
    printf(" enter input file name: ");
    scanf ("%s",filename);
    FILE *f=fopen(filename, "rb");
    *count=0;
    while (fscanf(f, " %c %s", &intab[*count].key.keychar, inp[*count].verse) != EOF)
    {
        intab[*count].index = *count;
        ++(*count);
    }
    fclose(f);
}

int bubble_sort(int count, t_table *stabe) 
{
    t_table tmp;
    for(int i = 0 ; i < count - 1; i++) 
    { 
       for(int j = 0 ; j < count - i - 1 ; j++) 
       {  
           if(stabe[j].key.keychar > stabe[j+1].key.keychar)
            {           
              tmp = stabe[j];
              stabe[j] = stabe[j+1] ;
              stabe[j+1] = tmp; 
           }
        }
    }
    return(1);
}

int compare_keys(const t_intchar_key *key1, const t_intchar_key *key2)
{
  int cmp;
  if ((cmp = COMPARE(key1->keychar, key2->keychar)) != 0)
    return cmp;
  return 0;
}

int binarsurch(char a, const t_table *table, int n)
{
    int low = 0, high = n - 1;
    const t_intchar_key  key ={ a };

    while (low <= high)
    {
        int middle = (low + high) / 2;
        int cmp = compare_keys(&key, &table[middle].key);
        if (cmp < 0)
            high = middle - 1;
        else if (cmp > 0)
            low = middle + 1;
        else 
            return middle;
    }
    return -1;
}

int find_by_key(int sor, t_table *table, t_input *input, int count, int *bi)
{
    char k;
    if (sor==1)
    {
        printf("\n enter key: ");
        scanf (" %c", &k);
        *bi=binarsurch(k, table, count);
        if (*bi==-1)
            printf("\n this item does not exist\n");
        else
            printf("|  %c  |%s\n", table[*bi].key.keychar, input[table[*bi].index].verse);
    }
    else 
        printf(" sort the table first \n");
}

void swap_table(t_table *x, t_table *y)
{
    t_table z = *x;
    *x = *y;
    *y = z;
}

void reverse_table(t_table *table, int count_lines)
{
    for (int i = 0; i < count_lines / 2; ++i)
        swap_table(&table[i], &table[count_lines - i - 1]);
}

void random_keys(t_table *table, int count_lines)
{
    for (int i = 0; i < count_lines; ++i)
    {
        int rand_key = rand() % count_lines;
        swap_table(&table[i], &table[rand_key]);
    }
}

void print_table(int count_lines, t_table *table, t_input *input)
{
    printf("\n|key| Verse\n");
    for (int i = 0; i < count_lines; i++)
            printf("| %c |%s\n", table[i].key.keychar, input[table[i].index].verse);
    printf("\n");
}

int menu()
{
	{
		int sw = 0;
		while (sw < 1 || sw > 8)
		{
			printf("\n 1. reallok table \n 2. sort table \n 3. find by key \n 4. reverse table \n 5. random key \n 6. print table \n 7. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw>8) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}

}

int main()
{
    t_table table[12];
    t_input tin[12];
    int lincount=0, act=1, sor=0, bi=0;
    while (act != 7)
        switch(act)
        {
        case 1: reading (table, tin, &lincount); act=8; break;
        case 2: sor=bubble_sort(lincount, table); act=8; break;
        case 3: find_by_key(sor, table, tin, lincount, &bi); act=8; break;
        case 4: reverse_table(table, lincount); act=8; break;
        case 5: random_keys(table, lincount); act=8; break;
        case 6: print_table(lincount, table, tin); act=8; break;
        case 8: act=menu(); break;
        }
}