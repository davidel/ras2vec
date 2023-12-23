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



#include<windows.h>
#include<windowsx.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<ctype.h>
#include<time.h>
#include<stdarg.h>
#include<ras2vec.h>
#include"log.h"
#include"util.h"


STLS int        (CALLBACK * log_proc) (char *, va_list) = NULL;
STLS int        (CALLBACK * err_proc) (char *, va_list) = NULL;
STLS int        (CALLBACK * scr_proc) (char *, va_list) = NULL;


/* OK */
int LIB_PROC    init_logging(int (CALLBACK * p_log_proc) (char *, va_list),
                        int (CALLBACK * p_err_proc) (char *, va_list),
                        int (CALLBACK * p_scr_proc) (char *, va_list))
{

    log_proc = p_log_proc;
    err_proc = p_err_proc;
    scr_proc = p_scr_proc;
    return (TRUE);

}


/* OK */
int             log_printf(char *p_str_format,...)
{

    int             num_bytes_writed;
    va_list         sp_arg;

    if (log_proc == NULL)
        return (0);
    va_start(sp_arg, p_str_format);
    num_bytes_writed = log_proc(p_str_format, sp_arg);
    va_end(sp_arg);
    return (num_bytes_writed);

}


/* OK */
int             log_vprintf(char *p_str_format, va_list sp_arg)
{

    int             num_bytes_writed;

    if (log_proc == NULL)
        return (0);
    num_bytes_writed = log_proc(p_str_format, sp_arg);
    return (num_bytes_writed);

}


/* OK */
int             scr_printf(char *p_str_format,...)
{

    int             num_bytes_writed;
    va_list         sp_arg;

    if (scr_proc == NULL)
        return (0);
    va_start(sp_arg, p_str_format);
    num_bytes_writed = scr_proc(p_str_format, sp_arg);
    va_end(sp_arg);
    return (num_bytes_writed);

}


/* OK */
int             err_printf(char *file_name, int line_num, char *p_str_format,...)
{

    int             num_bytes_writed;
    char           *src_file_name = strrchr(file_name, '\\'),
                   *buffer;
    va_list         sp_arg;
    char            error_prolog[256];

    if (err_proc == NULL)
        return (0);
    src_file_name = (src_file_name != NULL) ? (src_file_name + 1) : file_name;
    sprintf(error_prolog, "[%s:%d] ", src_file_name, line_num);
    if ((buffer = (char *) malloc(strlen(p_str_format) + strlen(error_prolog) + 2)) == NULL)
        return (-1);
    sprintf(buffer, "%s%s", error_prolog, p_str_format);
    va_start(sp_arg, p_str_format);
    num_bytes_writed = err_proc(buffer, sp_arg);
    va_end(sp_arg);
    free(buffer);
    return (num_bytes_writed);

}
