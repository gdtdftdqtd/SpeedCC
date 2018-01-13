//
//  SCCocosDef.h
//  speedcc
//
//  Created by Kevin on 4/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCCOCOSDEF_H__
#define __SPEEDCC__SCCOCOSDEF_H__

#include "../base/SCTemplateDef.h"
#include "../component/SCMessage.h"

namespace SpeedCC
{
    
#define kSCPositionIgnore       999
    
    ///------- define function type
    typedef void (cocos2d::Ref::*FUN_SCMapMessage_t)(SCMessage::Ptr ptrMsg);
    
    ///------- trait function
    template<typename T>
    cocos2d::SEL_MenuHandler SCTraitFunctionPointerType(void (T::*)(cocos2d::Ref*));
    
    template<typename T>
    cocos2d::SEL_SCHEDULE SCTraitFunctionPointerType(void (T::*)(float));
    
    template<typename T>
    cocos2d::SEL_CallFunc SCTraitFunctionPointerType(void (T::*)());
    
    template<typename T>
    cocos2d::SEL_CallFuncN SCTraitFunctionPointerType(void (T::*)(cocos2d::Node*));
    
    template<typename T>
    cocos2d::SEL_CallFuncND SCTraitFunctionPointerType(void (T::*)(cocos2d::Node*,void*));
    
    template<typename T>
    FUN_SCMapMessage_t SCTraitFunctionPointerType(void (T::*)(SCMessage::Ptr ptrMsg));
    
    ///--------------------- cocos2d transition template
    
    template<typename T>
    struct SCTransitionCreator
    {
        static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)
        {
            return T::create(duration, pScene);
        }
    };
    
    template<>
    struct SCTransitionCreator<SCClassNull>
    {
        static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)
        {return pScene;}
    };
    
    SCClassNull SCTraitTransitionSceneOpposite(SCClassNull*);
    cocos2d::TransitionRotoZoom SCTraitTransitionSceneOpposite(cocos2d::TransitionRotoZoom*);
    cocos2d::TransitionJumpZoom SCTraitTransitionSceneOpposite(cocos2d::TransitionJumpZoom*);
    cocos2d::TransitionShrinkGrow SCTraitTransitionSceneOpposite(cocos2d::TransitionShrinkGrow*);
    cocos2d::TransitionFlipX SCTraitTransitionSceneOpposite(cocos2d::TransitionFlipX*);
    cocos2d::TransitionFlipY SCTraitTransitionSceneOpposite(cocos2d::TransitionFlipY*);
    cocos2d::TransitionFlipAngular SCTraitTransitionSceneOpposite(cocos2d::TransitionFlipAngular*);
    cocos2d::TransitionZoomFlipX SCTraitTransitionSceneOpposite(cocos2d::TransitionZoomFlipX*);
    cocos2d::TransitionZoomFlipY SCTraitTransitionSceneOpposite(cocos2d::TransitionZoomFlipY*);
    cocos2d::TransitionZoomFlipAngular SCTraitTransitionSceneOpposite(cocos2d::TransitionZoomFlipAngular*);
    cocos2d::TransitionFade SCTraitTransitionSceneOpposite(cocos2d::TransitionFade*);
    cocos2d::TransitionTurnOffTiles SCTraitTransitionSceneOpposite(cocos2d::TransitionTurnOffTiles*);
    cocos2d::TransitionSplitCols SCTraitTransitionSceneOpposite(cocos2d::TransitionSplitCols*);
    cocos2d::TransitionSplitRows SCTraitTransitionSceneOpposite(cocos2d::TransitionSplitRows*);
    cocos2d::TransitionFadeTR SCTraitTransitionSceneOpposite(cocos2d::TransitionFadeTR*);
    cocos2d::TransitionFadeBL SCTraitTransitionSceneOpposite(cocos2d::TransitionFadeBL*);
    cocos2d::TransitionProgressRadialCCW SCTraitTransitionSceneOpposite(cocos2d::TransitionProgressRadialCCW*);
    
    cocos2d::TransitionMoveInL SCTraitTransitionSceneOpposite(cocos2d::TransitionMoveInR*);
    cocos2d::TransitionMoveInR SCTraitTransitionSceneOpposite(cocos2d::TransitionMoveInL*);
    
    cocos2d::TransitionMoveInT SCTraitTransitionSceneOpposite(cocos2d::TransitionMoveInB*);
    cocos2d::TransitionMoveInB SCTraitTransitionSceneOpposite(cocos2d::TransitionMoveInT*);
    
    cocos2d::TransitionSlideInL SCTraitTransitionSceneOpposite(cocos2d::TransitionSlideInR*);
    cocos2d::TransitionSlideInR SCTraitTransitionSceneOpposite(cocos2d::TransitionSlideInL*);
    
    cocos2d::TransitionSlideInB SCTraitTransitionSceneOpposite(cocos2d::TransitionSlideInT*);
    cocos2d::TransitionSlideInT SCTraitTransitionSceneOpposite(cocos2d::TransitionSlideInB*);
    
    cocos2d::TransitionFadeUp SCTraitTransitionSceneOpposite(cocos2d::TransitionFadeDown*);
    cocos2d::TransitionFadeDown SCTraitTransitionSceneOpposite(cocos2d::TransitionFadeUp*);
    
    ///-------- cocos2d efficiency macro
