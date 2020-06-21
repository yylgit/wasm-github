利用ccall和cwrap方法

emcc encode.cc -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s TOTAL_MEMORY=1610612736 -s TOTAL_STACK=67108864 -o encode.js

// 总内存256m 栈内存64m