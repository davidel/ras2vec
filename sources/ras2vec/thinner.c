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
#include<time.h>
#include<limits.h>
#include"ras2vec.h"
#include"dbll_list.h"
#include"himage.h"
#include"thinner.h"
#include"log.h"
#include"util.h"


#define ASM_VERSION


#ifdef ASM_VERSION
#define get_mem_bits            get_mem_bits_asm
#else
#define get_mem_bits            get_mem_bits_c
#endif


static int      do_thinning(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        BYTE * p_prev_mod_line, BYTE * p_curr_mod_line);
static int      step_1_check_func(BYTE * pix);
static int      step_2_check_func(BYTE * pix);
static int      get_mem_bits_c(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground,
                        int *p_switches);
static int      get_mem_bits_asm_bFF(BYTE * p_line, int x_size, BYTE * p_bits,
                        int *p_switches);
static int      get_mem_bits_asm_b00(BYTE * p_line, int x_size, BYTE * p_bits,
                        int *p_switches);
static int      get_mem_bits_asm(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground,
                        int *p_switches);
static int      do_step(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        BYTE * p_prev_mod_line, BYTE * p_curr_mod_line,
                        int (*step_check_func) (BYTE *));


static BYTE     bits[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};


/* OK */
int             thin_image_file(char *img_file_name)
{

    int             passes;
    BYTE           *p_img_mem;
    img_data        imgd;

    if ((p_img_mem = (BYTE *) get_image(img_file_name, IMAGE_OPEN_READWRITE,
                            &imgd)) == NULL)
        return (-1);
    passes = thin_image(p_img_mem, NULL);
    free_image(&imgd);
    return (passes);

}


/* OK */
int             thin_image(BYTE * p_img_mem, int *p_back_ground)
{

    int             passes = 0,
                    pixel_removed,
                    back_ground;
    BYTE           *p_mod_lines,
                   *p_curr_mod_line,
                   *p_prev_mod_line;
    bw_bmp_header   bmph;
    time_t          start_time,
                    end_time;

    bmph = *((bw_bmp_header *) p_img_mem);
    if ((bmph.bfh.bfType != *((WORD *) "BM")) || (bmph.bih.biSize != sizeof(BITMAPINFOHEADER)) ||
            (bmph.bih.biCompression != BI_RGB) || (bmph.bih.biBitCount != 1) ||
            (bmph.bih.biPlanes != 1))
        return (-1);
    if ((p_mod_lines = (BYTE *) malloc(2 * bmph.bih.biHeight)) == NULL)
        return (-1);
    p_prev_mod_line = p_mod_lines;
    memset(p_prev_mod_line, 1, bmph.bih.biHeight);
    p_curr_mod_line = p_prev_mod_line + bmph.bih.biHeight;
    memset(p_curr_mod_line, 0, bmph.bih.biHeight);
    back_ground = bmp_file_get_background(&bmph, p_img_mem, 100, 100);
    time(&start_time);
    while ((pixel_removed = do_thinning(&bmph, p_img_mem, back_ground, p_prev_mod_line,
                            p_curr_mod_line)) > 0)
    {
        BYTE           *tmp_byte_ptr;

        tmp_byte_ptr = p_prev_mod_line;
        p_prev_mod_line = p_curr_mod_line;
        p_curr_mod_line = tmp_byte_ptr;
        memset(p_curr_mod_line, 0, bmph.bih.biHeight);
        time(&end_time);
        scr_printf("- pass %3d - removed %8d pixel(s) in %.0lf sec\n", passes + 1,
                pixel_removed, difftime(end_time, start_time));
        time(&start_time);
        ++passes;
    }
    time(&end_time);
    scr_printf("- pass %3d - removed %8d pixel(s) in %.0lf sec\n", passes + 1,
            pixel_removed, difftime(end_time, start_time));
    free(p_mod_lines);
    if (p_back_ground != NULL)
        *p_back_ground = back_ground;
    return (passes);

}


