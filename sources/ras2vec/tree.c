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
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>
#include<float.h>
#include<math.h>
#include<limits.h>
#include"tree.h"

typedef struct node_record
{
    int             red;
    void           *data,
                   *key;
    struct node_record *l,
                   *r;
}               node;
typedef struct tree_record
{
    int             (*compare_keys) (void *, void *);
    int             sizeof_key;
    void           *init_key;
    node           *head,
                   *z,
                   *x,
                   *g,
                   *p,
                   *gg;
}               tree;

static node    *alloc_node(tree * p_tree, void *key, int red, void *data, node * l, node * r);
static void     free_node(node * p_node, int free_data);
static int      tree_cmp_keys(tree * p_tree, void *key1, void *key2);
static int      tree_search_equals(tree * p_tree, void *key, node * x,
                        int (*search_callback) (void *, void *), void *p_param);
static int      split(tree * p_tree, void *key);
static node    *rotate(tree * p_tree, void *key, node * y);
static void     tree_free_ll(tree * p_tree, node * x);
static void     tree_empty_ll(tree * p_tree, node * x);

/* OK */
static node    *alloc_node(tree * p_tree, void *key, int red, void *data, node * l, node * r)
{

    node           *p_node;

    if ((p_node = (node *) malloc(sizeof(node))) == NULL)
        return (NULL);
    if ((p_node->key = malloc(p_tree->sizeof_key)) == NULL)
    {
        free(p_node);
        return (NULL);
    }
    memcpy(p_node->key, key, p_tree->sizeof_key);
    p_node->data = data;
    p_node->red = red;
    p_node->l = l;
    p_node->r = r;
    return (p_node);

}

/* OK */
static void     free_node(node * p_node, int free_data)
{

    if (free_data && (p_node->data != NULL))
        free(p_node->data), p_node->data = NULL;
    if (p_node->key != NULL)
        free(p_node->key), p_node->key = NULL;
    free(p_node);
    return;

}

/* OK */
static int      tree_cmp_keys(tree * p_tree, void *key1, void *key2)
{

    return (p_tree->compare_keys(key1, key2));

}

/* OK */
HTREE           tree_create(int sizeof_key, void *init_key, int (*compare_keys) (void *, void *))
{

    tree           *p_tree;

    if ((p_tree = (tree *) malloc(sizeof(tree))) == NULL)
        return (NULL);
    p_tree->sizeof_key = sizeof_key;
    if ((p_tree->init_key = malloc(p_tree->sizeof_key)) == NULL)
    {
        free(p_tree);
        return (NULL);
    }
    memcpy(p_tree->init_key, init_key, p_tree->sizeof_key);
    p_tree->compare_keys = compare_keys;
    if ((p_tree->z = alloc_node(p_tree, init_key, 0, NULL, NULL, NULL)) == NULL)
    {
        free(p_tree->init_key);
        free(p_tree);
        return (NULL);
    }
    p_tree->z->l = p_tree->z->r = p_tree->z;
    if ((p_tree->head = alloc_node(p_tree, init_key, 0, NULL, p_tree->z, p_tree->z)) == NULL)
    {
        free_node(p_tree->z, FALSE);
        free(p_tree->init_key);
        free(p_tree);
        return (NULL);
    }
    return ((HTREE) p_tree);

}

/* OK */
int             tree_insert(HTREE htree, void *key, void *data)
{

    tree           *p_tree = (tree *) htree;

    p_tree->x = p_tree->head;
    p_tree->p = p_tree->head;
    p_tree->g = p_tree->head;
    while (p_tree->x != p_tree->z)
    {
        p_tree->gg = p_tree->g;
        p_tree->g = p_tree->p;
        p_tree->p = p_tree->x;
        p_tree->x = (tree_cmp_keys(p_tree, key, p_tree->x->key) < 0) ? p_tree->x->l : p_tree->x->r;
        if (p_tree->x->l->red && p_tree->x->r->red)
            split(p_tree, key);
    }
    if ((p_tree->x = alloc_node(p_tree, key, 0, data, p_tree->z, p_tree->z)) == NULL)
        return (FALSE);
    if (tree_cmp_keys(p_tree, key, p_tree->p->key) < 0)
        p_tree->p->l = p_tree->x;
    else
        p_tree->p->r = p_tree->x;
    split(p_tree, key);
    return (TRUE);

}

