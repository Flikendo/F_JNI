#include "jni_UserData.h"
#include <iostream>

/*
 * Class:     jni_UserData
 * Method:    createUser
 * Signature: (Ljava/lang/String;I)Ljni/User;
 */
JNIEXPORT jobject JNICALL Java_jni_UserData_createUser (JNIEnv *env, jobject thisObject, jstring name, jint balance) {
    // Create the object of the class UserData
        jclass userDataClass = env->FindClass("jni/User");
        jobject newUserData = env->AllocObject(userDataClass);

        // Get the UserData fields to be set
        jfieldID nameField = env->GetFieldID(userDataClass , "name", "Ljava/lang/String;");
        jfieldID balanceField = env->GetFieldID(userDataClass , "balance", "D");

        env->SetObjectField(newUserData, nameField, name);
        env->SetDoubleField(newUserData, balanceField, balance);

        return newUserData;
}

/*
 * Class:     jni_UserData
 * Method:    printData
 * Signature: (Ljni/User;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_jni_UserData_printData (JNIEnv *env, jobject thisObject, jobject user) {
    // Find the id of the Java method to be called
        jclass userDataClass=env->GetObjectClass(user);
        jmethodID methodId=env->GetMethodID(userDataClass, "getUserInfo", "()Ljava/lang/String;");

        jstring result = (jstring)env->CallObjectMethod(user, methodId);
        return result;
}