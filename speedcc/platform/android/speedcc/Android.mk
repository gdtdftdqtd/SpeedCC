LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := speedcc_static
LOCAL_MODULE_FILENAME := libspeedcc

#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/external)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/cocos)
#$(call import-add-path,$(LOCAL_PATH)/../../../../cocos2dx/v3/cocos/audio/include)
#$(call import-add-path,$(LOCAL_PATH)/../../../..)


LOCAL_SRC_FILES := ../../../base/SCMemAllocator.cpp \
					../../../base/SCString.cpp \
					../../../base/SCDataBlock.cpp \
					../../../base/SCDateTime.cpp \
					../../../base/SCDictionary.cpp \
					../../../base/SCObject.cpp \
					../../../base/SCValue.cpp \
					../../../base/SCVersion.cpp \
					../../../base/SCWatchString.cpp \
					../../../cocos/SCBinder.cpp \
					../../../cocos/SCEventEmitter.cpp \
					../../../cocos/SCNodeProperty.cpp \
					../../../cocos/SCNodeUtils.cpp \
					../../../cocos/SCRefHolder.cpp \
					../../../cocos/SCScene.cpp \
					../../../cocos/SCSceneController.cpp \
					../../../cocos/SCSceneNavigator.cpp \
					../../../cocos/SCUIArg.cpp \
					../../../cocos/SCUIBuilder.cpp \
					../../../component/SCActor.cpp \
					../../../component/SCBehaviorCocos.cpp \
					../../../component/SCBehaviorCommon.cpp \
					../../../component/SCBehaviorComponent.cpp \
					../../../component/SCBehaviorStage.cpp \
					../../../component/SCMessage.cpp \
					../../../component/SCMessageDefaultProc.cpp \
					../../../component/SCMessageDispatch.cpp \
					../../../component/SCPerformObject.cpp \
					../../../component/SCRole.cpp \
					../../../component/SCRoleBuilder.cpp \
					../../../component/SCStage.cpp \
					../../../component/SCStrategy.cpp \
					../../../system/SCAudioManager.cpp \
					../../../system/SCFileUtils.cpp \
					../../../system/SCSetting.cpp \
					../../../system/SCStore.cpp \
					../../../system/SCSystem.cpp \
					../../../platform/SCOSSystem.cpp \





LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../base \
					$(LOCAL_PATH)/../../../cocos \
                    $(LOCAL_PATH)/../../../component \
                    $(LOCAL_PATH)/../../../platform \
                    $(LOCAL_PATH)/../../../system \
                    $(LOCAL_PATH)/../../.. 

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_STATIC_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
