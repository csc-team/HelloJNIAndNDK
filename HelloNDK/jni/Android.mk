#текущая директория
LOCAL_PATH:= $(call my-dir)

# чтобы можно было вызвать команду ndk-build clean
include $(CLEAR_VARS)
# библиотека которую собираем
LOCAL_MODULE    := example
# исходные файлы через пробел
LOCAL_SRC_FILES := com_example_MyActivity.cpp


include $(BUILD_SHARED_LIBRARY)