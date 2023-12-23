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



#ifndef LOG_H
#define LOG_H


#include<stdarg.h>

#define ELOC               __FILE__,__LINE__


int LIB_PROC    init_logging(int (CALLBACK * p_log_proc) (char *, va_list),
                        int (CALLBACK * p_err_proc) (char *, va_list),
                        int (CALLBACK * p_scr_proc) (char *, va_list));
int             log_printf(char *p_str_format,...);
int             log_vprintf(char *p_str_format, va_list sp_arg);
int             scr_printf(char *p_str_format,...);
int             err_printf(char *file_name, int line_num, char *p_str_format,...);


#endif
