#include "interop.h"
#include "export.h"

// 初始化交互功能
void initInterop()
{
}

void MB_CALL_TYPE onMbRunJsCallback(mbWebView webView, void *param, mbJsExecState es, mbJsValue v)
{
    tempJsvalue = v;
    tempEs = es;
}

// 当JS引擎初始化完毕,这个时候需要挂载golang的Interop
void MB_CALL_TYPE onDidCreateScriptContextCallback(mbWebView window, void *param, mbWebFrameHandle frameId, void *context, int extensionGroup, int worldId)
{
    // 只有main frame才初始化
    if (mbIsMainFrame(window, frameId))
    {
        char *jsContent = goGetInteropJS(window);
        mbRunJs(window, frameId, jsContent, TRUE, onMbRunJsCallback, NULL, NULL);
        free(jsContent);
    }
}

// run js代理,供golang来调用
const utf8 *runJSProxy(mbWebView window, char *script)
{
    mbWebFrameHandle frameId = mbWebFrameGetMainFrame(window);
    mbRunJs(window, frameId, script, TRUE, onMbRunJsCallback, NULL, NULL);
    return mbJsToString(tempEs, tempJsvalue);
    free(script);
}

// 回调代理函数,由Golang来调用,当Golang的分发器函数完成调用后,会调用此函数,把调用结果返回给JS
void callbackProxy(mbWebView window, int64_t queryId, int customMsg, char *response)
{
    mbResponseQuery(window, queryId, customMsg, response);
    free(response);
}