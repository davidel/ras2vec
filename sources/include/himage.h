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

