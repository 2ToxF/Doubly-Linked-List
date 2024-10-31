#ifndef DL_LIST_H
#define DL_LIST_H

#include "settings.h"

struct DLList_t
{
    ListElem_t* data;

    int* next;
    int* prev;

    int free;

    int size;
};

enum ListError
{
    LIST_NO_ERROR,
    LIST_ALREADY_INITED_ERR,

    LIST_STRUCT_NULL_PTR,
    LIST_DATA_NULL_PTR,
    LIST_NEXT_NULL_PTR,
    LIST_PREV_NULL_PTR,

    LIST_NEG_SIZE,

    LIST_NEG_HEAD_IDX,
    LIST_NEG_TAIL_IDX,
    LIST_NEG_FREE_IDX,
};

#endif
