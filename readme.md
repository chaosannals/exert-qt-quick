# exert qt quick

## 参考的开源库

[FluentUI](https://github.com/zhuzichu520/FluentUI)

## 打包

```bash
# windeployqt 只是通过扫描 exe 文件把依赖复制到相同目录下。属于绿色版本。
# 要在 build （最好用 Release Build的）后的生成物目录里面执行。
# --qmldir QML 所在目录
# qml 的比传统 QT 要复杂，打包后还是不能执行 TODO
windeployqt appcppNqml.exe --qmldir "./cppNqml"
```