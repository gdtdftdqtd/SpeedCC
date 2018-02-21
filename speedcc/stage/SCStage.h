/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#ifndef __SPEEDCC__SCSTAGE_H__
#define __SPEEDCC__SCSTAGE_H__

#include "SCPerformObject.h"
#include "SCRole.h"
#include "SCMessage.h"
#include "SCMessageDispatch.h"

namespace SpeedCC
{
    class SCStage :
    public SCPerformObject,
    public SCMessageListener
    {
    public:
        SC_AVOID_CLASS_COPY(SCStage)
        SC_DEFINE_CLASS_PTR(SCStage)
        
        SC_DEFINE_CREATE_FUNC_0(SCStage)
        
        virtual ~SCStage();
        
        void addRole(SCRole::Ptr ptrRole);
        void removeRole(const int nID);
        SCRole::Ptr getRole(const int nID);
        
        /*
        void beginRole(const int nRoleID,const int nInitStrategyID);
        void endRole();
        
        void beginStragtegy(const int nStrategyID);
        void endStrategy();
        
        void insertBehavior(const int nMsg,SCBehavior::Ptr ptrBvr);
        void insertBehavior(const SCString& strCmd,SCBehavior::Ptr ptrBvr);
        void insertEnterBehavior(SCBehavior::Ptr ptrBvr);
        void insertExitBehavior(SCBehavior::Ptr ptrBvr);
        */
//        virtual void setUp(){}
        virtual SCStrategy::Ptr onCreateStrategy(const int nID) {SCASSERT(false); return nullptr;}
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
        template<typename T1,typename T2,typename ...Ts>
        void createActor2Role(const int nRoleID,const int nActorID=SCID::Act::kSCActDefault)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T1,T2,Ts...>();
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T>
        void createActor2Role(const int nRoleID,const int nActorID=SCID::Act::kSCActDefault)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T>();
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T1,typename T2,typename ...Ts>
        void createActor2Role(const int nRoleID,const int nActorID,const T1& t1,const T2& t2,Ts... ts)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T1,T2,Ts...>(t1,t2,ts...);
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T>
        void createActor2Role(const int nRoleID,const int nActorID,const T& t)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T>(t);
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
    private:
        struct SFlowInfo
        {
            SCRole::Ptr                 ptrRole;
            std::list<SCStrategy::Ptr>  strategyPtrList;
        };
        
    protected:
        SCStage();
        
        virtual void onActiveChanged(const bool bNewActive) override;
        
    private:
        std::map<int,SCRole::Ptr>                              _id2RoleMap;
    };
}

#endif // __SPEEDCC__SCSTAGE_H__