/* OK */
int             bmp_file_get_background(bw_bmp_header * p_bmph, BYTE * p_img_mem,
                        int x_samples, int y_samples)
{

    int             xx,
                    yy,
                    num_ones = 0,
                    num_zeros = 0,
                    x_step,
                    y_step,
                    img_line_size = get_line_size(p_bmph->bih.biWidth);
    BYTE           *p_raw_ptr = bmp_get_raw_ptr(p_img_mem),
                   *p_file_curr_line;

    x_step = max(1, p_bmph->bih.biWidth / x_samples);
    y_step = max(1, p_bmph->bih.biHeight / y_samples);
    for (yy = 0; yy < p_bmph->bih.biHeight; yy += y_step)
    {
        p_file_curr_line = get_raw_img_line(p_raw_ptr, img_line_size, yy);
        for (xx = 0; xx < p_bmph->bih.biWidth; xx += x_step)
        {
            if (read_bit(p_file_curr_line, xx))
                ++num_ones;
            else
                ++num_zeros;
        }
    }
    return ((num_ones > num_zeros) ? 0xff : 0x00);

}


/* OK */
static int      do_thinning(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        BYTE * p_prev_mod_line, BYTE * p_curr_mod_line)
{

    int             pixel_removed_1,
                    pixel_removed_2;

    if ((pixel_removed_1 = do_step(p_bmph, p_img_mem, back_ground, p_prev_mod_line,
                            p_curr_mod_line, step_1_check_func)) < 0)
        return (pixel_removed_1);

    if ((pixel_removed_2 = do_step(p_bmph, p_img_mem, back_ground, p_prev_mod_line,
                            p_curr_mod_line, step_2_check_func)) < 0)
        return (pixel_removed_2);

    return (pixel_removed_1 + pixel_removed_2);

}


/* OK */
static int      step_1_check_func(BYTE * pix)
{

    return ((((pix[1] * pix[3] * pix[5]) == 0) && ((pix[3] * pix[5] * pix[7]) == 0)) ? TRUE : FALSE);

}


/* OK */
static int      step_2_check_func(BYTE * pix)
{

    return ((((pix[1] * pix[3] * pix[7]) == 0) && ((pix[1] * pix[5] * pix[7]) == 0)) ? TRUE : FALSE);

}


/* OK */
static int      get_mem_bits_c(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground,
                        int *p_switches)
{

    int             xx,
                    bit = 7,
                    num_switches = 0;
    register BYTE   curr_byte = *p_bits,
                    last_is_zero = TRUE;
    BYTE           *p_dw_ptr_limit = p_bits + (get_line_size(x_size) - 4);

    memset(p_line, 0, x_size);
    if (back_ground != 0)
    {
        for (xx = 0; xx < x_size; xx++)
        {
            if (!(curr_byte & bits[bit]))
            {
                p_line[xx] = 1;
                if (last_is_zero)
                    p_switches[num_switches++] = xx, last_is_zero = FALSE;
            }
            else
                last_is_zero = TRUE;
            if ((--bit) < 0)
            {
                DWORD          *p_dw_bits = (DWORD *)++ p_bits;

                bit = 7;
                while (((BYTE *) p_dw_bits < p_dw_ptr_limit) && (*p_dw_bits == 0xffffffff))
                    ++p_dw_bits;
                if ((BYTE *) p_dw_bits > p_bits)
                {
                    xx += 8 * (int) ((BYTE *) p_dw_bits - p_bits);
                    p_bits = (BYTE *) p_dw_bits;
                    last_is_zero = TRUE;
                }
                if (xx < x_size)
                    curr_byte = *p_bits;
            }
        }
    }
    else
    {
        for (xx = 0; xx < x_size; xx++)
        {
            if (curr_byte & bits[bit])
            {
                p_line[xx] = 1;
                if (last_is_zero)
                    p_switches[num_switches++] = xx, last_is_zero = FALSE;
            }
            else
                last_is_zero = TRUE;
            if ((--bit) < 0)
            {
                DWORD          *p_dw_bits = (DWORD *)++ p_bits;

                bit = 7;
                while (((BYTE *) p_dw_bits < p_dw_ptr_limit) && (*p_dw_bits == 0x00000000))
                    ++p_dw_bits;
                if ((BYTE *) p_dw_bits > p_bits)
                {
                    xx += 8 * (int) ((BYTE *) p_dw_bits - p_bits);
                    p_bits = (BYTE *) p_dw_bits;
                    last_is_zero = TRUE;
                }
                if (xx < x_size)
                    curr_byte = *p_bits;
            }
        }
    }
    return (num_switches);

}


