// 事件相关的接口
#ifndef EVENT_DEFINE_H
#define EVENT_DEFINE_H

#include "mb.h"
#include "interop.h"

void initGlobalEvent();

void initWebViewEvent(mbWebView window);
void MB_CALL_TYPE onTitleChangedCallback(mbWebView window, void *param, const utf8 *title);
#endif