/* OK */
void           *tree_search(HTREE htree, void *key)
{

    tree           *p_tree = (tree *) htree;
    node           *x = p_tree->head->r;

    memcpy(p_tree->z->key, key, p_tree->sizeof_key);
    while (tree_cmp_keys(p_tree, key, x->key) != 0)
        x = (tree_cmp_keys(p_tree, key, x->key) < 0) ? x->l : x->r;
    return (x->data);

}

/* OK */
int             tree_search_multi(HTREE htree, void *key,
                        int (*search_callback) (void *, void *), void *p_param)
{

    tree           *p_tree = (tree *) htree;
    node           *x = p_tree->head->r;

    memcpy(p_tree->z->key, key, p_tree->sizeof_key);
    while (tree_cmp_keys(p_tree, key, x->key) != 0)
        x = (tree_cmp_keys(p_tree, key, x->key) < 0) ? x->l : x->r;
    if (x == p_tree->z)
        return (0);
    return (tree_search_equals(p_tree, key, x, search_callback, p_param));

}

/* OK */
static int      tree_search_equals(tree * p_tree, void *key, node * x,
                        int (*search_callback) (void *, void *), void *p_param)
{

    int             found = 1;

    if (search_callback(x->data, p_param) < 0)
        return (-1);
    if ((tree_cmp_keys(p_tree, key, x->l->key) == 0) && (x->l != p_tree->z))
    {
        int             found_result = tree_search_equals(p_tree, key, x->l, search_callback, p_param);

        if (found_result < 0)
            return (-1);
        found += found_result;
    }
    if ((tree_cmp_keys(p_tree, key, x->r->key) == 0) && (x->r != p_tree->z))
    {
        int             found_result = tree_search_equals(p_tree, key, x->r, search_callback, p_param);

        if (found_result < 0)
            return (-1);
        found += found_result;
    }
    return (found);

}

/* OK */
static int      split(tree * p_tree, void *key)
{

    p_tree->x->red = 1;
    p_tree->x->l->red = 0;
    p_tree->x->r->red = 0;
    if (p_tree->p->red)
    {
        p_tree->g->red = 1;
        if (tree_cmp_keys(p_tree, key, p_tree->g->key) !=
                tree_cmp_keys(p_tree, key, p_tree->p->key))
            p_tree->p = rotate(p_tree, key, p_tree->g);
        p_tree->x = rotate(p_tree, key, p_tree->gg);
        p_tree->x->red = 0;
    }
    p_tree->head->r->red = 0;
    return (TRUE);

}

/* OK */
static node    *rotate(tree * p_tree, void *key, node * y)
{

    node           *c,
                   *gc;

    c = (tree_cmp_keys(p_tree, key, y->key) < 0) ? y->l : y->r;
    if (tree_cmp_keys(p_tree, key, c->key) < 0)
    {
        gc = c->l;
        c->l = gc->r;
        gc->r = c;
    }
    else
    {
        gc = c->r;
        c->r = gc->l;
        gc->l = c;
    }
    if (tree_cmp_keys(p_tree, key, y->key) < 0)
        y->l = gc;
    else
        y->r = gc;
    return (gc);

}

/* OK */
int             tree_free(HTREE htree)
{

    tree           *p_tree = (tree *) htree;

    tree_free_ll(p_tree, p_tree->head->r);
    free(p_tree->z);
    free(p_tree->head);
    free(p_tree);
    return (TRUE);

}

