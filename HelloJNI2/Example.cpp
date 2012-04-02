

#include "Example.h"



JNIEXPORT jint JNICALL Java_Example_nativeMethod (JNIEnv *je, jobject jo){
	jclass javaClass;
	jfieldID javaFieldID;
	jmethodID javaMethodID;

	printf( "!!! In the native method !!!\n" );
	javaClass = je->GetObjectClass( jo );
	javaFieldID = je->GetFieldID( javaClass, "i", "I" );
	printf( "i = %d.\n", je->GetIntField( jo, javaFieldID ) );
	javaMethodID = je->GetMethodID( javaClass, "printMessage", "()V" );
	//printf( "javaMethodID = %x.\n", javaMethodID );
	je->CallVoidMethod( jo, javaMethodID );
	printf( "!!! About to leave the native method !!!\n" );
return 123;
}
