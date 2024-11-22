package blink

//#include "blink.h"
import "C"

import (
	"github.com/lxn/win"
	"path/filepath"
	"runtime"
)

//任务队列,保证所有的API调用都在痛一个线程
var jobQueue = make(chan func())

//初始化blink,释放并加载dll,启动调用队列
func InitBlink() error {
	//定义dll的路径
	dllPath, err := getDllPath()
	if err != nil {
		return err
	}
	mainDllPath, err := getMainDllPath()
	if err != nil {
		return err
	}
	//启动一个新的协程来处理blink的API调用
	go func() {
		//将这个协程锁在当前的线程上
		runtime.LockOSThread()

		//初始化
		C.initBlink(
			C.CString(dllPath),
			C.CString(mainDllPath),
			C.CString(TempPath),
			C.CString(filepath.Join(TempPath, "cookie.dat")),
		)

		//消费API调用,同时处理好windows消息
		for {
			select {
			case job := <-jobQueue:
				job()
			default:
				//消息循环
				msg := &win.MSG{}
				if win.GetMessage(msg, 0, 0, 0) != 0 {
					win.TranslateMessage(msg)
					//是否传递下去
					next := true
					//拿到对应的webview
					view := getWebViewByHandle(msg.HWnd)
					if view != nil {
						next = view.processMessage(msg)
					}
					if next {
						win.DispatchMessage(msg)
					}
				}
			}
		}
	}()

	return nil
}
