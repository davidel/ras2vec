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

