#ifndef EM_PORT_API
#	if defined(__EMSCRIPTEN__)
#		include <emscripten.h>
#		if defined(__cplusplus)
#			define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#		else
#			define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#		endif
#	else
#		if defined(__cplusplus)
#			define EM_PORT_API(rettype) extern "C" rettype
#		else
#			define EM_PORT_API(rettype) rettype
#		endif
#	endif
#endif

#include <stdio.h>
/**
 * Js 传给wasm A 获取到 用A加密的 随机的 对称密钥B
 */
EM_PORT_API(const char*) getTransKey(char* publicKey) {
	return "publicKey加密的对称密钥";
}

/**
 * Js把B传给后端  后端用私钥解密获取 B 用B加密传输 音视频密钥C
 */
EM_PORT_API(void)  saveDecodeKey(char* key) {
	printf("%s\n", key);
}

EM_PORT_API(int*) decodeData(int* ptr) {
	return ptr;
}