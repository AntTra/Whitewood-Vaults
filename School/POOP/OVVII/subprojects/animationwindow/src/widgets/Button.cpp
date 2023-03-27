#include "widgets/Button.h"
#include <utility>

TDT4102::Button::Button(TDT4102::Point location, unsigned int width, unsigned int height, std::string label) :
    TDT4102::Widget(location, width, height),
    label{std::move(label)} {}

void TDT4102::Button::update(nk_context *context) {

    bool rightMouseIsDown = nk_input_has_mouse_click_in_button_rect(&context->input, NK_BUTTON_RIGHT, context->current->layout->clip);
    bool rightMouseIsBeingPressed = rightMouseIsDown && !lastRightMouseButtonState;
    lastRightMouseButtonState = rightMouseIsDown;
    struct nk_style* s = &context->style;    
    nk_style_push_color(context, &s->button.text_normal, labelColor);
    nk_style_push_style_item(context, &s->button.normal, nk_style_item_color(buttonColor));
    nk_style_push_style_item(context, &s->button.hover, nk_style_item_color(buttonColor));
    nk_style_push_style_item(context, &s->button.active, nk_style_item_color(nk_rgb(255,255,255)));
    if (nk_button_label(context, label.c_str()) || rightMouseIsBeingPressed) {
        fire();
    }
    nk_style_pop_color(context);
    nk_style_pop_style_item(context);
    nk_style_pop_style_item(context);
    nk_style_pop_style_item(context);
}

void TDT4102::Button::setLabel(std::string newlabel) {
    label = newlabel;
}
