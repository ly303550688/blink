// golang导出的函数,将在这里定义,供C语言调用
#ifndef EXPORT_DEFINE_H
#define EXPORT_DEFINE_H

/******************netfs*****************/
// goGetNetFSData函数返回值
struct goGetNetFSData_Return
{
    int result;
    char *mineType;
    void *data;
    int length;
};

// 获取网络文件系统数据, -> netfs.go
struct goGetNetFSData_Return goGetNetFSData(mbWebView window, const char *url);
/*****************netfs end**************/

/******************interpo*****************/
// 将JS对Golang的调用分发出去
void goInvokeDispatcher(mbWebView webView, int64_t queryId, int customMsg, const utf8 *request);
// 获取interop js
char *goGetInteropJS(mbWebView window);
/*****************interpo end**************/

/******************event*****************/
// window关闭时的回调
void goOnWindowDestroyCallback(mbWebView window, void *param, void *unuse);
// document ready回调
void goOnDocumentReadyCallback(mbWebView window);
// title changed回调
void goOnTitleChangedCallback(mbWebView window, const utf8 *title);
void goOnDownloadFile(mbWebView window, const char *url);
void goOnNewWebView(mbWebView window, mbWebView newWeb, const utf8 *url);
void goNewWebViewInit(mbWebView window);
void goOnLoadingFinish(mbWebView window, const utf8 *url, mbLoadingResult result, const utf8 *reason);
// 回调js
void goOnMbRunJsCallback(const utf8 *result);
void goOnConsole(mbWebView window, mbConsoleLevel level, const utf8 *message, const utf8 *sourceName, unsigned sourceLine, const utf8 *stackTrace);
/*****************event end**************/
#endif