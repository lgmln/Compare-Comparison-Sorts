#include "selection_sort.h"
void selection_sort(char* s, int sz, tpifpcii order_is_broken, tpifpcii swap_items)
{
    int i, j;

    for (sz--; sz!=0; sz--)
    {
        i=sz;
        for (j=sz-1; j>=0; j--)
        {
            if (order_is_broken(s, j, i))
                i = j;
        }
        if (i!=sz)
            swap_items(s, i, sz);
    }
}
