//


#ifndef __SPEEDCC__SCTEMPLATEDEF_H__
#define __SPEEDCC__SCTEMPLATEDEF_H__

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
    
    
    ///---------- SCGetIndexByClassT
    template <typename T, typename Tuple>
    struct SCGetIndexByClassT { enum {value=0}; };
    
    template <typename T, typename... Ts>
    struct SCGetIndexByClassT<T, std::tuple<T, Ts...>> { enum {value=0}; };
    
    template <typename T1, typename T2, typename... Ts>
    struct SCGetIndexByClassT<T1, std::tuple<T2, Ts...>>
    {
        enum {value = (1 + SCGetIndexByClassT<T1, std::tuple<Ts...>>::value)};
    };
    
    ///----------- SCTraitMemberFunc
    template <typename>
    struct SCTraitMemberFuncT;
    
    template <typename T1, typename T2, typename... Ts>
    struct SCTraitMemberFuncT<T1 (T2::*)(Ts...)>
    {
        typedef T1 return_type;
        typedef T2 class_type;
        typedef T2& class_reference;
        
        enum {ArgCount = sizeof...(Ts)};
    };
    
    template <typename T1, typename T2, typename... Ts>
    struct SCTraitMemberFuncT<T1 (T2::*)(Ts...) const>
    {
        typedef T1 return_type;
        typedef T2 class_type;
        typedef T2 const& class_reference;
        
        enum {ArgCount = sizeof...(Ts)};
    };
    
}


#endif // __SPEEDCC__SCTEMPLATEDEF_H__
