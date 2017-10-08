

#ifndef __SPEEDCC__SCNODERENDERER_H__
#define __SPEEDCC__SCNODERENDERER_H__

#include "../SCComponent.h"

namespace SpeedCC
{
//    class SCCCRender : public SCComponent
//    {
//    protected:
//        cocos2d::Node*      _pNode;
//    };
    /*
    template<typename T>
    class SCCCNodeRendererT : public SCComponent
    {
    private:
        SC_AVOID_CLASS_COPY(SCCCNodeRendererT<T>);
        SCCCNodeRendererT()
        {
            this->setCastInherit(true);
        }
        
    public:
        SC_DEFINE_CLASS_PTR(SCCCNodeRendererT<T>);
        
        static Ptr create(const std::function<T*(void)>& funcCreateNode)
        {
            Ptr ret;
            ret.createInstanceWithCon([](void* pData)
                                      {
                                          new(pData)SCCCNodeRendererT<T>();
                                      });
            
            ret->setCastInherit(true);
            T* pNode = funcCreateNode();
            ret->_pNode = pNode;
            
            return ret;
        }
        
        T* getNode()
        {
            return _pNode;
        }
        
    private:
        T*      _pNode;
    };


#define DEFINE_CCRENDERER_CLASS(_class_) \
    typedef SCCCNodeRendererT<cocos2d::_class_>       SC##_class_##Renderer
    
    DEFINE_CCRENDERER_CLASS(Node);
    DEFINE_CCRENDERER_CLASS(Scene);
    DEFINE_CCRENDERER_CLASS(Sprite);
    DEFINE_CCRENDERER_CLASS(SpriteBatchNode);
    DEFINE_CCRENDERER_CLASS(Layer);
    DEFINE_CCRENDERER_CLASS(ProgressTimer);
    DEFINE_CCRENDERER_CLASS(RenderTexture);
    DEFINE_CCRENDERER_CLASS(MotionStreak);
    DEFINE_CCRENDERER_CLASS(ClippingNode);
    DEFINE_CCRENDERER_CLASS(ClippingRectangleNode);
    DEFINE_CCRENDERER_CLASS(Menu);
    DEFINE_CCRENDERER_CLASS(MenuItem);
    DEFINE_CCRENDERER_CLASS(ParticleBatchNode);
    DEFINE_CCRENDERER_CLASS(ParticleSystem);
    DEFINE_CCRENDERER_CLASS(Label);
    DEFINE_CCRENDERER_CLASS(LabelAtlas);
    //    DEFINE_CCRENDERER_CLASS(LabelBMFont);
    //    DEFINE_CCRENDERER_CLASS(LabelTTF);
    DEFINE_CCRENDERER_CLASS(DrawNode);
    DEFINE_CCRENDERER_CLASS(AtlasNode);
    DEFINE_CCRENDERER_CLASS(ProtectedNode);
    */
}
#endif // __SPEEDCC__SCNODERENDERER_H__
