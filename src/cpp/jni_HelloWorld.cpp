#include "jni_HelloWorld.h"
#include <iostream>
/*
 * Class:     jni_HelloWorld
 * Method:    sayHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jni_HelloWorld_sayHello (JNIEnv *, jobject) {
    std::cout << "Hello from C++ !!" << std::endl;
}