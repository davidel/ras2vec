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
#include<limits.h>
#include"ras2vec.h"
#include"dbll_list.h"
#include"himage.h"
#include"flushpoly.h"
#include"thinner.h"
#include"log.h"
#include"util.h"


/* OK */
char           *get_temp_file(char *file_name)
{

    char            temp_path[MAX_PATH];

    GetTempPath(sizeof(temp_path), temp_path);
    GetTempFileName(temp_path, "r2v", 0, file_name);
    return (file_name);

}


/* OK */
int LIB_PROC    dxf_poly_dump(char *dxf_file_name, char *poly_file_name, double x_scale,
                        double y_scale, char *layer_name, int color)
{

    FILE           *fp_dxf,
                   *fp_poly;

    if ((fp_poly = fopen(poly_file_name, "rt")) == NULL)
        return (FALSE);
    if ((fp_dxf = fopen(dxf_file_name, "wt")) == NULL)
    {
        fclose(fp_poly);
        return (FALSE);
    }
    fprintf(fp_dxf, "0\n"
            "SECTION\n"
            "2\n"
            "HEADER\n"
            "0\n"
            "ENDSEC\n"
            "0\n"
            "SECTION\n"
            "2\n"
            "TABLES\n"
            "0\n"
            "ENDSEC\n"
            "0\n"
            "SECTION\n"
            "2\n"
            "BLOCKS\n"
            "0\n"
            "ENDSEC\n"
            "0\n"
            "SECTION\n"
            "2\n"
            "ENTITIES\n");
    while (read_start_polyline(fp_poly))
    {
        img_point       pnt;

        fprintf(fp_dxf, "0\n"
                "POLYLINE\n"
                "8\n"
                "%s\n"
                "62\n"
                "%d\n"
                "66\n"
                "1\n"
                "70\n"
                "8\n", layer_name, color);
        while (read_img_point(fp_poly, &pnt))
        {
            fprintf(fp_dxf, "0\n"
                    "VERTEX\n"
                    "8\n"
                    "%s\n"
                    "62\n"
                    "%d\n"
                    "70\n"
                    "32\n"
                    "10\n"
                    "%lf\n"
                    "20\n"
                    "%lf\n"
                    "30\n"
                    "0\n", layer_name, color, x_scale * (double) pnt.x,
                    y_scale * (double) pnt.y);
        }
        fprintf(fp_dxf, "0\n"
                "SEQEND\n");
    }
    fprintf(fp_dxf, "0\n"
            "ENDSEC\n"
            "0\n"
            "EOF\n");
    fclose(fp_dxf);
    fclose(fp_poly);
    return (TRUE);

}


/* OK */
int LIB_PROC    hpgl_poly_dump(char *hpgl_file_name, char *poly_file_name, double x_scale,
                        double y_scale, int color)
{

    FILE           *fp_hpgl,
                   *fp_poly;

    if ((fp_poly = fopen(poly_file_name, "rt")) == NULL)
        return (FALSE);
    if ((fp_hpgl = fopen(hpgl_file_name, "wt")) == NULL)
    {
        fclose(fp_poly);
        return (FALSE);
    }
    fprintf(fp_hpgl, "IN;SP1;\n");
    while (read_start_polyline(fp_poly))
    {
        int             number_of_points = 0;
        img_point       pnt;

        if (!read_img_point(fp_poly, &pnt))
            continue;
        ++number_of_points;
        fprintf(fp_hpgl, "PU%.0lf,%.0lf;", (double) pnt.x * x_scale,
                (double) pnt.y * y_scale);
        while (read_img_point(fp_poly, &pnt))
        {
            ++number_of_points;
            if (number_of_points == 2)
                fprintf(fp_hpgl, "PD%.0lf,%.0lf", (double) pnt.x * x_scale,
                        (double) pnt.y * y_scale);
            else
                fprintf(fp_hpgl, ",%.0lf,%.0lf", (double) pnt.x * x_scale,
                        (double) pnt.y * y_scale);
        }
        if (number_of_points > 1)
            fprintf(fp_hpgl, ";\n");
    }
    fprintf(fp_hpgl, "PU;SP0;\n");
    fclose(fp_hpgl);
    fclose(fp_poly);
    return (TRUE);

}


/* OK */
int LIB_PROC    emf_poly_dump(char *emf_file_name, char *poly_file_name, double x_scale,
                        double y_scale, COLORREF color)
{

    HDC             hdc;
    HPEN            hpen = CreatePen(PS_SOLID, 0, color),
                    prev_hpen;
    FILE           *fp_poly;

    if ((fp_poly = fopen(poly_file_name, "rt")) == NULL)
        return (FALSE);
    if ((hdc = CreateEnhMetaFile(NULL, emf_file_name, NULL,
                            "Raster To Vector Library by Davide Libenzi\0\0")) == NULL)
    {
        fclose(fp_poly);
        return (FALSE);
    }
    prev_hpen = SelectObject(hdc, hpen);
    while (read_start_polyline(fp_poly))
    {
        img_point       pnt;

        if (!read_img_point(fp_poly, &pnt))
            continue;
        MoveToEx(hdc, (int) (pnt.x * x_scale), - (int) (pnt.y * y_scale), NULL);
        while (read_img_point(fp_poly, &pnt))
            LineTo(hdc, (int) (pnt.x * x_scale), - (int) (pnt.y * y_scale));
    }
    SelectObject(hdc, prev_hpen);
    DeleteObject(hpen);
    DeleteEnhMetaFile(CloseEnhMetaFile(hdc));
    fclose(fp_poly);
    return (TRUE);

}
