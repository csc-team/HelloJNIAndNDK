#include "com_example_MyActivity.h"

JNIEXPORT jstring JNICALL Java_com_example_MyActivity_getString (JNIEnv *env , jobject){
    jstring result = env->NewStringUTF("HELLO_DK");
 }