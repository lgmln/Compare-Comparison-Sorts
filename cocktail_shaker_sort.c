#include "cocktail_shaker_sort.h"
void cocktail_shaker_sort(char* s, int sz, tpifpcii order_is_broken, tpifpcii swap_items)
{
    int i, j, lower, upper, last_swap;

    lower = 0;
    upper = sz-1;

    while (lower < upper)
    {
        last_swap = upper;
        for(i=lower; (j=i+1) <= upper; i++)
        {
            if(order_is_broken(s, i, j))
            {
                swap_items(s, i, j);
                last_swap=i;
            }
        }
        if (upper != last_swap)
            upper = last_swap;
        else
            upper--;

        last_swap = lower;
        for(i=upper; (j=i-1) >= lower; i--)
        {
            if(order_is_broken(s, j, i))
            {
                swap_items(s, j, i);
                last_swap=i;
            }
        }
        if (lower != last_swap)
            lower = last_swap;
        else
            lower++;
    }
}
