/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
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

#ifndef __SPEEDCC__SCUIMACRO_H__
#define __SPEEDCC__SCUIMACRO_H__

// root
#define SC_BEGIN_CONTAINER_ROOT(_style_,_size_) \
{\
    SCUIBuilder::Ptr ptrSCTemUIBuilder = SCUIBuilder::create();\
    ptrSCTemUIBuilder->beginContainerRoot(0.5,0.5,(_style_),(_size_),this->getBedNode(),this);


#define SC_BEGIN_CONTAINER_ROOT_EX(_style_,_size_,_parent_,_ref_) \
{\
    SCUIBuilder::Ptr ptrSCTemUIBuilder = SCUIBuilder::create();\
    ptrSCTemUIBuilder->beginContainerRoot(kSCPositionIgnore,kSCPositionIgnore,(_style_),(_size_),(_parent_),(_ref_));

#define SC_END_CONTAINER \
    ptrSCTemUIBuilder->popContainerStack(); \
}

// sprite
#define SC_INSERT_SPRITE(_node_,_style_,_image_) \
    ptrSCTemUIBuilder->insertSprite((_node_),0,0,(_style_),(_image_));

#define SC_BEGIN_CONTAINER_SPRITE(_node_,_style_,_image_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertSprite((_node_),0,0,(_style_),(_image_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// layer
#define SC_INSERT_LAYER(_node_,_style_,_size_) \
    ptrSCTemUIBuilder->insertLayer((_node_),0,0,(_style_),(_size_));

#define SC_BEGIN_CONTAINER_LAYER(_node_,_style_,_size_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLayer((_node_),0,0,(_style_),(_size_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LAYER_COLOR(_node_,_style_,_size_,_color_) \
    ptrSCTemUIBuilder->insertLayerColor((_node_),0,0,(_style_),(_size_),(_color_));

#define SC_BEGIN_CONTAINER_LAYER_COLOR(_node_,_style_,_size_,_color_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLayerColor((_node_),0,0,(_style_),(_size_),(_color_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// label
#define SC_INSERT_LABEL(_node_,_style_,_string_,_font_,_size_)\
    ptrSCTemUIBuilder->insertLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\

#define SC_BEGIN_CONTAINER_LABEL(_node_,_style_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LABEL_TTF(_node_,_style_,_string_,_font_,_size_)\
    ptrSCTemUIBuilder->insertLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_));

#define SC_BEGIN_CONTAINER_LABEL_TTF(_node_,_style_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_));\
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LABEL_BMFONT(_node_,_style_,_string_,_file_)\
    ptrSCTemUIBuilder->insertLabelBMFont((_node_),0,0,(_style_),(_string_),(_file_));

#define SC_BEGIN_CONTAINER_LABEL_BMFONT(_node_,_style_,_string_,_file_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertLabelBMFont((_node_),0,0,(_style_),(_string_),(_file_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// user node
#define SC_INSERT_USER_NODE(_node_,_style_) \
    ptrSCTemUIBuilder->insertUserNode((_node_),0,0,(_style_));

