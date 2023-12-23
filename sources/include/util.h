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



#ifndef UTIL_H
#define UTIL_H


char           *get_temp_file(char *file_name);
int LIB_PROC    dxf_poly_dump(char *dxf_file_name, char *poly_file_name,
                        double x_scale, double y_scale, char *layer_name,
                        int color);
int LIB_PROC    hpgl_poly_dump(char *hpgl_file_name, char *poly_file_name,
                        double x_scale, double y_scale, int color);
int LIB_PROC    emf_poly_dump(char *emf_file_name, char *poly_file_name,
                        double x_scale, double y_scale, COLORREF color);


#endif
