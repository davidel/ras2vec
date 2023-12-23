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
#include<ctype.h>
#include<malloc.h>
#include<math.h>
#include<float.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include"ras2vec.h"
#include"dbll_list.h"
#include"bmputil.h"
#include"filescan.h"
#include"himage.h"
#include"vectorize.h"
#include"thinner.h"
#include"log.h"
#include"util.h"
#include"tiffio.h"
#include"tiffext.h"



/* #define DEMO_VERSION */



#define VERSION_HI                  1
#define VERSION_LO                  1
#define MAX_DEMO_SIZE               202
#define CENTER_LINE                 1
#define DOUBLE_LINE                 2
#define DXF_OUTPUT                  1
#define HPGL_OUTPUT                 2
#define POLYLINE_OUTPUT             3
#define EMF_OUTPUT                  4
#define MAX_TOLLERANCE              10.0

#define bound_value(v,mn,mx)        (min((mx),max((mn),(v))))




static int CALLBACK log_proc(char *str_format, va_list args);
static int CALLBACK err_proc(char *str_format, va_list args);
static void     tiff_warning_handler(const char *module, const char *fmt, va_list ap);
static void     tiff_error_handler(const char *module, const char *fmt, va_list ap);
static int      check_file_size(char *file_name, long int max_size_in_kb);




/* OK */
static int CALLBACK log_proc(char *str_format, va_list args)
{

    return (vfprintf(stdout, str_format, args));

}

/* OK */
static int CALLBACK err_proc(char *str_format, va_list args)
{

    return (vfprintf(stderr, str_format, args));

}

/* OK */
static void     tiff_warning_handler(const char *module, const char *fmt, va_list ap)
{

    char           *buffer;
    char            header_str[256];

    module = (module == NULL) ? "tifflib" : module;
    sprintf(header_str, "- %s warning :", module);
    if ((buffer = (char *) malloc(strlen(header_str) + strlen(fmt) + 2)) == NULL)
        return;
    sprintf(buffer, "%s %s\n", header_str, fmt);
    log_vprintf(buffer, ap);
    free(buffer);

}


/* OK */
static void     tiff_error_handler(const char *module, const char *fmt, va_list ap)
{

    char           *buffer;
    char            header_str[256];

    module = (module == NULL) ? "tifflib" : module;
    sprintf(header_str, "- %s error :", module);
    if ((buffer = (char *) malloc(strlen(header_str) + strlen(fmt) + 2)) == NULL)
        return;
    sprintf(buffer, "%s %s\n", header_str, fmt);
    log_vprintf(buffer, ap);
    free(buffer);

}


/* OK */
static int      check_file_size(char *file_name, long int max_size_in_kb)
{

    struct _stat    file_stat;

    _stat(file_name, &file_stat);
    return ((file_stat.st_size > (max_size_in_kb * 1024)) ? FALSE : TRUE);

}


/* OK */
static int      make_conversion_cntline(char *img_file_name, double pnt_error_tollerance,
                        double poly_lenght_factor, char *out_poly_file_name)
{

    int             use_a_copy = TRUE;
    time_t          start_time,
                    end_time;
    char            start_time_str[128],
                    end_time_str[128],
                    file_name_ext[MAX_PATH],
                    temp_img_file_name[MAX_PATH] = "";

    _splitpath(img_file_name, NULL, NULL, NULL, file_name_ext);
    if (stricmp(file_name_ext, ".tif") == 0)
    {
        GetTempFileName(".", "img", 0, temp_img_file_name);
        scr_printf("- reading tiff file %s to bmp file %s\n", img_file_name,
                temp_img_file_name);
        if (!tiff_file_to_bmp_file(img_file_name, temp_img_file_name))
        {
            remove(temp_img_file_name);
            log_printf("- error reading tiff file %s to bmp file %s\n", img_file_name,
                    temp_img_file_name);
            return (FALSE);
        }
        img_file_name = temp_img_file_name;
        use_a_copy = FALSE;
    }
#ifdef DEMO_VERSION
    if (!check_file_size(img_file_name, MAX_DEMO_SIZE))
    {
        if (strlen(temp_img_file_name) > 0)
            remove(temp_img_file_name);
        log_printf("- file %s too long for demo version\n", img_file_name);
        return (FALSE);
    }
#endif          // #ifdef DEMO_VERSION
    time(&start_time);
    scr_printf("- extracting vectors from file %s\n", img_file_name);
    if (!cntline_convert_file(img_file_name, use_a_copy, out_poly_file_name,
                    pnt_error_tollerance, poly_lenght_factor))
    {
        if (strlen(temp_img_file_name) > 0)
            remove(temp_img_file_name);
        log_printf("- error extracting vectors from file %s\n", img_file_name);
        return (FALSE);
    }
    time(&end_time);
    strcpy(start_time_str, ctime(&start_time));
    strcpy(end_time_str, ctime(&end_time));
    scr_printf("- file successfully converted\n"
            "- start conversion time ...: %s"
            "- end conversion time .....: %s"
            "- computation time ........: %lf sec\n", start_time_str,
            end_time_str, difftime(end_time, start_time));
    if (strlen(temp_img_file_name) > 0)
        remove(temp_img_file_name);
    return (TRUE);

}


