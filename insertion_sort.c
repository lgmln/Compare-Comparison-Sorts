#include "insertion_sort.h"
void insertion_sort(char* s, int sz, tpifpcii order_is_broken, tpifpcii swap_items)
{
    int i, j, k;

    for (k=1; k<sz; k++)
    {
        for (i=k-1; i>=0; i--)
        {
            if (order_is_broken(s, i, j=i+1))
                swap_items(s, i, j);
            else
                break;
        }
    }
}
