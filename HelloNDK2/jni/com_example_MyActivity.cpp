#include <cstdlib>
#include "android_log.h"
#include "com_example_MyActivity.h"

JNIEXPORT jstring JNICALL Java_com_example_MyActivity_function
  (JNIEnv * env, jobject obj, jbyteArray string){

	// get "string" from JVM
	const size_t STRING_LENGTH = env->GetArrayLength(string);
	char * buffer = new char[STRING_LENGTH];
	env->GetByteArrayRegion(string, 0, STRING_LENGTH, (jbyte*) buffer);
	env->ReleaseByteArrayElements(string, (jbyte*) buffer, 0);

	LOGI(buffer);

	jstring result = env->NewStringUTF("done");
	return result;
}
