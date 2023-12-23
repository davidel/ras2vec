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
int             ll_add_list_data(link_list_hdr * list, link_loc loc, void *data)
{

    dll_link       *new_link;

    if ((new_link = (dll_link *) malloc(sizeof(dll_link))) == NULL)
        return (FALSE);
    new_link->nxt = NULL;
    new_link->prev = NULL;
    memcpy(new_link->user_data, data, sizeof(new_link->user_data));
    if (list->head == NULL)
    {
        list->head = new_link;
        list->last = new_link;
    }
    else
    {
        switch (loc)
        {
            case (TG_HEAD):
                {
                    list->head->prev = new_link;
                    new_link->nxt = list->head;
                    list->head = new_link;
                }
                break;

            case (TG_AFTER):
                {
                    if (list->current->nxt != NULL)
                    {
                        list->current->nxt->prev = new_link;
                        new_link->nxt = list->current->nxt;
                        new_link->prev = list->current;
                        list->current->nxt = new_link;
                    }
                    else
                    {
                        list->last->nxt = new_link;
                        new_link->prev = list->last;
                        list->last = new_link;
                    }
                }
                break;

            case (TG_BEFORE):
                {
                    if (list->current->prev != NULL)
                    {
                        list->current->prev->nxt = new_link;
                        new_link->nxt = list->current;
                        new_link->prev = list->current->prev;
                        list->current->prev = new_link;
                    }
                    else
                    {
                        list->head->prev = new_link;
                        new_link->nxt = list->head;
                        list->head = new_link;
                    }
                }
                break;

            default:
                {
                    list->last->nxt = new_link;
                    new_link->prev = list->last;
                    list->last = new_link;
                }
                break;
        }
    }
    list->current = new_link;
    ++list->count;
    return (TRUE);

}
