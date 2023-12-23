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


#ifndef HIMAGE_H
#define HIMAGE_H

#define IMAGE_OPEN_READ              1
#define IMAGE_OPEN_READWRITE         2

typedef struct img_data_record{
                 int open_mode;
                 DWORD file_size_lo,
                       file_size_hi;
                 HANDLE h_file,
                        h_filemap;
                 void *p_file_mem;
                 } img_data;

void *        get_image(char *img_file_name,int open_mode,img_data *p_imgd);
void          free_image(img_data *p_imgd);

#endif

