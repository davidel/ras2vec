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

