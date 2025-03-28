package blink

import (
	log "github.com/sirupsen/logrus"
	"os"
	"path/filepath"
)

type writer bool

func (w writer) Write(p []byte) (n int, err error) {
	if w {
		return os.Stdout.Write(p)
	} else {
		return n, nil
	}
}

//日志输出,默认输出
var logger = log.StandardLogger()

//临时目录,用于存放临时文件如:dll,cookie等
var TempPath = filepath.Join(os.TempDir(), "blink")

//是否为调试模式
var isDebug = true

//设置是否为调试模式
func SetDebugMode(debug bool) {
	isDebug = debug
}

//设置临时目录
func SetTempPath(path string) {
	TempPath = path
}
