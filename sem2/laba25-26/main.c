#include <stdio.h>
#include "list.h"

int main()
{
    printf (" enter max size of list: ");
    scanf ("%d", &m_size);
    elem l[m_size];
    int act=8, lcount=0, ferel=1;
    while (act != 7)
		switch (act)
		{
		case 1: add_elem_base(l, &lcount, &ferel); act = 8; break;
		case 2: delet_elem(l, &lcount, &ferel); act = 8; break;
		case 3: printf("\n"); list_out(l, ferel); printf("\n"); act = 8; break;
		case 4: printf("\n length of the list is equal to: %d\n", plint_langht(l, ferel)); act = 8; break;
		case 5: sort(l, &ferel, &lcount); act = 8; break;
        case 6: serch(l, ferel); act=8; break;
		case 8: act = menu(); break;
		}
}