#define SCCCFileUtils() \
    (cocos2d::FileUtils::getInstance())
    
#define SCCCUserDefault() \
    (cocos2d::UserDefault::getInstance())
    
#define SCCCDirector() \
    (cocos2d::Director::getInstance())
    
#define SCCCTouchDispatch()\
    (SCCCDirector()->getEventDispatcher())
    
#define SCCCSoundEngine()\
    (CocosDenshion::SimpleAudioEngine::getInstance())
    
#define SCSchedule(_selector_,_target_,_interval_,_pause_)\
    (SCCCDirector()->getScheduler()->schedule((_selector_),(_target_),(_interval_),(_pause_)))
    
#define SCUnschedule(_selector_,_target_) \
    (SCCCDirector()->getScheduler()->unschedule((_selector_),(_target_)))
    
#define SCWinSize() \
    (SCCCDirector()->getWinSize())
    
#define SCCCScheduler()\
    (SCCCDirector()->getScheduler())
    
#define SC_FUNC(_fun_)\
    (decltype(SpeedCC::SCTraitFunctionPointerType(&_fun_))(&_fun_))
    
#define SCF(_fun_)\
    ((decltype(SpeedCC::SCTraitFunctionPointerType(&std::remove_pointer<decltype(this)>::type::_fun_)))(&std::remove_pointer<decltype(this)>::type::_fun_))
    
#define SCSceneNav() \
    (SpeedCC::SCSceneNavigator::getInstance())
    
#define SCMsgDisp() \
    (SpeedCC::SCMessageDispatch::getInstance())

    
    ////---------------------- Actions
#define ASequence               cocos2d::Sequence::create
#define AMoveTo                 cocos2d::MoveTo::create
#define AMoveBy                 cocos2d::MoveBy::create
#define AScaleTo                cocos2d::ScaleTo::create
#define AScaleBy                cocos2d::ScaleBy::create
#define ARotateTo               cocos2d::RotateTo::create
#define ARotateBy               cocos2d::RotateBy::create
#define APlace                  cocos2d::Place::create
#define ASpawn                  cocos2d::Spawn::create
#define AFadeIn                 cocos2d::FadeIn::create
#define AFadeOut                cocos2d::FadeOut::create
#define AProgressTo             cocos2d::ProgressTo::create
#define AProgressFromTo         cocos2d::ProgressFromTo::create
#define ADelayTime              cocos2d::DelayTime::create
#define ATintBy                 cocos2d::TintBy::create
#define AShow                   cocos2d::Show::create
#define AHide                   cocos2d::Hide::create
#define ABlink                  cocos2d::Blink::create
#define ABezierTo               cocos2d::BezierTo::create
#define ABezierBy               cocos2d::BezierBy::create
#define AJumpBy                 cocos2d::JumpBy::create
#define AJumpTo                 cocos2d::JumpTo::create
#define ASkewTo                 cocos2d::SkewTo::create
#define ASkewBy                 cocos2d::SkewBy::create
#define AFlipY                  cocos2d::FlipY::create
#define AFlipX                  cocos2d::FlipX::create
#define ARemoveSelf             cocos2d::RemoveSelf::create
#define ARepeat                 cocos2d::Repeat::create
#define ARepeatForever          cocos2d::RepeatForever::create
#define ACallFunc               cocos2d::CallFunc::create
#define ACallFuncN              cocos2d::CallFuncN::create
#define ACallFuncND             cocos2d::CallFuncND::create
    
#define AEaseIn                 cocos2d::EaseIn::create
#define AEaseOut                cocos2d::EaseOut::create
#define AEaseInOut              cocos2d::EaseInOut::create
    
#define AEaseSineIn             cocos2d::EaseSineIn::create
#define AEaseSineOut            cocos2d::EaseSineOut::create
#define AEaseSineInOut          cocos2d::EaseSineInOut::create
    
#define AEaseExponentialIn      cocos2d::EaseExponentialIn::create
#define AEaseExponentialOut     cocos2d::EaseExponentialOut::create
#define AEaseExponentialInOut   cocos2d::EaseExponentialInOut::create
    
#define AEaseElasticIn          cocos2d::EaseElasticIn::create
#define AEaseElasticOut         cocos2d::EaseElasticOut::create
#define AEaseElasticInOut       cocos2d::EaseElasticInOut::create
    
#define AWaves3D                cocos2d::Waves3D::create
#define AFlipX3D                cocos2d::FlipX3D::create
#define AFlipY3D                cocos2d::FlipY3D::create
#define ALens3D                 cocos2d::Lens3D::create
#define ARipple3D               cocos2d::Ripple3D::create
#define AShaky3D                cocos2d::Shaky3D::create
#define ALiquid                 cocos2d::Liquid::create
#define AWaves                  cocos2d::Waves::create
#define ATwirl                  cocos2d::Twirl::create
}

#endif // __SPEEDCC__SCCOCOSDEF_H__
