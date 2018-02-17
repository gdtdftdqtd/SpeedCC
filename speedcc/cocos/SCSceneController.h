

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCScene.h"
#include "SCRefHolder.h"
#include "SCCocosDef.h"
#include "SCBinderCocos.h"
#include "SCUIBuilder.h"

#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStage.h"


namespace SpeedCC
{

    class SCSceneController :
    public SCStage,
    public cocos2d::Ref
    {
    public:
        SC_DEFINE_CLASS_PTR(SCSceneController)
        SC_AVOID_CLASS_COPY(SCSceneController)
        
        friend class SCSceneNavigator;
        template<typename> friend class SCSceneNavigationCreator;
        
        typedef std::function<void(SCMessage::Ptr ptrMsg)>  MsgFunc_t;
        
        virtual ~SCSceneController();
        
        inline bool getAllTouchEnabled() const  {return (_pDisableTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Node* getBedNode()  {return _pBedNode;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setAllTouchEnabled(const bool bEnabled);
        void showBlackMask(const bool bShow);

        void pushModalController(SCSceneController::Ptr controllerPtr);
        SCSceneController::Ptr popModalFromParent();
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        void delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic);
        void listenMessage(const int nMsg,MsgFunc_t func);
        
        void schedule(cocos2d::SEL_SCHEDULE selector);
        void schedule(cocos2d::SEL_SCHEDULE selector, float interval);
        void schedule(cocos2d::SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);
        void scheduleOnce(cocos2d::SEL_SCHEDULE selector, float delay);
        void unschedule(cocos2d::SEL_SCHEDULE selector);
        
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
        void finish(int nResult=0);
        
    protected:
        SCSceneController();
        
        virtual void onCreate(SCDictionary parameters){}
        
    private:
        void setBedNode(SCBedNode* pLayer);
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)
        { _ptrParentModalController = controllerPtr; }
        
        inline void setFinishFunc(const std::function<void(int)>& func)
        { _finishFunc = func; }
        
    private:
        SCBedNode*			                        _pBedNode;
        SCScene*                                    _pScene;
        SCSceneController::WeakPtr                  _ptrParentModalController;
        SCLayerDisableTouch*                        _pDisableTouchLayer;
        cocos2d::Layer*                             _pBlackMaskLayer;
        bool                                        _bBlackMaskForModal;
        std::list<SCObject::Ptr>                    _ownLifecycleList;
        std::map<int,MsgFunc_t>                     _msg2FuncMap;
        std::function<void(int)>                    _finishFunc;
    };
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
