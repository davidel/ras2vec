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
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include"dbll_list.h"

/* OK */
int             ll_clear_list(link_list_hdr * p_list)
{

    void           *p_data;

    ll_set_list_currpntr(p_list, TG_HEAD);
    while ((p_data = ll_delete_list_item(p_list, TG_CURRENT, TG_AFTER)) != NULL)
        free(p_data);
    return (0);

}
