#include "dl_list.h"
#include "dll_input_output.h"


int main()
{
    DLList_t list = {};

    ListInit(&list);
    ListDump(&list);

    for (int i = 1; i < 4; ++i)
    {
        ListInsertHead(&list, i*10);
        ListDump(&list);
    }

    DumpClose();
    return 0;
}
