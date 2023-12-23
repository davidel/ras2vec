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
