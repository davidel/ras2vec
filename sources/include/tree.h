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

