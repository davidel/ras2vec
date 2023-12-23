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
#include<ctype.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include<limits.h>
#include"ras2vec.h"
#include"dbll_list.h"
#include"flushpoly.h"
#include"log.h"
#include"util.h"

#define TETA_TOLL                 ((PIG*2.0)/3.0)
#define OPT_MIN_NUM_POLY_PNTS     8
#define POLY_START_STR            "POLYLINE"
#define POLY_END_STR              "END"

typedef struct imp_line_2d_record
{
    double          a,
                    b,
                    c;
}               imp_line_2d;

static double   distance_pnt_2d(img_point * pnt1, img_point * pnt2);
static int      get_imp_line_eq_2d(img_point * p_pnt0, img_point * p_pnt1,
                        imp_line_2d * p_ile);
static double   pnt_line_position(img_point * p_pnt, imp_line_2d * p_ile);
static double   angle_value_xy(double x_val, double y_val);
static char    *get_token(char *str, int n_token, char *token, int max_token_size);
static int      read_file_line(FILE * fp_poly, char *buffer, int sizeof_buffer);
static int      is_integer(char *str);
static int      is_end_of_polyline(char *line_buffer);

/* OK */
static double   distance_pnt_2d(img_point * pnt1, img_point * pnt2)
{

    return (sqrt((double) pnt_distance_2(pnt1, pnt2)));

}

/* OK */
static int      get_imp_line_eq_2d(img_point * p_pnt0, img_point * p_pnt1, imp_line_2d * p_ile)
{

    double          distance,
                    k_norm;

    if ((distance = distance_pnt_2d(p_pnt0, p_pnt1)) == 0.0)
    {
        p_ile->a = p_ile->b = p_ile->c = 0.0;
        return (FALSE);
    }
    k_norm = 1.0 / distance;
    p_ile->a = k_norm * (double) (p_pnt1->y - p_pnt0->y);
    p_ile->b = -k_norm * (double) (p_pnt1->x - p_pnt0->x);
    p_ile->c = k_norm * (double) (p_pnt1->x * p_pnt0->y - p_pnt0->x * p_pnt1->y);
    return (TRUE);

}

/* OK */
static double   pnt_line_position(img_point * p_pnt, imp_line_2d * p_ile)
{

    return (p_ile->a * (double) p_pnt->x + p_ile->b * (double) p_pnt->y + p_ile->c);

}

/* OK */
static double   angle_value_xy(double x_val, double y_val)
{

    double          mod,
                    teta;

    if ((mod = sqrt(x_val * x_val + y_val * y_val)) == 0.0)
        return (0.0);
    teta = acos(x_val / mod);
    return ((y_val < 0.0) ? (2.0 * PIG - teta) : teta);

}

/* OK */
static char    *get_token(char *str, int n_token, char *token, int max_token_size)
{

    int             ii = 0,
                    ltk = 0,
                    n_tok = 0;

    do
    {
        ii += ltk;
        while ((str[ii] == ' ') || (str[ii] == '\t'))
            ++ii;
        if (str[ii] == '\0')
            break;
        ltk = 0;
        while ((str[ii + ltk] != ' ') && (str[ii + ltk] != '\t') && (str[ii + ltk] != '\0'))
        {
            if (ltk < max_token_size)
                token[ltk] = str[ii + ltk];
            ++ltk;
        }
        token[min(ltk, (max_token_size - 1))] = '\0';
        ++n_tok;
    } while ((n_tok < n_token) && (str[ii + ltk] != '\0'));
    return ((n_tok == n_token) ? (str + ii) : NULL);

}

/* OK */
static int      read_file_line(FILE * fp_poly, char *buffer, int sizeof_buffer)
{

    while (fgets(buffer, sizeof_buffer, fp_poly) != NULL)
    {
        char            token[256];

        buffer[strlen(buffer) - 1] = '\0';
        if (get_token(buffer, 1, token, sizeof(token) - 1) != NULL)
            return (TRUE);
    }
    return (FALSE);

}

/* OK */
static int      is_integer(char *str)
{

    if ((*str == '+') || (*str == '-'))
        ++str;
    while (*str != '\0')
        if (!isdigit(*str++))
            return (FALSE);
    return (TRUE);

}

