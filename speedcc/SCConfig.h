

#ifndef __SPEEDCC__SCCONFIG_H__
#define __SPEEDCC__SCCONFIG_H__

/// SPEEDCC version
// 0x00 HI ME LO
// 00   00 00 00
#define SPEEDCC_VERSION 0x00000100

#define SPEEDCC_FEATURE_ENABLE_MEMORY_POOL

#ifdef SPEEDCC_FEATURE_ENABLE_MEMORY_POOL
#define SPEEDCC_FEATURE_MEMORY_POOL_THREAD_SAFE
#endif

#ifndef kSCDurationOfSceneTransition
#define     kSCDurationOfSceneTransition            0.3 // duration of scene transition
#endif

#ifndef kSCMaxNumberSceneInStack
#define     kSCMaxNumberSceneInStack                20 // max number of scenes in navigation stack
#endif

#ifndef kSCFolderOfAssetSmall
#define kSCFolderOfAssetSmall                                     "assets-small"
#endif

#ifndef kSCFolderOfAssetMedium
#define kSCFolderOfAssetMedium                                    "assets-medium"
#endif

#ifndef kSCFolderOfAssetLarge
#define kSCFolderOfAssetLarge                                     "assets-large"
#endif

#ifndef kSCFolderOfAssetXLarge
#define kSCFolderOfAssetXLarge                                    "assets-xlarge"
#endif

#ifndef kSCFolderOfLanguage
#define kSCFolderOfLanguage                                       "lang"
#endif

#ifndef kSCSettingKeySound
#define kSCSettingKeySound                                          "__speedcc_sound__"
#endif

#ifndef kSCSettingKeyMusic
#define kSCSettingKeyMusic                                          "__speedcc_music__"
#endif

#ifndef kSCDefaultResolutionAsset
#define kSCDefaultResolutionAsset                                   SpeedCC::SCSystem::kAssetBitMaskMedium
#endif

#ifndef kSCWidthOfAssetDesignBaseline
#define kSCWidthOfAssetDesignBaseline                             (384)
#endif

#ifndef kSCHeightOfAssetDesignBaseline
#define kSCHeightOfAssetDesignBaseline                            (512)
#endif

#ifndef kSCWidthOfAssetDesignSmall
#define kSCWidthOfAssetDesignSmall                                 kSCWidthOfAssetDesignBaseline
#endif

#ifndef kSCHeightOfAssetDesignSmall
#define kSCHeightOfAssetDesignSmall                                kSCHeightOfAssetDesignBaseline
#endif

#ifndef kSCWidthOfAssetDesignMedium
#define kSCWidthOfAssetDesignMedium                                (kSCWidthOfAssetDesignSmall*2)
#endif

#ifndef kSCHeightOfAssetDesignMedium
#define kSCHeightOfAssetDesignMedium                               (kSCHeightOfAssetDesignSmall*2)
#endif

#ifndef kSCWidthOfAssetDesignLarge
#define kSCWidthOfAssetDesignLarge                                 (kSCWidthOfAssetDesignSmall*4)
#endif

#ifndef kSCHeightOfAssetDesignLarge
#define kSCHeightOfAssetDesignLarge                                (kSCHeightOfAssetDesignSmall*4)
#endif

#ifndef kSCWidthOfAssetDesignXLarge
#define kSCWidthOfAssetDesignXLarge                                (kSCWidthOfAssetDesignSmall*8)
#endif

#ifndef kSCHeightOfAssetDesignXLarge
#define kSCHeightOfAssetDesignXLarge                               (kSCHeightOfAssetDesignSmall*8)
#endif

#endif // __SPEEDCC__SCCONFIG_H__
