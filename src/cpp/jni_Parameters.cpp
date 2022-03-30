#include "jni_Parameters.h"
#include <iostream>

using namespace std;

/*
 * Class:     jni_Parameters
 * Method:    sumIntegers
 * Signature: (II)I
 */
JNIEXPORT jlong JNICALL Java_jni_Parameters_sumIntegers (JNIEnv *env, jobject j_parameters, jint first_num,
                                                         jint second_num) {
    return (long)first_num + (long)second_num;
}

/*
 * Class:     jni_Parameters
 * Method:    isHigherThan
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_jni_Parameters_isHigherThan (JNIEnv *env, jobject j_parameters, jint first_num,
                                                            jint second_num) {
    if (first_num < second_num) {
        cout << "Firts number is lower than the second number." << endl;
    } else {
        cout << "Second number is higher than the first number." << endl;
    }
}