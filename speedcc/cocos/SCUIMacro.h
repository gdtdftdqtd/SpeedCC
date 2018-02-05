

#ifndef __SPEEDCC__SCUIMACRO_H__
#define __SPEEDCC__SCUIMACRO_H__

// root
#define SC_BEGIN_CONTAINER_ROOT(_x_,_y_,_property_,_size_) \
    SC_BEGIN_CONTAINER_ROOT_EX((_x_),(_y_),(_property_),(_size_),this->getBedNode(),this);

#define SC_BEGIN_CONTAINER_ROOT_EX(_x_,_y_,_property_,_size_,_parent_,_ref_) \
{\
    _ptrUI->beginContainerRoot((_x_),(_y_),(_property_),(_size_),(_parent_),(_ref_));

#define SC_END_CONTAINER \
    _ptrUI->popContainerStack(); \
}

// sprite
#define SC_INSERT_SPRITE(_node_,_x_,_y_,_property_,_image_) \
    _ptrUI->insertSprite((_node_),(_x_),(_y_),(_property_),(_image_));

#define SC_BEGIN_CONTAINER_SPRITE(_node_,_x_,_y_,_property_,_image_) \
{\
    auto pSCContainerNode = _ptrUI->insertSprite((_node_),(_x_),(_y_),(_property_),(_image_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

// layer
#define SC_INSERT_LAYER(_node_,_x_,_y_,_property_,_size_) \
    _ptrUI->insertLayer((_node_),(_x_),(_y_),(_property_),(_size_));

#define SC_BEGIN_CONTAINER_LAYER(_node_,_x_,_y_,_property_,_size_) \
{\
    auto pSCContainerNode = _ptrUI->insertLayer((_node_),(_x_),(_y_),(_property_),(_size_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LAYER_COLOR(_node_,_x_,_y_,_property_,_size_,_color_) \
    _ptrUI->insertLayerColor((_node_),(_x_),(_y_),(_property_),(_size_),(_color_));

#define SC_BEGIN_CONTAINER_LAYER_COLOR(_node_,_x_,_y_,_property_,_size_,_color_) \
{\
    auto pSCContainerNode = _ptrUI->insertLayerColor((_node_),(_x_),(_y_),(_property_),(_size_),(_color_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

// label
#define SC_INSERT_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
    _ptrUI->insertLabel((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_));\

#define SC_BEGIN_CONTAINER_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = _ptrUI->insertLabel((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_));\
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
    _ptrUI->insertLabelTTF((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_));

#define SC_BEGIN_CONTAINER_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
{\
    auto pSCContainerNode = _ptrUI->insertLabelTTF((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_));\
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_file_)\
    _ptrUI->insertLabelBMFont((_node_),(_x_),(_y_),(_property_),(_string_),(_file_));

#define SC_BEGIN_CONTAINER_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_file_)\
{\
    auto pSCContainerNode = _ptrUI->insertLabelBMFont((_node_),(_x_),(_y_),(_property_),(_string_),(_file_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

// user node
#define SC_INSERT_USER_NODE(_node_,_x_,_y_,_property_) \
    _ptrUI->insertUserNode((_node_),(_x_),(_y_),(_property_));

#define SC_BEGIN_CONTAINER_USER_NODE(_node_,_x_,_y_,_property_) \
{\
    auto pSCContainerNode = _ptrUI->insertUserNode((_node_),(_x_),(_y_),(_property_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

// button
#define SC_INSERT_BUTTON(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_func_)\
    _ptrUI->insertButton((_node_),(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_func_)\
{\
    auto pSCContainerNode = _ptrUI->insertButton((_node_),(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),(_func_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
    _ptrUI->insertButtonLabel((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = _ptrUI->insertButtonLabel((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),(_func_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
    _ptrUI->insertButtonLabelTTF((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
{\
    auto pSCContainerNode = _ptrUI->insertButtonLabelTTF((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),(_func_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_func_) \
    _ptrUI->insertButtonLabelBMFont((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_func_) \
{\
    auto pSCContainerNode = _ptrUI->insertButtonLabelBMFont((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_func_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_BUTTON_SWITCH(_node_,_x_,_y_,_property_,_true_item_,_false_item_,_value_,_func_) \
    _ptrUI->insertButtonSwitch((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),(_value_),(_func_));

#define SC_BEGIN_CONTAINER_BUTTON_SWITCH(_node_,_x_,_y_,_property_,_true_item_,_false_item_,_value_,_func_) \
{\
    auto pSCContainerNode = _ptrUI->insertButtonSwitch((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),(_value_),(_func_)); \
    _ptrUI->pushContainerStack(pSCContainerNode);

// progress bar
#define SC_INSERT_PROGRESS_BAR(_node_,_x_,_y_,_property_,_image_back_,_image_front_,_value_,_is_hor_,_is_desc_,_is_left_or_bottom_)\
    _ptrUI->insertProgressBar((_node_),(_x_),(_y_),(_property_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_desc_),(_is_left_or_bottom_));

#define SC_BEGIN_CONTAINER_PROGRESS_BAR(_node_,_x_,_y_,_property_,_image_back_,_image_front_,_value_,_is_hor_,_is_desc_,_is_left_or_bottom_)\
{\
auto pSCContainerNode = _ptrUI->insertProgressBar((_node_),(_x_),(_y_),(_property_),(_image_back_),(_image_front_),(_value_),(_is_hor_),(_is_desc_),(_is_left_or_bottom_));\
_ptrUI->pushContainerStack(pSCContainerNode);

#define SC_INSERT_PROGRESS_RADIAL(_node_,_x_,_y_,_property_,_image_back_,_image_front_,_value_)\
    _ptrUI->insertProgressRadial((_node_),(_x_),(_y_),(_property_),(_image_back_),(_image_front_),(_value_));

#define SC_BEGIN_CONTAINER_PROGRESS_RADIAL(_node_,_x_,_y_,_property_,_image_back_,_image_front_,_value_)\
{\
    auto pSCContainerNode = _ptrUI->insertProgressRadial((_node_),(_x_),(_y_),(_property_),(_image_back_),(_image_front_),(_value_));\
    _ptrUI->pushContainerStack(pSCContainerNode);

// layout
#define SC_BEGIN_CONTAINER_PADDING(_node_,_x_,_y_,_property_,_size_,_is_hor_,_padding_,_dock_) \
{\
    _ptrUI->containerLayoutPadding((_node_),(_x_),(_y_),(_property_),(_size_),(_is_hor_),(_padding_),(_dock_));\


// build-in
#define SC_INSERT_OPTION_MUSIC(_node_,_x_,_y_,_property_,_true_item_,_false_item_) \
do{\
    auto ptrMusic = SpeedCC::SCSetting::getInstance()->getMusicWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),ptrMusic,NULL) \
}while(0);

#define SC_INSERT_OPTION_SOUND(_node_,_x_,_y_,_property_,_true_item_,_false_item_) \
do{\
    auto ptrSound = SpeedCC::SCSetting::getInstance()->getSoundWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),ptrSound,NULL) \
}while(0);

#endif
