#include <stdio.h>
int m_size;

typedef struct list
{
    int info;
    int ind;
}elem;

int next_el(elem *l, int k)//индекс следующего элемента
{
    k=l[k].ind;
    return (k);
}

int next_el_value(elem *l, int k)//значение следующего лемента
{
    k=l[next_el(l,k)].info;
    return (k);
}

void el_ind_enter(elem *l, int k, int inf)//заменить индекс элемента на который ссылается элемент
{
    l[k].ind = inf;
}

int el_value(elem *l, int k)//вывести значение элемента
{
    k=l[k].info;
    return (k);
}

void el_value_enter(elem *l, int k, int inf)//заменить значение элемента
{
    l[k].info = inf;
}

int plint_langht(elem *l, int i)//вывести длинну списка
{
    int lan=0;
    while(next_el(l, i)!=-1)
    {
        i=next_el(l, i);
        lan++;
    }
    return(lan+1);
}

void add_elem(elem *arr, int ins, int count, int pos, int *ferel)//добавление элемента
{
    int np=*ferel, prev;
    short int a=2;
    if (count == 1)
    {
        el_value_enter(arr, count, ins);
        el_ind_enter(arr, count, -1);
    }
    else
    {
        for (int i=1; i<pos; i++)
            if (next_el(arr, np)!=-1)
            {
                a=1;
                prev=np;
                np=next_el(arr, np);
            }
            else
            {
                a=0;
                break;
            }
        if (a==0)
        {
            el_value_enter(arr, count, ins);
            el_ind_enter(arr, count, -1);
            el_ind_enter(arr, np, count);
        }
        else if(a==2)
        {
            el_value_enter(arr, count, ins);
            el_ind_enter(arr, count, *ferel);
            *ferel=count;
        }
        else if(a==1)
        {
            el_value_enter(arr, count, ins);
            el_ind_enter(arr, count, next_el(arr,prev));
            el_ind_enter(arr, prev, count);
        }
    }
}

void garbeg_coll(elem *l, int *ferel, int *count)//удаление дырок
{
    int k=*ferel, i=1;
    elem q[m_size];
    while (k!=-1)
    {
        el_value_enter(q, i, el_value(l, k));
        el_ind_enter(q, i, i+1);
        k=next_el(l, k);
        i++;
    }
    el_ind_enter(q, i-1, -1);
    *count=i-1;
    *ferel=1;
    for (int j=1; j<=*count; j++)
        l[j]=q[j];
}

void list_out(elem *arr, int i)//печать списка
{
    while (i!=-1)
    {
        printf(" %d", el_value(arr, i));
        i=next_el(arr, i);
    }
}

void delet_elem(elem *arr, int *count, int *ferel)//удалить элемент
{
    int pos, a=2;
    int np=*ferel;
    printf ("\n enter value and position: ");
    scanf ("%d", &pos);
    if (pos==2)
        a=1;
    for (int i=1; i<pos-1; i++)
        if (next_el(arr, next_el(arr,np))!=-1)
        {
            a=1;
            np=next_el(arr, np);
        }
        else
        {
            a=0;
            break;
        }
    if (a==2)
    {
        *ferel=next_el(arr, *ferel);
    }
    if (a==0)
    {
        el_ind_enter(arr, np, -1);
    }
    if (a==1)
    {
        el_ind_enter(arr, np, next_el(arr, next_el(arr,np)));
    }
}

void add_elem_base(elem *arr, int *lcount, int *ferel)//база добавления элемента
{
    int inf, pos;
    char chek;
    printf ("\n enter value and position: ");
    scanf ("%d %d", &inf, &pos);
    (*lcount)++;
    if (*lcount>m_size)
    {
        printf("\n array overfull, check for holes and get rid of them?(Y/N): ");
        scanf (" %c",&chek);
        if (chek=='Y') 
        {
            garbeg_coll(arr, &*ferel, &*lcount);
            (*lcount)++;     
            if (*lcount>m_size)
                printf("\n array overfull and does not contain holes!");
            else{
                add_elem(arr, inf, *lcount, pos, &*ferel);
            }
        }
        else
            printf("\n in this case action is impossible!");
    }
    else
        add_elem(arr, inf, *lcount, pos, &*ferel);
}

void swap_two(elem *arr, int pos1, int pos2)//переставить 2 элемента
{
    int t=el_value(arr, pos2);
    el_value_enter(arr, pos2, el_value(arr, pos1));
    el_value_enter(arr, pos1, t);
}

void sort(elem *l, int *ferel, int *lcount)
{
    garbeg_coll(l, &*ferel, &*lcount);
    int n = plint_langht(l, *ferel);
    for(int i = 1; i < n+1; i++) 
    { 
        for(int j = 1; j < 1+n-i; j++) 
        {  
            if(el_value(l, j) > el_value(l, j+1))//l[j].info > l[j+1].info)
                swap_two(l, j, j+1);
        }
    }
}

void serch(elem *l, int fer)
{
    int f=fer;
    while (next_el(l, f)!=-1)//l[l[f].ind].ind!=-1)
    {
        if (el_value(l, f)>next_el_value(l, f))//l[f].info>l[l[f].ind].info)
        {
            printf("\n were found and rearranged: %d, %d\n", el_value(l, f), next_el_value(l, f));
            swap_two(l, f, l[f].ind);
            break;
        }
        f=next_el(l, f);//l[f].ind;
    }
}

int menu()
{
	{
		int sw = 0;
		while (sw < 1 || sw > 8)
		{
			printf("\n 1. add element \n 2. delete element \n 3. print list \n 4. print langht \n 5. sort \n 6. swap two if f1 > f2 \n 7. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw > 8) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}
}