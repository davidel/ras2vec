/*
 *  Ras2Vec by Davide Libenzi ( Raster to vector conversion program )
 *  Copyright (C) 1999, 2000, 2001  Davide Libenzi
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Davide Libenzi <davidel@xmailserver.org>
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
