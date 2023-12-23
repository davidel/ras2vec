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


#ifndef TREE_H
#define TREE_H

typedef void *HTREE;

HTREE         tree_create(int sizeof_key,void *init_key,
                          int (*compare_keys)(void *,void *));
int           tree_insert(HTREE htree,void *key,void *data);
void *        tree_search(HTREE htree,void *key);
int           tree_search_multi(HTREE htree,void *key,
                                int (*search_callback)(void *,void *),
                                void *p_param);
int           tree_free(HTREE htree);
int           tree_empty(HTREE htree);
void *        tree_delete(HTREE htree,void *key);
void *        tree_delete_from_data(HTREE htree,void *key,void *data);

#endif

