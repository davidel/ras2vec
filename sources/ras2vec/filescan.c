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
#include"dbll_list.h"
#include"himage.h"
#include"thinner.h"
#include"flushpoly.h"
#include"filescan.h"
#include"log.h"
#include"util.h"





#define RESYNC_FREQUENCY       32
#define DELETED_POLYLINE       ((void *)(-1))





typedef struct ins_polyline_record
{
    int             insert_location;
    img_point       link_pnt,
                    pnt;
    polyline       *p_polyline;
}               ins_polyline;
typedef struct scan_data_record
{
    int             x_size,
                    y_size;
    int             img_line_size,
                    line_size;
    int             current_line;
    int             back_ground;
    double          pnt_error_tollerance,
                    min_polyline_lenght;
    img_data        imgd;
    BYTE           *p_img_mem,
                   *p_raw_ptr;
    BYTE           *p_lines,
                   *p_line,
                   *p_next_line,
                   *p_nnext_line;
    BYTE           *v_open;
    FILE           *fp_poly;
    link_list_hdr  *p_polylines_list;
    link_list_hdr **pp_gating_polylines;
    int             number_of_polylines;
}               scan_data;





static int      add_point_in_poly(polyline * p_ins_polyline, img_point * p_imgp,
                        int insert_location);
static BYTE    *tx_bits_mem(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground);
static scan_data *alloc_scan_data(char *img_file_name, char *poly_file_name,
                        double pnt_error_tollerance,
                        double poly_lenght_factor);
static int      free_scan_data(scan_data * p_scd);
static int      add_poly_gate(scan_data * p_scd, int gate, polyline * p_polyline);
static int      remove_poly_gate(scan_data * p_scd, int gate, polyline * p_polyline);
static int      try_to_join_polylines(scan_data * p_scd, polyline * p_owner_polyline,
                        img_point * p_join_pnt, int pnt_location);
static int      add_line(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1);
static int      get_insert_link(link_list_hdr * p_gating_poly_list,
                        img_point * p_img_pnt0, img_point * p_img_pnt1,
                        ins_polyline * p_iply);
static int      get_insert_info(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1, ins_polyline * p_iply);
static int      create_new_polyline(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1);
static int      remove_polyline(scan_data * p_scd, polyline * p_polyline);
static int      transfer_polyline_points(polyline * p_dest_polyline,
                        polyline * p_src_polyline, int insert_location,
                        int direction);
static int      resync_polyline_lists(scan_data * p_scd);
static int      flush_all_polylines(scan_data * p_scd);
static int      next_line(scan_data * p_scd);
static int      scan_current_line(scan_data * p_scd);





