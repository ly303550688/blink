#include "webview.h"
#include "export.h"

void initGlobalEvent()
{
}

// 当文档ready的时候
void MB_CALL_TYPE onDocumentReady2Callback(mbWebView window, void *param, mbWebFrameHandle frameId)
{
    // 只触发main frame 的 ready
    if (mbWebFrameGetMainFrame(window) == frameId)
    {
        goOnDocumentReadyCallback(window);
    }
}

BOOL MB_CALL_TYPE onWindowDestroyCallback(mbWebView webView, void *param, void *unuse)
{
    goOnWindowDestroyCallback(webView, param, unuse);
    return TRUE;
}

// 当网页标题(title)改变的时候
void MB_CALL_TYPE onTitleChangedCallback(mbWebView window, void *param, const utf8 *title)
{
    goOnTitleChangedCallback(window, title);
}
BOOL MB_CALL_TYPE onDownload(mbWebView webView, void *param, mbWebFrameHandle frameId, const char *url, void *downloadJob)
{
    goOnDownloadFile(webView, url);
    return false;
}

// 加载完成
void MB_CALL_TYPE onLoadingFinish(mbWebView webView, void *param, mbWebFrameHandle frameId, const utf8 *url, mbLoadingResult result, const utf8 *failedReason)
{
    goOnLoadingFinish(webView, url, result, failedReason);
}

mbWebView MB_CALL_TYPE onCreateView(mbWebView webView, void *param, mbNavigationType navigationType, const utf8 *url, const mbWindowFeatures *windowFeatures)
{
    mbWebView newWebView = mbCreateWebWindow(MB_WINDOW_TYPE_POPUP, NULL, windowFeatures->x, windowFeatures->y, windowFeatures->width, windowFeatures->height);
    mbSetLocalStorageFullPath(newWebView, wlocalstorage);
    mbSetCookieJarFullPath(newWebView, wcookiejar);
    mbSetNavigationToNewWindowEnable(newWebView, true);
    initWebViewEvent(newWebView);
    goNewWebViewInit(newWebView);
    goOnNewWebView(webView, newWebView, url);
    mbShowWindow(newWebView, true);
    return newWebView;
}
void MB_CALL_TYPE onJsQueryCallback(mbWebView webView, void *param, mbJsExecState es, int64_t queryId, int customMsg, const utf8 *request)
{
    if (customMsg == 0)
    {
        goInvokeDispatcher(webView, queryId, customMsg, request);
    }
}

void initWebViewEvent(mbWebView window)
{
    // 窗口被销毁
    mbOnDestroy(window, onWindowDestroyCallback, NULL);
    // JS引擎初始化完毕
    mbOnDidCreateScriptContext(window, onDidCreateScriptContextCallback, NULL);
    // document ready
    mbOnDocumentReady(window, onDocumentReady2Callback, NULL);
    // title changed
    mbOnTitleChanged(window, onTitleChangedCallback, NULL);
    // 文件下载
    mbOnDownload(window, onDownload, NULL);
    // 打开新窗口
    mbOnCreateView(window, onCreateView, NULL);
    // 加载完成事件
    mbOnLoadingFinish(window, onLoadingFinish, NULL);
    mbOnJsQuery(window, onJsQueryCallback, NULL);
}