/* OK */
static int      make_conversion_dblline(char *img_file_name, double pnt_error_tollerance,
                        double poly_lenght_factor, char *out_poly_file_name)
{

    time_t          start_time,
                    end_time;
    char            start_time_str[128],
                    end_time_str[128],
                    file_name_ext[MAX_PATH],
                    temp_img_file_name[MAX_PATH] = "";

    _splitpath(img_file_name, NULL, NULL, NULL, file_name_ext);
    if (stricmp(file_name_ext, ".tif") == 0)
    {
        GetTempFileName(".", "img", 0, temp_img_file_name);
        scr_printf("- reading tiff file %s to bmp file %s\n", img_file_name,
                temp_img_file_name);
        if (!tiff_file_to_bmp_file(img_file_name, temp_img_file_name))
        {
            remove(temp_img_file_name);
            log_printf("- error reading tiff file %s to bmp file %s\n", img_file_name,
                    temp_img_file_name);
            return (FALSE);
        }
        img_file_name = temp_img_file_name;
    }
#ifdef DEMO_VERSION
    if (!check_file_size(img_file_name, MAX_DEMO_SIZE))
    {
        if (strlen(temp_img_file_name) > 0)
            remove(temp_img_file_name);
        log_printf("- file %s too long for demo version\n", img_file_name);
        return (FALSE);
    }
#endif          // #ifdef DEMO_VERSION
    time(&start_time);
    scr_printf("- extracting vectors from file %s\n", img_file_name);
    if (!dblline_convert_file(img_file_name, out_poly_file_name, pnt_error_tollerance,
                    poly_lenght_factor))
    {
        if (strlen(temp_img_file_name) > 0)
            remove(temp_img_file_name);
        log_printf("- error extracting vectors from file %s\n", img_file_name);
        return (FALSE);
    }
    time(&end_time);
    strcpy(start_time_str, ctime(&start_time));
    strcpy(end_time_str, ctime(&end_time));
    scr_printf("- file successfully converted\n"
            "- start conversion time ...: %s"
            "- end conversion time .....: %s"
            "- computation time ........: %lf sec\n", start_time_str,
            end_time_str, difftime(end_time, start_time));
    if (strlen(temp_img_file_name) > 0)
        remove(temp_img_file_name);
    return (TRUE);

}


