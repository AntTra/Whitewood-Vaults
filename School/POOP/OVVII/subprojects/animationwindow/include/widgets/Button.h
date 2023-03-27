#pragma once

#include "Widget.h"
#include "Point.h"
#include <string>
#include "Color.h"
namespace TDT4102 {
    class Button : public TDT4102::Widget {
    private:
        std::string label;
        bool lastRightMouseButtonState = false;
        nk_color labelColor = nk_color();
        nk_color buttonColor = nk_rgba(200,200,200,255);
    protected:
        void update(nk_context* context) override;
    public:
        explicit Button(TDT4102::Point location, unsigned int width, unsigned int height, std::string label);
        void setLabel(std::string newlabel);
        void setLabelColor(Color newColor) {labelColor = nk_color{(nk_byte)newColor.redChannel, (nk_byte)newColor.greenChannel, (nk_byte)newColor.blueChannel, (nk_byte)newColor.alphaChannel};};
        void setButtonColor(Color newColor) {buttonColor = nk_color{(nk_byte)newColor.redChannel, (nk_byte)newColor.greenChannel, (nk_byte)newColor.blueChannel, (nk_byte)newColor.alphaChannel};}
    
    };
}