package blink

//#include "event.h"
//#include "webview.h"
import "C"
import (
	"github.com/lxn/win"
	"unsafe"
)

//export goOnWindowDestroyCallback
func goOnWindowDestroyCallback(window C.mbWebView, param unsafe.Pointer, unuse unsafe.Pointer) {
	go func() {
		view := getWebViewByWindow(window)
		view.Emit("destroy", view)
	}()
}

//export goOnDocumentReadyCallback
func goOnDocumentReadyCallback(window C.mbWebView) {
	go func() {
		view := getWebViewByWindow(window)
		view.Emit("documentReady", view)
	}()
}

//export goOnTitleChangedCallback
func goOnTitleChangedCallback(window C.mbWebView, titleString *C.char) {
	//把C过来的字符串转化为golang的
	titleGoString := C.GoString(titleString)

	go func() {
		view := getWebViewByWindow(window)
		view.Emit("titleChanged", view, titleGoString)
	}()
}

//export goOnDownloadFile
func goOnDownloadFile(window C.mbWebView, url *C.char) {
	strurl := C.GoString(url)
	go func() {
		view := getWebViewByWindow(window)
		view.Emit("DownloadFile", strurl)
	}()
}

//export goOnLoadingFinish
func goOnLoadingFinish(window C.mbWebView, url *C.char, result C.mbLoadingResult, failedReason *C.char) {
	strurl := C.GoString(url)
	reason := C.GoString(failedReason)
	go func() {
		view := getWebViewByWindow(window)
		view.Emit("LoadingFinish", view, strurl, int(result), reason)
	}()
}

//export goOnNewWebView
func goOnNewWebView(window C.mbWebView, newWebView C.mbWebView, url *C.char) {
	strurl := C.GoString(url)
	go func() {
		view := getWebViewByWindow(window)
		view.Emit("NewWebView", getWebViewByWindow(newWebView), strurl)
	}()
}

//export goNewWebViewInit
func goNewWebViewInit(window C.mbWebView) {
	view := &WebView{
		autoTitle:     true,
		jsFunc:        make(map[string]interface{}),
		jsData:        make(map[string]string),
		DocumentReady: make(chan interface{}),
		Destroy:       make(chan interface{}),
		IsDestroy:     false,
		isTransparent: false,
	}
	//初始化event emitter
	view.Init()

	view.window = window
	view.handle = win.HWND(uintptr(unsafe.Pointer(C.getWindowHandle(view.window))))

	//初始化各种事件
	//destroy的时候需要设置标志位
	view.On("destroy", func(v *WebView) {
		//关闭destroy,如果已经关闭了,则无需关闭
		select {
		case <-v.Destroy:
			break
		default:
			close(v.Destroy)
		}
		v.IsDestroy = true
	})
	view.On("documentReady", func(v *WebView) {
		select {
		case <-v.DocumentReady:
			break
		default:
			close(v.DocumentReady)
		}
	})
	//同步网页标题到窗口
	view.On("titleChanged", func(view *WebView, title string) {
		if view.autoTitle {
			view.SetWindowTitle(title)
		}
	})

	//注入预置的API给js调用
	view.Inject("MoveToCenter", view.MoveToCenter)
	view.Inject("SetWindowTitle", view.SetWindowTitle)
	view.Inject("EnableAutoTitle", view.EnableAutoTitle)
	view.Inject("DisableAutoTitle", view.DisableAutoTitle)
	view.Inject("ShowDockIcon", view.ShowDockIcon)
	view.Inject("HideDockIcon", view.HideDockIcon)
	view.Inject("ShowWindow", view.ShowWindow)
	view.Inject("HideWindow", view.HideWindow)
	view.Inject("ShowDevTools", view.ShowDevTools)
	view.Inject("ToTop", view.ToTop)
	view.Inject("MostTop", view.MostTop)
	view.Inject("MinimizeWindow", view.MinimizeWindow)
	view.Inject("MaximizeWindow", view.MaximizeWindow)
	view.Inject("RestoreWindow", view.RestoreWindow)
	view.Inject("DestroyWindow", view.DestroyWindow)
	view.Inject("SetResizable", view.SetResizable)
	view.Inject("ResizeWindow", view.ResizeWindow)
	//把webview添加到池中
	addViewToPool(view)
}
