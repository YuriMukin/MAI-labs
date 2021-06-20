#include <stdio.h>
int m_size;

typedef struct list
{
    int info;
    int ind;
}elem;

void add_elem(elem *arr, int ins, int count, int pos, int *ferel)
{
    int np=*ferel;
    short int a=2;
    if (count == 1)
    {
        arr[count].info=ins;
        arr[count].ind=-1;
    }
    else
    {
        for (int i=1; i<pos; i++)
            if (arr[np].ind!=-1)
            {
                a=1;
                np=arr[np].ind;
            }
            else
            {
                a=0;
                break;
            }
        if (a==0)
        {
            arr[count].info=ins;
            arr[count].ind=-1;
            arr[np].ind=count;
        }
        else if(a==2)
        {
            arr[count].info=ins;
            arr[count].ind=*ferel;
            *ferel=count;
        }
        else if(a==1)
        {
            arr[count].info=ins;
            arr[count].ind=arr[np-1].ind;
            arr[np-1].ind=count;
        }
    }
}

int plint_langht(elem *l, int i)
{
    int lan=0;
    while(l[i].ind!=-1)
    {
        i=l[i].ind;
        lan++;
    }
    return(lan+1);
}

void garbeg_coll(elem *l, int *ferel, int *count)
{
    int k=*ferel, i=1;
    elem q[m_size];
    while (k!=-1)
    {
        q[i].info=l[k].info;
        q[i].ind=i+1;
        k=l[k].ind;
        i++;
    }
    q[i-1].ind=-1;
    *count=i-1;
    *ferel=1;
    for (int j=1; j<=*count; j++)
        l[j]=q[j];
}

void list_out(elem *arr, int i)
{
    while (i!=-1)
    {
        printf(" %d", arr[i].info);
        i=arr[i].ind;
    }
}

void delet_elem(elem *arr, int *count, int *ferel)
{
    int pos, a=2;
    int np=*ferel;
    printf ("\n enter value and position: ");
    scanf ("%d", &pos);
    if (pos==2)
        a=1;
    for (int i=1; i<pos-1; i++)
        if (arr[arr[np].ind].ind!=-1)
        {
            a=1;
            np=arr[np].ind;
        }
        else
        {
            a=0;
            break;
        }
    if (a==2)
    {
        *ferel=arr[*ferel].ind;
    }
    if (a==0)
    {
        arr[np].ind=-1;
    }
    if (a==1)
    {
        arr[np].ind=arr[arr[np].ind].ind;
    }
}

void add_elem_base(elem *arr, int *lcount, int *ferel)
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

void swap_two(elem *arr, int pos1, int pos2)
{
    elem t=arr[pos2];
    arr[pos2].info=arr[pos1].info;
    arr[pos1].info=t.info;
}

void swap(elem *arr, int *count, int *ferel)
{
    garbeg_coll(arr, &*ferel, &*count);
    int langht=*count;
    if (langht % 2 == 0)
		for (int i = langht / 2; i >= 1; i--)
			swap_two(arr, i, i + langht / 2);
	else
    {
		for (int i = langht / 2; i >= 1; i--)
		    swap_two(arr, i, 1 + i + langht / 2);
        for (int i=(langht / 2)+1; i<langht; i++)
            swap_two(arr, i, i+1);
    }
}

int menu() //меню программы
{
	{
		int sw = 0;
		while (sw < 1 || sw > 7)
		{
			printf("\n 1. add element \n 2. delete element \n 3. print list \n 4. print langht \n 5. swop \n 6. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw>7) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}
}

int main()
{
    printf (" enter max size of list: ");
    scanf ("%d", &m_size);
    elem l[m_size];
    int act=7, lcount=0, ferel=1;
    while (act != 6)
		switch (act)
		{
		case 1: add_elem_base(l, &lcount, &ferel); act = 7; break;
		case 2: delet_elem(l, &lcount, &ferel); act = 7; break;
		case 3: printf("\n"); list_out(l, ferel); printf("\n"); act = 7; break;
		case 4: printf("\n length of the list is equal to: %d\n",plint_langht(l, ferel)); act = 7; break;
		case 5: swap(l, &lcount, &ferel); act = 7; break;
		case 7: act = menu(); break;
		}
}