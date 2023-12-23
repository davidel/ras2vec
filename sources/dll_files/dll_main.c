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

/* OK */
BOOL WINAPI DllMain(HINSTANCE h_instance,DWORD reason,LPVOID p_param)
{

static int process_attached=0,
           thread_attached=0;

switch(reason){
  case(DLL_PROCESS_ATTACH):
    ++process_attached;
    break;

  case(DLL_PROCESS_DETACH):
    --process_attached;
    break;

  case(DLL_THREAD_ATTACH):
    ++thread_attached;
    break;

  case(DLL_THREAD_DETACH):
    --thread_attached;
    break;
}
return(TRUE);

}

