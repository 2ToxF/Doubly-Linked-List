#include <stdlib.h>

#include "dl_list.h"
#include "list_utils.h"
#include "list_verify.h"

static ListError ListAddFreeElem(DLList_t* list, int new_free_idx);
static ListError ListResizeDown (DLList_t* list);
static ListError ListResizeUp   (DLList_t* list);


static ListError ListAddFreeElem(DLList_t* list, int new_free_idx)
{
    LIST_VERIFY(list);

    list->prev[new_free_idx] = 0;

    if (list->free == new_free_idx)
        SET_LIST_ERROR(LIST_ELEM_ALREADY_FREE_ERR);

    else if (list->free > new_free_idx)
    {
        list->next[new_free_idx] = list->free;
        list->free = new_free_idx;
    }

    else
    {
        int prev_free = list->free;
        while (list->next[prev_free] < new_free_idx)
            prev_free = list->next[prev_free];

        list->next[new_free_idx] = list->next[prev_free];
        list->next[prev_free]    = new_free_idx;
    }

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListDtor(DLList_t* list)
{
    LIST_VERIFY(list);

    free(list->data); list->data = NULL;
    free(list->next); list->next = NULL;
    free(list->prev); list->prev = NULL;

    list->free = list->capacity = list->size = 0;

    list->err_code = LIST_NO_ERROR;
    return LIST_NO_ERROR;
}


ListError ListInit(DLList_t* list)
{
    if (list->data != NULL || list->next != 0 || list->prev != 0 || list->free != 0)
        SET_LIST_ERROR(LIST_ALREADY_INITED_ERR);

    list->capacity = MIN_LIST_CAPAC;

    list->data = (ListElem_t*) calloc(list->capacity, sizeof(ListElem_t));
    list->next = (int*)        calloc(list->capacity, sizeof(int));
    list->prev = (int*)        calloc(list->capacity, sizeof(int));

    for (int i = 1; i < list->capacity; ++i)
        list->next[i] = i+1;

    list->size = list->free = 1;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListInsertAfter(DLList_t* list, ListElem_t insert_value, int prev_elem_idx)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size >= list->capacity)
        if ((list_err = ListResizeUp(list)) != LIST_NO_ERROR)
            return list_err;

    int old_free = list->free;

    list->data[old_free] = insert_value;
    list->free = list->next[old_free];

    list->prev[old_free] = prev_elem_idx;
    list->next[old_free] = list->next[prev_elem_idx];

    list->prev[list->next[prev_elem_idx]] = old_free;
    list->next[prev_elem_idx] = old_free;

    ++list->size;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListInsertTail(DLList_t* list, ListElem_t insert_value)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size >= list->capacity)
        if ((list_err = ListResizeUp(list)) != LIST_NO_ERROR)
            return list_err;

    int old_free = list->free;

    list->data[old_free] = insert_value;

    list->free = list->next[old_free];
    list->next[old_free] = list->prev[0];

    list->prev[old_free] = 0;
    list->prev[0] = old_free;

    ++list->size;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListInsertHead(DLList_t* list, ListElem_t insert_value)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size >= list->capacity)
        if ((list_err = ListResizeUp(list)) != LIST_NO_ERROR)
            return list_err;

    int old_free = list->free;

    list->data[old_free] = insert_value;

    list->free = list->next[old_free];
    list->next[old_free] = 0;

    list->prev[old_free] = list->prev[0];
    list->prev[0] = old_free;

    ++list->size;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListLinearize(DLList_t* list)
{
    LIST_VERIFY(list);

    ListElem_t* new_data = (ListElem_t*) calloc(list->capacity, sizeof(ListElem_t));
    int*        new_next = (int*)        calloc(list->capacity, sizeof(int));
    int*        new_prev = (int*)        calloc(list->capacity, sizeof(int));

    int cur_elem_idx = 0;

    for (int i = 1; i < list->size; ++i)
    {
        cur_elem_idx = list->next[cur_elem_idx];

        new_data[i] = list->data[cur_elem_idx];
        new_next[i] = i+1;
        new_prev[i] = i-1;
    }

    new_next[0] = list->size == 1 ? list->size - 1 : list->size;
    new_prev[0] = 1;

    free(list->data); list->data = new_data;
    free(list->next); list->next = new_next;
    free(list->prev); list->prev = new_prev;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListPopIdx(DLList_t* list, ListElem_t* var_for_pop, int pop_idx)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size == 0)
        return LIST_ANTIOVERFLOW_ERR;

    *var_for_pop = list->data[pop_idx];
    list->next[list->prev[pop_idx]] = list->next[pop_idx];
    list->prev[list->next[pop_idx]] = list->prev[pop_idx];

    if ((list_err = ListAddFreeElem(list, pop_idx)) != LIST_NO_ERROR)
        return list_err;

    --list->size;
    if (list->size <= list->capacity / RESIZE_COEF_DOWN && list->size > MIN_LIST_CAPAC)
        if ((list_err = ListResizeDown(list)) != LIST_NO_ERROR)
            return list_err;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListPopTail(DLList_t* list, ListElem_t* var_for_pop)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size == 0)
        return LIST_ANTIOVERFLOW_ERR;

    *var_for_pop = list->data[list->prev[0]];

    int new_tail_idx = list->next[list->prev[0]];
    if ((list_err = ListAddFreeElem(list, list->prev[0])) != LIST_NO_ERROR)
        return list_err;

    list->prev[0] = new_tail_idx;
    list->prev[new_tail_idx] = 0;

    --list->size;
    if (list->size <= list->capacity / RESIZE_COEF_DOWN && list->size > MIN_LIST_CAPAC)
        if ((list_err = ListResizeDown(list)) != LIST_NO_ERROR)
            return list_err;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListPopHead(DLList_t* list, ListElem_t* var_for_pop)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if (list->size == 0)
        return LIST_ANTIOVERFLOW_ERR;

    *var_for_pop = list->data[list->next[0]];

    int new_head_idx = list->prev[list->next[0]];
    if ((list_err = ListAddFreeElem(list, list->next[0])) != LIST_NO_ERROR)
        return list_err;

    list->next[0] = new_head_idx;
    list->next[new_head_idx] = 0;

    --list->size;
    if (list->size <= list->capacity / RESIZE_COEF_DOWN && list->size > MIN_LIST_CAPAC)
        if ((list_err = ListResizeDown(list)) != LIST_NO_ERROR)
            return list_err;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


static ListError ListResizeDown(DLList_t* list)
{
    ListError list_err = LIST_NO_ERROR;

    LIST_VERIFY(list);

    if ((list_err = ListLinearize(list)) != LIST_NO_ERROR)
        return list_err;

    list->capacity /= RESIZE_COEF;

    list->data = (ListElem_t*) realloc(list->data, list->capacity*sizeof(ListElem_t));
    list->next = (int*)        realloc(list->data, list->capacity*sizeof(int));
    list->prev = (int*)        realloc(list->data, list->capacity*sizeof(int));

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}

static ListError ListResizeUp(DLList_t* list)
{
    LIST_VERIFY(list);

    int old_capacity = list->capacity;
    list->capacity  *= RESIZE_COEF;

    list->data = (ListElem_t*) MyRecalloc(list->data, list->capacity*sizeof(ListElem_t), list->size*sizeof(ListElem_t));
    list->prev = (int*)        MyRecalloc(list->data, list->capacity*sizeof(int), list->size*sizeof(int));

    list->next = (int*)        realloc(list->data, list->capacity*sizeof(int));

    for (int i = old_capacity; i < list->capacity; ++i)
        list->next[i] = i+1;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}
