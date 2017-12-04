//


#ifndef __SC__TEMPLATEDEF_H__
#define __SC__TEMPLATEDEF_H__

#include <type_traits>
#include "cocos2d.h"

namespace SpeedCC
{
    // atom special class
    struct SCClassNull;
    
    struct SCClassEmpty{};
    
    template<typename T>
    struct SCShadowClassT{typedef T type;};
    
    template<>
    struct SCShadowClassT<SCClassNull> {typedef SCClassEmpty type;};
    
    // judgement class
    template<typename T1,typename T2>
    struct SCIsSameTypeT { enum {value=0};};
    
    template<typename T>
    struct SCIsSameTypeT<T,T> { enum {value=1};};
    
    template<typename T>
    struct SCIsNullClassT { enum {value=SCIsSameTypeT<T,SCClassNull>::value};};
    
    template<typename T>
    struct SCIsEmptyClassT { enum {value=SCIsSameTypeT<T,SCClassEmpty>::value};};
    
    template<typename BaseT, typename DeriveT>
    struct SCIsBaseOfT
    {
    private:
        template <typename B, typename D>
        struct Host { operator B*() const; operator D*(); };
        
        template <typename T>
        static int check(DeriveT*, T); // yes
        static char check(BaseT*, int); // no
        
    public:
        enum {value = SCIsSameTypeT<decltype(check(Host<BaseT,DeriveT>(), int())),int>::value};
    };
    
    template<typename BaseT, typename DeriveT>
    struct SCAvoidDuplicateDeriveT
    {
    private:
        template<typename T,int>
        struct GetClass { typedef SCIsSameTypeT<BaseT,DeriveT> type; };
        
        template<typename T>
        struct GetClass<T,0> { typedef T type;};
        
    public:
        typedef typename GetClass<BaseT,SCIsBaseOfT<BaseT,DeriveT>::value>::type type;
    };
    
    template<int n>
    struct SCNumber2ClassT {typedef SCShadowClassT<SCClassEmpty> type; };
    
    template<>
    struct SCNumber2ClassT<0> { typedef SCShadowClassT<SCClassNull> type; };
    
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
    
    
    ///--------------------- cocos2d transition template
    
    template<typename T>
    struct SCTransitionCreator
    {
        typedef T    OppositeType;
        static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)
        {
            return T::create(duration, pScene);
        }
    };
    
    template<>
    struct SCTransitionCreator<SCClassNull>
    {
        typedef SCClassNull    OppositeType;
        static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)
        {return pScene;}
    };
    
    template<>
    struct SCTransitionCreator<void>
    {
        typedef SCClassNull    OppositeType;
        static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)
        {return pScene;}
    };
    
    
    
    // single transition
#define SC_DEFINE_TRANSITION_SINGLE(_transition_)\
template<>\
struct SCTransitionCreator<_transition_>\
{\
typedef _transition_    OppositeType;\
static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)\
{return _transition_::create(duration,(cocos2d::Scene*)pScene);}\
};
    
    // pair transition
#define SC_DEFINE_TRANSITION_PAIR(_transition1_,_transition2_)\
template<>\
struct SCTransitionCreator<_transition1_>\
{\
typedef _transition2_    OppositeType;\
static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)\
{return _transition1_::create(duration,(cocos2d::Scene*)pScene);}\
};\
template<>\
struct SCTransitionCreator<_transition2_>\
{\
typedef _transition1_    OppositeType;\
static cocos2d::Scene* create(float duration,cocos2d::Scene* pScene)\
{return _transition2_::create(duration,(cocos2d::Scene*)pScene);}\
\
};
    
    
    
    
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionRotoZoom)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionJumpZoom)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionShrinkGrow)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFlipX)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFlipY)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFlipAngular)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionZoomFlipX)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionZoomFlipY)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionZoomFlipAngular)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFade)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionTurnOffTiles)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionSplitCols)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionSplitRows)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFadeTR)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionFadeBL)
    SC_DEFINE_TRANSITION_SINGLE(cocos2d::TransitionProgressRadialCCW)
    
    //DEFINE_TRANSITION_SINGLE(cocos2d::TransitionPageTurn)
    SC_DEFINE_TRANSITION_PAIR(cocos2d::TransitionMoveInL,cocos2d::TransitionMoveInR)
    SC_DEFINE_TRANSITION_PAIR(cocos2d::TransitionMoveInT,cocos2d::TransitionMoveInB)
    SC_DEFINE_TRANSITION_PAIR(cocos2d::TransitionSlideInL,cocos2d::TransitionSlideInR)
    SC_DEFINE_TRANSITION_PAIR(cocos2d::TransitionSlideInT,cocos2d::TransitionSlideInB)
    SC_DEFINE_TRANSITION_PAIR(cocos2d::TransitionFadeUp,cocos2d::TransitionFadeDown)
}


#endif // __SC__TEMPLATEDEF_H__
