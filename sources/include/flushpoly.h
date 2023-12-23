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


#ifndef FLUSHPOLY_H
#define FLUSHPOLY_H

int             start_polyline(FILE *fp_poly);
int             end_polyline(FILE *fp_poly);
int             write_img_point(FILE *fp_poly,img_point *p_imgp);
int             read_start_polyline(FILE *fp_poly);
int             read_img_point(FILE *fp_poly,img_point *p_imgp);
void            update_min_max_pnt(img_point *p_imgp,img_point *p_min_imgp,
                                   img_point *p_max_imgp);
double          img_points_dist(img_point *p_imgp0,img_point *p_imgp1);
int             flush_polyline(FILE *fp_poly,link_list_hdr *p_polyline_list,
                               double min_polyline_lenght);
int             opt_flush_polyline(FILE *fp_poly,link_list_hdr *p_polyline_list,
                                   double pnt_error_tollerance,
                                   double min_polyline_lenght);

#endif

