
#include "TestLabelBinderController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLabelBinderController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    _watchIntPtr = SCWatchInt::create();
    _watchStrPtr = SCWatchString::create();
    *_watchStrPtr = "test string";
    
//    SCBinderUILabel::Ptr binderNumPtr = SCBinderUILabel::create();
//    this->ownLifecycle(binderNumPtr);
//    binderNumPtr->setWatchSource(_watchIntPtr);
    
    SCBinderUILabel::Ptr binderStrPtr = SCBinderUILabel::create();
//    this->ownLifecycle(binderStrPtr);
    binderStrPtr->setWatch(_watchStrPtr);

    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(NULL,0.5,0.95,"","Label Binder","blue_font.fnt")
    
        // binding number
        SC_INSERT_LABEL(NULL,0.4,0.75,"",_watchIntPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.6,0.75,"color-text=red;","+","",33,SCF(onButtonAdd))
        SC_INSERT_BUTTON_LABEL(NULL,0.7,0.75,"color-text=red;","-","",33,SCF(onButtonSub))
    
        // binding string
        SC_INSERT_LABEL(NULL,0.4,0.5,"color-text=yellow;",binderStrPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.65,0.5,"color-text=red;","click","",25,SCF(onButtonRandomText))
    
        // back
        SC_INSERT_BUTTON_LABEL(NULL,0.05,0.95,"color-text=red;","back","",25,SCF(onButtonBack))
    SC_END_CONTAINER
    
}

void TestLabelBinderController::onButtonAdd()
{
    ++(*_watchIntPtr);
}

void TestLabelBinderController::onButtonSub()
{
    --(*_watchIntPtr);
}

void TestLabelBinderController::onButtonRandomText()
{
    (*_watchStrPtr).format("%d",rand());
}

void TestLabelBinderController::onButtonBack()
{
    SCSceneNav()->back();
}

