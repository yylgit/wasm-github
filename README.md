
https://www.wenjiangs.com/doc/80ukjl3j

1 安装emcc
编译c文件的方法 gcc 文件名

2 emcc 编译命令的参数
emcc mem.cc -o mem.js

EMSCRIPTEN_KEEPALIVE

默认情况下，Emscripten生成的代码只会调用main()函数，其他函数将被视为无用代码。
为了避免这件事发生，我们需要在C函数名之前，添加EMSCRIPTEN_KEEPALIVE，它在emscripten.h中声明。


3 用户可以使用胶水代码 引入wasm 直接使用Module变量  也可以自己用APi进行倒入

其基本思路是在Module初始化前，向Module中注入一个名为onRuntimeInitialized的方法，Emscripten的Runtime就绪后，将会回调该方法。在hello.js中，我们可以观察到该回调的调用过程：

4 javasript调用c中的方法
添加 EMSCRIPTEN_KEEPALIVE  胶水代码Module._方法名 可以调用

5 javascript方法注入c中
c中声明 
//capi_js.cc
EM_PORT_API(int) js_add(int a, int b);
EM_PORT_API(void) js_console_log_int(int param);

EM_PORT_API(void) print_the_answer() {
    int i = js_add(21, 21);
    js_console_log_int(i);
}

编译的时候打入

执行下列命令：

emcc capi_js.cc --js-library pkg.js -o capi_js.js
--js-library pkg.js意为将pkg.js作为附加库参与链接。命令执行后得到capi_js.js以及capi_js.wasm。按照之前章节的例子在网页中将其载入，并调用C导出的print_the_answer()函数：



5 JavaScript与C交换数据

参数和返回值只能是Number
2.4.1 参数及返回值
在之前章节的例程中，我们有意忽略了一个基础性的问题：JavaScript与C/C++相互调用的时候，参数与返回值究竟是如何传递的？

答案是：一切皆为Number。

tips JavaScript只有一种数值类型：Number，既64位浮点数（IEEE 754标准）

2.4.2 通过内存交换数据  通过内存地址进行交换
需要在JavaScript与C/C++之间交换大块的数据时，直接使用参数传递数据显然不可行，此时可以通过内存来交换数据。如下例，JavaScript调用C函数在内存中生成斐波拉契数列后输出，C代码：

js访问 c的内存
胶水的Module
c返回内存地址 js通过Module.HEAP32 进行访问  HEAP32代表元素的每一项是4个字节 4个字节一个单位 c返回的是字节的绝对地址。

js分配内存传给c
这种用法之所以可行，核心原因在于：Emscripten导出了C的malloc()/free()函数。例如：
var count = 50;
      var ptr = Module._malloc(4 * count);
      for (var i = 0; i < count; i++){
        Module.HEAP32[ptr / 4 + i] = i + 1;
      }
      console.log(Module._sum(ptr, count));
      Module._free(ptr);

6 String类型的处理
胶水代码了提供方法   UTF8ToString 从c中获取string    allocateUTF8 从js中生成string地址
 var ptr = Module._get_string();
       var str = UTF8ToString(ptr);
       console.log(typeof(str));
       console.log(str);
       _free(ptr);
       var ptr2 = allocateUTF8("你好，Emscripten！");
       Module._print_string(ptr2);
       _free(ptr2);




7 ccall/cwrap 封装了 参数传递 可以是非Number类型 但是问题是都放在栈内 数据量要小

2.4节我们提到，JavaScript调用C/C++时只能使用Number作为参数，因此如果参数是字符串、数组等非Number类型，则需要拆分为以下步骤：

使用Module._malloc()在Module堆中分配内存，获取地址ptr；
将字符串/数组等数据拷入内存的ptr处；
将ptr作为参数，调用C/C++函数进行处理；
使用Module._free()释放ptr。
由此可见调用过程相当繁琐，尤其当非Number参数个数较多时，JavaScript侧的调用代码会急剧膨胀。为了简化调用过程，Emscripten提供了ccall/cwrap封装函数。

虽然ccall/cwrap可以简化字符串参数的交换，但这种便利性是有代价的：当输入参数类型为'string'/'array'时，ccall/cwrap在C环境的栈上分配了相应的空间，并将数据拷入了其中，然后调用相应的导出函数。

相对于堆来说，栈空间是很稀缺的资源，因此使用ccall/cwrap时需要格外注意传入的字符串/数组的大小，避免爆栈。





