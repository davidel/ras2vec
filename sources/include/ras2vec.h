/*    Copyright 2023 Davide Libenzi
 * 
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 * 
 *        http://www.apache.org/licenses/LICENSE-2.0
 * 
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
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

