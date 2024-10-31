#include <stdio.h>

#include "dl_list.h"
#include "list_verify.h"

ListError ListVerify(DLList_t* list)
{
    if (list == NULL)
        return LIST_STRUCT_NULL_PTR;

    if (list->data == NULL)
        return LIST_DATA_NULL_PTR;

    if (list->next == NULL)
        return LIST_NEXT_NULL_PTR;

    if (list->prev == NULL)
        return LIST_PREV_NULL_PTR;

    if (list->size < 0)
        return LIST_NEG_SIZE;

    if (list->next[0] < 0)
        return LIST_NEG_HEAD_IDX;

    if (list->prev[0] < 0)
        return LIST_NEG_TAIL_IDX;

    if (list->free < 0)
        return LIST_NEG_FREE_IDX;
}


void ListDump(DLList_t* list)
{
}
