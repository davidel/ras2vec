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


#ifndef DBLL_LIST_H
#define DBLL_LIST_H

#ifndef FALSE
#define FALSE                 0
#endif

#ifndef TRUE
#define TRUE                  1
#endif

#define TG_FORWARD            (+1)
#define TG_BACKWARD           (-1)

typedef struct dll_link_record{
          union{
            struct{
              void   *data;
              int  datatype;
            };
            char user_data[8];
          };
          struct dll_link_record *prev;
          struct dll_link_record *nxt;
        } dll_link;

typedef struct {
          dll_link *head;
          dll_link *last;
          dll_link *current;
          int count;
        } link_list_hdr;

typedef enum {
          TG_ERROR=-1,
          TG_HEAD,
          TG_TAIL,
          TG_AFTER,
          TG_BEFORE,
          TG_CURRENT
          } link_loc;

typedef enum {
          LSC_SUCCESS = 0,
          LSC_MATCH_FOUND,
          LSC_MATCH_NOT_FOUND,
          LSC_BAD_SEARCH_DIR,
          LSC_BAD_START_LOC,
          LSC_BAD_STOP_LOC,
          LSC_BAD_LIST,
          LSC_BAD_COMPARE_FUNCTION,
          LSC_ITEMS_NOT_PURGED,
          LSC_PURGE_POLY_FAILED
          } list_status_code;

int              ll_add_list_item(link_list_hdr *list,link_loc loc,void *data,
		                              int datatype);
link_list_hdr*   ll_create_list(void);
void *           ll_delete_list_item(link_list_hdr *list,link_loc del_loc,
			                               link_loc ret_loc);
int              ll_get_list_count(link_list_hdr *list);
int              ll_get_datatype(link_list_hdr *list);
void *           ll_get_list_data(link_list_hdr *list);
list_status_code ll_purge_list(link_list_hdr *list);
void             ll_rearrange_list(link_list_hdr *list,int dir);
link_loc         ll_set_list_currpntr(link_list_hdr *list,link_loc set_loc);
int              ll_append_list(link_list_hdr *ldst,link_list_hdr *lsrc);
int              ll_destroy_free_list(link_list_hdr *p_list);
int              ll_empty_free_list(link_list_hdr *p_list);
void *           ll_set_list_data(link_list_hdr *list,void *data);
int              ll_add_list_data(link_list_hdr *list,link_loc loc,void *data);
int              ll_get_list_user_data(link_list_hdr *list,void *user_data);
int              ll_set_list_user_data(link_list_hdr *list,link_loc set_loc,
                                       void *data);
void *           ll_get_list_user_data_addr(link_list_hdr *list);

#endif

