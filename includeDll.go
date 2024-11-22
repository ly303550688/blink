//不包含dll，使用独立dll

package blink

//获取dll路径
func getDllPath() (string, error) {
	return  "mb.dll", nil
}
func getMainDllPath() (string, error) {
	return "node.dll", nil
}
