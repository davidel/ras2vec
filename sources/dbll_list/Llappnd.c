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
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include"dbll_list.h"

/* OK */
int             ll_append_list(link_list_hdr * ldst, link_list_hdr * lsrc)
{

    if (lsrc->count != 0)
    {
        if (ldst->count != 0)
        {
            ldst->count += lsrc->count;
            ldst->last->nxt = lsrc->head;
            lsrc->head->prev = ldst->last;
            ldst->last = lsrc->last;
        }
        else
            *ldst = *lsrc;
    }
    free(lsrc);
    return (0);

}
