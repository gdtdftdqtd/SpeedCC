//

#ifndef __SPEEDCC__SCMEMALLOCATOR_H__
#define __SPEEDCC__SCMEMALLOCATOR_H__

#include "stdio.h"
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <stdlib.h>

namespace SpeedCC
{
    class SCPoolAllocator
    {
    private:
        enum
        {
            SIZE_OF_ALIGN           = 8,
            SIZE_OF_MAX_IN_BYTES    = 512,
            NUMBER_OF_FREE_LIST     = SIZE_OF_MAX_IN_BYTES/SIZE_OF_ALIGN,
        };
        
        union SCMemBlock
        {
            union SCMemBlock* pNext;
            char cClineData[1];
        };
        
    public:
        template<typename T>
        static inline T* newObject()
        {
            void* p = SCPoolAllocator::allocate(sizeof(T));
            T* pRet = new(p)T();
            
            return pRet;
        }
        
        template<typename T, typename P>
        static inline T* newObject(const P& p1)
        {
            void* p = SCPoolAllocator::allocate(sizeof(T));
            T* pRet = new(p)T(p1);
            
            return pRet;
        }
        
        template<typename T, typename P1,typename P2>
        static inline T* newObject(const P1& p1,const P2& p2)
        {
            void* p = SCPoolAllocator::allocate(sizeof(T));
            T* pRet = new(p)T(p1,p2);
            
            return pRet;
        }
        
        template<typename T, typename P1,typename P2,typename P3>
        static inline T* newObject(const P1& p1,const P2& p2,const P3& p3)
        {
            void* p = SCPoolAllocator::allocate(sizeof(T));
            T* pRet = new(p)T(p1,p2,p3);
            
            return pRet;
        }
        
        template<typename T>
        static inline void deleteObject(T* p)
        {
            if(p)
            {
                p->~T();
                SCPoolAllocator::deallocate(static_cast<T*>(p), sizeof(T));
            }
        }
        
        static void* allocate(size_t nSize);
        static void deallocate(void* pBuffer, size_t nSize);
        
    private:
        
        static inline size_t roundUp(size_t nBytes)
        { return (((nBytes) + (size_t) SIZE_OF_ALIGN-1) & ~((size_t) SIZE_OF_ALIGN - 1));}
        
        static  inline size_t getIndexInFreeList(size_t nBytes)
        { return (((nBytes) + (size_t)SIZE_OF_ALIGN-1)/(size_t)SIZE_OF_ALIGN - 1);}
        
        static void* refill(size_t nSize);
        static char* allocChunk(size_t nSize, int& nNodeNumber);
        
        // chunk allocation state
        static char* _pFreeStart;
        static char* _pFreeEnd;
        static size_t _nHeapSize;
        static SCMemBlock* _pFreeList[NUMBER_OF_FREE_LIST];
        
    } ;
    
    class SCSimpleAllocator
    {
    public:
        static inline void* allocate(size_t nSize)
        {
            return malloc(nSize);
        }
        
        static inline void deallocate(void* pBuffer, size_t nSize)
        {
            ::free(pBuffer);
        }
        
        template<typename T>
        static T* newObject()
        {
            return new T();
        }
        
        template<typename T, typename P>
        static inline T* newObject(const P& p1)
        {
            return new T(p1);
        }
        
        template<typename T, typename P1,typename P2>
        static inline T* newObject(const P1& p1,const P2& p2)
        {
            return new T(p1,p2);
        }
        
        template<typename T, typename P1,typename P2,typename P3>
        static inline T* newObject(const P1& p1,const P2& p2,const P3& p3)
        {
            return new T(p1,p2,p3);
        }
        
        template<typename T>
        static void deleteObject(T* p)
        {
            delete p;
        }
    };
    
    template <class T>
    class SCSTLAllocator
    {
        
    public:
        typedef size_t     size_type;
        typedef ptrdiff_t  difference_type;
        typedef T*       pointer;
        typedef const T* const_pointer;
        typedef T&       reference;
        typedef const T& const_reference;
        typedef T        value_type;
        
        template <class P>
        struct rebind
        {
            typedef SCSTLAllocator<P> other;
        };
        
        SCSTLAllocator() throw() {}
        SCSTLAllocator(const SCSTLAllocator&) throw() {}
        template <class T2> SCSTLAllocator(const SCSTLAllocator<T2>&) throw() {}
        ~SCSTLAllocator() throw() {}
        
        pointer address(reference x) const { return &x; }
        const_pointer address(const_reference x) const { return &x; }
        
        // nSize is permitted to be 0.  The C++ standard says nothing about what
        // the return value is when nSize == 0.
        T* allocate(size_type nSize, const void* = 0)
        {
            return (nSize != 0 ? static_cast<T*>(SCPoolAllocator::allocate(nSize * sizeof(T))) : 0);
        }
        
        void deallocate(pointer p, size_type nSize)
        { SCPoolAllocator::deallocate(p, nSize * sizeof(T)); }
        
        size_type max_size() const throw()
        { return size_t(-1) / sizeof(T); }
        
        void construct(pointer p, const T& val) { new(p) T(val); }
        void destroy(pointer p) { p->~T(); }
    };
    
    template<typename T1, typename T2>
    inline bool operator==(const SCSTLAllocator<T1>&, const SCSTLAllocator<T2>&)
    { return true; }
    
    template<typename T1, typename T2>
    inline bool operator!=(const SCSTLAllocator<T1>&, const SCSTLAllocator<T2>&)
    { return false; }
    
    
#ifdef SPEEDCC_FEATURE_ENABLE_MEMORY_POOL
    typedef SCPoolAllocator        SCMemAllocator;
    
    template <typename T>
    using MySTLAllocator = SCSTLAllocator<T>;
    
#else
    typedef SCSimpleAllocator      SCMemAllocator;
    
    template <typename T>
    using MySTLAllocator = std::allocator<T>;
#endif // SPEEDCC_FEATURE_ENABLE_MEMORY_POOL
    
    ///----------- stl allocator
    
    template <typename T>
    using stl_vector = std::vector<T, MySTLAllocator<T> >;
    
    template <typename T>
    using stl_list = std::list<T, MySTLAllocator<T> >;
    
    template <typename T1,typename T2,typename T3=std::less<T1> >
    using stl_map = std::map<T1,T2,T3, MySTLAllocator<std::pair<const T1, T2> > >;
    
    template <typename T1,typename T2,typename T3=std::less<T1> >
    using stl_multimap = std::multimap<T1,T2,T3, MySTLAllocator<std::pair<const T1, T2> > >;
    
    template <typename T1,typename T2=std::less<T1> >
    using stl_set = std::set<T1,T2, MySTLAllocator<T1> >;
    
    template <typename T1,typename T2=std::less<T1> >
    using stl_multiset = std::multiset<T1,T2, MySTLAllocator<T1> >;
    
    template <typename T>
    using stl_deque = std::deque<T, MySTLAllocator<T> >;
    
    template <typename T>
    using stl_queue = std::queue<T, stl_deque<T> >;
    
    template <typename T>
    using stl_stack = std::stack<T, stl_deque<T> >;
    
    typedef std::basic_string<char,std::char_traits<char>,MySTLAllocator<char> > stl_string;
}

#endif // __SPEEDCC__SCMEMALLOCATOR_H__
