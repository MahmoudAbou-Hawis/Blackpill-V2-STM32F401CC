/**
 * @brief External C linkage for the included C header
 */
extern "C"
{
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_systick.h"
#include "TFT_CFG.h"
#include "TFT_Fonts.h"
}

#include "TFT.hpp"

using namespace display;

#define DISPLAY_OUT ((uint8_t)0x11)
#define PIXEL_FORMAT ((uint8_t)0x3A)
#define DISPLAY_ON ((uint8_t)0x29)
#define SET_COL ((uint8_t)0x2A)
#define SET_ROW ((uint8_t)0x2B)
#define WRITE_IN_RAM ((uint8_t)0x2C)
#define COLOR_R5G6B5 ((uint8_t)0x05)
#define PIN_HIGH ((uint8_t)0x01)
#define PIN_LOW ((uint8_t)0x00)

TFT_ErrorStatus TFT::Send(uint8_t frame, RequestType requestType)
{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;
    if (this->controlPin == nullptr || this->SendingFrame == nullptr)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        switch (requestType)
        {
        case RequestType::DATA:
            this->controlPin(TFT::A0_Idx, PIN_HIGH);
            break;
        case RequestType::COMMAND:
            this->controlPin(TFT::A0_Idx, PIN_LOW);
            break;
        default:
            break;
        }
        this->SendingFrame(frame);
    }
    return RET_Error;
}

void TFT::TFT_Initialization()
{
    if (this->controlPin == nullptr || this->SendingFrame == nullptr || this->DelayFunction == nullptr)
    {
        return;
    }
    else
    {
        this->controlPin(TFT::RST_Idx, PIN_HIGH);
        this->DelayFunction(100);
        this->controlPin(TFT::RST_Idx, PIN_LOW);
        this->DelayFunction(3);
        this->controlPin(TFT::RST_Idx, PIN_HIGH);
        this->DelayFunction(100);
        this->controlPin(TFT::RST_Idx, PIN_LOW);
        this->DelayFunction(100);
        this->controlPin(TFT::RST_Idx, PIN_HIGH);
        this->DelayFunction(120000);
        TFT::Send(DISPLAY_OUT, RequestType::COMMAND);
        this->DelayFunction(150000);
        TFT::Send(PIXEL_FORMAT, RequestType::COMMAND);
        TFT::Send(COLOR_R5G6B5, RequestType::DATA);
        TFT::Send(DISPLAY_ON, RequestType::COMMAND);
    }
}

TFT::TFT(uint32_t _width, uint32_t _height,
         std::function<void(uint32_t)> DelayFunc,
         std::function<void(uint32_t, uint8_t)> PinControlFun,
         std::function<void(uint8_t)> SPI_Func, uint8_t _RST_Idx, uint8_t _A0_Idx)
{

    this->A0_Idx = _A0_Idx;
    this->RST_Idx = _RST_Idx;
    this->hight = _height;
    this->width = _width;
    this->controlPin = PinControlFun;
    this->DelayFunction = DelayFunc;
    this->SendingFrame = SPI_Func;
    TFT::TFT_Initialization();
}

TFT_ErrorStatus TFT::SetWindow(point *start, point *end)
{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;
    if (start->x > this->width || start->y > this->hight || end->x > this->width || end->y > this->hight)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        start->x--;
        start->y--;
        end->x--;
        end->y--;
        TFT::Send(SET_COL, RequestType::COMMAND);
        TFT::Send((start->x >> 8), RequestType::DATA);
        TFT::Send((start->x & 0x00FF), RequestType::DATA);
        TFT::Send((end->x >> 8), RequestType::DATA);
        TFT::Send((end->x & 0x00FF), RequestType::DATA);
        TFT::Send(SET_ROW, RequestType::COMMAND);
        TFT::Send((start->y >> 8), RequestType::DATA);
        TFT::Send((start->y & 0x00FF), RequestType::DATA);
        TFT::Send((end->y >> 8), RequestType::DATA);
        TFT::Send((end->y & 0x00FF), RequestType::DATA);
        TFT::Send(WRITE_IN_RAM, RequestType::COMMAND);
    }
    return RET_Error;
}

TFT_ErrorStatus TFT::DrawImage(const uint16_t *Image, point *start, uint32_t image_width, uint32_t image_hight)

