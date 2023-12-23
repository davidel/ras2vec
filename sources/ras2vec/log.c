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
