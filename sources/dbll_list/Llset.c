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
