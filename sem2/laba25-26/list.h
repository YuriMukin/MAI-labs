#ifndef list_h
#define list_h
#include <stdio.h>
int m_size;

typedef struct list
{
    int info;
    int ind;
}elem;

void delet_elem(elem *arr, int *count, int *ferel);
int plint_langht(elem *l, int i);
void list_out(elem *arr, int i);
void add_elem_base(elem *arr, int *lcount, int *ferel);
void sort(elem *l, int *ferel, int *lcount);
void serch(elem *l, int fer);
int menu();
#endif