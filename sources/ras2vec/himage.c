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
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include"ras2vec.h"
#include"himage.h"
#include"util.h"

/* OK */
void           *get_image(char *img_file_name, int open_mode, img_data * p_imgd)
{

    DWORD           file_access,
                    file_protection,
                    desired_access;

    switch (open_mode)
    {
        case (IMAGE_OPEN_READ):
            file_access = GENERIC_READ;
            file_protection = PAGE_READONLY;
            desired_access = FILE_MAP_READ;
            break;

        case (IMAGE_OPEN_READWRITE):
            file_access = GENERIC_WRITE | GENERIC_READ;
            file_protection = PAGE_READWRITE;
            desired_access = FILE_MAP_WRITE;
            break;

        default:
            return (NULL);
    }
    p_imgd->open_mode = open_mode;
    if ((p_imgd->h_file = CreateFile(img_file_name, file_access, 0, NULL, OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
        return (NULL);
    p_imgd->file_size_lo = GetFileSize(p_imgd->h_file, &p_imgd->file_size_hi);
    if ((p_imgd->h_filemap = CreateFileMapping(p_imgd->h_file, NULL, file_protection,
                            p_imgd->file_size_hi, p_imgd->file_size_lo, NULL)) == NULL)
    {
        CloseHandle(p_imgd->h_file);
        return (NULL);
    }
    if ((p_imgd->p_file_mem = MapViewOfFile(p_imgd->h_filemap,
                            desired_access, 0, 0, 0)) == NULL)
    {
        CloseHandle(p_imgd->h_filemap);
        CloseHandle(p_imgd->h_file);
        return (NULL);
    }
    return (p_imgd->p_file_mem);

}

/* OK */
void            free_image(img_data * p_imgd)
{

    if (p_imgd->open_mode == IMAGE_OPEN_READWRITE)
    {
        SetFilePointer(p_imgd->h_file, p_imgd->file_size_lo, &p_imgd->file_size_hi,
                FILE_BEGIN);
        SetEndOfFile(p_imgd->h_file);
    }
    UnmapViewOfFile(p_imgd->p_file_mem);
    CloseHandle(p_imgd->h_filemap);
    CloseHandle(p_imgd->h_file);

}
