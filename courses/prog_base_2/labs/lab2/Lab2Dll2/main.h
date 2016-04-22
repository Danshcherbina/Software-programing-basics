#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

//#include <stdio.h>
#include "list.h"

int DLL_EXPORT compare(list_t * self);
void DLL_EXPORT reaction(list_t * self,int ind);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
