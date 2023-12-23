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
void           *ll_change_list_data(link_list_hdr * list, void *prev_data,
                        void *new_data)
{

    ll_set_list_currpntr(list, TG_HEAD);
    do
    {
        void           *curr_data;

        if ((curr_data = ll_get_list_data(list)) == NULL)
            break;
        if (curr_data == prev_data)
            return (ll_set_list_data(list, new_data));
    } while (ll_set_list_currpntr(list, TG_AFTER) == TG_AFTER);
    return (NULL);

}
