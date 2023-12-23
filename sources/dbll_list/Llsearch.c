/*    Copyright 2023 Davide Libenzi
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * 
 */



#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<float.h>
#include<math.h>
#include"dbll_list.h"

/* OK */
list_status_code ll_search_list(link_list_hdr * list, link_loc start_loc,
                        link_loc stop_loc, link_loc sdir,
                        int (*cmp) (void *, void *),
                        void *cmp_data)
{

    dll_link       *start = NULL,
                   *stop = NULL;
    list_status_code cmp_status;
    int             continue_repeat = TRUE;

    if ((sdir != TG_AFTER) && (sdir != TG_BEFORE))
        return (LSC_BAD_SEARCH_DIR);
    if ((start_loc != TG_HEAD) && (start_loc != TG_TAIL) && (start_loc != TG_CURRENT))
        return (LSC_BAD_START_LOC);
    if ((stop_loc != TG_HEAD) && (stop_loc != TG_TAIL) && (stop_loc != TG_CURRENT))
        return (LSC_BAD_STOP_LOC);
    if (list->head == NULL)
        return (LSC_BAD_LIST);
    if (!cmp)
        return (LSC_BAD_COMPARE_FUNCTION);
    switch (start_loc)
    {
        case (TG_HEAD):
            start = list->head;
            break;

        case (TG_TAIL):
            start = list->last;
            break;

        case (TG_CURRENT):
            start = list->current;
            break;
    }
    switch (stop_loc)
    {
        case (TG_HEAD):
            stop = list->head;
            break;

        case (TG_TAIL):
            stop = list->last;
            break;

        case (TG_CURRENT):
            stop = list->current;
            break;
    }
    while (continue_repeat)
    {
        cmp_status = (*cmp) (start->data, cmp_data);
        if (cmp_status == LSC_MATCH_FOUND)
        {
            list->current = start;
            return (cmp_status);
        }
        if (start == stop)
            return (LSC_MATCH_NOT_FOUND);
        else
        {
            if (sdir == TG_AFTER)
            {
                if (start->nxt == NULL)
                    return (LSC_MATCH_NOT_FOUND);
                else
                    start = start->nxt;
            }
            else
            {
                if (start->prev == NULL)
                    return (LSC_MATCH_NOT_FOUND);
                else
                    start = start->prev;
            }
        }
    }
    return (LSC_SUCCESS);

}
