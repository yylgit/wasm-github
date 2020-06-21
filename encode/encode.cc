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
 * 传输加密key
 *  */ 
char  *privateKey;

/**
 * 解密key
 *  */ 
char  *decodeKey;



EM_PORT_API(const char*)  get_key(char* publicKey) {
  printf("%s\n", publicKey);
	static const char str[] = "wasm:publicKey 加密后的privateKey";
	return str;
}

EM_PORT_API(const char*)  set_key(char* key) {
  static const char str[] = "wasm:privateKey 解密后的decodeKey";
  printf("%s\n", str);
	return 0;
}

//ccall_wrap.cc
EM_PORT_API(char*) decode_data(char* data, int count) {
	data[0] = 1;
	return data;
}