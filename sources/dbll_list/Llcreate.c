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
link_list_hdr  *ll_create_list(void)
{

    link_list_hdr  *hdr_record;

    if ((hdr_record = (link_list_hdr *) malloc(sizeof(link_list_hdr))) == NULL)
        return (NULL);
    hdr_record->head = NULL;
    hdr_record->last = NULL;
    hdr_record->current = NULL;
    hdr_record->count = 0;
    return (hdr_record);

}
