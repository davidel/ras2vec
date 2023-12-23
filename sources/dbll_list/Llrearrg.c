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
void            ll_rearrange_list(link_list_hdr * list, int dir)
{

    dll_link       *first,
                   *start,
                   *end,
                   *hold,
                   *last,
                   *curr,
                   *prev;

    first = list->head;
    last = list->last;
    curr = list->current;
    prev = list->current->prev;
    if (prev != NULL)
    {
        first->prev = last;
        last->nxt = first;
        prev->nxt = NULL;
        curr->prev = NULL;
        list->head = curr;
        list->last = prev;
    }
    if (dir == TG_BACKWARD)
    {
        start = list->last;
        end = list->head;
        curr = list->last;
        do
        {
            hold = curr->prev;
            curr->prev = curr->nxt;
            curr->nxt = hold;
            curr = curr->nxt;
        } while (curr != NULL);
        start->prev = NULL;
        end->nxt = NULL;
        list->head = start;
        list->last = end;
        list->current = start;
    }
    return;

}
