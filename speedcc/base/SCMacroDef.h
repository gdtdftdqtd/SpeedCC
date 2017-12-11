


#ifndef __SC__MACRODEF_H__
#define __SC__MACRODEF_H__

#include <assert.h>


////------------------

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

// assert at debug and release
#define SCASSERTR(_condition_) \
	assert((_condition_))

// assert at debug
#ifdef COCOS2D_DEBUG
#define SCASSERT(_condition_) \
    assert((_condition_))
#else
#define SCASSERT(_condition_)
#endif

// SPEEDCC_TEST_MODE

///---------- assert at compile time
#define SCASSERTCT(_condition_) \
    do { char SCASSERTArrayCT[(_condition_)?1:-1];SCASSERTArrayCT[0]=0;} while(0)


#define SC_IN_RANGE(_v_,_min_,_max_)\
    MAX((_min_),MIN((_max_),(_v_)))

#define SC_ARRAY_LENGTH(_array_)\
    (sizeof(_array_)/sizeof((_array_)[0]))

#define SC_NEW(_class_)\
    SCMemAllocator::newObject<_class_>()

#define SC_NEW_ARG(_class_,_arg_)\
    SCMemAllocator::newObject<_class_>((_arg_))

#define SC_DELETE(_pointer_)\
    do{\
        if((_pointer_)) {SCMemAllocator::deleteObject((_pointer_));}\
        (_pointer_) = NULL;\
    }while(0)

#define SCMapInsert(_map_,_key_,_value_)\
    (_map_).insert(std::remove_reference<decltype(_map_)>::type::value_type((_key_),(_value_)))

#define SCLogR(_format_, ...)\
    SCSystem::log((_format_), ##__VA_ARGS__)

#ifdef COCOS2D_DEBUG
#define SCLog  SCLogR
#else
#define SCLog(_format_, ...)
#endif

#define SCAutoLock(_lock_)\
    std::lock_guard<decltype(_lock_)> SPEEDCC_locker((_lock_))

#define SC_MAKE_WORD(_hight_,_low_)\
    (((_hight_)<<8)|(_low_))

///------- execute flow control short name
#define SC_CONTINUE_IF(_condition_)\
    if((_condition_)) {continue;}

#define SC_RETURN_IF(_condition_,_result_)\
    if((_condition_)) {return (_result_);}

#define SC_RETURN_IF_LOG(_condition_,_result_,_log_,...)\
    if((_condition_)) {SCLog((_log_),##__VA_ARGS__); return (_result_);}

#define SC_RETURN_IF_V(_condition_)\
    if((_condition_)) {return ;}

#define SC_BREAK_IF(_condition_)\
    if((_condition_)) break;

#define SC_FUNCTOR(_fun_)\
    (decltype(SCTraitFunctor(&_fun_))(&_fun_))

///----- bit test
#define SC_BIT_HAS_OR(_set_,_bit_)\
    (((_set_)&(_bit_)) ? true : false)

#define SC_BIT_HAS_AND(_set_,_bit_)\
    ((((_set_)&(_bit_))==(_bit_)) ? true : false)

#define SC_BIT_ADD(_set_,_bit_)\
    ((_set_)|=(_bit_))

#define SC_BIT_REMOVE(_set_,_bit_)\
    ((_set_)&=(~(_bit_)))

///------- class relate
#define SC_AVOID_CLASS_COPY(_class_) \
    _class_(const _class_&)= delete; \
    _class_& operator=(const _class_&)= delete

#define SC_DEFINE_CLASS_PTR(_class_) \
    typedef SCObjPtrT<_class_>              Ptr; \
    typedef SCObjPtrT<_class_,false>        WeakPtr

#define SC_PTR_HAS_CLASS(_ptr_,_class_) \
    ((_ptr_).cast<_class_>()!=NULL)

#define SC_DECLEAR_COMPONENT_ID \
    public: \
    static const char* CMP_ID; \
    virtual SCString getID() const {return CMP_ID;}

#define SC_DEFINE_COMPONENT_ID(_class_) \
    const char* _class_::CMP_ID = #_class_


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

#define SC_SELECTOR(_fun_)\
    (decltype(SCTraitFunctionPointerType(&_fun_))(&_fun_))


//#define SC_TRAIT_PTR_CLASS(_ptr_) \
//    decltype(std::remove_reference<std::remove_const<_ptr_>::type>::type)::type

///--------- SPEEDCCD version
#define SPEEDCC_VERSION_MAJOR                       ((SPEEDCC_VERSION & 0x00ff0000)>>(4*4))
#define SPEEDCC_VERSION_MINOR                       ((SPEEDCC_VERSION & 0x0000ff00)>>(4*2))
#define SPEEDCC_VERSION_FIX                         ((SPEEDCC_VERSION & 0x000000ff))

#ifndef INT64
#define INT64       long long
#endif

#endif //__SC__MACRODEF_H__
