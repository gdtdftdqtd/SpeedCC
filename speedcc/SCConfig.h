

#ifndef __SPEEDCC__SCCONFIG_H__
#define __SPEEDCC__SCCONFIG_H__


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

#ifndef kSCDefaultResolutionAsset
#define kSCDefaultResolutionAsset                                   SCSystem::kAssetBitMaskMedium
#endif

#ifndef kSCWidthOfAssetDesignBaseline
#define kSCWidthOfAssetDesignBaseline                             (320)
#endif

#ifndef kSCHeightOfAssetDesignBaseline
#define kSCHeightOfAssetDesignBaseline                            (480)
#endif

#define kSCWidthOfAssetDesignSmall                                 kSCWidthOfAssetDesignBaseline
#define kSCHeightOfAssetDesignSmall                                kSCHeightOfAssetDesignBaseline

#define kSCWidthOfAssetDesignMedium                                (kSCWidthOfAssetDesignSmall*2)
#define kSCHeightOfAssetDesignMedium                               (kSCHeightOfAssetDesignSmall*2)

#define kSCWidthOfAssetDesignLarge                                 (kSCWidthOfAssetDesignSmall*4)
#define kSCHeightOfAssetDesignLarge                                (kSCHeightOfAssetDesignSmall*4)

#define kSCWidthOfAssetDesignXLarge                                (kSCWidthOfAssetDesignSmall*8)
#define kSCHeightOfAssetDesignXLarge                               (kSCHeightOfAssetDesignSmall*8)

#endif // __SPEEDCC__SCCONFIG_H__
