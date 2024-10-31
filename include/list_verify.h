#ifndef LIST_VERIFY_H
#define LIST_VERIFY_H

#include "dl_list.h"

#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"

#define LIST_VERIFY(list_ptr)                                                   \
    do                                                                          \
    {                                                                           \
        ListError temp_list_error = LIST_NO_ERROR;                              \
        if ((temp_list_error = ListVerify(list_ptr)) != LIST_NO_ERROR)          \
        {                                                                       \
            printf("\n" RED "ERROR: LIST_ERRNO: %d" WHT "\n", temp_list_error)  \
            return temp_list_error;                                             \
        }                                                                       \
    } while (0)


ListError ListVerify(DLList_t* list);
void ListDump(DLList_t* list);

#endif
