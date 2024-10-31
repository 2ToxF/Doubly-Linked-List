#include <stdlib.h>

#include "dl_list.h"
#include "list_verify.h"

static const int MIN_LIST_SIZE = 8;
static const int REALLOC_COEF  = 2;


ListError ListInit(DLList_t* list)
{
    if (list->data != NULL || list->next != 0 || list->prev != 0 || list->free != 0)
        return LIST_ALREADY_INITED_ERR;

    list->size = MIN_LIST_SIZE;

    list->data = (ListElem_t*) calloc(list->size, sizeof(ListElem_t));
    list->next = (int*) calloc(list->size, sizeof(int));
    list->prev = (int*) calloc(list->size, sizeof(int));

    list->next[0] = list->prev[0] = 0;
    list->free = 1;

    LIST_VERIFY(list);
    return LIST_NO_ERROR;
}


ListError ListDtor(DLList_t* list)
{
    LIST_VERIFY(list);

    free(list->data); list->data = NULL;
    free(list->next); list->next = NULL;
    free(list->prev); list->prev = NULL;

    list->free = list->size = 0;

    return LIST_NO_ERROR;
}


ListError ListInsertMid(DLList_t* list, ListElem_t insert_value, int insert_idx)
{
    LIST_VERIFY(list);

    LIST_VERIFY(list);
}


ListError ListInsertEnd(DLList_t* list, ListElem_t insert_value)
{
    LIST_VERIFY(list);

    // TODO: добавить проверку на реаллок
    int old_free = list->free;

    list->data[old_free] = insert_value;

    list->free = list->next[old_free];
    list->next[old_free] = 0;

    list->prev[old_free] = list->next[0];
    list->next[0] = old_free;

    LIST_VERIFY(list);
    return NO_ERROR;
}
