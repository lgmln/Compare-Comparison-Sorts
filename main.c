#include <stdio.h>
#include <mem.h>

#define LINE_TO_SORT "sample text"

#include "tpifpcii.h"

#include "bubble_sort.h"
#include "cocktail_shaker_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "comb_sort.h"

typedef void (*tpf_sort)(char*, int, tpifpcii, tpifpcii);

#define ALG_LIST\
    ALG(bubble_sort)\
    ALG(cocktail_shaker_sort)\
    ALG(insertion_sort)\
    ALG(selection_sort)\
    ALG(comb_sort)\

#define ALG(alg) alg_id_##alg,
enum ALG_IDS
{
    ALG_LIST
};
#undef ALG

struct ALG_INFO
{
    const char*    name;
    const tpf_sort pf;
};

#define ALG(alg) {#alg, alg},
struct ALG_INFO alg_infos[] =
{
    ALG_LIST
};
#undef ALG

const unsigned int alg_num = sizeof(alg_infos)/sizeof(struct ALG_INFO);

int cmp = 0;
int swp = 0;
int alg = 0;
int reverse_sort = 0;
int show_cmp = 1;
int show_swp = 1;

#define SWAP(a,b) a^=b; b^=a; a^=b;

int order_is_broken(char* s, int i, int j)
{
    printf("%s\n", s);
    if (i==j)
    {
        printf ("hm... i==j ?\n");
        return 0;
    }
    cmp++;
    if (reverse_sort? s[i] < s[j]: s[i] > s[j])
    {
        printf("%*c%*c\n", i+1, '#', j-i, '#');
        return 1;
    }
    printf("%*c%*c\n", i+1, '|', j-i, '|');
    return 0;
}

int swap_items(char* s, int i, int j)
{
    printf("%s\n", s);
    printf("%*c%*c\n", i+1, '>', j-i, '<');
    SWAP(s[i], s[j]);
    swp++;
    return 0;
}

int order_is_broken_silent(char* s, int i, int j)
{
    cmp++;
    if (reverse_sort? s[i] < s[j]: s[i] > s[j])
    {
        return 1;
    }
    return 0;
}

int swap_items_silent(char* s, int i, int j)
{
    SWAP(s[i], s[j]);
    swp++;
    return 0;
}

void legend()
{
    printf("-------------------\n");
    printf(" || - in order     \n");
    printf(" ## - NOT in order \n");
    printf(" >< - swap         \n");
    printf("-------------------\n");
}

void print_buf(char* s)
{
    int i;
    printf("%s\n", s);
    for (i=0; s[i]; i++) {printf("-");} printf("\n");
}

void results(char* s)
{
    printf("cmp = %*d, ", 4, cmp);
    printf("swp = %*d, ", 4, swp);
    printf("alg = %s\n", alg_infos[alg].name);
;
}

int main()
{
    char s[81], ss[81];

    tpf_sort pf_srt;
    tpifpcii pf_brk = order_is_broken;
    tpifpcii pf_swp = swap_items;
    int sz, i;

    for (sz=0; 0!=(ss[sz]=LINE_TO_SORT[sz]); sz++);

    while (1)
    {
        for (sz=0; (s[sz]=ss[sz])>=' '; sz++);
        s[sz]=0;
        for (i=0; i<alg_num; i++)
            printf("%d - %s\n", i+1, alg_infos[i].name);
        printf(
"\n\
0  - exit program\n\
-1 - change line in buffer\n\
-2 - toggle order        (now: %s)\n\
-3 - toggle comparisons  (now: %s)\n\
-4 - toggle swaps        (now: %s)\n\
-5 - test all algorithms (silent)\n\
Which algorithm to run? ",
reverse_sort?"Descending":"Ascending",
show_cmp?"Visible":"Hidden",
show_swp?"Visible":"Hidden"
        );

        scanf("%d", &alg);

        switch (alg)
        {
        case -1:
            printf("New line:\n");
            fgets(ss, sizeof(ss), stdin);
            fgets(ss, sizeof(ss), stdin);
            break;
        case -2:
            reverse_sort ^= 1;
            break;
        case -3:
            show_cmp ^= 1;
            pf_brk = show_cmp?order_is_broken:order_is_broken_silent;
            break;
        case -4:
            show_swp ^= 1;
            pf_swp = show_swp?swap_items:swap_items_silent;
            break;
        case -5:
            pf_brk = order_is_broken_silent;
            pf_swp = swap_items_silent;
            for (alg=0; alg<alg_num; alg++)
            {
                for (sz=0; (s[sz]=ss[sz])>=' '; sz++);
                s[sz]=0;
                pf_srt = alg_infos[alg].pf;
                pf_srt(s, sz, pf_brk, pf_swp);
                results(s);
                cmp = swp = 0;
            }
            pf_brk = show_cmp?order_is_broken:order_is_broken_silent;
            pf_swp = show_swp?swap_items:swap_items_silent;
            break;
        default:
            printf("\n");
            if (alg<=0 || alg>alg_num) return 0;
            alg--;
            pf_srt = alg_infos[alg].pf;
            legend();
            print_buf(s);
            pf_srt(s, sz, pf_brk, pf_swp);
            print_buf(s);
            results(s);
            cmp = swp = 0;
        }
        printf ("\n");
    }
    return 0;
}


