#include "event.h"
#include "webview.h"

mbWebView createWebWindow(bool isTransparent, int x, int y, int width, int height)
{
    mbWebView window = mbCreateWebWindow(isTransparent ? MB_WINDOW_TYPE_TRANSPARENT : MB_WINDOW_TYPE_POPUP, NULL, x, y, width, height);
    // 设置数据目录
    mbSetLocalStorageFullPath(window, wlocalstorage);
    mbSetCookieJarFullPath(window, wcookiejar);
    mbSetNavigationToNewWindowEnable(window, true);
    // 初始化网络文件系统
    initNetFS(window);
    // 初始化webview事件
    initWebViewEvent(window);
    return window;
}

HWND getWindowHandle(mbWebView window)
{
    return mbGetHostHWND(window);
}

void loadURL(mbWebView window, char *url)
{
    mbLoadURL(window, url);
    free(url);
}

void reloadURL(mbWebView window)
{
    mbReload(window);
}

void setWindowTitle(mbWebView window, char *title)
{
    mbSetWindowTitle(window, title);
    free(title);
}

const char *getWebTitle(mbWebView window)
{
    return mbGetTitle(window);
}

void destroyWindow(mbWebView window)
{
    mbDestroyWebView(window);
}

void resizeWindow(mbWebView window, int width, int height)
{
    mbResize(window, width, height);
}

void setDebugConfig(mbWebView webView, const char *debugString, const char *param)
{
    mbSetDebugConfig(webView, debugString, param);
}