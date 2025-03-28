// blink函数实现,负责和golang做交互,并包装wke调用
#include "blink.h"

void initBlink(char *dllpath, char *mainDllpath, char *localstorage, char *cookiejar)
{
    // 转换路径字符串类型
    size_t cSize = strlen(dllpath) + 1;
    wchar_t *wdllpath = (wchar_t *)malloc(sizeof(wchar_t) * cSize);
    mbstowcs(wdllpath, dllpath, cSize);

    cSize = strlen(mainDllpath) + 1;
    wchar_t *wmainDllpath = (wchar_t *)malloc(sizeof(wchar_t) * cSize);
    mbstowcs(wmainDllpath, mainDllpath, cSize);

    cSize = strlen(localstorage) + 1;
    wlocalstorage = (wchar_t *)malloc(sizeof(wchar_t) * cSize);
    mbstowcs(wlocalstorage, localstorage, cSize);

    cSize = strlen(cookiejar) + 1;
    wcookiejar = (wchar_t *)malloc(sizeof(wchar_t) * cSize);
    mbstowcs(wcookiejar, cookiejar, cSize);

    // 加载dll
    //mbSetMbDllPath(wdllpath);
    //mbSetMbMainDllPath(wmainDllpath);

    mbSettings settings;
    memset(&settings, 0, sizeof(settings));
    mbInit(&settings);
    // 初始化全局事件
    initGlobalEvent();

    // 初始化JS与Golang的交互功能
    // initInterop();

    // 释放内存
    free(wdllpath);
    free(dllpath);
    free(wmainDllpath);
    free(mainDllpath);
    free(localstorage);
    free(cookiejar);
}