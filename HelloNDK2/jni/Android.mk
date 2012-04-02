LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
# библиотека которую собираем
LOCAL_MODULE    := native_lab1
# исходные файлы через пробел
LOCAL_SRC_FILES := com_example_MyActivity.cpp
# библиотека для работы с логом андроида
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
