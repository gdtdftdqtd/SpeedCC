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
}


#endif // __SC__TEMPLATEDEF_H__
