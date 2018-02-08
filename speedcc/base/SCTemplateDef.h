//


#ifndef __SPEEDCC__SCTEMPLATEDEF_H__
#define __SPEEDCC__SCTEMPLATEDEF_H__

#include <type_traits>
#include <tuple>

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
    template<typename T>
    struct SCIsNullClassT { enum {value=std::is_same<T,SCClassNull>::value};};
    
    template<typename T>
    struct SCIsEmptyClassT { enum {value=std::is_same<T,SCClassEmpty>::value};};
    
    
    ///---------- SCGetIndexByClassT
    template <typename T, typename Tuple>
    struct SCGetIndexByClassT { enum {value=0}; };
    
    template <typename T, typename ...Ts>
    struct SCGetIndexByClassT<T, std::tuple<T, Ts...>> { enum {value=0}; };
    
    template <typename T1, typename T2, typename ...Ts>
    struct SCGetIndexByClassT<T1, std::tuple<T2, Ts...>>
    {
        enum {value = (1 + SCGetIndexByClassT<T1, std::tuple<Ts...>>::value)};
    };
    
    ///----------- SCTraitMemberFunc
    template <typename>
    struct SCTraitMemberFuncT;
    
    template <typename T1, typename T2, typename ...Ts>
    struct SCTraitMemberFuncT<T1 (T2::*)(Ts...)>
    {
        typedef T1 return_type;
        typedef T2 class_type;
        typedef T2& class_reference;
        
        enum {ArgCount = sizeof...(Ts)};
    };
    
    template <typename T1, typename T2, typename ...Ts>
    struct SCTraitMemberFuncT<T1 (T2::*)(Ts...) const>
    {
        typedef T1 return_type;
        typedef T2 class_type;
        typedef T2 const& class_reference;
        
        enum {ArgCount = sizeof...(Ts)};
    };
    
    ///--------------  detect class internal type define
    template<typename T>
    struct SCDefineVoidT
    {
        typedef void type;
    };
    
    template<typename T1, typename T2 = void>
    struct SCHasInternalTypeT
    {
        enum { value = 0 };
    };
    
    template<typename T>
    struct SCHasInternalTypeT<T, typename SCDefineVoidT<typename T::type>::type>
    {
        enum { value = 1 };
    };

    
}


#endif // __SPEEDCC__SCTEMPLATEDEF_H__
