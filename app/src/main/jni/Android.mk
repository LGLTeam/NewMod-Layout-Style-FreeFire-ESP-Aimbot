LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

#include $(CLEAR_VARS)
#LOCAL_MODULE := epcm
#LOCAL_ARM_MODE := arm
#LOCAL_SRC_FILES := $(MAIN_LOCAL_PATH)/src/GL/libAegisGL.a
#LOCAL_EXPORT_C_INCLUDES := /src/GL/include

#include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
# Here is the name of your lib.
# When you change the lib name, change also on System.loadLibrary("") under OnCreate method on StaticActivity.java
# Both must have same name
LOCAL_MODULE    := VXTeam

# Code optimization
# -std=c++17 is required to support AIDE app with NDK
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

# Here you add the cpp file
LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)
LOCAL_SRC_FILES := src/main.cpp \
	src/Substrate/hde64.c \
	src/Substrate/SubstrateDebug.cpp \
	src/Substrate/SubstrateHook.cpp \
	src/Substrate/SubstratePosixMemory.cpp \
	src/KittyMemory/KittyMemory.cpp \
	src/KittyMemory/MemoryPatch.cpp \
    src/KittyMemory/MemoryBackup.cpp \
    src/KittyMemory/KittyUtils.cpp \
	src/Unity/Vector2.hpp \
    src/Unity/Vector3.hpp \
    src/Unity/Quaternion.hpp \
    src/Unity/Color.hpp \
    src/Engine/Rect.cpp \
    src/Engine/Paint.cpp \
    src/Engine/Canvas.cpp \
    src/Engine/Typeface.cpp \

LOCAL_LDLIBS := -llog -landroid

include $(BUILD_SHARED_LIBRARY)
