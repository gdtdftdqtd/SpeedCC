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
    
    
    
    // class list
    template<typename T1,typename T2>
    struct SClassListT
    {
        typedef T1 firstClass;
        typedef T2 secondClass;
    };
    
    // calculate class list length
    template<typename T1>
    struct SCGetClassListLengthT { enum {value=0};};
    
    template<>
    struct SCGetClassListLengthT<SCClassNull> { enum {value=0};};
    
    template<typename T1,typename T2>
    struct SCGetClassListLengthT<SClassListT<T1,T2> >
    {
        enum {value= (SCIsNullClassT<T1>::value ? 0 : SCGetClassListLengthT<T2>::value + 1) };
    };
    
    // retrive class type by index
    template<typename T1,int index>
    struct SCGetClassByIndexT
    {
        typedef SCClassNull type;
    };
    
    template<typename T1,typename T2>
    struct SCGetClassByIndexT<SClassListT<T1,T2>,0>
    {
        typedef T1 type;
    };
    
    template<typename T1,typename T2,int index>
    struct SCGetClassByIndexT<SClassListT<T1,T2>,index>
    {
        typedef typename SCGetClassByIndexT<T2,index-1>::type type;
    };
    
    // retrive index by class type
    template<typename T1,typename T2>
    struct SCGetIndexByClassT { enum {value=-1};};
    
    
    template<typename T1,typename T2,typename T3>
    struct SCGetIndexByClassT<SClassListT<T1,T2>,T3>
    {
        enum
        {
            value= (SCIsSameTypeT<T1, T3>::value ?
                    0 : (SCGetIndexByClassT<T2,T3>::value==-1 ? -1 : (SCGetIndexByClassT<T2,T3>::value+1)))
        };
    };
    
    template<typename T1>
    struct SCGetIndexByClassT<SCClassNull,T1> { enum {value=-1};};
    
    // define class list macro
#define SCLASSLIST_0 \
    SClassListT<SCClassNull,SCClassNull>
    
#define SCLASSLIST_1(c0) \
    SClassListT<c0,SCClassNull>
    
#define SCLASSLIST_2(c0,c1) \
    SClassListT<c0,SCLASSLIST_1(c1)>
    
#define SCLASSLIST_3(c0,c1,c2) \
    SClassListT<c0,SCLASSLIST_2(c1,c2)>
    
#define SCLASSLIST_4(c0,c1,c2,c3) \
    SClassListT<c0,SCLASSLIST_3(c1,c2,c3)>
    
#define SCLASSLIST_5(c0,c1,c2,c3,c4) \
    SClassListT<c0,SCLASSLIST_4(c1,c2,c3,c4)>
    
#define SCLASSLIST_6(c0,c1,c2,c3,c4,c5) \
    SClassListT<c0,SCLASSLIST_5(c1,c2,c3,c4,c5)>
    
#define SCLASSLIST_7(c0,c1,c2,c3,c4,c5,c6) \
    SClassListT<c0,SCLASSLIST_6(c1,c2,c3,c4,c5,c6)>
    
#define SCLASSLIST_8(c0,c1,c2,c3,c4,c5,c6,c7) \
    SClassListT<c0,SCLASSLIST_7(c1,c2,c3,c4,c5,c6,c7)>
    
#define SCLASSLIST_9(c0,c1,c2,c3,c4,c5,c6,c7,c8) \
    SClassListT<c0,SCLASSLIST_8(c1,c2,c3,c4,c5,c6,c7,c8)>
    
#define SCLASSLIST_10(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9) \
    SClassListT<c0,SCLASSLIST_9(c1,c2,c3,c4,c5,c6,c7,c8,c9)>
    
#define SCLASSLIST_11(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10) \
    SClassListT<c0,SCLASSLIST_10(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10)>
    
#define SCLASSLIST_12(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11) \
    SClassListT<c0,SCLASSLIST_11(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11)>
    
#define SCLASSLIST_13(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12) \
    SClassListT<c0,SCLASSLIST_12(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12)>
    
#define SCLASSLIST_14(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13) \
    SClassListT<c0,SCLASSLIST_13(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13)>
    
#define SCLASSLIST_15(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14) \
    SClassListT<c0,SCLASSLIST_14(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14)>
    
#define SCLASSLIST_16(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15) \
    SClassListT<c0,SCLASSLIST_15(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15)>
    
#define SCLASSLIST_17(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16) \
    SClassListT<c0,SCLASSLIST_16(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16)>
    
#define SCLASSLIST_18(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17) \
    SClassListT<c0,SCLASSLIST_17(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17)>
    
#define SCLASSLIST_19(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18) \
    SClassListT<c0,SCLASSLIST_18(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18)>
    
#define SCLASSLIST_20(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19) \
    SClassListT<c0,SCLASSLIST_19(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19)>
    
#define SCLASSLIST_21(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20) \
    SClassListT<c0,SCLASSLIST_20(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20)>
    
#define SCLASSLIST_22(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21) \
    SClassListT<c0,SCLASSLIST_21(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21)>
    
#define SCLASSLIST_23(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22) \
    SClassListT<c0,SCLASSLIST_22(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22)>
    
#define SCLASSLIST_24(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23) \
    SClassListT<c0,SCLASSLIST_23(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23)>
    
#define SCLASSLIST_25(c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23,c24) \
    SClassListT<c0,SCLASSLIST_24(c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15,c16,c17,c18,c19,c20,c21,c22,c23,c24)>

    
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
