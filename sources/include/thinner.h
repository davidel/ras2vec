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



#ifndef THINNER_H
#define THINNER_H

int             thin_image_file(char *img_file_name);
int             thin_image(BYTE *p_img_mem,int *p_back_ground);
int             bmp_file_get_background(bw_bmp_header *p_bmph,BYTE *p_img_mem,
                                        int x_samples,int y_samples);
link_list_hdr * get_node_points(bw_bmp_header *p_bmph,BYTE *p_img_mem,
                                int back_ground);

#endif

