#include "display.hpp"
// #include "./img_up_arrow.c"
// #include "./img_down_arrow.c"
// #include "./img_circle.c"


// images
LV_IMG_DECLARE(img_up_arrow)
LV_IMG_DECLARE(img_down_arrow)
LV_IMG_DECLARE(img_circle)


namespace display {


  void init() {

    // white background
    lv_style_t parent_style;
    lv_style_copy(&parent_style, &lv_style_scr);
    lv_obj_set_style(lv_scr_act(), &parent_style);

    // create image
    img_deposit_assist = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_deposit_assist, &img_circle);
    lv_obj_align(img_deposit_assist, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
  }


  void set_assist_state(AssistState state) {
    switch (state) {

      case (STATE_NONE): lv_obj_set_hidden(img_deposit_assist, true); break;
      case (STATE_GOOD): lv_img_set_src(img_deposit_assist, &img_circle); lv_obj_set_hidden(img_deposit_assist, false); break;
      case (STATE_FORWARD): lv_img_set_src(img_deposit_assist, &img_up_arrow); lv_obj_set_hidden(img_deposit_assist, false); break;
      case (STATE_BACKWARD): lv_img_set_src(img_deposit_assist, &img_down_arrow); lv_obj_set_hidden(img_deposit_assist, false); break;
    }
  }
}