#include <string.h>
#include <jni.h>
#include "../com_blogspot_jia3ep_test_TestActivity.h"
#include "../com_blogspot_jia3ep_test_HistogramView.h"
#include "histogram.h"

JNIEXPORT jstring JNICALL Java_com_blogspot_jia3ep_test_TestActivity_get_1text_1from_1cpp
  (JNIEnv * env, jobject)
{
	return env->NewStringUTF( "hello from C++" );
}

JNIEXPORT jlong JNICALL Java_com_blogspot_jia3ep_test_HistogramView_initCppSide
  (JNIEnv *, jobject)
{
	histogram* h = new histogram;
	return reinterpret_cast<long>( h );
}

JNIEXPORT void JNICALL Java_com_blogspot_jia3ep_test_HistogramView_doneCppSide
  (JNIEnv *, jobject, jlong cppobj)
{
	histogram* h = reinterpret_cast<histogram*>( cppobj );
	delete h;
}

JNIEXPORT void JNICALL Java_com_blogspot_jia3ep_test_HistogramView_calculateHistogram
  (JNIEnv* env, jobject, jlong cppobj, jintArray jr, jintArray jg, jintArray jb)
{
	int* r = static_cast<int*>(env->GetPrimitiveArrayCritical( jr, 0 ));
	int* g = static_cast<int*>(env->GetPrimitiveArrayCritical( jg, 0 ));
	int* b = static_cast<int*>(env->GetPrimitiveArrayCritical( jb, 0 ));

	histogram* h = reinterpret_cast<histogram*>( cppobj );
	h->get_histograms( r, g, b );

	env->ReleasePrimitiveArrayCritical( jb, r, 0 );
	env->ReleasePrimitiveArrayCritical( jg, g, 0 );
	env->ReleasePrimitiveArrayCritical( jr, b, 0 );
}

JNIEXPORT void JNICALL Java_com_blogspot_jia3ep_test_HistogramView_decodeYUV420SP
  (JNIEnv* env, jobject, jlong cppobj, jbyteArray jyuv420sp, jint width, jint height)
{
	unsigned char* yuv420sp = static_cast<unsigned char*>(env->GetPrimitiveArrayCritical( jyuv420sp, 0 ));

	histogram* h = reinterpret_cast<histogram*>( cppobj );
	h->init_from_YUV420SP( yuv420sp, width, height );

	env->ReleasePrimitiveArrayCritical( jyuv420sp, yuv420sp, 0 );
}

JNIEXPORT jint JNICALL Java_com_blogspot_jia3ep_test_HistogramView_getMaxHeight
  (JNIEnv *, jobject, jlong cppobj)
{
	const histogram* h = reinterpret_cast<const histogram*>( cppobj );
	return h->get_max_height();
}

JNIEXPORT jint JNICALL Java_com_blogspot_jia3ep_test_HistogramView_getHeight
  (JNIEnv *, jobject, jlong cppobj)
{
	const histogram* h = reinterpret_cast<const histogram*>( cppobj );
	return h->get_height();
}


JNIEXPORT jint JNICALL Java_com_blogspot_jia3ep_test_HistogramView_getWidth
  (JNIEnv *, jobject, jlong cppobj)
{
	const histogram* h = reinterpret_cast<const histogram*>( cppobj );
	return h->get_width();

}
