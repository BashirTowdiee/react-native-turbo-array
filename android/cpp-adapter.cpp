#include <jni.h>
#include "react-native-turbo-array.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_turboarray_TurboArrayModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return turboarray::multiply(a, b);
}
