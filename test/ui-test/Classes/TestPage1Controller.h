//
//  TestPage1Controller.hpp
//  UITest-mobile
//
//  Created by Kevin on 10/12/2017.
//

#ifndef TestPage1Controller_hpp
#define TestPage1Controller_hpp


#include "cocos2d.h"
#include "SpeedCC.h"

class TestPage1Controller : public SpeedCC::SCSceneControllerT<TestPage1Controller>
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void onButtonClicked();
};

#endif /* TestPage1Controller_hpp */
