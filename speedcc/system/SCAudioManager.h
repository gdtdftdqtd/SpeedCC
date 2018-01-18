//
//  SCAudioPlayer.hpp
//  libspeedcc
//
//  Created by Kevin on 18/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCAUDIOPLAYER_H__
#define __SPEEDCC__SCAUDIOPLAYER_H__

#include "../base/SCWatchNumberT.h"
#include "../base/SCString.h"

#include "../component/SCMessageDispatch.h"
#include "../component/SCMessage.h"

namespace SpeedCC
{
    class SCAudioManager : public SCMessageListener
    {
    public:
        enum
        {
            kMaskBitIsMusic     = 1<<0,
            kMaskBitIsLoop      = 1<<1,
            kMaskBitIsPreload   = 1<<2,
        };
        
    public:
        struct SAudioListInfo
        {
            const char* const       pszAudioFile;
            unsigned char           byAudioFlag; //
            SCMessageGroup::Ptr     ptrOnMsgGroup;
            SCMessageGroup::Ptr     ptrOffMsgGroup;
        };
    public:
        virtual ~SCAudioManager();
        static SCAudioManager* getInstance();
        
        void pauseMusic();
        void resumeMusic();
        
        void pauseSound(const int nID);
        void resumeSound(const int nID);
        void stopSound(const int nID);
        
        int playSound(const SCString& strFile,const bool bLoop=false);
        void playMusic(const SCString& strFile,const bool bLoop=true);
        
        void preloadSound(const SCString& strFile);
        void preloadMusic(const SCString& strFile);
        
        void unloadSound(const SCString& strFile);
        
        void stopMusic(const bool bRelease=true);
        void stopAllSound();
        
        void setMusicVolume(const float fPercent);
        void setSoundVolume(const float fPercent);
        float getMusicVolume() const;
        float getSoundVolume() const;
        
        inline bool getMusicEnabled() const { return (*_ptrWatchMusic); }
        inline void setMusicEnabled(const bool bEnable) { (*_ptrWatchMusic) = bEnable; }
        
        inline bool getSoundEnabled() const { return (*_ptrWatchSound); }
        inline void setSuondEnabled(const bool bEnable) { (*_ptrWatchSound) = bEnable; }
        
        bool setup(const SAudioListInfo* pInfo,const int nSize);
        
    protected:
        SCAudioManager();
        
        void Unsetup();
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
    private:
        struct SAudioInfo
        {
            const char*            pszAudioFile;
            unsigned char           byAudioFlag; //
            int                     nSoundID;
        };
        
        struct SSwitchIDSet
        {
            std::list<int>  onIndexList;
            std::list<int>  offIndexList;
        };
        
        void performAudio(const SSwitchIDSet& sis);
        void setupSwitchList(const std::list<SCMessage::Ptr>& ptrMsg,const bool bOn,const int nIndex);
        
    private:
        static SCAudioManager*          s_pInstance;
        
        SCWatchBool::Ptr                _ptrWatchSound;
        SCWatchBool::Ptr                _ptrWatchMusic;
        
        std::vector<SAudioInfo>         _audioInfoVtr;
        std::map<int,SSwitchIDSet>               _msgID2AudioIndexMap;
        std::map<SCString,SSwitchIDSet>         _cmd2AudioIndexMap;
        
        bool                            _bMsgProcessing;
        int                             _nCurrentMusicIndex;
    };
    
#define SC_AUDIO_FLAG(_is_music_,_is_loop_,_is_preload_) \
    (((_is_music_) ? (SpeedCC::SCAudioManager::kMaskBitIsMusic) : 0) | \
    ((_is_loop_) ? (SpeedCC::SCAudioManager::kMaskBitIsLoop) : 0) | \
    ((_is_preload_) ? (SpeedCC::SCAudioManager::kMaskBitIsPreload) : 0))
}

#endif // __SPEEDCC__SCAUDIOPLAYER_H__
