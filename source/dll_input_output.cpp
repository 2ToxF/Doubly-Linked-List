#include <stdio.h>
#include <stdlib.h>

#include "dll_input_output.h"

#define DUMP_LOG_PATH  "logs/"
#define DUMP_DOT_FNAME DUMP_LOG_PATH "dump_dotfile"

static const int MAX_CMD_LEN             = 100;
static const int MAX_FNAME_LEN           = 30;
static const char* const DUMP_HTML_FNAME = DUMP_LOG_PATH "list_log.html";

static char dump_graph_fname[MAX_FNAME_LEN] = {};

static int  dump_number = 0;

static FILE* dump_html_fptr = NULL;

static void DumpDotFile  (DLList_t* list);
static void DumpHtmlFile (DLList_t* list);
static void SystemCallDot();

void DumpClose()
{
    if (dump_html_fptr != NULL)
    {
        fclose(dump_html_fptr);
        dump_html_fptr = NULL;
    }

    dump_number = 0;
}

static void DumpDotFile(DLList_t* list)
{
    FILE* dot_file = fopen(DUMP_DOT_FNAME, "w");
    int cur_elem_idx = 0;

    fprintf(dot_file,
            "digraph {\n"
            "\trankdir=LR;\n"
            "\tbgcolor=\"darkslategray1\";\n"
            "\tfontname=\"Courier New\";\n"
            "\tnode[shape=\"Mrecord\",color=\"coral\",style=\"filled\",fillcolor=\"darkmagenta\",fontcolor=\"white\",fontsize=14];\n"
            "\tedge[color=\"blue\"];\n"
            );

    for (int i = 0; i < list->size; ++i)
    {
        fprintf(dot_file, "\t%d[label=\"IDX%d | data: %lg | next: %d | prev: %d\"];\n",
                i, cur_elem_idx, list->data[cur_elem_idx],
                list->next[cur_elem_idx], list->prev[cur_elem_idx]);
        cur_elem_idx = list->next[cur_elem_idx];
    }

    for (int i = 1; i < list->size; ++i)
        fprintf(dot_file, "\t%d -> %d;\n%d -> %d\n", i-1, i, i, i-1);

    fprintf(dot_file, "}\n");

    fclose(dot_file);
}

void DumpHtmlFile(DLList_t * list)
{
    if (dump_number == 0)
        dump_html_fptr = fopen(DUMP_HTML_FNAME, "w");

    fprintf(dump_html_fptr,
            "<h2>\n"
            "\n"
            "err_code: %d <br><br>\n"
            "\n"
            "data:",
            (int) list->err_code);
    for (int i = 0; i < list->capacity; ++i)
        fprintf(dump_html_fptr, " %-5lg", list->data[i]);

    fprintf(dump_html_fptr, " <br>\nnext:");
    for (int i = 0; i < list->capacity; ++i)
        fprintf(dump_html_fptr, " %-5d", list->next[i]);

    fprintf(dump_html_fptr, " <br>\nprev:");
    for (int i = 0; i < list->capacity; ++i)
        fprintf(dump_html_fptr, " %-5d", list->prev[i]);

    fprintf(dump_html_fptr,
            " <br><br>\n\n"
            "free:     %d <br>\n"
            "capacity: %d <br>\n"
            "size:     %d <br><br>\n"
            "\n"
            "<img src=\"%s\"> <br>"
            "\n"
            "------------------------------------------------------------------------------------\n"
            "\n",
            list->free, list->capacity, list->size,
            dump_graph_fname);
}


void ListDump(DLList_t* list)
{
    DumpDotFile(list);
    SystemCallDot();
    DumpHtmlFile(list);
    ++dump_number;
}


void SystemCallDot()
{
    sprintf(dump_graph_fname, "list_graph%d.png", dump_number);

    char command[MAX_CMD_LEN] = {};
    sprintf(command, "dot -Tpng -Gdpi=150 " DUMP_DOT_FNAME " > " DUMP_LOG_PATH "%s", dump_graph_fname);

    if (system(command) != 0)
    {
        printf(RED "ERROR: SYSTEM CALL ERROR" WHT "\n");
        return;
    }
}

#undef DUMP_LOG_PATH
#undef DUMP_DOT_FNAME
