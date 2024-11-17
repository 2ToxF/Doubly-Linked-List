#ifndef DLL_INPUT_OUTPUT_H
#define DLL_INPUT_OUTPUT_H

#include "dl_list.h"

#define BLK "\033[0;30m"
#define RED "\033[0;31m"
#define GRN "\033[0;32m"
#define YEL "\033[0;33m"
#define BLU "\033[0;34m"
#define MAG "\033[0;35m"
#define CYN "\033[0;36m"
#define WHT "\033[0;37m"

void DumpClose();
void ListDump (DLList_t* list, const char* file_name, const char* func_name, const int line);

#endif
