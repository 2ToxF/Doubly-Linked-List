#include <stdio.h>

#include "dl_list.h"
#include "list_verify.h"

ListError ListVerify(DLList_t* list)
{
    if (list == NULL)
        return LIST_STRUCT_NULL_PTR_ERR;

    if (list->data == NULL)
        return LIST_DATA_NULL_PTR_ERR;

    if (list->next == NULL)
        return LIST_NEXT_NULL_PTR_ERR;

    if (list->prev == NULL)
        return LIST_PREV_NULL_PTR_ERR;

    if (list->capacity < 0)
        return LIST_NEG_ELEM_NUM_ERR;

    if (list->size <= 0)
        return LIST_NEG_SIZE_ERR;

    if (list->free <= 0)
        return LIST_NEG_FREE_IDX_ERR;

    if (list->next[0] < 0)
        return LIST_NEG_HEAD_IDX_ERR;

    if (list->prev[0] < 0)
        return LIST_NEG_TAIL_IDX_ERR;

    if (list->size > list->capacity)
        return LIST_OVERFLOW_ERR;

    if (list->size < list->capacity / RESIZE_COEF_DOWN && list->capacity > MIN_LIST_CAPAC)
        return LIST_USES_MUCH_MEM_ERR;

    return LIST_NO_ERROR;
}
