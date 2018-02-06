//
//  SCBinder.hpp
//  libspeedcc
//
//  Created by Kevin on 17/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBINDER_H__
#define __SPEEDCC__SCBINDER_H__

#include "SCObject.h"
//#include "SCString.h"
#include "SCMacroDef.h"
//#include "SCWatchString.h"
#include "SCWatchNumberT.h"

namespace SpeedCC
{
    ///------------- SCBinder
    class SCBinder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinder)
        SC_DEFINE_CLASS_PTR(SCBinder)
        
        void setActive(const bool bActive);
        inline bool getActive() const {return _bActive;}
        
        virtual void reset();
        
        void removeUpdateFunc();
    protected:
        SCBinder():
        _bActive(true),
        _nFuncID(0)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) {}
        
    protected:
        SCObject::Ptr       _ptrWatch;
        std::function<void(SCObject::Ptr ptr,const int nID)>   _removeUpdateFunc;
        int                     _nFuncID;
        
    private:
        bool    _bActive;
    };
    
    
}

#endif //__SPEEDCC__SCBINDER_H__
