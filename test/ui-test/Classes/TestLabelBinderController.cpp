
#include "TestLabelBinderController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLabelBinderController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    _watchIntPtr = SCWatchInt::create();
    _watchStrPtr = SCWatchString::create();
    *_watchStrPtr = "test string";
    
//    SCBinderLabel::Ptr binderNumPtr = SCBinderLabel::create();
//    this->ownLifecycle(binderNumPtr);
//    binderNumPtr->setWatchSource(_watchIntPtr);
    
    SCBinderLabel::Ptr binderStrPtr = SCBinderLabel::create();
//    this->ownLifecycle(binderStrPtr);
    binderStrPtr->setWatchSource(_watchStrPtr);

    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(NULL,0,0.9,"","Label Binder","blue_font.fnt")
    
        // binding number
        SC_INSERT_LABEL(NULL,-0.2,0.5,"",_watchIntPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.2,0.5,"color-text=red;","+","",33,SCF(onButtonAdd))
        SC_INSERT_BUTTON_LABEL(NULL,0.4,0.5,"color-text=red;","-","",33,SCF(onButtonSub))
    
        // binding string
        SC_INSERT_LABEL(NULL,-0.2,0,"color-text=yellow;",binderStrPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.3,0,"color-text=red;","click","",25,SCF(onButtonRandomText))
    
        // back
        SC_INSERT_BUTTON_LABEL(NULL,-0.90,0.90,"color-text=red;","back","",25,SCF(onButtonBack))
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

