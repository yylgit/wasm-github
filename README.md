
1 安装emcc
编译c文件的方法 gcc 文件名

2 emcc 编译命令的参数
emcc mem.cc -o mem.js

EMSCRIPTEN_KEEPALIVE

默认情况下，Emscripten生成的代码只会调用main()函数，其他函数将被视为无用代码。
为了避免这件事发生，我们需要在C函数名之前，添加EMSCRIPTEN_KEEPALIVE，它在emscripten.h中声明。


Module._malloc(4 * count); c中分配内存的单位是字节

3 c中编译导出的方法在js中的调用

4 参数的传递 



