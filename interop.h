// JS和GO交互的部分
#ifndef INTEROP_DEFINE_H
#define INTEROP_DEFINE_H

#include "stdio.h"
#include "stdlib.h"
#include "mb.h"
mbJsValue tempJsvalue;
mbJsExecState tempEs;
void initInterop();
void MB_CALL_TYPE onDidCreateScriptContextCallback(mbWebView webView, void *param, mbWebFrameHandle frameId, void *context, int extensionGroup, int worldId);
const char *runJSProxy(mbWebView window, char *script);
void callbackProxy(mbWebView window, int64_t queryId, int customMsg, char *response);
#endif