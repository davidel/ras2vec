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


#ifndef RAS2VEC_H
#define RAS2VEC_H

#ifdef MULTITHREAD
#define TLS                      __declspec(thread)
#else // #ifdef MULTITHREAD
#define TLS
#endif // #ifdef MULTITHREAD
#define STLS                     static TLS

#ifdef DLL_LIB
#define LIB_PROC                  WINAPI
#else // #ifdef DLL_LIB
#define LIB_PROC
#endif // #ifdef DLL_LIB


#define PIG                       3.14159265358979323846

#define CNT_DEF_MAX_PNT_ERROR     1.4143
#define DBL_DEF_MAX_PNT_ERROR     (2.0*1.4143)

#define HORIZONTAL_LINE           0
#define VERTICAL_LINE             1

#define read_bit(m,n)         (((((BYTE *)(m))[(n) >> 3]) & (1 << (7-((n) & 7))))?1:0)
#define read_bit2(fp,m,n)     (((((BYTE *)(m))[(n) >> 3]) & (1 << (7-((n) & 7))))? \
                              (fp):(1-(fp)))
#define set_bit(m,n)          ((BYTE *)(m))[(n) >> 3] |= (1 << (7-((n) & 7)))
#define clear_bit(m,n)        ((BYTE *)(m))[(n) >> 3] &= (~(1 << (7-((n) & 7))))
#define clear_pixel(m,n,b) \
        { \
        if((b)!=0) \
          set_bit(m,n); \
        else \
          clear_bit(m,n); \
        }
#define set_pixel(m,n,b) \
        { \
        if((b)==0) \
          set_bit(m,n); \
        else \
          clear_bit(m,n); \
        }
#define swap_value(t,a,b) \
        { \
        t tmp=a; \
        a=b; \
        b=tmp; \
        }
#define get_line_size(x)      ((((x)+31)/32)*4)
#define get_line(p,l)         (((BYTE *)(p))+sizeof(img_file_header)+ \
                              (l)*get_line_size(((img_file_header *)(p))->x_size))
#define bmp_get_line(p,l)     (((BYTE *)(p))+sizeof(bw_bmp_header)+ \
                              (l)*get_line_size(((bw_bmp_header *)(p))->bih.biWidth))
#define bmp_get_raw_ptr(p)    (((BYTE *)(p))+sizeof(bw_bmp_header))
#define get_raw_img_line(p,lsz,nl) (((BYTE *)(p))+(nl)*(lsz))
#define same_point(p0,p1)     (((p0)->x==(p1)->x) && ((p0)->y==(p1)->y))
#define line_type(p0,p1)      (((p0)->x==(p1)->x)?VERTICAL_LINE:HORIZONTAL_LINE)
#define pnt_distance_2(p0,p1) ((((p0)->x-(p1)->x)*((p0)->x-(p1)->x))+ \
                              (((p0)->y-(p1)->y)*((p0)->y-(p1)->y)))
#define incr(i,n)             ((((i)+1)<(n))?((i)+1):0)
#define decr(i,n)             ((((i)-1)>=0)?((i)-1):((n)-1))

typedef struct img_point_record{
                 int x,y;
                 } img_point;
typedef struct img_file_header_record{
                 int x_size,
                     y_size;
                 unsigned short int back_ground;
                 } img_file_header;
typedef struct bw_bmp_header_record{
                 BITMAPFILEHEADER bfh;
                 BITMAPINFOHEADER bih;
                 RGBQUAD colors[2];
                 } bw_bmp_header;

#endif