/* OK */
static int      add_point_in_poly(polyline * p_ins_polyline, img_point * p_imgp,
                        int insert_location)
{

    switch (insert_location)
    {
 case (TG_HEAD):
            {
                if ((p_ins_polyline->prev_pnt0.x == p_ins_polyline->pnt0.x) &&
                        (p_ins_polyline->pnt0.x == p_imgp->x))
                {
                    p_ins_polyline->last_pnt0 = p_ins_polyline->pnt0;
                    if (!ll_set_list_user_data(p_ins_polyline->p_poly_list, (link_loc) insert_location,
                                    p_imgp))
                        return (FALSE);
                    p_ins_polyline->pnt0 = *p_imgp;
                }
                else
                {
                    if ((p_ins_polyline->prev_pnt0.y == p_ins_polyline->pnt0.y) &&
                            (p_ins_polyline->pnt0.y == p_imgp->y))
                    {
                        p_ins_polyline->last_pnt0 = p_ins_polyline->pnt0;
                        if (!ll_set_list_user_data(p_ins_polyline->p_poly_list, (link_loc) insert_location,
                                        p_imgp))
                            return (FALSE);
                        p_ins_polyline->pnt0 = *p_imgp;
                    }
                    else
                    {
                        if (!ll_add_list_data(p_ins_polyline->p_poly_list, insert_location, p_imgp))
                            return (FALSE);
                        p_ins_polyline->prev_pnt0 = p_ins_polyline->last_pnt0 = p_ins_polyline->pnt0;
                        p_ins_polyline->pnt0 = *p_imgp;
                    }
                }
            }
            break;

        case (TG_TAIL):
            {
                if ((p_ins_polyline->prev_pnt1.x == p_ins_polyline->pnt1.x) &&
                        (p_ins_polyline->pnt1.x == p_imgp->x))
                {
                    p_ins_polyline->last_pnt1 = p_ins_polyline->pnt1;
                    if (!ll_set_list_user_data(p_ins_polyline->p_poly_list, (link_loc) insert_location,
                                    p_imgp))
                        return (FALSE);
                    p_ins_polyline->pnt1 = *p_imgp;
                }
                else
                {
                    if ((p_ins_polyline->prev_pnt1.y == p_ins_polyline->pnt1.y) &&
                            (p_ins_polyline->pnt1.y == p_imgp->y))
                    {
                        p_ins_polyline->last_pnt1 = p_ins_polyline->pnt1;
                        if (!ll_set_list_user_data(p_ins_polyline->p_poly_list, (link_loc) insert_location,
                                        p_imgp))
                            return (FALSE);
                        p_ins_polyline->pnt1 = *p_imgp;
                    }
                    else
                    {
                        if (!ll_add_list_data(p_ins_polyline->p_poly_list, insert_location, p_imgp))
                            return (FALSE);
                        p_ins_polyline->prev_pnt1 = p_ins_polyline->last_pnt1 = p_ins_polyline->pnt1;
                        p_ins_polyline->pnt1 = *p_imgp;
                    }
                }
            }
            break;

        default:
            return (FALSE);
    }
    return (TRUE);

}

