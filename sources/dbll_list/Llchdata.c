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