/* OK */
int             start_polyline(FILE * fp_poly)
{

    fprintf(fp_poly, "%s\n", POLY_START_STR);
    return (TRUE);

}

/* OK */
int             end_polyline(FILE * fp_poly)
{

    fprintf(fp_poly, "%s\n", POLY_END_STR);
    return (TRUE);

}

/* OK */
int             write_img_point(FILE * fp_poly, img_point * p_imgp)
{

    fprintf(fp_poly, "%-8ld %-8ld\n", (long int) p_imgp->x, (long int) p_imgp->y);
    return (TRUE);

}

/* OK */
int             read_start_polyline(FILE * fp_poly)
{

    char            line_buffer[256],
                    token[128];

    if (!read_file_line(fp_poly, line_buffer, sizeof(line_buffer) - 1))
        return (FALSE);
    if (get_token(line_buffer, 1, token, sizeof(token) - 1) == NULL)
        return (FALSE);
    return ((strcmp(token, POLY_START_STR) == 0) ? TRUE : FALSE);

}

/* OK */
static int      is_end_of_polyline(char *line_buffer)
{

    char            token[128];

    if (get_token(line_buffer, 1, token, sizeof(token) - 1) == NULL)
        return (FALSE);
    return ((strcmp(token, POLY_END_STR) == 0) ? TRUE : FALSE);

}

/* OK */
int             read_img_point(FILE * fp_poly, img_point * p_imgp)
{

    char            line_buffer[256],
                    token[128];

    if (!read_file_line(fp_poly, line_buffer, sizeof(line_buffer) - 1))
        return (FALSE);
    if (is_end_of_polyline(line_buffer))
        return (FALSE);
    if ((get_token(line_buffer, 1, token, sizeof(token) - 1) == NULL) ||
            (!is_integer(token)))
        return (FALSE);
    p_imgp->x = (int) atol(token);
    if ((get_token(line_buffer, 2, token, sizeof(token) - 1) == NULL) ||
            (!is_integer(token)))
        return (FALSE);
    p_imgp->y = (int) atol(token);
    return (TRUE);

}

/* OK */
void            update_min_max_pnt(img_point * p_imgp, img_point * p_min_imgp,
                        img_point * p_max_imgp)
{

    if (p_min_imgp->x > p_imgp->x)
        p_min_imgp->x = p_imgp->x;
    if (p_min_imgp->y > p_imgp->y)
        p_min_imgp->y = p_imgp->y;
    if (p_max_imgp->x < p_imgp->x)
        p_max_imgp->x = p_imgp->x;
    if (p_max_imgp->y < p_imgp->y)
        p_max_imgp->y = p_imgp->y;
    return;

}

/* OK */
double          img_points_dist(img_point * p_imgp0, img_point * p_imgp1)
{

    return (sqrt((double) pnt_distance_2(p_imgp0, p_imgp1)));

}

/* OK */
int             flush_polyline(FILE * fp_poly, link_list_hdr * p_polyline_list,
                        double min_polyline_lenght)
{

    int             num_pnts;
    double          polyline_lenght = 0.0;
    img_point       prev_pnt,
                    pnt;

    if ((num_pnts = ll_get_list_count(p_polyline_list)) < 2)
        return (FALSE);
    ll_set_list_currpntr(p_polyline_list, TG_HEAD);
    ll_get_list_user_data(p_polyline_list, &pnt);
    while (ll_set_list_currpntr(p_polyline_list, TG_AFTER) == TG_AFTER)
    {
        prev_pnt = pnt;
        if (!ll_get_list_user_data(p_polyline_list, &pnt))
            break;
        polyline_lenght += img_points_dist(&prev_pnt, &pnt);
    }
    if ((min_polyline_lenght > 0.0) && (polyline_lenght < min_polyline_lenght))
        return (FALSE);
    start_polyline(fp_poly);
    ll_set_list_currpntr(p_polyline_list, TG_HEAD);
    do
    {
        if (!ll_get_list_user_data(p_polyline_list, &pnt))
            break;
        if (!write_img_point(fp_poly, &pnt))
            return (FALSE);
    } while (ll_set_list_currpntr(p_polyline_list, TG_AFTER) == TG_AFTER);
    end_polyline(fp_poly);
    return (TRUE);

}

