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


#ifndef THINNER_H
#define THINNER_H

int             thin_image_file(char *img_file_name);
int             thin_image(BYTE *p_img_mem,int *p_back_ground);
int             bmp_file_get_background(bw_bmp_header *p_bmph,BYTE *p_img_mem,
                                        int x_samples,int y_samples);
link_list_hdr * get_node_points(bw_bmp_header *p_bmph,BYTE *p_img_mem,
                                int back_ground);

#endif