/* OK */
static int      get_mem_bits_asm_bFF(BYTE * p_line, int x_size, BYTE * p_bits,
                        int *p_switches)
{

    int             num_switches = 0;
    BYTE           *p_dw_ptr_limit = p_bits + (get_line_size(x_size) - 4);
/* INDENT OFF */

__asm{
  push ebx;
  push ecx;
  push edx;
  push edi;
  push esi;
  mov ecx,x_size;
  mov esi,offset bits;
  mov edi,p_bits;
  mov bl,[edi];
  mov bh,1;
  mov edx,7;
  xor eax,eax;
main_loop:
  cmp eax,ecx;
  jae exit_label;
  test bl,byte ptr [esi+edx];
  jnz no_set;
  push esi;
  mov esi,p_line;
  mov byte ptr [esi+eax],1;
  pop esi;
  cmp bh,0;
  je no_switch;
  push edx;
  push esi;
  mov edx,num_switches;
  inc num_switches;
  mov esi,p_switches;
  mov dword ptr[esi+edx*4],eax;
  pop esi;
  pop edx;
  mov bh,0;
  jmp no_switch;
no_set:
  mov bh,1;
no_switch:
  cmp edx,0;
  je switch_bit;
  dec edx;
  inc eax;
jmp main_loop;
switch_bit:
  mov edx,7;
  inc edi;
  push ecx;
  push edx;
  mov ecx,edi;
  mov edx,p_dw_ptr_limit;
skip_loop:
  cmp edi,edx;
  jae skip_loop_exit;
  cmp dword ptr [edi],0xffffffff;
  jne small_loop_entry;
  add edi,4;
  jmp skip_loop;
small_loop:
  cmp edi,edx;
  jae skip_loop_exit;
small_loop_entry:
  cmp byte ptr [edi],0xff;
  jne skip_loop_exit;
  inc edi;
  jmp small_loop;
skip_loop_exit:
  cmp edi,ecx;
  jbe not_skipped;
  push ebx;
  mov ebx,edi;
  sub ebx,ecx;
  shl ebx,3;
  add eax,ebx;
  pop ebx;
  mov bh,1;
not_skipped:
  pop edx;
  pop ecx;
  cmp eax,ecx
  jae exit_label;
  mov bl,[edi];
  inc eax;
  jmp main_loop;
exit_label:
  pop esi;
  pop edi;
  pop edx;
  pop ecx;
  pop ebx;
}

/* INDENT ON */

    return (num_switches);

}


/* OK */
static int      get_mem_bits_asm_b00(BYTE * p_line, int x_size, BYTE * p_bits,
                        int *p_switches)
{

    int             num_switches = 0;
    BYTE           *p_dw_ptr_limit = p_bits + (get_line_size(x_size) - 4);
/* INDENT OFF */

__asm{
  push ebx;
  push ecx;
  push edx;
  push edi;
  push esi;
  mov ecx,x_size;
  mov esi,offset bits;
  mov edi,p_bits;
  mov bl,[edi];
  mov bh,1;
  mov edx,7;
  xor eax,eax;
main_loop:
  cmp eax,ecx;
  jae exit_label;
  test bl,byte ptr [esi+edx];
  jz no_set;
  push esi;
  mov esi,p_line;
  mov byte ptr [esi+eax],1;
  pop esi;
  cmp bh,0;
  je no_switch;
  push edx;
  push esi;
  mov edx,num_switches;
  inc num_switches;
  mov esi,p_switches;
  mov dword ptr[esi+edx*4],eax;
  pop esi;
  pop edx;
  mov bh,0;
  jmp no_switch;
no_set:
  mov bh,1;
no_switch:
  cmp edx,0;
  je switch_bit;
  dec edx;
  inc eax;
jmp main_loop;
switch_bit:
  mov edx,7;
  inc edi;
  push ecx;
  push edx;
  mov ecx,edi;
  mov edx,p_dw_ptr_limit;
skip_loop:
  cmp edi,edx;
  jae skip_loop_exit;
  cmp dword ptr [edi],0x00000000;
  jne small_loop_entry;
  add edi,4;
  jmp skip_loop;
small_loop:
  cmp edi,edx;
  jae skip_loop_exit;
small_loop_entry:
  cmp byte ptr [edi],0x00;
  jne skip_loop_exit;
  inc edi;
  jmp small_loop;
skip_loop_exit:
  cmp edi,ecx;
  jbe not_skipped;
  push ebx;
  mov ebx,edi;
  sub ebx,ecx;
  shl ebx,3;
  add eax,ebx;
  pop ebx;
  mov bh,1;
not_skipped:
  pop edx;
  pop ecx;
  cmp eax,ecx
  jae exit_label;
  mov bl,[edi];
  inc eax;
  jmp main_loop;
exit_label:
  pop esi;
  pop edi;
  pop edx;
  pop ecx;
  pop ebx;
}

/* INDENT ON */

    return (num_switches);

}