{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;

    if (Image == nullptr || start == nullptr || image_hight > TFT::hight || image_width > TFT::width)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        point str{start->x - (image_width - 1), start->y - (image_hight - 1)};
        if (TFT::SetWindow(&str, start) == TFT_ErrorStatus::TFT_OK)
        {
            for (uint32_t cnt = 0; cnt < (image_hight * image_width); cnt++)
            {
                TFT::Send((Image[cnt] >> 8), RequestType::DATA);
                TFT::Send((Image[cnt] & 0x00FF), RequestType::DATA);
            }
        }
        else
        {
            RET_Error = TFT_ErrorStatus::TFT_ERROR;
        }
    }
    return RET_Error;
}

TFT_ErrorStatus TFT::WriteText(const char *str, Fonts font,
                               Colors TextColor, Colors bgColor,
                               point *startPosition)
{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;
    if (str == nullptr || startPosition == nullptr ||
        startPosition->x > TFT::width || startPosition->y > TFT::hight)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        const uint16_t *fontArr = nullptr;
        point start;
        point end{startPosition->x, startPosition->y};
        uint8_t font_width;
        uint8_t font_height;
        switch (font)
        {
        case Fonts::Font_7X10:
            fontArr = reinterpret_cast<const uint16_t *>(Font7x10);
            font_width = 7;
            font_height = 10;
            break;
        case Fonts::Font_11X18:
            fontArr = reinterpret_cast<const uint16_t *>(Font11x18);
            font_width = 11;
            font_height = 18;
            break;
        default:
            font_width = 11;
            font_height = 18;
            break;
        }
        while (*str != '\0')
        {
            start = {end.x - 15, end.y - (font_height - 1)};
            if ((start.x > TFT::width || start.y > TFT::hight) || *str =='\n')
            {
                if(*str == '\n') str++;
                end = {128,end.y - font_height}; 
                continue;
            }
            else
            {
                if(start.x > TFT::width || start.y > TFT::hight || end.x > TFT::width || end.y > TFT::hight)
                {
                    RET_Error = TFT_ErrorStatus::TFT_ERROR;
                    break;
                }
                TFT::WriteChar(*str, fontArr, font_width , font_height, start, end, TextColor, bgColor);
            }
            str++;
            end.x -= 16;
        }
    }
    return RET_Error;
}

void TFT::WriteChar(uint8_t ch, const uint16_t *font,
                    uint32_t font_w , uint32_t font_h, display::point start, display::point end,
                    display::Colors color, display::Colors bgColor)
{
    TFT::SetWindow(&start, &end);
    uint32_t data;
    for(uint32_t i =  font_h -1 ; i <  UINT32_MAX  ; i--)
    {
        data = font[(ch - 32) * font_h + i];
        for(uint32_t j = 0 ; j < 16 ; j++)
        {
            if(data & (1 << j))
            {
                TFT::Send((color >> 8), RequestType::DATA);
                TFT::Send((color & 0x00FF), RequestType::DATA);
            }
            else
            {
                TFT::Send((bgColor >> 8), RequestType::DATA);
                TFT::Send((bgColor & 0x00FF), RequestType::DATA);
            }
        }
    }
}


void TFT::drawPixel(display::point * point, display::Colors color)
{
    display::point start = {point->x , point->y };
    SetWindow(&start,&start);
    TFT::Send((color >> 8), RequestType::DATA);
    TFT::Send((color & 0x00FF), RequestType::DATA);
}

TFT_ErrorStatus TFT::DrawLine(point *start, point *end, Colors color )
{
    int16_t x0 = start->x;
    int16_t y0 = start->y;
    int16_t x1 = end->x;
    int16_t y1 = end->y;

    int16_t dx = abs(x1 - x0);
    int16_t dy = abs(y1 - y0);
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t sy = y0 < y1 ? 1 : -1;
    int16_t err = (dx > dy ? dx : -dy) / 2;
    int16_t e2;

    while (1) {
        display::point p = {(uint32_t)x0, (uint32_t)y0};
        drawPixel(&p, color);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}


TFT_ErrorStatus TFT::DrawCircle(point *center, uint8_t radius, Colors color ) {
       int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {

        display::point p1 = {center->x + x, center->y - y};
        drawPixel(&p1, color);
        display::point p2 = {center->x + y, center->y - x};
        drawPixel(&p2, color);

        display::point p3 = {center->x - y, center->y - x};
        drawPixel(&p3, color);
        display::point p4 = {center->x - x, center->y - y};
        drawPixel(&p4, color);

        display::point p5 = {center->x - x, center->y + y};
        drawPixel(&p5, color);
        display::point p6 = {center->x - y, center->y + x};
        drawPixel(&p6, color);

        display::point p7 = {center->x + y, center->y + x};
        drawPixel(&p7, color);
        display::point p8 = {center->x + x, center->y + y};
        drawPixel(&p8, color);

        if (err <= 0) {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}