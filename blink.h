// blink接口头文件
#ifndef BLINK_DEFINE_H
#define BLINK_DEFINE_H

#include "stdio.h"
#include "mb.h"
#include "interop.h"
#include "event.h"
#include "webview.h"

void initBlink(char *dllpath, char *mainDllpath, char *localstorage, char *cookiejar);

#endif