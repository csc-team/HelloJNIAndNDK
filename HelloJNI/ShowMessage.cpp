
#include <jni.h>
#include <stdio.h>
#include "ShowMessage.h"

extern "C" JNIEXPORT void JNICALL 
Java_ShowMessage_showMessage(JNIEnv* env, jobject, jstring jMsg) {
  const char* msg=env->GetStringUTFChars(jMsg,0);
  printf("%s \n",msg);
  env->ReleaseStringUTFChars(jMsg, msg);
} ///:~