/* OK */
static void     tree_free_ll(tree * p_tree, node * x)
{

    if ((x->l->l == p_tree->z) && (x->l->r == p_tree->z))
    {
        if (x->l != p_tree->z)
            free_node(x->l, TRUE);
        x->l = p_tree->z;
    }
    else
        tree_free_ll(p_tree, x->l);
    if ((x->r->l == p_tree->z) && (x->r->r == p_tree->z))
    {
        if (x->r != p_tree->z)
            free_node(x->r, TRUE);
        x->r = p_tree->z;
    }
    else
        tree_free_ll(p_tree, x->r);
    free_node(x, TRUE);
    return;

}

/* OK */
int             tree_empty(HTREE htree)
{

    tree           *p_tree = (tree *) htree;

    tree_empty_ll(p_tree, p_tree->head->r);
    free(p_tree->z);
    free(p_tree->head);
    free(p_tree);
    return (TRUE);

}

/* OK */
static void     tree_empty_ll(tree * p_tree, node * x)
{

    if ((x->l->l == p_tree->z) && (x->l->r == p_tree->z))
    {
        if (x->l != p_tree->z)
            free_node(x->l, FALSE);
        x->l = p_tree->z;
    }
    else
        tree_empty_ll(p_tree, x->l);
    if ((x->r->l == p_tree->z) && (x->r->r == p_tree->z))
    {
        if (x->r != p_tree->z)
            free_node(x->r, FALSE);
        x->r = p_tree->z;
    }
    else
        tree_empty_ll(p_tree, x->r);
    free_node(x, FALSE);
    return;

}

/* OK */
void           *tree_delete(HTREE htree, void *key)
{

    tree           *p_tree = (tree *) htree;
    node           *c,
                   *p,
                   *x,
                   *t;
    void           *unlinked_data;

    p_tree->z->data = NULL;
    memcpy(p_tree->z->key, key, p_tree->sizeof_key);
    p = p_tree->head;
    x = p_tree->head->r;
    while (tree_cmp_keys(p_tree, key, x->key) != 0)
    {
        p = x;
        x = (tree_cmp_keys(p_tree, key, x->key) < 0) ? x->l : x->r;
    }
    if (x == p_tree->z)
        return (NULL);
    t = x;
    if (t->r == p_tree->z)
        x = x->l;
    else
    {
        if (t->r->l == p_tree->z)
        {
            x = x->r;
            x->l = t->l;
        }
        else
        {
            c = x->r;
            while (c->l->l != p_tree->z)
                c = c->l;
            x = c->l;
            c->l = x->r;
            x->l = t->l;
            x->r = t->r;
        }
    }
    unlinked_data = t->data;
    free_node(t, FALSE);
    if (tree_cmp_keys(p_tree, key, p->key) < 0)
        p->l = x;
    else
        p->r = x;
    return (unlinked_data);

}

/* OK */
void           *tree_delete_from_data(HTREE htree, void *key, void *data)
{

    tree           *p_tree = (tree *) htree;
    node           *c,
                   *p,
                   *x,
                   *t;
    void           *unlinked_data;

    p_tree->z->data = data;
    p = p_tree->head;
    x = p_tree->head->r;
    while (data != x->data)
    {
        p = x;
        x = (tree_cmp_keys(p_tree, key, x->key) < 0) ? x->l : x->r;
    }
    p_tree->z->data = NULL;
    if (x == p_tree->z)
        return (NULL);
    t = x;
    if (t->r == p_tree->z)
        x = x->l;
    else
    {
        if (t->r->l == p_tree->z)
        {
            x = x->r;
            x->l = t->l;
        }
        else
        {
            c = x->r;
            while (c->l->l != p_tree->z)
                c = c->l;
            x = c->l;
            c->l = x->r;
            x->l = t->l;
            x->r = t->r;
        }
    }
    unlinked_data = t->data;
    free_node(t, FALSE);
    if (tree_cmp_keys(p_tree, key, p->key) < 0)
        p->l = x;
    else
        p->r = x;
    return (unlinked_data);

}
