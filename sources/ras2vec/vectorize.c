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
#include"thinner.h"
#include"vectorize.h"
#include"filescan.h"
#include"flushpoly.h"
#include"tree.h"
#include"log.h"
#include"util.h"


#define NUM_DIRECTIONS              8
#define MAX_SEARCH_DIRS             (NUM_DIRECTIONS-1)


typedef struct vect_poly_record
{
    link_list_hdr  *p_poly_list;
    img_point       prev_pnt,
                    last_pnt,
                    pnt;
}               vect_poly;


static int      cmp_img_points(img_point * p_imgp1, img_point * p_imgp2);
static HTREE    get_points_tree(link_list_hdr * p_pnts_list);
static int      do_vectorize(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        FILE * fp_poly, double pnt_error_tollerance,
                        double min_polyline_lenght, HTREE node_pnts_htree,
                        link_list_hdr * p_node_pnts_list);
static int      trace_point(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        FILE * fp_poly, double pnt_error_tollerance,
                        double min_polyline_lenght, int curr_direction,
                        HTREE node_pnts_htree, vect_poly * p_vect_poly,
                        img_point * p_imgp, int *p_poly_flushed_flag);
static int      find_start_point(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        int yy_start, img_point * p_imgp);
static void     get_next_point(img_point * p_start_imgp, int direction,
                        img_point * p_imgp);
static vect_poly *create_vect_poly(img_point * p_imgp);
static void     free_vect_poly(vect_poly * p_vect_poly);
static int      add_vect_poly_point(vect_poly * p_vect_poly, img_point * p_imgp);
static int      get_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy);
static void     clear_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy);
static void     set_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy);


static img_point dirs[] = {{0, 1},
{1, 0},
{0, -1},
{-1, 0},
{1, 1},
{1, -1},
{-1, -1},
{-1, 1},
};
static int      search_dirs[NUM_DIRECTIONS + 1][NUM_DIRECTIONS] =
{
    {0, 4, 7, 1, 3, 5, 6, 2},
    {1, 5, 4, 2, 0, 6, 7, 3},
    {2, 6, 5, 3, 1, 7, 4, 0},
    {3, 7, 6, 0, 2, 4, 5, 1},
    {1, 0, 4, 5, 7, 2, 3, 6},
    {2, 1, 5, 6, 4, 3, 0, 7},
    {3, 2, 6, 7, 5, 0, 1, 4},
    {0, 3, 7, 4, 6, 1, 2, 5},
    {0, 1, 2, 3, 4, 5, 6, 7}
};



