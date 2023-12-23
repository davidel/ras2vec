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

