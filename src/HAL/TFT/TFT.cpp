/**
 * @brief External C linkage for the included C header
 */
extern "C"
{
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_systick.h"
#include "TFT_Fonts.hpp"
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
    switch (requestType)
    {
    case RequestType::DATA:
        TFT_SelectPin(TFT::A0_Idx, PIN_HIGH);
        break;
    case RequestType::COMMAND:
        TFT_SelectPin(TFT::A0_Idx, PIN_LOW);
        break;
    default:
        break;
    }
    TFT_SendSPI(frame);
    return RET_Error;
}

void TFT::TFT_Initialization()
{
    TFT_SelectPin(TFT::RST_Idx, PIN_HIGH);
    TFT_WaitMicroSeconds(100);
    TFT_SelectPin(TFT::RST_Idx, PIN_LOW);
    TFT_WaitMicroSeconds(3);
    TFT_SelectPin(TFT::RST_Idx, PIN_HIGH);
    TFT_WaitMicroSeconds(100);
    TFT_SelectPin(TFT::RST_Idx, PIN_LOW);
    TFT_WaitMicroSeconds(100);
    TFT_SelectPin(TFT::RST_Idx, PIN_HIGH);
    TFT_WaitMicroSeconds(120000);
    TFT::Send(DISPLAY_OUT, RequestType::COMMAND);
    TFT_WaitMicroSeconds(150000);
    TFT::Send(PIXEL_FORMAT, RequestType::COMMAND);
    TFT::Send(COLOR_R5G6B5, RequestType::DATA);
    TFT::Send(DISPLAY_ON, RequestType::COMMAND);
}

TFT::TFT()
{
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

void TFT::DrawLine(point *start, point *end, Colors color)
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


void TFT::DrawCircle(point *center, uint8_t radius, Colors color ) {
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


TFT_ErrorStatus TFT::DrawRectOrSquare(point *upperPoint, point *lowerPoint, Colors color )
{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;
    if(upperPoint == nullptr || lowerPoint == nullptr)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        display::point b = {upperPoint->x, lowerPoint->y};
        display::point c = {lowerPoint->x, upperPoint->y};
        DrawLine(upperPoint,&b,color);
        DrawLine(upperPoint,&c,color);
        DrawLine(&b,lowerPoint,color);
        DrawLine(&c,lowerPoint,color);
    }
    return RET_Error;
}

TFT_ErrorStatus TFT::Button(point * pos, const char *str, Colors TextColor, Colors bgColor)
{
    TFT_ErrorStatus RET_Error = TFT_ErrorStatus::TFT_OK;
    if(pos == nullptr || strlen(str) > 5)
    {
        RET_Error = TFT_ErrorStatus::TFT_ERROR;
    }
    else
    {
        for(int i = 0 ; i < 30 ; i++)
        {
            display::point end = {pos->x-90 , pos->y};
            DrawLine(pos,&end,bgColor);
            pos->y--;
        }
        pos->y += 20;
        pos->x -= 10;
        WriteText(str,display::Fonts::Font_7X10,TextColor,bgColor,pos);
        pos->y += 10;
        pos->x += 10;
    }
    return RET_Error;
}

#if NUMBER_OF_LISTS 


int TFT::OptionList(char ** List, uint8_t len)
{
    int RET = -1;
    if(List != nullptr && len > 0 && NumberOfEmptyLists != 0)
    {
        Lists[--NumberOfEmptyLists].idx  = 0;
        Lists[NumberOfEmptyLists].len    = len;
        Lists[NumberOfEmptyLists].List   = List;
        RET = NumberOfEmptyLists;
    }   
    else
    {
        /** No thing */
    }
    return RET;
}

void TFT::printList(int idx)
{
    int i = 0;
    display::point x = {128,140};
    display::point start = {128,160};
    display::point end = {1,start.y};
    while (start.y > 0)
    {
        DrawLine(&start,&end,display::WHITE);
        start.y--;
        end = {0,start.y};
    }
    for(i = 0 ; i < 4 && (i+idx) < Lists[currentIdx].len ; i++)
    {
        WriteText(Lists[currentIdx].List[idx + i],display::Fonts::Font_7X10,display::BLACK,display::WHITE,&x);
        x.y -= 40;
    }
    if(i < 4)
    {
        x.y +=20;
        point end = {1,x.y};
        while (x.y > 0)
        {
            DrawLine(&x,&end,display::WHITE);
            x.y--;
            end = {1,x.y};
        }
        
    }
}

void TFT::mark(int idx)
{
    display::point start = {128,(160 - ((idx%4) * 40))};
    display::point end   = {1,start.y}; 
    for(int i = 0 ; i < 40 ; i++)
    {
        DrawLine(&start,&end,display::CHOCOLATE);
        start.y--;
        end.y = start.y;
    }
    start.y +=20;
    WriteText(Lists[currentIdx].List[idx],display::Fonts::Font_7X10,display::BLACK,display::CHOCOLATE,&start);
}

void TFT::unmarked(int idx)
{
    display::point start = {128,(160 - ((idx%4) * 40))};
    display::point end   = {1,start.y}; 
    for(int i = 0 ; i < 40 ; i++)
    {
        DrawLine(&start,&end,display::WHITE);
        start.y--;
        end.y = start.y;
    }
    start.y +=20;
    WriteText(Lists[currentIdx].List[idx],display::Fonts::Font_7X10,display::BLACK,display::WHITE,&start);
}

TFT_ErrorStatus TFT::ShowOptionList(uint8_t Id)
{
    TFT_ErrorStatus RET_ErrorStatus = TFT_ErrorStatus::TFT_OK;
    if(Id >= NumberOfEmptyLists && Id < NUMBER_OF_LISTS)
    {
        currentIdx = Id;
        printList(Lists[currentIdx].idx);
        mark(Lists[currentIdx].idx);
    }
    else
    {
        RET_ErrorStatus = TFT_ErrorStatus::TFT_ERROR;
    }
    return RET_ErrorStatus;
}



void TFT::next()
{
    Lists[currentIdx].idx++;
    Lists[currentIdx].idx %= Lists[currentIdx].len;
    if((Lists[currentIdx].idx) %4 == 0)
    {
        printList(Lists[currentIdx].idx);
        mark(Lists[currentIdx].idx);
    }
    else
    {
        unmarked(Lists[currentIdx].idx-1);
        mark(Lists[currentIdx].idx);
    }
}


void TFT::previous()
{
    Lists[currentIdx].idx--;
    Lists[currentIdx].idx %= Lists[currentIdx].len;
    if((Lists[currentIdx].idx) %4 == 3)
    {
        int n = ((Lists[currentIdx].idx /4)) * 4;
        printList(n);
        mark(Lists[currentIdx].idx);
    }
    else
    {
        unmarked(Lists[currentIdx].idx+1);
        mark(Lists[currentIdx].idx);
    }
}


int TFT::getCurrenListElement()
{
    return Lists[currentIdx].idx;
}




#endif