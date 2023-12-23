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
