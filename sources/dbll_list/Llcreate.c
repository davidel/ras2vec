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
