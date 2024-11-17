#ifndef LIST_VERIFY_H
#define LIST_VERIFY_H

#include <stdio.h>

#include "dl_list.h"
#include "dll_input_output.h"

#define SET_LIST_ERROR(__list_error_code__)    \
    do                                         \
    {                                          \
        list->err_code = __list_error_code__;  \
        return __list_error_code__;            \
    } while (0)

#define LIST_VERIFY(__list_ptr__)                                                                           \
    do                                                                                                      \
    {                                                                                                       \
        ListError temp_list_error = LIST_NO_ERROR;                                                          \
        if ((temp_list_error = ListVerify(__list_ptr__)) != LIST_NO_ERROR)                                  \
        {                                                                                                   \
            printf("\n" RED "ERROR: LIST_ERRNO: %d   in file: %s   line: %d   func: %s" WHT "\n",           \
                   temp_list_error, __FILE__, __LINE__, __PRETTY_FUNCTION__);                               \
            SET_LIST_ERROR(temp_list_error);                                                                \
        }                                                                                                   \
    } while (0)


ListError ListVerify(DLList_t* list);

#endif
