/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class jni_UserData */

#ifndef _Included_jni_UserData
#define _Included_jni_UserData
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     jni_UserData
 * Method:    createUser
 * Signature: (Ljava/lang/String;I)Ljni/User;
 */
JNIEXPORT jobject JNICALL Java_jni_UserData_createUser
  (JNIEnv *, jobject, jstring, jint);

/*
 * Class:     jni_UserData
 * Method:    printData
 * Signature: (Ljni/User;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jni_UserData_printData
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
