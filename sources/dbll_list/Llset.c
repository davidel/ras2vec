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
link_loc        ll_set_list_currpntr(link_list_hdr * list, link_loc set_loc)
{

    link_loc        ret_pos;

    if (list->head == NULL)
        return (TG_ERROR);
    ret_pos = set_loc;
    switch (set_loc)
    {
        case (TG_HEAD):
            {
                list->current = list->head;
            }
            break;

        case (TG_TAIL):
            {
                list->current = list->last;
            }
            break;

        case (TG_AFTER):
            {
                if (list->current->nxt == NULL)
                {
                    list->current = list->head;
                    ret_pos = TG_HEAD;
                }
                else
                {
                    list->current = list->current->nxt;
                }
            }
            break;

        case (TG_BEFORE):
            {
                if (list->current->prev == NULL)
                {
                    list->current = list->last;
                    ret_pos = TG_TAIL;
                }
                else
                {
                    list->current = list->current->prev;
                }
            }
            break;
    }
    return (ret_pos);

}
