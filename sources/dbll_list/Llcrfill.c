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
#include<ctype.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include"dbll_list.h"

/* OK */
link_list_hdr  *ll_create_fill_list(int count, int size)
{

    int             ii;
    link_list_hdr  *p_data_list;

    if ((p_data_list = ll_create_list()) == NULL)
        return (NULL);
    for (ii = 0; ii < count; ii++)
    {
        char           *p_data;

        if ((p_data = (char *) malloc(size)) == NULL)
        {
            ll_destroy_free_list(p_data_list);
            return (NULL);
        }
        if (!ll_add_list_item(p_data_list, TG_TAIL, p_data, size))
        {
            free(p_data);
            ll_destroy_free_list(p_data_list);
            return (NULL);
        }
    }
    return (p_data_list);

}
