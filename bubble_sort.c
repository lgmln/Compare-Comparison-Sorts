#include "bubble_sort.h"
void bubble_sort(char* s, int sz, tpifpcii order_is_broken, tpifpcii swap_items)
{
    int i, j, swap_num;

    while (sz > 1)
    {
        swap_num=0;
        for (i=0; (j=i+1) < sz; i++)
        {
            if (order_is_broken(s, i, j))
            {
                swap_items(s, i, j);
                swap_num++;
            }
        }
        if (!swap_num) return;
        sz--;
    }
}