/* OK */
int             opt_flush_polyline(FILE * fp_poly, link_list_hdr * p_polyline_list,
                        double pnt_error_tollerance, double min_polyline_lenght)
{

    int             poly_num_pnts,
                    start_seq_index,
                    curr_index;
    double          prev_teta,
                    teta;
    link_list_hdr  *p_opt_polyline_list;
    img_point     **pp_poly_pnts;

    if ((poly_num_pnts = (int) ll_get_list_count(p_polyline_list)) < OPT_MIN_NUM_POLY_PNTS)
        return (flush_polyline(fp_poly, p_polyline_list, min_polyline_lenght));
    if ((pp_poly_pnts = (img_point **) malloc(poly_num_pnts * sizeof(img_point *))) == NULL)
        return (FALSE);
    if ((p_opt_polyline_list = ll_create_list()) == NULL)
    {
        free(pp_poly_pnts);
        return (FALSE);
    }
    poly_num_pnts = 0;
    ll_set_list_currpntr(p_polyline_list, TG_HEAD);
    do
    {
        void           *p_user_data_addr;

        if ((p_user_data_addr = ll_get_list_user_data_addr(p_polyline_list)) == NULL)
            break;
        pp_poly_pnts[poly_num_pnts++] = (img_point *) p_user_data_addr;
    } while (ll_set_list_currpntr(p_polyline_list, TG_AFTER) == TG_AFTER);
    if (!ll_add_list_data(p_opt_polyline_list, TG_TAIL, pp_poly_pnts[0]))
    {
        ll_empty_free_list(p_opt_polyline_list);
        free(pp_poly_pnts);
        return (FALSE);
    }
    teta = angle_value_xy((double) (pp_poly_pnts[1]->x - pp_poly_pnts[0]->x),
            (double) (pp_poly_pnts[1]->y - pp_poly_pnts[0]->y));
    for (curr_index = 1, start_seq_index = 0; curr_index < poly_num_pnts; curr_index++)
    {
        int             index;
        double          pnt_error = 0.0;
        imp_line_2d     ile;

        prev_teta = teta;
        teta = angle_value_xy(
                (double) (pp_poly_pnts[curr_index]->x - pp_poly_pnts[start_seq_index]->x),
                (double) (pp_poly_pnts[curr_index]->y - pp_poly_pnts[start_seq_index]->y));
        get_imp_line_eq_2d(pp_poly_pnts[start_seq_index], pp_poly_pnts[curr_index], &ile);
        for (index = start_seq_index + 1; index < curr_index; index++)
        {
            double          error = fabs(pnt_line_position(pp_poly_pnts[index], &ile));

            if (error > pnt_error)
                pnt_error = error;
        }
        if ((pnt_error < pnt_error_tollerance) && (fabs(teta - prev_teta) < TETA_TOLL))
            continue;
        if (!ll_add_list_data(p_opt_polyline_list, TG_TAIL, pp_poly_pnts[curr_index - 1]))
        {
            ll_empty_free_list(p_opt_polyline_list);
            free(pp_poly_pnts);
            return (FALSE);
        }
        start_seq_index = curr_index - 1;
        teta = angle_value_xy(
                (double) (pp_poly_pnts[curr_index]->x - pp_poly_pnts[start_seq_index]->x),
                (double) (pp_poly_pnts[curr_index]->y - pp_poly_pnts[start_seq_index]->y));
    }
    if (!ll_add_list_data(p_opt_polyline_list, TG_TAIL, pp_poly_pnts[curr_index - 1]))
    {
        ll_empty_free_list(p_opt_polyline_list);
        free(pp_poly_pnts);
        return (FALSE);
    }
    free(pp_poly_pnts);
    if (!flush_polyline(fp_poly, p_opt_polyline_list, min_polyline_lenght))
    {
        ll_empty_free_list(p_opt_polyline_list);
        return (FALSE);
    }
    ll_empty_free_list(p_opt_polyline_list);
    return (TRUE);

}
