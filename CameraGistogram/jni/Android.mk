LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := test
### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES := test.cpp histogram.cpp
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)