/* OK */
int LIB_PROC    cntline_convert_file(char *img_file_name, int use_a_copy,
                        char *poly_file_name, double pnt_error_tollerance,
                        double poly_lenght_factor)
{

    int             passes,
                    back_ground,
                    number_of_polylines;
    HTREE           node_pnts_htree;
    double          min_polyline_lenght = 1.0;
    BYTE           *p_img_mem;
    link_list_hdr  *p_node_pnts_list;
    FILE           *fp_poly;
    img_data        imgd;
    bw_bmp_header   bmph;
    char            temp_img_file_name[MAX_PATH];

    if (use_a_copy)
    {
        char            temp_path[MAX_PATH];

        GetTempPath(sizeof(temp_path), temp_path);
        GetTempFileName(temp_path, "img", 0, temp_img_file_name);
        if (!CopyFile(img_file_name, temp_img_file_name, FALSE))
            return (FALSE);
        img_file_name = temp_img_file_name;
    }
    if ((p_img_mem = (BYTE *) get_image(img_file_name, IMAGE_OPEN_READWRITE,
                            &imgd)) == NULL)
    {
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    bmph = *((bw_bmp_header *) p_img_mem);
    log_printf("- processing image file %s ( %lu bytes )\n", img_file_name,
            (unsigned long) bmph.bih.biHeight * (unsigned long) get_line_size(bmph.bih.biWidth));
    if ((passes = thin_image(p_img_mem, &back_ground)) < 0)
    {
        free_image(&imgd);
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    min_polyline_lenght = (poly_lenght_factor > 0.0) ?
            (((double) max(bmph.bih.biWidth, bmph.bih.biHeight)) / poly_lenght_factor) : 1.0;
    log_printf("- retrieving node points\n");
    if ((p_node_pnts_list = get_node_points(&bmph, p_img_mem, back_ground)) == NULL)
    {
        free_image(&imgd);
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    log_printf("- found %d node points\n", ll_get_list_count(p_node_pnts_list));
    if ((node_pnts_htree = get_points_tree(p_node_pnts_list)) == NULL)
    {
        ll_empty_free_list(p_node_pnts_list);
        free_image(&imgd);
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    if ((fp_poly = fopen(poly_file_name, "wt")) == NULL)
    {
        tree_empty(node_pnts_htree);
        ll_empty_free_list(p_node_pnts_list);
        free_image(&imgd);
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    log_printf("- begin raster to vector conversion to file %s\n", poly_file_name);
    if ((number_of_polylines = do_vectorize(&bmph, p_img_mem, back_ground, fp_poly,
                            pnt_error_tollerance, min_polyline_lenght, node_pnts_htree, p_node_pnts_list)) < 0)
    {
        tree_empty(node_pnts_htree);
        ll_empty_free_list(p_node_pnts_list);
        fclose(fp_poly);
        free_image(&imgd);
        if (use_a_copy)
            remove(temp_img_file_name);
        return (FALSE);
    }
    log_printf("- generated %d polylines in file %s\n", number_of_polylines,
            poly_file_name);
    ll_empty_free_list(p_node_pnts_list);
    tree_empty(node_pnts_htree);
    fclose(fp_poly);
    free_image(&imgd);
    if (use_a_copy)
        remove(temp_img_file_name);
    return (TRUE);

}


/* OK */
static int      cmp_img_points(img_point * p_imgp1, img_point * p_imgp2)
{

    if (p_imgp1->y > p_imgp2->y)
        return (+1);
    if (p_imgp1->y < p_imgp2->y)
        return (-1);
    if (p_imgp1->x > p_imgp2->x)
        return (+1);
    if (p_imgp1->x < p_imgp2->x)
        return (-1);
    return (0);

}


/* OK */
static HTREE    get_points_tree(link_list_hdr * p_pnts_list)
{

    int             index = 0;
    HTREE           htree;
    img_point       min_img_point = {INT_MIN, INT_MIN};

    if ((htree = tree_create(sizeof(img_point), &min_img_point,
                            (int (*) (void *, void *)) cmp_img_points)) == NULL)
        return (NULL);
    ll_set_list_currpntr(p_pnts_list, TG_HEAD);
    do
    {
        img_point       pnt;

        if (!ll_get_list_user_data(p_pnts_list, &pnt))
            break;
        if (!tree_insert(htree, &pnt, (void *) (index + 1)))
        {
            tree_empty(htree);
            return (NULL);
        }
        ++index;
    } while (ll_set_list_currpntr(p_pnts_list, TG_AFTER) == TG_AFTER);
    return (htree);

}


/* OK */
static int      do_vectorize(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        FILE * fp_poly, double pnt_error_tollerance,
                        double min_polyline_lenght, HTREE node_pnts_htree,
                        link_list_hdr * p_node_pnts_list)
{

    int             number_of_polylines = 0,
                    current_line = 0,
                    polyline_flushed;
    vect_poly      *p_vect_poly;
    img_point       pnt,
                    next_pnt;

    ll_set_list_currpntr(p_node_pnts_list, TG_HEAD);
    do
    {
        int             direction;

        if (!ll_get_list_user_data(p_node_pnts_list, &pnt))
            break;
        for (direction = 0; direction < NUM_DIRECTIONS; direction++)
        {
            get_next_point(&pnt, direction, &next_pnt);
            if ((next_pnt.x >= 0) && (next_pnt.x < p_bmph->bih.biWidth) &&
                    (next_pnt.y >= 0) && (next_pnt.y < p_bmph->bih.biHeight) &&
                    get_img_pixel(p_img_mem, back_ground, next_pnt.x, next_pnt.y))
            {
                if ((p_vect_poly = create_vect_poly(&pnt)) == NULL)
                    return (-1);
                if (!trace_point(p_bmph, p_img_mem, back_ground, fp_poly, pnt_error_tollerance,
                                min_polyline_lenght, direction, node_pnts_htree, p_vect_poly, &next_pnt,
                                &polyline_flushed))
                {
                    free_vect_poly(p_vect_poly);
                    return (-1);
                }
                if (polyline_flushed)
                    ++number_of_polylines;
            }
        }
    } while (ll_set_list_currpntr(p_node_pnts_list, TG_AFTER) == TG_AFTER);
    for (;;)
    {
        if (!find_start_point(p_bmph, p_img_mem, back_ground, current_line, &pnt))
            break;
        if ((p_vect_poly = create_vect_poly(NULL)) == NULL)
            return (-1);
        if (!trace_point(p_bmph, p_img_mem, back_ground, fp_poly, pnt_error_tollerance,
                        min_polyline_lenght, -1, node_pnts_htree, p_vect_poly, &pnt, &polyline_flushed))
        {
            free_vect_poly(p_vect_poly);
            return (-1);
        }
        if (polyline_flushed)
            ++number_of_polylines;
        current_line = pnt.y;
    }
    return (number_of_polylines);

}


/* OK */
static int      trace_point(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        FILE * fp_poly, double pnt_error_tollerance,
                        double min_polyline_lenght, int curr_direction,
                        HTREE node_pnts_htree, vect_poly * p_vect_poly,
                        img_point * p_imgp, int *p_poly_flushed_flag)
{

    int             inserted_points = ll_get_list_count(p_vect_poly->p_poly_list),
                    direction,
                    max_directions;
    img_point       pnt = *p_imgp,
                    next_pnt;

    do
    {
        if (inserted_points > 0)
            clear_img_pixel(p_img_mem, back_ground, pnt.x, pnt.y);
        if (!add_vect_poly_point(p_vect_poly, &pnt))
            return (FALSE);
        ++inserted_points;
        if (curr_direction < 0)
            max_directions = NUM_DIRECTIONS, curr_direction = NUM_DIRECTIONS;
        else
            max_directions = NUM_DIRECTIONS - 1;
        for (direction = 0; direction < max_directions; direction++)
        {
            get_next_point(&pnt, search_dirs[curr_direction][direction], &next_pnt);
            if ((next_pnt.x >= 0) && (next_pnt.x < p_bmph->bih.biWidth) &&
                    (next_pnt.y >= 0) && (next_pnt.y < p_bmph->bih.biHeight) &&
                    get_img_pixel(p_img_mem, back_ground, next_pnt.x, next_pnt.y))
                break;
        }
        if (direction < max_directions)
            pnt = next_pnt, curr_direction = search_dirs[curr_direction][direction];
    } while (direction < max_directions);
    if (inserted_points == 1)
        clear_img_pixel(p_img_mem, back_ground, pnt.x, pnt.y);
    if (curr_direction == NUM_DIRECTIONS)
        max_directions = NUM_DIRECTIONS;
    else
        max_directions = NUM_DIRECTIONS - 1;
    for (direction = 0; direction < max_directions; direction++)
    {
        get_next_point(&pnt, search_dirs[curr_direction][direction], &next_pnt);
        if (tree_search(node_pnts_htree, &next_pnt) != NULL)
            break;
    }
    if (direction < max_directions)
        if (!add_vect_poly_point(p_vect_poly, &next_pnt))
            return (FALSE);
    *p_poly_flushed_flag = opt_flush_polyline(fp_poly, p_vect_poly->p_poly_list,
            pnt_error_tollerance, min_polyline_lenght);
    free_vect_poly(p_vect_poly);
    return (TRUE);

}


/* OK */
static int      find_start_point(bw_bmp_header * p_bmph, BYTE * p_img_mem, int back_ground,
                        int yy_start, img_point * p_imgp)
{

    int             yy,
                    img_line_size = get_line_size(p_bmph->bih.biWidth);
    BYTE           *p_raw_ptr = bmp_get_raw_ptr(p_img_mem);

    for (yy = yy_start; yy < p_bmph->bih.biHeight; yy++)
    {
        int             xx,
                        xxl,
                        xx_end;
        BYTE           *p_line = get_raw_img_line(p_raw_ptr, img_line_size, yy);

        for (xx = 0; xx < img_line_size; xx++)
        {
            if (p_line[xx] == back_ground)
                continue;
            xx_end = min((xx + 1) * 8, p_bmph->bih.biWidth);
            for (xxl = xx * 8; xxl < xx_end; xxl++)
            {
                if (get_img_pixel(p_img_mem, back_ground, xxl, yy))
                {
                    p_imgp->x = xxl;
                    p_imgp->y = yy;
                    return (TRUE);
                }
            }
        }
    }
    return (FALSE);

}


/* OK */
static void     get_next_point(img_point * p_start_imgp, int direction,
                        img_point * p_imgp)
{

    img_point       pnt;

    pnt.x = p_start_imgp->x + dirs[direction].x;
    pnt.y = p_start_imgp->y + dirs[direction].y;
    *p_imgp = pnt;

}


/* OK */
static vect_poly *create_vect_poly(img_point * p_imgp)
{

    vect_poly      *p_vect_poly;

    if ((p_vect_poly = (vect_poly *) malloc(sizeof(vect_poly))) == NULL)
        return (NULL);
    if ((p_vect_poly->p_poly_list = ll_create_list()) == NULL)
    {
        free(p_vect_poly);
        return (NULL);
    }
    if (p_imgp != NULL)
    {
        p_vect_poly->prev_pnt = p_vect_poly->last_pnt = p_vect_poly->pnt = *p_imgp;
        if (!ll_add_list_data(p_vect_poly->p_poly_list, TG_HEAD, &p_vect_poly->pnt))
        {
            ll_empty_free_list(p_vect_poly->p_poly_list);
            free(p_vect_poly);
            return (NULL);
        }
    }
    return (p_vect_poly);

}


/* OK */
static void     free_vect_poly(vect_poly * p_vect_poly)
{

    ll_empty_free_list(p_vect_poly->p_poly_list);
    free(p_vect_poly);

}


/* OK */
static int      add_vect_poly_point(vect_poly * p_vect_poly, img_point * p_imgp)
{

    if (ll_get_list_count(p_vect_poly->p_poly_list) == 0)
    {
        if (!ll_add_list_data(p_vect_poly->p_poly_list, TG_TAIL, p_imgp))
            return (FALSE);
        p_vect_poly->prev_pnt = p_vect_poly->last_pnt = p_vect_poly->pnt = *p_imgp;
        return (TRUE);
    }
    if (ll_get_list_count(p_vect_poly->p_poly_list) == 1)
    {
        if (!ll_add_list_data(p_vect_poly->p_poly_list, TG_TAIL, p_imgp))
            return (FALSE);
        p_vect_poly->prev_pnt = p_vect_poly->last_pnt = p_vect_poly->pnt;
        p_vect_poly->pnt = *p_imgp;
        return (TRUE);
    }
    if ((p_vect_poly->prev_pnt.x == p_vect_poly->pnt.x) &&
            (p_vect_poly->pnt.x == p_imgp->x))
    {
        p_vect_poly->last_pnt = p_vect_poly->pnt;
        if (!ll_set_list_user_data(p_vect_poly->p_poly_list, TG_TAIL, p_imgp))
            return (FALSE);
        p_vect_poly->pnt = *p_imgp;
    }
    else
    {
        if ((p_vect_poly->prev_pnt.y == p_vect_poly->pnt.y) &&
                (p_vect_poly->pnt.y == p_imgp->y))
        {
            p_vect_poly->last_pnt = p_vect_poly->pnt;
            if (!ll_set_list_user_data(p_vect_poly->p_poly_list, TG_TAIL, p_imgp))
                return (FALSE);
            p_vect_poly->pnt = *p_imgp;
        }
        else
        {
            if (!ll_add_list_data(p_vect_poly->p_poly_list, TG_TAIL, p_imgp))
                return (FALSE);
            p_vect_poly->prev_pnt = p_vect_poly->last_pnt = p_vect_poly->pnt;
            p_vect_poly->pnt = *p_imgp;
        }
    }
    return (TRUE);

}


/* OK */
static int      get_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy)
{

    BYTE            fpix = ((back_ground != 0) ? 0 : 1),
                   *p_line;

    p_line = bmp_get_line(p_img_mem, yy);
    return (read_bit2(fpix, p_line, xx));

}


/* OK */
static void     clear_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy)
{

    BYTE           *p_line;

    p_line = bmp_get_line(p_img_mem, yy);
    clear_pixel(p_line, xx, back_ground);

}


/* OK */
static void     set_img_pixel(BYTE * p_img_mem, int back_ground, int xx, int yy)
{

    BYTE           *p_line;

    p_line = bmp_get_line(p_img_mem, yy);
    set_pixel(p_line, xx, back_ground);

}
