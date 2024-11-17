#include <stdio.h>

#include "dl_list.h"
#include "dll_input_output.h"


int main()
{
    ListError list_err = LIST_NO_ERROR;

    DLList_t list = CREATE_LIST(list);

    if ((list_err = ListInit(&list)) != LIST_NO_ERROR)
        return list_err;

    ListLinearize(&list);
    ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);

    for (int i = 1; i < 10; ++i)
        if ((list_err = ListInsertHead(&list, i*10)) != LIST_NO_ERROR)
            return list_err;

    ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);

    if ((list_err = ListInsertAfter(&list, 15, 1)) != LIST_NO_ERROR)
        return list_err;
    ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);

    ListElem_t var_for_pop = 0;
    for (int i = 0; i < 10; ++i)
    {
        if ((list_err = ListPopHead(&list, &var_for_pop)) != LIST_NO_ERROR)
            return list_err;
        ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);
    }

    // ListElem_t var_for_pop = 0;
    // if ((list_err = ListPopIdx(&list, &var_for_pop, 1)) != LIST_NO_ERROR)  // Here is equivalent to ListPopTail(&list, &var_for_pop)
    //     return list_err;
    // ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);
    // printf("var_for_pop (IDX = 1) = %lg\n", var_for_pop);

    // if ((list_err = ListPopIdx(&list, &var_for_pop, 6)) != LIST_NO_ERROR)  // Here is equivalent to ListPopHead(&list, &var_for_pop)
    //     return list_err;
    // ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);
    // printf("var_for_pop (IDX = 6) = %lg\n", var_for_pop);

    // if ((list_err = ListLinearize(&list)) != LIST_NO_ERROR)
    //     return list_err;
    // ListDump(&list, __FILE__, __PRETTY_FUNCTION__, __LINE__);

    ListDtor(&list);
    DumpClose();
    return 0;
}
