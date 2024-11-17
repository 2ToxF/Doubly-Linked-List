#ifndef DL_LIST_H
#define DL_LIST_H

#define CREATE_LIST(__list_name__) {#__list_name__};

typedef double ListElem_t;

const int MIN_LIST_CAPAC   = 8;
const int RESIZE_COEF      = 2;
const int RESIZE_COEF_DOWN = RESIZE_COEF * 2;

enum ListError
{
    LIST_NO_ERROR,
    LIST_ALREADY_INITED_ERR,

    LIST_STRUCT_NULL_PTR_ERR,
    LIST_DATA_NULL_PTR_ERR,
    LIST_NEXT_NULL_PTR_ERR,
    LIST_PREV_NULL_PTR_ERR,

    LIST_ELEM_ALREADY_FREE_ERR,

    LIST_NEG_ELEM_NUM_ERR,
    LIST_NEG_SIZE_ERR,

    LIST_NEG_FREE_IDX_ERR,
    LIST_NEG_HEAD_IDX_ERR,
    LIST_NEG_TAIL_IDX_ERR,

    LIST_ANTIOVERFLOW_ERR,
    LIST_OVERFLOW_ERR,

    LIST_USES_MUCH_MEM_ERR,
};

struct DLList_t
{
    const char* list_name;
    ListError   err_code;

    ListElem_t* data;

    int* next;
    int* prev;

    int  capacity;
    int  size;

    int  free;
};

ListError ListDtor       (DLList_t* list);
ListError ListInit       (DLList_t* list);

ListError ListInsertAfter(DLList_t* list, ListElem_t insert_value, int insert_idx);
ListError ListInsertHead (DLList_t* list, ListElem_t insert_value);
ListError ListInsertTail (DLList_t* list, ListElem_t insert_value);

ListError ListLinearize  (DLList_t* list);

ListError ListPopHead    (DLList_t* list, ListElem_t* var_for_pop);
ListError ListPopIdx     (DLList_t* list, ListElem_t* var_for_pop, int pop_idx);
ListError ListPopTail    (DLList_t* list, ListElem_t* var_for_pop);

#endif