/* OK */
static int      get_mem_bits_asm(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground,
                        int *p_switches)
{

    memset(p_line, 0, x_size);
    return ((back_ground != 0) ?
            get_mem_bits_asm_bFF(p_line, x_size, p_bits, p_switches) :
            get_mem_bits_asm_b00(p_line, x_size, p_bits, p_switches));

}


/* OK */
static int      do_step(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        BYTE * p_prev_mod_line, BYTE * p_curr_mod_line,
                        int (*step_check_func) (BYTE *))
{

    int             xx,
                    yy,
                    x_size = p_bmph->bih.biWidth,
                    y_size = p_bmph->bih.biHeight,
                    line_size = p_bmph->bih.biWidth,
                    img_line_size = get_line_size(p_bmph->bih.biWidth),
                    pixel_removed = 0,
                    curr_num_switches,
                    next_num_switches,
                    prev_rm_index = y_size,
                    curr_rm_index = y_size;
    int            *p_switches,
                   *p_curr_switches,
                   *p_next_switches;
    BYTE           *p_raw_ptr = bmp_get_raw_ptr(p_img_mem),
                   *p_rm_line,
                   *p_rm_lines,
                   *p_prev_rm_line,
                   *p_curr_rm_line,
                   *p_lines,
                   *p_prev_line,
                   *p_curr_line,
                   *p_next_line,
                   *p_file_prev_line,
                   *p_file_curr_line,
                   *p_file_next_line;

    if ((p_switches = (int *) malloc(2 * x_size * sizeof(int))) == NULL)
        return (-1);
    p_curr_switches = p_switches;
    p_next_switches = p_curr_switches + x_size;
    if ((p_rm_lines = (BYTE *) malloc(2 * line_size)) == NULL)
    {
        free(p_switches);
        return (-1);
    }
    memset(p_rm_lines, 0, 2 * line_size);
    p_prev_rm_line = p_rm_lines;
    p_curr_rm_line = p_prev_rm_line + line_size;
    if ((p_lines = (BYTE *) malloc(3 * line_size)) == NULL)
    {
        free(p_rm_lines);
        free(p_switches);
        return (-1);
    }
    memset(p_lines, 0, 3 * line_size);
    p_prev_line = p_lines;
    p_curr_line = p_prev_line + line_size;
    p_next_line = p_curr_line + line_size;
    p_file_next_line = get_raw_img_line(p_raw_ptr, img_line_size, 0);
    next_num_switches = get_mem_bits(p_next_line, line_size, p_file_next_line,
            back_ground, p_next_switches);
    for (yy = 0; yy < y_size; yy++)
    {
        int             ss,
                        yy_found = -1;
        BYTE           *p_next_mod,
                       *tmp_byte_ptr;
        int            *tmp_int32_ptr;
        BYTE            pix[9];

        if (yy > (prev_rm_index + 1))
        {
            p_rm_line = get_raw_img_line(p_raw_ptr, img_line_size, prev_rm_index);
            for (xx = 0; xx < x_size; xx++)
            {
                if (p_prev_rm_line[xx] == 0)
                {
                    BYTE           *p_next_one = (BYTE *) memchr(p_prev_rm_line + xx, 1, x_size - xx);

                    if (p_next_one == NULL)
                        break;
                    xx = (int) (p_next_one - p_prev_rm_line);
                }
                p_prev_mod_line[prev_rm_index] = p_curr_mod_line[prev_rm_index] = 1;
                clear_pixel(p_rm_line, xx, back_ground);
            }
        }
        if ((p_next_mod = (BYTE *) memchr(p_prev_mod_line + yy, 1, y_size - yy)) != NULL)
            yy_found = (int) (p_next_mod - p_prev_mod_line);
        if (yy_found > (yy + 2))
        {
            yy = yy_found;
            tmp_byte_ptr = p_prev_rm_line;
            p_prev_rm_line = p_curr_rm_line;
            p_curr_rm_line = tmp_byte_ptr;
            memset(p_curr_rm_line, 0, line_size);
            prev_rm_index = curr_rm_index;
            curr_rm_index = yy;
            p_file_curr_line = get_raw_img_line(p_raw_ptr, img_line_size, yy);
            p_file_prev_line = (yy > 0) ? get_raw_img_line(p_raw_ptr, img_line_size, yy - 1) : NULL;
            p_file_next_line = ((yy + 1) < y_size) ? get_raw_img_line(p_raw_ptr, img_line_size, yy + 1) : NULL;
            if (p_file_prev_line != NULL)
                get_mem_bits(p_prev_line, line_size, p_file_prev_line, back_ground,
                        p_curr_switches);
            else
                memset(p_prev_line, 0, line_size);
            curr_num_switches = get_mem_bits(p_curr_line, line_size, p_file_curr_line,
                    back_ground, p_curr_switches);
            if (p_file_next_line != NULL)
                next_num_switches = get_mem_bits(p_next_line, line_size, p_file_next_line,
                        back_ground, p_next_switches);
            else
                memset(p_next_line, 0, line_size), next_num_switches = 0;
        }
        else
        {
            tmp_byte_ptr = p_prev_rm_line;
            p_prev_rm_line = p_curr_rm_line;
            p_curr_rm_line = tmp_byte_ptr;
            memset(p_curr_rm_line, 0, line_size);
            prev_rm_index = curr_rm_index;
            curr_rm_index = yy;
            tmp_int32_ptr = p_next_switches;
            p_next_switches = p_curr_switches;
            p_curr_switches = tmp_int32_ptr;
            curr_num_switches = next_num_switches;
            p_file_curr_line = get_raw_img_line(p_raw_ptr, img_line_size, yy);
            p_file_prev_line = (yy > 0) ? get_raw_img_line(p_raw_ptr, img_line_size, yy - 1) : NULL;
            p_file_next_line = ((yy + 1) < y_size) ? get_raw_img_line(p_raw_ptr, img_line_size, yy + 1) : NULL;
            tmp_byte_ptr = p_next_line;
            p_next_line = p_prev_line;
            p_prev_line = p_curr_line;
            p_curr_line = tmp_byte_ptr;
            if (p_file_next_line != NULL)
                next_num_switches = get_mem_bits(p_next_line, line_size, p_file_next_line,
                        back_ground, p_next_switches);
            else
                memset(p_next_line, 0, line_size), next_num_switches = 0;
            if ((p_prev_mod_line[max(yy - 1, 0)] + p_prev_mod_line[yy] +
                            p_prev_mod_line[min(yy + 1, y_size)]) == 0)
                continue;
        }
        for (ss = 0; ss < curr_num_switches; ss++)
        {
            int             bound_sum,
                            switch_sum;

            for (xx = p_curr_switches[ss]; xx < x_size; xx++)
            {
                if (p_curr_line[xx] == 0)
                    break;
                pix[0] = p_curr_line[xx];
                pix[7] = (xx > 0) ? p_curr_line[xx - 1] : 0;
                pix[3] = ((xx + 1) < x_size) ? p_curr_line[xx + 1] : 0;
                if (p_file_prev_line != NULL)
                {
                    pix[1] = p_prev_line[xx];
                    pix[8] = (xx > 0) ? p_prev_line[xx - 1] : 0;
                    pix[2] = ((xx + 1) < x_size) ? p_prev_line[xx + 1] : 0;
                }
                else
                    pix[8] = pix[1] = pix[2] = 0;
                if (p_file_next_line != NULL)
                {
                    pix[5] = p_next_line[xx];
                    pix[6] = (xx > 0) ? p_next_line[xx - 1] : 0;
                    pix[4] = ((xx + 1) < x_size) ? p_next_line[xx + 1] : 0;
                }
                else
                    pix[6] = pix[5] = pix[4] = 0;
                bound_sum = (int) (pix[1] + pix[2] + pix[3] + pix[4] + pix[5] + pix[6] + pix[7] + pix[8]);
                if ((bound_sum < 2) || (bound_sum > 6))
                    continue;
                switch_sum = 0;
                if ((pix[1] == 0) && (pix[2] == 1))
                    ++switch_sum;
                if ((pix[2] == 0) && (pix[3] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[3] == 0) && (pix[4] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[4] == 0) && (pix[5] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[5] == 0) && (pix[6] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[6] == 0) && (pix[7] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[7] == 0) && (pix[8] == 1))
                    if (++switch_sum > 1)
                        continue;
                if ((pix[8] == 0) && (pix[1] == 1))
                    if (++switch_sum > 1)
                        continue;
                if (step_check_func(pix))
                    p_curr_rm_line[xx] = 1, ++pixel_removed;
            }
        }
    }
    free(p_lines);
    free(p_switches);
    if (y_size > prev_rm_index)
    {
        p_rm_line = get_raw_img_line(p_raw_ptr, img_line_size, prev_rm_index);
        for (xx = 0; xx < x_size; xx++)
        {
            if (p_prev_rm_line[xx] == 0)
            {
                BYTE           *p_next_one = (BYTE *) memchr(p_prev_rm_line + xx, 1, x_size - xx);

                if (p_next_one == NULL)
                    break;
                xx = (int) (p_next_one - p_prev_rm_line);
            }
            p_prev_mod_line[prev_rm_index] = p_curr_mod_line[prev_rm_index] = 1;
            clear_pixel(p_rm_line, xx, back_ground);
        }
    }
    if (y_size > curr_rm_index)
    {
        p_rm_line = get_raw_img_line(p_raw_ptr, img_line_size, curr_rm_index);
        for (xx = 0; xx < x_size; xx++)
        {
            if (p_curr_rm_line[xx] == 0)
            {
                BYTE           *p_next_one = (BYTE *) memchr(p_curr_rm_line + xx, 1, x_size - xx);

                if (p_next_one == NULL)
                    break;
                xx = (int) (p_next_one - p_curr_rm_line);
            }
            p_prev_mod_line[curr_rm_index] = p_curr_mod_line[curr_rm_index] = 1;
            clear_pixel(p_rm_line, xx, back_ground);
        }
    }
    free(p_rm_lines);
    return (pixel_removed);

}


