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


#ifndef R2VDLL_H
#define R2VDLL_H


#define LIB_PROC                  WINAPI


#ifdef  __cplusplus
extern "C" {
#endif


int LIB_PROC    init_logging(int (CALLBACK * p_log_proc) (char *, va_list),
                        int (CALLBACK * p_err_proc) (char *, va_list),
                        int (CALLBACK * p_scr_proc) (char *, va_list));
int LIB_PROC    cntline_convert_file(char *img_file_name, int use_a_copy,
                        char *poly_file_name, double pnt_error_tollerance,
                        double poly_lenght_factor);
int LIB_PROC    dblline_convert_file(char *img_file_name, char *poly_file_name,
                        double pnt_error_tollerance, double poly_lenght_factor);
int LIB_PROC    dxf_poly_dump(char *dxf_file_name, char *poly_file_name,
                        double x_scale, double y_scale, char *layer_name, int color);
int LIB_PROC    hpgl_poly_dump(char *hpgl_file_name, char *poly_file_name,
                        double x_scale, double y_scale, int color);
int LIB_PROC    emf_poly_dump(char *emf_file_name, char *poly_file_name,
                        double x_scale, double y_scale, COLORREF color);


#ifdef  __cplusplus
}

#endif


#endif