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
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include"ras2vec.h"
#include"dbll_list.h"
#include"util.h"

static int      bih_num_colors(BITMAPINFOHEADER * pbi);
static int      bih_palette_size(BITMAPINFOHEADER * pbi);
static int      bih_line_size(BITMAPINFOHEADER * pbi);
static int      img_file_get_background(FILE * fp_img, int x_size, int y_size,
                        int x_step, int y_step);

/* OK */
static int      bih_num_colors(BITMAPINFOHEADER * pbi)
{

    int             bit_count;
    BITMAPCOREHEADER *pbc;

    pbc = (BITMAPCOREHEADER *) pbi;
    if (pbi->biSize != sizeof(BITMAPCOREHEADER))
    {
        if (pbi->biClrUsed != 0)
            return ((int) pbi->biClrUsed);
        bit_count = (int) pbi->biBitCount;
    }
    else
        bit_count = (int) pbc->bcBitCount;
    switch (bit_count)
    {
        case (1):
            return (2);

        case (4):
            return (16);

        case (8):
            return (256);
    }
    return (0);

}

/* OK */
static int      bih_palette_size(BITMAPINFOHEADER * pbi)
{

    int             num_colors;

    num_colors = bih_num_colors(pbi);
    if (pbi->biSize == sizeof(BITMAPCOREHEADER))
        return (num_colors * sizeof(RGBTRIPLE));
    return (num_colors * sizeof(RGBQUAD));

}

/* OK */
static int      bih_line_size(BITMAPINFOHEADER * pbi)
{

    return (((pbi->biWidth * pbi->biBitCount + 31) / 32) * 4);

}

/* OK */
static int      img_file_get_background(FILE * fp_img, int x_size, int y_size,
                        int x_step, int y_step)
{

    int             xx,
                    yy;
    int             line_size,
                    num_ones = 0,
                    num_zeros = 0;
    BYTE           *p_line;

    line_size = ((x_size + 31) / 32) * 4;
    if ((p_line = (BYTE *) malloc(line_size)) == NULL)
        return (-1);
    for (yy = 0; yy < y_size; yy += y_step)
    {
        if (!fread(p_line, line_size, 1, fp_img))
        {
            free(p_line);
            return (-1);
        }
        fseek(fp_img, (y_step - 1) * line_size, SEEK_CUR);
        for (xx = 0; xx < x_size; xx += x_step)
        {
            if (read_bit(p_line, xx))
                ++num_ones;
            else
                ++num_zeros;
        }
    }
    free(p_line);
    return ((num_ones > num_zeros) ? 1 : 0);

}

/* OK */
int             bmp_image_to_raw_image(char *bmp_file_name, char *raw_file_name)
{

    int             line_size;
    unsigned int    readed;
    FILE           *fp_bmp,
                   *fp_raw;
    char           *line_buffer;
    img_file_header ifh;
    BITMAPINFOHEADER hbmi;
    BITMAPFILEHEADER hbmf;

    if ((fp_bmp = fopen(bmp_file_name, "rb")) == NULL)
        return (FALSE);
    if (!fread(&hbmf, sizeof(BITMAPFILEHEADER), 1, fp_bmp))
    {
        fclose(fp_bmp);
        return (FALSE);
    }
    if (hbmf.bfType != *(WORD *) "BM")
    {
        fclose(fp_bmp);
        return (FALSE);
    }
    if (!fread(&hbmi, sizeof(BITMAPINFOHEADER), 1, fp_bmp))
    {
        fclose(fp_bmp);
        return (FALSE);
    }
    if ((hbmi.biSize != sizeof(BITMAPINFOHEADER)) ||
            (hbmi.biCompression != BI_RGB) || ((hbmi.biBitCount * hbmi.biPlanes) != 1))
    {
        fclose(fp_bmp);
        return (FALSE);
    }
    ifh.x_size = hbmi.biWidth;
    ifh.y_size = hbmi.biHeight;
    line_size = bih_line_size(&hbmi);
    if ((line_buffer = (char *) malloc(line_size)) == NULL)
    {
        fclose(fp_bmp);
        return (FALSE);
    }
    fseek(fp_bmp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
            bih_palette_size(&hbmi), SEEK_SET);
    if ((ifh.back_ground = img_file_get_background(fp_bmp, hbmi.biWidth, hbmi.biHeight,
                            8, 8)) < 0)
    {
        free(line_buffer);
        fclose(fp_bmp);
        return (FALSE);
    }
    if ((fp_raw = fopen(raw_file_name, "wb")) == NULL)
    {
        free(line_buffer);
        fclose(fp_bmp);
        return (FALSE);
    }
    if (!fwrite(&ifh, sizeof(ifh), 1, fp_raw))
    {
        fclose(fp_raw);
        free(line_buffer);
        fclose(fp_bmp);
        return (FALSE);
    }
    fseek(fp_bmp, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
            bih_palette_size(&hbmi), SEEK_SET);
    do
    {
        readed = fread(line_buffer, 1, line_size, fp_bmp);
        if (readed > 0)
            fwrite(line_buffer, line_size, 1, fp_raw);
    } while (readed == (unsigned int) (line_size));
    fclose(fp_raw);
    free(line_buffer);
    fclose(fp_bmp);
    return (TRUE);

}
