2.4.4 字符串
字符串是极为常用的数据类型，然而C/C++中的字符串表达方式（0值标志结尾）与JavaScript完全不兼容；幸运的是，Emscripten为我们提供了一组辅助函数用于二者的转换，下面介绍其中较为常用的两个。

Pointer_stringify()
该方法可以将C/C++的字符串转换为JavaScript字符串。例如：

C函数get_string()返回了一个字符串的地址：

//strings.cc
EM_PORT_API(const char*) get_string() {
	static const char str[] = "Hello, wolrd! 你好，世界！"
	return str;
}
在JavaScript中获取该字符串地址，并通过Pointer_stringify()将其转换为JavaScript字符串：

//strings.html
      var ptr = Module._get_string();
      var str = Pointer_stringify(ptr);
      console.log(typeof(str));
      console.log(str);
控制台将输出：

string
Hello, wolrd! 你好，世界！
allocateUTF8()
该方法将在C/C内存中分配足够大的空间，并将字符串按UTF8格式拷入其中。例如，在JavaScript中使用allocateUTF8()将字符串传入C/C内存，然后调用C函数print_string()打印它：

//strings.html
      ptr = allocateUTF8("你好，Emscripten！");
      Module._print_string(ptr);
      _free(ptr);
C代码部分：

//strings.cc
EM_PORT_API(void) print_string(char* str) {
	printf("%s\n", str);
}
网页浏览后，控制台将输出：

你好，Emscripten！
此外，Emscripten还提供了AsciiToString()/stringToAscii()/UTF8ArrayToString()/stringToUTF8Array()等一系列辅助函数用于处理各种格式的字符串在各种存储对象中的转换，欲知详情请自行参考胶水代码。