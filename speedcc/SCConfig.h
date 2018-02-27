/****************************************************************************

 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
****************************************************************************/


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
#define kSCDefaultResolutionAsset                                   SpeedCC::SCSystem::kResolutionBitMaskMedium
#endif

#ifndef kSCWidthOfResolutionBaseline
#define kSCWidthOfResolutionBaseline                             (320)
#endif

#ifndef kSCHeightOfResolutionBaseline
#define kSCHeightOfResolutionBaseline                            (480)
#endif

#ifndef kSCWidthOfResolutionSmall
#define kSCWidthOfResolutionSmall                                 kSCWidthOfResolutionBaseline
#endif

#ifndef kSCHeightOfResolutionSmall
#define kSCHeightOfResolutionSmall                                kSCHeightOfResolutionBaseline
#endif

#ifndef kSCWidthOfResolutionMedium
#define kSCWidthOfResolutionMedium                                (kSCWidthOfResolutionSmall*2)
#endif

#ifndef kSCHeightOfResolutionMedium
#define kSCHeightOfResolutionMedium                               (kSCHeightOfResolutionSmall*2)
#endif

#ifndef kSCWidthOfResolutionLarge
#define kSCWidthOfResolutionLarge                                 (kSCWidthOfResolutionSmall*4)
#endif

#ifndef kSCHeightOfResolutionLarge
#define kSCHeightOfResolutionLarge                                (kSCHeightOfResolutionSmall*4)
#endif

#ifndef kSCWidthOfResolutionXLarge
#define kSCWidthOfResolutionXLarge                                (kSCWidthOfResolutionSmall*8)
#endif

#ifndef kSCHeightOfResolutionXLarge
#define kSCHeightOfResolutionXLarge                               (kSCHeightOfResolutionSmall*8)
#endif

#endif // __SPEEDCC__SCCONFIG_H__