/* OK */
static BYTE    *tx_bits_mem(BYTE * p_line, int x_size, BYTE * p_bits, int back_ground)
{

    int             ii,
                    bit = 7;
    register BYTE   curr_byte = *p_bits;
    static BYTE     bits[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

    memset(p_line, 0, x_size + 2);
    if (back_ground != 0)
    {
        for (ii = 0; ii < x_size; ii++)
        {
            if (!(curr_byte & bits[bit]))
                p_line[ii + 1] = 1;
            if ((--bit) < 0)
            {
                DWORD          *p_dw_bits = (DWORD *)++ p_bits;

                bit = 7;
                while ((ii < x_size) && (*p_dw_bits == 0xffffffff))
                    ++p_dw_bits, ii += 32;
                p_bits = (BYTE *) p_dw_bits;
                if (ii < x_size)
                    curr_byte = *p_bits;
            }
        }
    }
    else
    {
        for (ii = 0; ii < x_size; ii++)
        {
            if (curr_byte & bits[bit])
                p_line[ii + 1] = 1;
            if ((--bit) < 0)
            {
                DWORD          *p_dw_bits = (DWORD *)++ p_bits;

                bit = 7;
                while ((ii < x_size) && (*p_dw_bits == 0x00000000))
                    ++p_dw_bits, ii += 32;
                p_bits = (BYTE *) p_dw_bits;
                if (ii < x_size)
                    curr_byte = *p_bits;
            }
        }
    }
    return (p_line);

}

/* OK */
static scan_data *alloc_scan_data(char *img_file_name, char *poly_file_name,
                        double pnt_error_tollerance,
                        double poly_lenght_factor)
{

    int             ii;
    scan_data      *p_scd;
    BYTE           *p_img_line;
    bw_bmp_header   bmph;

    if ((p_scd = (scan_data *) malloc(sizeof(scan_data))) == NULL)
        return (NULL);
    memset(p_scd, 0, sizeof(scan_data));
    if ((p_scd->p_img_mem = (BYTE *) get_image(img_file_name, IMAGE_OPEN_READ,
                            &p_scd->imgd)) == NULL)
    {
        free(p_scd);
        return (NULL);
    }
    bmph = *((bw_bmp_header *) p_scd->p_img_mem);
    if ((bmph.bfh.bfType != *((WORD *) "BM")) ||
            (bmph.bih.biSize != sizeof(BITMAPINFOHEADER)) ||
            (bmph.bih.biCompression != BI_RGB) || (bmph.bih.biBitCount != 1) ||
            (bmph.bih.biPlanes != 1) || (bmph.bih.biClrUsed != 2))
    {
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    p_scd->p_raw_ptr = bmp_get_raw_ptr(p_scd->p_img_mem);
    p_scd->x_size = bmph.bih.biWidth;
    p_scd->y_size = bmph.bih.biHeight;
    p_scd->back_ground = bmp_file_get_background(&bmph, p_scd->p_img_mem, 100, 100);
    p_scd->pnt_error_tollerance = pnt_error_tollerance;
    p_scd->min_polyline_lenght = (poly_lenght_factor > 0.0) ?
            (((double) max(p_scd->x_size, p_scd->y_size)) / poly_lenght_factor) : 1.0;
    p_scd->line_size = p_scd->x_size + 2;
    p_scd->img_line_size = get_line_size(p_scd->x_size);
    if ((p_scd->p_lines = (BYTE *) malloc(3 * p_scd->line_size)) == NULL)
    {
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    memset(p_scd->p_lines, 0, 3 * p_scd->line_size);
    p_scd->p_line = p_scd->p_lines;
    p_scd->p_next_line = p_scd->p_line + p_scd->line_size;
    p_scd->p_nnext_line = p_scd->p_next_line + p_scd->line_size;
    if ((p_scd->v_open = (BYTE *) malloc(p_scd->line_size)) == NULL)
    {
        free(p_scd->p_lines);
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    memset(p_scd->v_open, 0, p_scd->line_size);
    p_img_line = get_raw_img_line(p_scd->p_raw_ptr, p_scd->img_line_size, 0);
    tx_bits_mem(p_scd->p_next_line, p_scd->x_size, p_img_line, p_scd->back_ground);
    if (p_scd->y_size > 1)
    {
        p_img_line = get_raw_img_line(p_scd->p_raw_ptr, p_scd->img_line_size, 1);
        tx_bits_mem(p_scd->p_nnext_line, p_scd->x_size, p_img_line, p_scd->back_ground);
    }
    p_scd->current_line = 0;
    if ((p_scd->p_polylines_list = ll_create_list()) == NULL)
    {
        free(p_scd->v_open);
        free(p_scd->p_lines);
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    if ((p_scd->pp_gating_polylines = (link_list_hdr **) malloc((p_scd->x_size + 2) *
                            sizeof(link_list_hdr *))) == NULL)
    {
        ll_purge_list(p_scd->p_polylines_list);
        free(p_scd->v_open);
        free(p_scd->p_lines);
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    for (ii = 0; ii < (p_scd->x_size + 2); ii++)
        p_scd->pp_gating_polylines[ii] = ll_create_list();
    if ((p_scd->fp_poly = fopen(poly_file_name, "wt")) == NULL)
    {
        for (ii = 0; ii < (p_scd->x_size + 2); ii++)
            if (p_scd->pp_gating_polylines[ii] != NULL)
                ll_purge_list(p_scd->pp_gating_polylines[ii]);
        free(p_scd->pp_gating_polylines);
        ll_purge_list(p_scd->p_polylines_list);
        free(p_scd->v_open);
        free(p_scd->p_lines);
        free_image(&p_scd->imgd);
        free(p_scd);
        return (NULL);
    }
    p_scd->number_of_polylines = 0;
    return (p_scd);

}

/* OK */
static int      free_scan_data(scan_data * p_scd)
{

    if (p_scd->p_polylines_list != NULL)
        flush_all_polylines(p_scd);
    if (p_scd->fp_poly != NULL)
        fclose(p_scd->fp_poly), p_scd->fp_poly = NULL;
    if (p_scd->v_open != NULL)
        free(p_scd->v_open), p_scd->v_open = NULL;
    if (p_scd->p_lines != NULL)
        free(p_scd->p_lines), p_scd->p_lines = NULL;
    if (p_scd->pp_gating_polylines != NULL)
    {
        int             ii;

        for (ii = 0; ii < (p_scd->x_size + 2); ii++)
            if (p_scd->pp_gating_polylines[ii] != NULL)
                ll_empty_free_list(p_scd->pp_gating_polylines[ii]),
                        p_scd->pp_gating_polylines[ii] = NULL;
        free(p_scd->pp_gating_polylines), p_scd->pp_gating_polylines = NULL;
    }
    free_image(&p_scd->imgd);
    free(p_scd);
    return (TRUE);

}

/* OK */
static int      add_poly_gate(scan_data * p_scd, int gate, polyline * p_polyline)
{

    link_list_hdr  *p_gating_poly_list;

    if ((gate < 0) || (gate >= (p_scd->x_size + 2)))
        return (FALSE);
    p_gating_poly_list = p_scd->pp_gating_polylines[gate];
    ll_set_list_currpntr(p_gating_poly_list, TG_HEAD);
    do
    {
        polyline       *p_curr_polyline;

        if ((p_curr_polyline = (polyline *) ll_get_list_data(p_gating_poly_list)) == NULL)
            break;
        if (p_curr_polyline == p_polyline)
            return (TRUE);
        if (p_curr_polyline == DELETED_POLYLINE)
        {
            ll_set_list_data(p_gating_poly_list, p_polyline);
            return (TRUE);
        }
    } while (ll_set_list_currpntr(p_gating_poly_list, TG_AFTER) == TG_AFTER);
    return (ll_add_list_item(p_gating_poly_list, TG_HEAD, p_polyline, 0));

}

/* OK */
static int      remove_poly_gate(scan_data * p_scd, int gate, polyline * p_polyline)
{

    link_list_hdr  *p_gating_poly_list;

    if ((gate < 0) || (gate >= (p_scd->x_size + 2)))
        return (FALSE);
    p_gating_poly_list = p_scd->pp_gating_polylines[gate];
    ll_set_list_currpntr(p_gating_poly_list, TG_HEAD);
    do
    {
        polyline       *p_curr_polyline;

        if ((p_curr_polyline = (polyline *) ll_get_list_data(p_gating_poly_list)) == NULL)
            break;
        if (p_curr_polyline == p_polyline)
            ll_set_list_data(p_gating_poly_list, DELETED_POLYLINE);
    } while (ll_set_list_currpntr(p_gating_poly_list, TG_AFTER) == TG_AFTER);
    return (TRUE);

}

/* OK */
static int      try_to_join_polylines(scan_data * p_scd, polyline * p_owner_polyline,
                        img_point * p_join_pnt, int pnt_location)
{

    link_list_hdr  *p_gating_poly_list = p_scd->pp_gating_polylines[p_join_pnt->x];

    ll_set_list_currpntr(p_gating_poly_list, TG_HEAD);
    do
    {
        polyline       *p_polyline;

        if ((p_polyline = (polyline *) ll_get_list_data(p_gating_poly_list)) == NULL)
            break;
        if ((p_polyline == p_owner_polyline) || (p_polyline == DELETED_POLYLINE))
            continue;
        if ((pnt_location == TG_HEAD) && same_point(&p_polyline->pnt1, p_join_pnt))
        {
            remove_poly_gate(p_scd, p_owner_polyline->pnt0.x, p_owner_polyline);
            if (!transfer_polyline_points(p_owner_polyline, p_polyline, TG_HEAD, -1))
                return (FALSE);
            add_poly_gate(p_scd, p_owner_polyline->pnt0.x, p_owner_polyline);
            remove_poly_gate(p_scd, p_polyline->pnt0.x, p_polyline);
            remove_poly_gate(p_scd, p_polyline->pnt1.x, p_polyline);
            remove_polyline(p_scd, p_polyline);
            return (TRUE);
        }
        if ((pnt_location == TG_TAIL) && same_point(&p_polyline->pnt0, p_join_pnt))
        {
            remove_poly_gate(p_scd, p_owner_polyline->pnt1.x, p_owner_polyline);
            if (!transfer_polyline_points(p_owner_polyline, p_polyline, TG_TAIL, +1))
                return (FALSE);
            add_poly_gate(p_scd, p_owner_polyline->pnt1.x, p_owner_polyline);
            remove_poly_gate(p_scd, p_polyline->pnt0.x, p_polyline);
            remove_poly_gate(p_scd, p_polyline->pnt1.x, p_polyline);
            remove_polyline(p_scd, p_polyline);
            return (TRUE);
        }
    } while (ll_set_list_currpntr(p_gating_poly_list, TG_AFTER) == TG_AFTER);
    return (FALSE);

}

/* OK */
static int      add_line(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1)
{

    ins_polyline    iply;

    if (get_insert_info(p_scd, p_img_pnt0, p_img_pnt1, &iply))
    {
        if (!add_point_in_poly(iply.p_polyline, &iply.pnt, iply.insert_location))
            return (FALSE);
        switch (line_type(p_img_pnt0, p_img_pnt1))
        {
            case (HORIZONTAL_LINE):
                remove_poly_gate(p_scd, iply.link_pnt.x, iply.p_polyline);
                add_poly_gate(p_scd, iply.pnt.x, iply.p_polyline);
                break;

            case (VERTICAL_LINE):
                break;
        }
        try_to_join_polylines(p_scd, iply.p_polyline, &iply.pnt, iply.insert_location);
        return (TRUE);
    }
    return (create_new_polyline(p_scd, p_img_pnt0, p_img_pnt1));

}

/* OK */
static int      get_insert_link(link_list_hdr * p_gating_poly_list,
                        img_point * p_img_pnt0, img_point * p_img_pnt1,
                        ins_polyline * p_iply)
{

    ll_set_list_currpntr(p_gating_poly_list, TG_HEAD);
    do
    {
        polyline       *p_polyline;

        if ((p_polyline = (polyline *) ll_get_list_data(p_gating_poly_list)) == NULL)
            break;
        if (p_polyline == DELETED_POLYLINE)
            continue;
        if (same_point(&p_polyline->pnt1, p_img_pnt0))
        {
            if (same_point(&p_polyline->pnt0, p_img_pnt1))
            {
                if ((p_img_pnt1->x > p_img_pnt0->x) || (p_img_pnt1->y > p_img_pnt0->y))
                {
                    p_iply->p_polyline = p_polyline;
                    p_iply->insert_location = TG_TAIL;
                    p_iply->link_pnt = *p_img_pnt0;
                    p_iply->pnt = *p_img_pnt1;
                }
                else
                {
                    p_iply->p_polyline = p_polyline;
                    p_iply->insert_location = TG_HEAD;
                    p_iply->link_pnt = *p_img_pnt1;
                    p_iply->pnt = *p_img_pnt0;
                }
                return (TRUE);
            }
            else
            {
                p_iply->p_polyline = p_polyline;
                p_iply->insert_location = TG_TAIL;
                p_iply->link_pnt = *p_img_pnt0;
                p_iply->pnt = *p_img_pnt1;
                return (TRUE);
            }
        }
        else
        {
            if (same_point(&p_polyline->pnt0, p_img_pnt1))
            {
                p_iply->p_polyline = p_polyline;
                p_iply->insert_location = TG_HEAD;
                p_iply->link_pnt = *p_img_pnt1;
                p_iply->pnt = *p_img_pnt0;
                return (TRUE);
            }
        }
    } while (ll_set_list_currpntr(p_gating_poly_list, TG_AFTER) == TG_AFTER);
    return (FALSE);

}

/* OK */
static int      get_insert_info(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1, ins_polyline * p_iply)
{

    link_list_hdr  *p_gating_poly_list0 = p_scd->pp_gating_polylines[p_img_pnt0->x],
                   *p_gating_poly_list1 = p_scd->pp_gating_polylines[p_img_pnt1->x];

    p_iply->p_polyline = NULL;
    if (get_insert_link(p_gating_poly_list0, p_img_pnt0, p_img_pnt1, p_iply))
        return (TRUE);
    return ((p_gating_poly_list0 != p_gating_poly_list1) ?
            get_insert_link(p_gating_poly_list1, p_img_pnt0, p_img_pnt1, p_iply) : FALSE);

}

/* OK */
static int      create_new_polyline(scan_data * p_scd, img_point * p_img_pnt0,
                        img_point * p_img_pnt1)
{

    polyline       *p_polyline;

    if ((p_polyline = (polyline *) malloc(sizeof(polyline))) == NULL)
        return (FALSE);
    if ((p_polyline->p_poly_list = ll_create_list()) == NULL)
    {
        free(p_polyline);
        return (FALSE);
    }
    p_polyline->pnt0 = p_polyline->last_pnt1 = p_polyline->prev_pnt1 = *p_img_pnt0;
    p_polyline->pnt1 = p_polyline->last_pnt0 = p_polyline->prev_pnt0 = *p_img_pnt1;
    if (!ll_add_list_data(p_polyline->p_poly_list, TG_HEAD, &p_polyline->pnt0))
    {
        ll_empty_free_list(p_polyline->p_poly_list);
        free(p_polyline);
        return (FALSE);
    }
    if (!ll_add_list_data(p_polyline->p_poly_list, TG_TAIL, &p_polyline->pnt1))
    {
        ll_empty_free_list(p_polyline->p_poly_list);
        free(p_polyline);
        return (FALSE);
    }
    if (!ll_add_list_item(p_scd->p_polylines_list, TG_HEAD, p_polyline, 1))
    {
        ll_empty_free_list(p_polyline->p_poly_list);
        free(p_polyline);
        return (FALSE);
    }
    switch (line_type(p_img_pnt0, p_img_pnt1))
    {
        case (HORIZONTAL_LINE):
            add_poly_gate(p_scd, p_img_pnt0->x, p_polyline);
            add_poly_gate(p_scd, p_img_pnt1->x, p_polyline);
            break;

        case (VERTICAL_LINE):
            add_poly_gate(p_scd, p_img_pnt0->x, p_polyline);
            break;
    }
    return (TRUE);

}

/* OK */
static int      remove_polyline(scan_data * p_scd, polyline * p_polyline)
{

    ll_set_list_currpntr(p_scd->p_polylines_list, TG_HEAD);
    do
    {
        polyline       *p_curr_polyline;

        if ((p_curr_polyline = (polyline *) ll_get_list_data(p_scd->p_polylines_list)) == NULL)
            break;
        if (p_curr_polyline == p_polyline)
        {
            ll_empty_free_list(p_curr_polyline->p_poly_list);
            free(ll_delete_list_item(p_scd->p_polylines_list, TG_CURRENT, TG_HEAD));
            return (TRUE);
        }
    } while (ll_set_list_currpntr(p_scd->p_polylines_list, TG_AFTER) == TG_AFTER);
    return (FALSE);

}

/* OK */
static int      transfer_polyline_points(polyline * p_dest_polyline,
                        polyline * p_src_polyline, int insert_location,
                        int direction)
{

    int             points_count = 0;
    img_point       pnt;

    switch (direction)
    {
        case (+1):
            {
                ll_set_list_currpntr(p_src_polyline->p_poly_list, TG_HEAD);
                do
                {
                    if (!ll_get_list_user_data(p_src_polyline->p_poly_list, &pnt))
                        break;
                    if (points_count++ > 0)
                        if (!add_point_in_poly(p_dest_polyline, &pnt, insert_location))
                            return (FALSE);
                } while (ll_set_list_currpntr(p_src_polyline->p_poly_list, TG_AFTER) == TG_AFTER);
            }
            break;

        case (-1):
            {
                ll_set_list_currpntr(p_src_polyline->p_poly_list, TG_TAIL);
                do
                {
                    if (!ll_get_list_user_data(p_src_polyline->p_poly_list, &pnt))
                        break;
                    if (points_count++ > 0)
                        if (!add_point_in_poly(p_dest_polyline, &pnt, insert_location))
                            return (FALSE);
                } while (ll_set_list_currpntr(p_src_polyline->p_poly_list, TG_BEFORE) == TG_BEFORE);
            }
            break;

        default:
            return (FALSE);
    }
    return (TRUE);

}

/* OK */
static int      resync_polyline_lists(scan_data * p_scd)
{

    polyline       *p_polyline;

    ll_set_list_currpntr(p_scd->p_polylines_list, TG_HEAD);
    do
    {
        int             deleted;

        do
        {
            deleted = FALSE;
            if ((p_polyline = (polyline *) ll_get_list_data(p_scd->p_polylines_list)) == NULL)
                break;
            if (same_point(&p_polyline->pnt0, &p_polyline->pnt1) &&
                    (p_scd->current_line > (max(p_polyline->pnt0.y, p_polyline->pnt1.y) + 1)))
            {
                if (opt_flush_polyline(p_scd->fp_poly, p_polyline->p_poly_list,
                                p_scd->pnt_error_tollerance, p_scd->min_polyline_lenght))
                    ++p_scd->number_of_polylines;
                remove_poly_gate(p_scd, p_polyline->pnt0.x, p_polyline);
                remove_poly_gate(p_scd, p_polyline->pnt1.x, p_polyline);
                ll_empty_free_list(p_polyline->p_poly_list);
                free(ll_delete_list_item(p_scd->p_polylines_list, TG_CURRENT, TG_HEAD));
                deleted = TRUE;
            }
        } while (deleted);
    } while (ll_set_list_currpntr(p_scd->p_polylines_list, TG_AFTER) == TG_AFTER);
    return (TRUE);

}

/* OK */
static int      flush_all_polylines(scan_data * p_scd)
{

    polyline       *p_polyline;

    ll_set_list_currpntr(p_scd->p_polylines_list, TG_HEAD);
    while ((p_polyline = (polyline *)
                    ll_delete_list_item(p_scd->p_polylines_list, TG_CURRENT, TG_AFTER)) != NULL)
    {
        if (opt_flush_polyline(p_scd->fp_poly, p_polyline->p_poly_list,
                        p_scd->pnt_error_tollerance, p_scd->min_polyline_lenght))
            ++p_scd->number_of_polylines;
        remove_poly_gate(p_scd, p_polyline->pnt0.x, p_polyline);
        remove_poly_gate(p_scd, p_polyline->pnt1.x, p_polyline);
        ll_empty_free_list(p_polyline->p_poly_list);
        free(p_polyline);
    }
    ll_purge_list(p_scd->p_polylines_list);
    p_scd->p_polylines_list = NULL;
    return (TRUE);

}

/* OK */
static int      next_line(scan_data * p_scd)
{

    BYTE           *p_img_line,
                   *tmp_byte_ptr;

    ++p_scd->current_line;
    tmp_byte_ptr = p_scd->p_line;
    p_scd->p_line = p_scd->p_next_line;
    p_scd->p_next_line = p_scd->p_nnext_line;
    p_scd->p_nnext_line = tmp_byte_ptr;
    if ((p_scd->current_line + 1) < p_scd->y_size)
    {
        p_img_line = get_raw_img_line(p_scd->p_raw_ptr, p_scd->img_line_size,
                p_scd->current_line + 1);
        tx_bits_mem(p_scd->p_next_line, p_scd->x_size, p_img_line, p_scd->back_ground);
    }
    else
        memset(p_scd->p_nnext_line, 0, p_scd->line_size);
    return (TRUE);

}

/* OK */
static int      scan_current_line(scan_data * p_scd)
{

    BYTE            h_open = 0;
    int             xx,
                    curr_bit,
                    right_bit,
                    top_bit,
                    top_right_bit,
                    node = FALSE,
                    prev_node = FALSE;
    img_point       pnt0,
                    pnt1;

    for (xx = 0; xx <= p_scd->x_size; xx++, prev_node = node)
    {
        curr_bit = (int) p_scd->p_line[xx];
        right_bit = (int) p_scd->p_line[xx + 1];
        top_bit = (int) p_scd->p_next_line[xx];
        top_right_bit = (int) p_scd->p_next_line[xx + 1];
        node = ((curr_bit ^ top_bit) && (curr_bit ^ right_bit) &&
                (right_bit ^ top_right_bit)) ? TRUE : FALSE;
        if (curr_bit ^ right_bit)
        {
            h_open = ~h_open;
            if (h_open)
            {
                pnt0.x = xx + 1;
                pnt0.y = p_scd->current_line;
                pnt1.x = xx + 1;
                pnt1.y = p_scd->current_line + 1;
            }
            else
            {
                pnt0.x = xx + 1;
                pnt0.y = p_scd->current_line + 1;
                pnt1.x = xx + 1;
                pnt1.y = p_scd->current_line;
            }
            if (!add_line(p_scd, &pnt0, &pnt1))
                return (FALSE);
        }
        if (curr_bit ^ top_bit)
        {
            p_scd->v_open[xx] = ~p_scd->v_open[xx];
            if (p_scd->v_open[xx])
            {
                pnt0.x = xx + 1;
                pnt0.y = p_scd->current_line + 1;
                pnt1.x = xx;
                pnt1.y = p_scd->current_line + 1;
                if (!prev_node)
                    if (!add_line(p_scd, &pnt0, &pnt1))
                        return (FALSE);
            }
            else
            {
                if (node)
                {
                    pnt0.x = xx + 2;
                    pnt0.y = p_scd->current_line + 1;
                    pnt1.x = xx + 1;
                    pnt1.y = p_scd->current_line + 1;
                    if (!add_line(p_scd, &pnt0, &pnt1))
                        return (FALSE);
                }
                pnt0.x = xx;
                pnt0.y = p_scd->current_line + 1;
                pnt1.x = xx + 1;
                pnt1.y = p_scd->current_line + 1;
                if (!add_line(p_scd, &pnt0, &pnt1))
                    return (FALSE);
            }
        }
    }
    curr_bit = p_scd->p_line[xx];
    top_bit = p_scd->p_next_line[xx];
    if (curr_bit ^ top_bit)
    {
        p_scd->v_open[xx] = ~p_scd->v_open[xx];
        if (p_scd->v_open[xx])
        {
            pnt0.x = xx + 1;
            pnt0.y = p_scd->current_line + 1;
            pnt1.x = xx;
            pnt1.y = p_scd->current_line + 1;
            if (!prev_node)
                if (!add_line(p_scd, &pnt0, &pnt1))
                    return (FALSE);
        }
        else
        {
            pnt0.x = xx;
            pnt0.y = p_scd->current_line + 1;
            pnt1.x = xx + 1;
            pnt1.y = p_scd->current_line + 1;
            if (!add_line(p_scd, &pnt0, &pnt1))
                return (FALSE);
        }
    }
    return (TRUE);

}

/* OK */
int LIB_PROC    dblline_convert_file(char *img_file_name, char *poly_file_name,
                        double pnt_error_tollerance,
                        double poly_lenght_factor)
{

    int             img_line;
    scan_data      *p_scd;

    if ((p_scd = alloc_scan_data(img_file_name, poly_file_name,
                            pnt_error_tollerance, poly_lenght_factor)) == NULL)
        return (FALSE);
    log_printf("- processing image file %s ( %lu bytes )\n", img_file_name,
            (unsigned long) p_scd->y_size * (unsigned long) get_line_size(p_scd->x_size));
    for (img_line = 0; img_line <= p_scd->y_size; img_line++)
    {
        if (!scan_current_line(p_scd))
        {
            free_scan_data(p_scd);
            return (FALSE);
        }
        if (((img_line + 1) % RESYNC_FREQUENCY) == 0)
        {
            if (!resync_polyline_lists(p_scd))
            {
                free_scan_data(p_scd);
                scr_printf("\n");
                return (FALSE);
            }
            scr_printf("\r- %-9d of %d lines processed", img_line, p_scd->y_size);
        }
        next_line(p_scd);
    }
    scr_printf("\r- %-9d of %d lines processed\n", p_scd->y_size, p_scd->y_size);
    if (!resync_polyline_lists(p_scd))
    {
        free_scan_data(p_scd);
        return (FALSE);
    }
    if (!flush_all_polylines(p_scd))
    {
        free_scan_data(p_scd);
        return (FALSE);
    }
    log_printf("- generated %d polyline(s)\n", p_scd->number_of_polylines);
    free_scan_data(p_scd);
    return (TRUE);

}
