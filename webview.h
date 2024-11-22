//webview接口头文件
#ifndef WEBVIEW_DEFINE_H
#define WEBVIEW_DEFINE_H

#include "stdio.h"
#include "mb.h"
#include "netfs.h"
#include "interop.h"
#include "event.h"

wchar_t *wlocalstorage;
wchar_t *wcookiejar;

mbWebView createWebWindow(bool isTransparent, int x, int y, int width, int height);
HWND getWindowHandle(mbWebView window);
void loadURL(mbWebView window, char *url);
void reloadURL(mbWebView window);
void setWindowTitle(mbWebView window, char *title);
const char *getWebTitle(mbWebView window);
void destroyWindow(mbWebView window);
void showDevTools(mbWebView window);
void resizeWindow(mbWebView window,int width,int height);
void setDebugConfig(mbWebView webView, const char* debugString, const char* param);
#endif