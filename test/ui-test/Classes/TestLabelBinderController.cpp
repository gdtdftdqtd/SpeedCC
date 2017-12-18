
#include "TestLabelBinderController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestLabelBinderController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);
    
    _watchIntPtr = SCWatchInt::create();
    _watchStrPtr = SCWatchString::create();
    *_watchStrPtr = "test string";
    
    SCBinderLabel::Ptr binderNumPtr = SCBinderLabel::create();
    this->ownLifecycle(binderNumPtr);
    binderNumPtr->setStringSource(_watchIntPtr);
    
    SCBinderLabel::Ptr binderStrPtr = SCBinderLabel::create();
    this->ownLifecycle(binderStrPtr);
    binderStrPtr->setStringSource(_watchStrPtr);

    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(NULL,0,0.9,"","Label Binder","blue_font.fnt")
    
        // binding number
        SC_INSERT_LABEL(NULL,-0.2,0.5,"",binderNumPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.2,0.5,"color-text=red;","+","",33,FN(onButtonAdd))
        SC_INSERT_BUTTON_LABEL(NULL,0.4,0.5,"color-text=red;","-","",33,FN(onButtonSub))
    
        // binding string
        SC_INSERT_LABEL(NULL,-0.2,0,"color-text=yellow;",binderStrPtr,"",30)
        SC_INSERT_BUTTON_LABEL(NULL,0.3,0,"color-text=red;","click","",25,FN(onButtonRandomText))
    
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
//    int ppp = 0;
    (*_watchStrPtr).format("%d",rand());
}

