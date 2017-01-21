LOCAL_PATH := $(call my-dir)
3RD_PARTY_SUPERPOWERED_RELATIVE_PATH := ../../../../../../3rdparty/Superpowered/

include $(CLEAR_VARS)
LOCAL_MODULE := Superpowered
ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	LOCAL_SRC_FILES := $(3RD_PARTY_SUPERPOWERED_RELATIVE_PATH)/libSuperpoweredAndroidarmeabi-v7a.a
else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
	LOCAL_SRC_FILES := $(3RD_PARTY_SUPERPOWERED_RELATIVE_PATH)/libSuperpoweredAndroidarm64-v8a.a
else ifeq ($(TARGET_ARCH_ABI),x86)
	LOCAL_SRC_FILES := $(3RD_PARTY_SUPERPOWERED_RELATIVE_PATH)/libSuperpoweredAndroidX86.a
else ifeq ($(TARGET_ARCH_ABI),x86_64)
	LOCAL_SRC_FILES := $(3RD_PARTY_SUPERPOWERED_RELATIVE_PATH)/libSuperpoweredAndroidX86_64.a
endif

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := game
LOCAL_CFLAGS    := -Wall -Wextra -DNG_OPENGL -DGL_GLEXT_PROTOTYPES=1 -O3 -fsigned-char

#traverse all the directory and subdirectory
define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

PROJECT_ROOT_PATH := $(LOCAL_PATH)/../../../../../../

# Game Framework
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/entity/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/math/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/network/client/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/sound/superpowered/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/state/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/ui/portable/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/ui/opengl/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/framework/util/portable/

ENTITY_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/entity/)
FILE_LIST := $(filter %.cpp, $(ENTITY_FILES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(ENTITY_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

MATH_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/math/)
FILE_LIST := $(filter %.cpp, $(MATH_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(MATH_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

NETWORK_CLIENT_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/network/client/)
FILE_LIST := $(filter %.cpp, $(NETWORK_CLIENT_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(NETWORK_CLIENT_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

SOUND_SUPERPOWERED_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/sound/superpowered/)
FILE_LIST := $(filter %.cpp, $(SOUND_SUPERPOWERED_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(SOUND_SUPERPOWERED_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

STATE_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/state/)
FILE_LIST := $(filter %.cpp, $(STATE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(STATE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

UI_OPENGL_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/ui/opengl)
FILE_LIST := $(filter %.cpp, $(UI_OPENGL_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(UI_OPENGL_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

UI_PORTABLE_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/ui/portable)
FILE_LIST := $(filter %.cpp, $(UI_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(UI_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

UTIL_PORTABLE_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/framework/util/portable)
FILE_LIST := $(filter %.cpp, $(UTIL_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(UTIL_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

# Game
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/game/logic/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/core/game/ui/portable/

GAME_LOGIC_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/game/logic/)
FILE_LIST := $(filter %.cpp, $(GAME_LOGIC_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(GAME_LOGIC_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

GAME_UI_PORTABLE_FILES = $(call walk, $(PROJECT_ROOT_PATH)/core/game/ui/portable/)
FILE_LIST := $(filter %.cpp, $(GAME_UI_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(GAME_UI_PORTABLE_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

# Android
JNI_FILES = $(call walk, $(LOCAL_PATH))
FILE_LIST := $(filter %.cpp, $(JNI_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(JNI_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

# 3rd Party
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/3rdparty/Superpowered/
LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/3rdparty/Superpowered/AndroidIO/

SUPERPOWERED_ANDROID_FILES = $(call walk, $(PROJECT_ROOT_PATH)/3rdparty/Superpowered/AndroidIO/)
FILE_LIST := $(filter %.cpp, $(SUPERPOWERED_ANDROID_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)
FILE_LIST := $(filter %.c, $(SUPERPOWERED_ANDROID_FILES))
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES += $(PROJECT_ROOT_PATH)/3rdparty/
LOCAL_STATIC_LIBRARIES := libpng Superpowered
LOCAL_LDLIBS := -lGLESv2 -landroid -lOpenSLES

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(PROJECT_ROOT_PATH)/3rdparty)
$(call import-module, libpng)