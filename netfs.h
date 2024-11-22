//网络文件系统接口头文件
#ifndef NETFS_DEFINE_H
#define NETFS_DEFINE_H

#include "stdio.h"
#include "stdlib.h"
#include "mb.h"

//初始化指定webview的网络文件系统
void initNetFS(mbWebView window);

//url加载开始,回调
BOOL MB_CALL_TYPE handleLoadUrlBegin(mbWebView window, void *param, const char *url, mbNetJob job);
//url加载完毕,回调
void MB_CALL_TYPE handleLoadUrlEnd(mbWebView window, void *param, const char *url, mbNetJob job, void *buf, int len);

#endif