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
