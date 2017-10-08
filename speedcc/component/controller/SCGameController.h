

#ifndef __SPEEDCC__SCGameController_H__
#define __SPEEDCC__SCGameController_H__

#include "../SCComponent.h"
#include "SCNavigationController.h"

namespace SPEEDCC
{
    class SCGameController : public SCComponent
    {
    public:
        SCObjPtrT<SCNavigationController> getComponent<SCNavigationController>() const
        {
            return _navCtlPtr;
        }
        
    private:
        SCObjPtrT<SCNavigationController> _navCtlPtr;
    };
}

#endif // __SPEEDCC__SCGameController_H__