/* OK */
link_list_hdr  *get_node_points(bw_bmp_header * p_bmph, BYTE * p_img_mem,
                        int back_ground)
{

    int             xx,
                    yy,
                    x_size = p_bmph->bih.biWidth,
                    y_size = p_bmph->bih.biHeight,
                    line_size = p_bmph->bih.biWidth,
                    img_line_size = get_line_size(p_bmph->bih.biWidth),
                    curr_num_switches,
                    next_num_switches;
    int            *p_switches,
                   *p_curr_switches,
                   *p_next_switches;
    link_list_hdr  *p_node_pnts_list;
    BYTE           *p_raw_ptr = bmp_get_raw_ptr(p_img_mem),
                   *p_lines,
                   *p_prev_line,
                   *p_curr_line,
                   *p_next_line,
                   *p_file_prev_line,
                   *p_file_curr_line,
                   *p_file_next_line;

    if ((p_switches = (int *) malloc(2 * x_size * sizeof(int))) == NULL)
        return (NULL);
    p_curr_switches = p_switches;
    p_next_switches = p_curr_switches + x_size;
    if ((p_node_pnts_list = ll_create_list()) == NULL)
    {
        free(p_switches);
        return (NULL);
    }
    if ((p_lines = (BYTE *) malloc(3 * line_size)) == NULL)
    {
        ll_empty_free_list(p_node_pnts_list);
        free(p_switches);
        return (NULL);
    }
    memset(p_lines, 0, 3 * line_size);
    p_prev_line = p_lines;
    p_curr_line = p_prev_line + line_size;
    p_next_line = p_curr_line + line_size;
    p_file_next_line = get_raw_img_line(p_raw_ptr, img_line_size, 0);
    next_num_switches = get_mem_bits(p_next_line, line_size, p_file_next_line,
            back_ground, p_next_switches);
    for (yy = 0; yy < y_size; yy++)
    {
        int             ss;
        BYTE           *tmp_byte_ptr;
        int            *tmp_int32_ptr;
        BYTE            pix[9];

        tmp_int32_ptr = p_next_switches;
        p_next_switches = p_curr_switches;
        p_curr_switches = tmp_int32_ptr;
        curr_num_switches = next_num_switches;
        p_file_curr_line = get_raw_img_line(p_raw_ptr, img_line_size, yy);
        p_file_prev_line = (yy > 0) ? get_raw_img_line(p_raw_ptr, img_line_size, yy - 1) : NULL;
        p_file_next_line = ((yy + 1) < y_size) ? get_raw_img_line(p_raw_ptr, img_line_size, yy + 1) : NULL;
        tmp_byte_ptr = p_next_line;
        p_next_line = p_prev_line;
        p_prev_line = p_curr_line;
        p_curr_line = tmp_byte_ptr;
        if (p_file_next_line != NULL)
            next_num_switches = get_mem_bits(p_next_line, line_size, p_file_next_line,
                    back_ground, p_next_switches);
        else
            memset(p_next_line, 0, line_size), next_num_switches = 0;
        for (ss = 0; ss < curr_num_switches; ss++)
        {
            int             bound_sum,
                            switch_sum;

            for (xx = p_curr_switches[ss]; xx < x_size; xx++)
            {
                if (p_curr_line[xx] == 0)
                    break;
                pix[0] = p_curr_line[xx];
                pix[7] = (xx > 0) ? p_curr_line[xx - 1] : 0;
                pix[3] = ((xx + 1) < x_size) ? p_curr_line[xx + 1] : 0;
                if (p_file_prev_line != NULL)
                {
                    pix[1] = p_prev_line[xx];
                    pix[8] = (xx > 0) ? p_prev_line[xx - 1] : 0;
                    pix[2] = ((xx + 1) < x_size) ? p_prev_line[xx + 1] : 0;
                }
                else
                    pix[8] = pix[1] = pix[2] = 0;
                if (p_file_next_line != NULL)
                {
                    pix[5] = p_next_line[xx];
                    pix[6] = (xx > 0) ? p_next_line[xx - 1] : 0;
                    pix[4] = ((xx + 1) < x_size) ? p_next_line[xx + 1] : 0;
                }
                else
                    pix[6] = pix[5] = pix[4] = 0;
                bound_sum = (int) (pix[1] + pix[2] + pix[3] + pix[4] + pix[5] + pix[6] + pix[7] + pix[8]);
                if ((bound_sum < 3) || (bound_sum > 5))
                    continue;
                switch_sum = 0;
                if ((pix[1] == 0) && (pix[2] == 1))
                    ++switch_sum;
                if ((pix[2] == 0) && (pix[3] == 1))
                    ++switch_sum;
                if ((pix[3] == 0) && (pix[4] == 1))
                    ++switch_sum;
                if ((pix[4] == 0) && (pix[5] == 1))
                    ++switch_sum;
                if ((pix[5] == 0) && (pix[6] == 1))
                    ++switch_sum;
                if ((pix[6] == 0) && (pix[7] == 1))
                    ++switch_sum;
                if ((pix[7] == 0) && (pix[8] == 1))
                    ++switch_sum;
                if ((pix[8] == 0) && (pix[1] == 1))
                    ++switch_sum;
                if (switch_sum > 2)
                {
                    img_point       pnt = {xx, yy};

                    if (!ll_add_list_data(p_node_pnts_list, TG_TAIL, &pnt))
                    {
                        free(p_lines);
                        ll_empty_free_list(p_node_pnts_list);
                        free(p_switches);
                        return (NULL);
                    }
                }
            }
        }
    }
    free(p_lines);
    free(p_switches);
    return (p_node_pnts_list);

}
