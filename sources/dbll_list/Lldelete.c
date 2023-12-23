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
void           *ll_delete_list_item(link_list_hdr * list, link_loc del_loc,
                        link_loc ret_loc)
{

    void           *delete_data;
    dll_link       *dpntr;

    switch (del_loc)
    {
        case (TG_HEAD):
            if (list->head == NULL)
                return (NULL);
            delete_data = list->head->data;
            dpntr = list->head;
            list->head = list->head->nxt;
            if (list->head != NULL)
                list->head->prev = NULL;
            break;

        case (TG_TAIL):
            if (list->last == NULL)
                return (NULL);
            delete_data = list->last->data;
            dpntr = list->last;
            list->last = list->last->prev;
            if (list->last != NULL)
                list->last->nxt = NULL;
            break;

        case (TG_AFTER):
            if (list->current == NULL)
                return (NULL);
            if (list->current->nxt == NULL)
                return (NULL);
            dpntr = list->current->nxt;
            delete_data = dpntr->data;
            if (dpntr->nxt != NULL)
                dpntr->nxt->prev = list->current;
            else
                list->last = list->current;
            list->current->nxt = dpntr->nxt;
            break;

        case (TG_BEFORE):
            if (list->current == NULL)
                return (NULL);
            if (list->current->prev == NULL)
                return (NULL);
            dpntr = list->current->prev;
            delete_data = dpntr->data;
            if (dpntr->prev != NULL)
                dpntr->prev->nxt = list->current;
            else
                list->head = list->current;
            list->current->prev = dpntr->prev;
            break;

        default:
            if (list->current == NULL)
                return (NULL);
            dpntr = list->current;
            delete_data = dpntr->data;
            if (dpntr->prev == NULL)
            {
                list->head = list->head->nxt;
                if (list->head != NULL)
                    list->head->prev = NULL;
            }
            else
                list->current->prev->nxt = list->current->nxt;
            if (dpntr->nxt == NULL)
            {
                list->last = list->last->prev;
                if (list->last != NULL)
                    list->last->nxt = NULL;
            }
            else
                list->current->nxt->prev = list->current->prev;
            break;
    }
    switch (ret_loc)
    {
        case (TG_HEAD):
            list->current = list->head;
            break;

        case (TG_TAIL):
            list->current = list->last;
            break;

        case (TG_AFTER):
            if (list->current->nxt == NULL)
                list->current = list->last;
            else
                list->current = list->current->nxt;
            break;

        case (TG_BEFORE):
            if (list->current->prev == NULL)
                list->current = list->head;
            else
                list->current = list->current->prev;
            break;
    }
    free(dpntr);
    --list->count;
    return (delete_data);

}