#define SC_BEGIN_CONTAINER_USER_NODE(_node_,_style_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertUserNode((_node_),0,0,(_style_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// button
#define SC_INSERT_BUTTON(_node_,_style_,_image_normal_,_image_select_,_image_disable_,_func_)\
    ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_normal_),(_image_select_),(_image_disable_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON(_node_,_style_,_image_normal_,_image_select_,_image_disable_,_func_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButton((_node_),0,0,(_style_),(_image_normal_),(_image_select_),(_image_disable_),(_func_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL(_node_,_style_,_string_,_font_,_size_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL(_node_,_style_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabel((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_TTF(_node_,_style_,_string_,_font_,_size_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL_TTF(_node_,_style_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabelTTF((_node_),0,0,(_style_),(_string_),(_font_),(_size_),(_func_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_BMFONT(_node_,_style_,_string_,_font_,_func_) \
    ptrSCTemUIBuilder->insertButtonLabelBMFont((_node_),0,0,(_style_),(_string_),(_font_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL_BMFONT(_node_,_style_,_string_,_font_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonLabelBMFont((_node_),0,0,(_style_),(_string_),(_font_),(_func_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_SWITCH(_node_,_style_,_true_item_,_false_item_,_value_,_func_) \
    ptrSCTemUIBuilder->insertButtonSwitch((_node_),0,0,(_style_),(_true_item_),(_false_item_),(_value_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_SWITCH(_node_,_style_,_true_item_,_false_item_,_value_,_func_) \
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertButtonSwitch((_node_),0,0,(_style_),(_true_item_),(_false_item_),(_value_),(_func_)); \
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// progress bar
#define SC_INSERT_PROGRESS_BAR(_node_,_style_,_image_back_,_image_front_,_value_,_is_hor_,_is_left_or_bottom_)\
    ptrSCTemUIBuilder->insertProgressBar((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_left_or_bottom_));

#define SC_BEGIN_CONTAINER_PROGRESS_BAR(_node_,_style_,_image_back_,_image_front_,_value_,_is_hor_,_is_left_or_bottom_)\
{\
auto pSCContainerNode = ptrSCTemUIBuilder->insertProgressBar((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_left_or_bottom_));\
ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

#define SC_INSERT_PROGRESS_RADIAL(_node_,_style_,_image_back_,_image_front_,_value_,_ccw_)\
    ptrSCTemUIBuilder->insertProgressRadial((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_ccw_));

#define SC_BEGIN_CONTAINER_PROGRESS_RADIAL(_node_,_style_,_image_back_,_image_front_,_value_,_ccw_)\
{\
    auto pSCContainerNode = ptrSCTemUIBuilder->insertProgressRadial((_node_),0,0,(_style_),(_image_back_),(_image_front_),(_value_),(_ccw_));\
    ptrSCTemUIBuilder->pushContainerStack(pSCContainerNode);

// layout
#define SC_BEGIN_CONTAINER_ALIGNMENT(_node_,_style_,_is_hor_,_padding_,_dock_) \
{\
    ptrSCTemUIBuilder->containerAlignment((_node_),0,0,(_style_),(_is_hor_),(_padding_),(_dock_));\

// scrollview
#define SC_BEGIN_CONTAINER_SCROLLVIEW(_node_,_style_,_is_hor_,_view_size_,_container_size_,_callback_) \
{\
    ptrSCTemUIBuilder->containerScrollView((_node_),0,0,(_style_),(_is_hor_),(_view_size_),(_container_size_),(_callback_));

// pageview
#define SC_BEGIN_CONTAINER_PAGEVIEW(_node_,_style_,_dir_,_size_,_page_index_,_callback_) \
{\
    ptrSCTemUIBuilder->containerPageView((_node_),0,0,(_style_),(_dir_),(_size_),(_page_index_),(_callback_));

#define SC_BEGIN_CONTAINER_PAGE(_node_,_size_) \
{\
    ptrSCTemUIBuilder->containerPage((_node_),(_size_));

// editbox
#define SC_INSERT_EDITBOX(_node_,_style_,_size_,_image_,_callback_) \
    ptrSCTemUIBuilder->insertEditBox((_node_),0,0,(_style_),(_size_),(_image_),(_callback_));

///---------- build-in
#define SC_INSERT_OPTION_MUSIC(_node_,_style_,_true_item_,_false_item_) \
do{\
    auto ptrMusic = SpeedCC::SCSetting::getInstance()->getMusicWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_style_),(_true_item_),(_false_item_),ptrMusic,nullptr) \
}while(0);

#define SC_INSERT_OPTION_SOUND(_node_,_style_,_true_item_,_false_item_) \
do{\
    auto ptrSound = SpeedCC::SCSetting::getInstance()->getSoundWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_style_),(_true_item_),(_false_item_),ptrSound,nullptr) \
}while(0);

#endif
