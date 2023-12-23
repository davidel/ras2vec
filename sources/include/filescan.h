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


#ifndef FILESCAN_H
#define FILESCAN_H

typedef struct polyline_record{
                 link_list_hdr *p_poly_list;
                 img_point prev_pnt0,
                           last_pnt0,
                           pnt0,
                           prev_pnt1,
                           last_pnt1,
                           pnt1;
                 } polyline;

int LIB_PROC      dblline_convert_file(char *img_file_name,char *poly_file_name,
                                       double pnt_error_tollerance,
                                       double poly_lenght_factor);

#endif