/* OK */
int             main(int argc, char *argv[])
{

    int             arg,
                    color = 0,
                    conversion_mode = CENTER_LINE,
                    output_mode = DXF_OUTPUT;
    double          x_scale = 1.0,
                    y_scale = 1.0,
                    pnt_error_tollerance = CNT_DEF_MAX_PNT_ERROR,
                    poly_lenght_factor = -1.0;
    char            layer_name[64] = "RAS2VEC",
                    out_directory[MAX_PATH] = ".";

    init_logging(log_proc, err_proc, log_proc);
    TIFFSetErrorHandler((TIFFErrorHandler) tiff_error_handler);
    TIFFSetWarningHandler((TIFFErrorHandler) tiff_warning_handler);
#ifdef DEMO_VERSION
    log_printf("- ras2vec %d.%d DEMO (max %d kb uncompressed)\n"
            "---- by Davide Libenzi <davidel@xmailserver.org> ----\n",
            VERSION_HI, VERSION_LO, MAX_DEMO_SIZE - 2);
#else
    log_printf("- ras2vec %d.%d\n"
            "---- by Davide Libenzi <davidel@xmailserver.org> ----\n", VERSION_HI, VERSION_LO);
#endif          // #ifdef DEMO_VERSION
    if (argc < 2)
    {
        log_printf("- use : ras2vec [-cdhxpXYeo] img_file ...\n"
                "        -c        = centerline (default)\n"
                "        -d        = doubleline\n"
                "        -h        = hpgl output\n"
                "        -m        = emf output\n"
                "        -x        = dxf output (default)\n"
                "        -p        = polyline output\n"
                "        -X sf     = X scale factor (default 1.0)\n"
                "        -Y sf     = Y scale factor (default 1.0)\n"
                "        -e tf     = set tollerance [0..10] (default %lf)\n"
                "        -o dir    = set output directory\n"
                "        -f plf    = set min poly length factor as max(x, y) / plf (default -1.0 = none)\n"
                "        img_file  = image files type {bmp | tif}\n"
                "                    black & white , 1 bit x pixel\n"
                "                    bmp uncompressed , tif all types\n"
                "                    wildcards are allowed\n", pnt_error_tollerance,
                out_directory);
        return (__LINE__);
    }
    for (arg = 1; (arg < argc) && (argv[arg][0] == '-'); arg++)
    {
        switch (argv[arg][1])
        {
            case ('c'):
                conversion_mode = CENTER_LINE;
                break;

            case ('d'):
                conversion_mode = DOUBLE_LINE;
                break;

            case ('h'):
                output_mode = HPGL_OUTPUT;
                break;

            case ('x'):
                output_mode = DXF_OUTPUT;
                break;

            case ('m'):
                output_mode = EMF_OUTPUT;
                break;

            case ('p'):
                output_mode = POLYLINE_OUTPUT;
                break;

            case ('o'):
                if (++arg < argc)
                {
                    int             ii,
                                    dir_length = strlen(argv[arg]);

                    strcpy(out_directory, argv[arg]);

                    for (ii = (dir_length - 1); out_directory[ii] == '\\'; ii--)
                        out_directory[ii] = '\0';
                }
                break;

            case ('X'):
                if (++arg < argc)
                    x_scale = atof(argv[arg]);
                break;

            case ('Y'):
                if (++arg < argc)
                    y_scale = atof(argv[arg]);
                break;

            case ('e'):
                if (++arg < argc)
                    pnt_error_tollerance = atof(argv[arg]);
                pnt_error_tollerance = bound_value(pnt_error_tollerance, 0.0, MAX_TOLLERANCE);
                break;

            case('f'):
                if (++arg < argc)
                    poly_lenght_factor = atof(argv[arg]);
                break;
        }
    }
    for (; arg < argc; arg++)
    {
        HANDLE          find_handle;
        char           *p_bkslsh = strrchr(argv[arg], '\\');
        WIN32_FIND_DATA wfd;
        char            base_file_path[MAX_PATH] = "";

        if (p_bkslsh != NULL)
        {
            int             base_path_length = (int) (p_bkslsh - argv[arg]) + 1;

            strncpy(base_file_path, argv[arg], base_path_length);
            base_file_path[base_path_length] = '\0';
        }

        if ((find_handle = FindFirstFile(argv[arg], &wfd)) == INVALID_HANDLE_VALUE)
        {
            log_printf("- unable to find %s\n", argv[arg]);
            continue;
        }
        do
        {
            int             conversion_result;
            char            input_file_name[MAX_PATH],
                            file_name_base[MAX_PATH],
                            file_name_ext[MAX_PATH],
                            out_poly_file_name[MAX_PATH];

            sprintf(input_file_name, "%s%s", base_file_path, wfd.cFileName);
            _splitpath(wfd.cFileName, NULL, NULL, file_name_base, file_name_ext);
            sprintf(out_poly_file_name, "%s\\%s.ply", out_directory, file_name_base);
            switch (conversion_mode)
            {
                case (DOUBLE_LINE):
                    conversion_result = make_conversion_dblline(input_file_name,
                            pnt_error_tollerance, poly_lenght_factor * 4.0,
                            out_poly_file_name);
                    break;

                case (CENTER_LINE):
                    conversion_result = make_conversion_cntline(input_file_name,
                            pnt_error_tollerance, poly_lenght_factor,
                            out_poly_file_name);
                    break;
            }
            if (conversion_result)
            {
                char            out_file_name[MAX_PATH];

                switch (output_mode)
                {
                    case (EMF_OUTPUT):
                        {
                            sprintf(out_file_name, "%s\\%s.emf", out_directory, file_name_base);
                            scr_printf("- writing emf file %s\n", out_file_name);
                            if (!emf_poly_dump(out_file_name, out_poly_file_name, x_scale, y_scale,
                                            RGB(0, 0, 0)))
                                log_printf("- error writing emf file %s\n", out_file_name);
                            remove(out_poly_file_name);
                        }
                        break;

                    case (HPGL_OUTPUT):
                        {
                            sprintf(out_file_name, "%s\\%s.hgl", out_directory, file_name_base);
                            scr_printf("- writing hpgl file %s\n", out_file_name);
                            if (!hpgl_poly_dump(out_file_name, out_poly_file_name, x_scale, y_scale,
                                            color))
                                log_printf("- error writing hpgl file %s\n", out_file_name);
                            remove(out_poly_file_name);
                        }
                        break;

                    case (DXF_OUTPUT):
                        {
                            sprintf(out_file_name, "%s\\%s.dxf", out_directory, file_name_base);
                            scr_printf("- writing dxf file %s\n", out_file_name);
                            if (!dxf_poly_dump(out_file_name, out_poly_file_name, x_scale, y_scale,
                                            layer_name, color))
                                log_printf("- error writing dxf file %s\n", out_file_name);
                            remove(out_poly_file_name);
                        }
                        break;

                    case (POLYLINE_OUTPUT):
                        break;
                }
            }
            else
                remove(out_poly_file_name);
            scr_printf("- done\n\n");
        } while (FindNextFile(find_handle, &wfd));
        FindClose(find_handle);
    }
    return (0);

}
