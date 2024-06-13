/*******************************************************************************/
/**
 * @file TFT.hpp
 * @brief Header file for the TFT library.
 *
 * @par project
 * TFT Display Driver
 *
 * @par language
 *  C++
 *
 * @par description
 * This header file contains the declarations for a comprehensive library
 * designed to interface with TFT (Thin-Film-Transistor) displays. It includes
 * essential functions, classes, and data structures required for initializing
 * the display, managing graphics, and handling user interactions. Detailed
 * implementation is provided in the corresponding source file (.cpp).
 *
 * @details
 * The library aims to provide an easy-to-use and efficient interface for
 * developers working with TFT displays. It supports various display operations
 * such as drawing shapes, displaying text.
 *
 * @note
 * Ensure that the appropriate hardware configurations and connections are made
 * before using this library. Refer to the documentation for supported TFT display
 * models and wiring instructions.
 *
 *
 * @version 1.0
 *
 * @date 2024-05-19
 *
 * @copyright GNU General Public License v3.0
 * 
 * @author
 * Mahmoud Abou-Hawis
 *
 *******************************************************************************/

/******************************************************************************/
/* MULTIPLE INCLUSION GUARD */
/******************************************************************************/
#ifndef _TFT_H_
#define _TFT_H_
/*******************************************************************************/

/******************************************************************************/
/* INCLUDES */
/******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <TFT_Conf.hpp>
#include <TFT_Port.hpp>
/******************************************************************************/

/** @defgroup TFT_display
 * @{
 * @file
 */

/**
 * @brief This namespace contain all classes needed for TFT.
 * 
 */
namespace display
{

  /**
   * @brief Enumerated type for TFT error status.
   *
   * This enumeration represents the status of TFT (Thin-Film-Transistor) operations.
   */
  enum class TFT_ErrorStatus
  {
    TFT_ERROR /**<! An error occurred during TFT operations. */,
    TFT_OK /**<! TFT operation was successful. */
  };

  /** @brief Types of requests that can be sent to the TFT display. */
  enum class RequestType
  {
    COMMAND /**<! Issued to the TFT display to control its behavior. */,
    DATA /**<! Sent to the TFT display to update its content*/
  };

  /** @brief Enumerated type for different font sizes.
   *
   *  This enumeration defines different font sizes that can be used in a TFT (Thin-Film-Transistor) display.
   *  The available font sizes include Font_16X20, Font_7X10, and Font_11X18.
   */
  enum class Fonts
  {
    Font_7X10,  /**<! Font size 7x10 pixels. (Default) */
    Font_11X18  /**<! Font size 11x18 pixels. */
  };

  /**
   * @brief Defines a set of basic color constants.
   */
enum Colors : uint16_t
{
    BLACK = 0x0000,       /**< Represents the color black. */
    RED = 0xF800,         /**< Represents the color red. */
    BLUE = 0x001F,        /**< Represents the color blue. */
    GREEN = 0x07E0,       /**< Represents the color green. */
    WHITE = 0xFFFF,       /**< Represents the color white. */
    YELLOW = 0xFFE0,      /**< Represents the color yellow. */
    PINK = 0xF81F,        /**< Represents the color pink. */
    BROWN = 0xA145,       /**< Represents the color brown. */
    GRAY = 0x8410,        /**< Represents the color gray (or grey). */
    ORANGE = 0xFD20,      /**< Represents the color orange. */
    PURPLE = 0x780F,      /**< Represents the color purple. */
    CYAN = 0x07FF,        /**< Represents the color cyan. */
    MAGENTA = 0xF81F,     /**< Represents the color magenta. */
    LIGHT_GRAY = 0xC618,  /**< Represents the color light gray. */
    DARK_GRAY = 0x7BEF,   /**< Represents the color dark gray. */
    LIGHT_BLUE = 0x7D7C,  /**< Represents the color light blue. */
    DARK_BLUE = 0x000D,   /**< Represents the color dark blue. */
    LIGHT_GREEN = 0x97F6, /**< Represents the color light green. */
    DARK_GREEN = 0x03E0,  /**< Represents the color dark green. */
    LIGHT_RED = 0xFC10,   /**< Represents the color light red. */
    DARK_RED = 0x8000,    /**< Represents the color dark red. */
    SKY_BLUE = 0x867D,    /**< Represents the color sky blue. */
    INDIGO = 0x4810,      /**< Represents the color indigo. */
    VIOLET = 0x801F,      /**< Represents the color violet. */
    TURQUOISE = 0x471A,   /**< Represents the color turquoise. */
    GOLD = 0xFEA0,        /**< Represents the color gold. */
    SILVER = 0xC618,      /**< Represents the color silver. */
    LAVENDER = 0xE73F,    /**< Represents the color lavender. */
    CORAL = 0xFBEA,       /**< Represents the color coral. */
    SALMON = 0xFC0E,      /**< Represents the color salmon. */
    CHOCOLATE = 0xD343,   /**< Represents the color chocolate. */
    TOMATO = 0xFB08,      /**< Represents the color tomato. */
    GOLDENROD = 0xDD24,   /**< Represents the color goldenrod. */
    FIREBRICK = 0xB104,   /**< Represents the color firebrick. */
    PLUM = 0xDD1B,        /**< Represents the color plum. */
    ORCHID = 0xDB9A,      /**< Represents the color orchid. */
    TAN = 0xD5B1,         /**< Represents the color tan. */
    NAVY = 0x0010,        /**< Represents the color navy. */
    AQUA = 0x07FF,        /**< Represents the color aqua. */
    TEAL = 0x0410,        /**< Represents the color teal. */
    MINT = 0x9DF3,        /**< Represents the color mint. */
    LIME = 0x07E0,        /**< Represents the color lime. */
    SPRING_GREEN = 0x07EF,/**< Represents the color spring green. */
    OLIVE = 0x7BE0,       /**< Represents the color olive. */
    MAROON = 0x7800,      /**< Represents the color maroon. */
    FUCHSIA = 0xF81F,     /**< Represents the color fuchsia. */
    PERIWINKLE = 0xC618,  /**< Represents the color periwinkle. */
    CHARTREUSE = 0x7FE0,  /**< Represents the color chartreuse. */
    SEASHELL = 0xFFF5,    /**< Represents the color seashell. */
    IVORY = 0xFFFE,       /**< Represents the color ivory. */
    BEIGE = 0xF7BB,       /**< Represents the color beige. */
    PEACH = 0xFED6,       /**< Represents the color peach. */
    SIENNA = 0xA285,      /**< Represents the color sienna. */
    KHAKI = 0xF731,       /**< Represents the color khaki. */
    PALE_GREEN = 0x9FD3,  /**< Represents the color pale green. */
    MIDNIGHT_BLUE = 0x18CE /**< Represents the color midnight blue. */
};


  /**
   * @brief Represents a point in two-dimensional space with integer coordinates.
   */
  struct point
  {
    uint32_t x; /**< The x-coordinate of the point. */
    uint32_t y; /**< The y-coordinate of the point. */
  };

  /*!
   * @brief Class representing the TFT display interface.
   *
   * This class provides methods for initializing and interacting with a
   * Thin-Film-Transistor (TFT) display, allowing for graphical operations
   * such as drawing shapes, displaying text, and managing color schemes.
   *
   * @ingroup TFT_display
   */
  class TFT : public TFT_COM
  {
  private:
    uint32_t hight   = TFT_HIGHT;    /**< Height of the TFT display. */
    uint32_t width   = TFT_WIDTH;    /**< Width of the TFT display. */
    uint32_t A0_Idx  = A0_PIN_IDX;   /**<A0 TFT pin identifier send to controlPin */
    uint32_t RST_Idx = RST_PIN_IDX;  /**<RST TFT pin identifier send to controlPin */
    int currentIdx = -1;                        /**< Refer to the current shown List */
    int NumberOfEmptyLists = NUMBER_OF_LISTS;   /**< Refer to the empty Lists which u can create*/

    struct List
    {
        char **List = nullptr;
        uint8_t len = 0;
        uint8_t idx = -1; 
    };
    List Lists[NUMBER_OF_LISTS];

    /**
     * @brief Send a frame via SPI.
     *
     * This function sends a frame via SPI with the specified request type.
     *
     * @param frame The frame to be sent.
     * @param requestType The request type for the SPI transmission.
     * @return no thing.
     */
    TFT_ErrorStatus Send(uint8_t frame, RequestType requestType);

    /**
     * @brief Set the Window size.
     *
     * @param[in] start start Row,column Address which will be Set.
     * @param[in] end end Row,column Address which will be Set.
     * @return TFT_ErrorStatus
     */
    TFT_ErrorStatus SetWindow(point *start, point *end);

    /**
     * @brief Initialize the TFT display.
     *
     * This function initializes the TFT display.
     */
    void TFT_Initialization();

/**
 * @brief Write a character to the TFT display.
 *
 * This function writes a single character to the TFT display at the specified position,
 * using the provided font, font dimensions, and specified foreground and background colors.
 *
 * @param[in] ch      The character to be written to the display.
 *                    It should be provided as an 8-bit unsigned integer (uint8_t).
 * @param[in] font    A pointer to the font data array. 
 *                    This array contains the bitmap representation of the font.
 * @param[in] font_w  The width of the character in the font, specified as a 32-bit unsigned integer (uint32_t).
 * @param[in] font_h  The height of the character in the font, specified as a 32-bit unsigned integer (uint32_t).
 * @param[in] start   A point structure specifying the starting position (bottom-right corner) on the screen
 *                    where the character should be written. The point structure should contain x and y coordinates.
 * @param[in] end     A point structure specifying the ending position (top-left corner) on the screen
 *                    to constrain where the character can be written. The point structure should contain x and y coordinates.
 * @param[in] color   The color to be used for the character (foreground color). 
 *                    This should be an enumeration or structure that defines color properties in 16-bit R5G6B5 format.
 * @param[in] bgColor The background color to be used behind the character.
 *                    This should also be an enumeration or structure that defines color properties in 16-bit R5G6B5 format.
 *
 * @return None.
 */
void WriteChar(uint8_t ch, const uint16_t *font, uint32_t font_w, uint32_t font_h, point start, point end, Colors color, Colors bgColor);



/**
 * @brief Draw a single pixel on the TFT display.
 *
 * This function draws a single pixel at the specified position on the TFT display
 * using the provided color.
 *
 * @param[in] point A pointer to a Point structure that specifies the position
 *                  on the screen where the pixel should be drawn.
 *                  The Point structure should contain x and y coordinates.
 * @param[in] color The color to be used for the pixel.
 *                  This should be an enumeration or structure that defines color properties
 *                  in the 16-bit R5G6B5 format.
 *
 * @return None.
*/
    void drawPixel(display::point * point, display::Colors color);



    void printList(int idx);

    void mark(int idx);

    void unmarked(int idx);
  
  public:

    /**
     * @brief Explicit constructor for initializing a TFT display.
     *
     * This constructor initializes a TFT display with the specified width and height.
     *
     * @param[in] _width The width of the TFT display.
     * @param[in] _height The height of the TFT display.
     * @param[in] DelayFunc The function for introducing delays .
     * @param[in] PinControlFun The function for controlling pins of the TFT display.
     *                          Takes two parameters: pin identifier and value.
     * @param[in] SPI_Func The function for SPI communication with the TFT display.
     *                     Takes a single parameter representing the data to be transferred.
     * @param[in] _RST_Idx The index or identifier of the RST (reset) pin of the TFT display.
     * @param[in] _A0_Idx The index or identifier of the A0 (command/data) pin of the TFT display.
     */
    explicit TFT();

    /**
     * @brief Copy constructor.
     *
     * This constructor creates a new TFT object by copying the contents of another TFT object.
     *
     * @param _TFT The TFT object to be copied.
     */
    TFT(const TFT &_TFT);

    /**
     * @brief Move constructor.
     *
     * This constructor creates a new TFT object by moving the contents of another TFT object.
     *
     * @param _TFT The TFT object to be moved.
     */
    TFT(TFT &&_TFT) noexcept;

    /**
     * @brief Draw a line on the TFT display.
     *
     * This function draws a line on the TFT display from the start point to the end point.
     *
     * @param[in] start The start point of the line.
     * @param[in] end The end point of the line.
     * @param[in] color The color of the line (default: BLACK).
     * @return The status of the draw operation.
     */
    void DrawLine(point *start, point *end, Colors color = Colors::BLACK);

    /**
     * @brief Draw a circle on the TFT display.
     *
     * This function draws a circle on the TFT display with the specified center and radius.
     *
     * @param[in] center The center point of the circle.
     * @param[in] radius The radius of the circle.
     * @param[in] color The color of the circle (default: BLACK).
     * @return The status of the draw operation.
     */
    void DrawCircle(point *center, uint8_t radius, Colors color = Colors::BLACK) ;

    /**
     * @brief Draw a square on the TFT display.
     *
     * This function draws a square on the TFT display with the specified upper and lower points.
     *
     * @param[in] upperPoint The upper-left point of the square.
     * @param[in] lowerPoint The lower-right point of the square.
     * @param[in] color The color of the square (default: BLACK).
     * @return The status of the draw operation.
     */
    TFT_ErrorStatus DrawRectOrSquare(point *upperPoint, point *lowerPoint, Colors color = Colors::BLACK);

    /**
     * @brief Draw text on the TFT display.
     *
     * This function draws text on the TFT display at the specified position.
     *
     * @param[in] str The text string to be drawn.
     * @param[in] font The font to be used for text (default: Font_7X10).
     * @param[in] color The color of the text (default: BLACK).
     * @return The status of the draw operation.
     */
    TFT_ErrorStatus WriteText(const char *str, Fonts font = Fonts::Font_7X10,
                              Colors TextColor = Colors::BLACK, Colors bgColor = Colors::WHITE,
                              point *startPosition = nullptr);

    /**
     * @brief Draw an image on the TFT display.
     *
     * This function draws an image on the TFT display.
     *
     * @param[in] Image Pointer to the image data.
     * @return The status of the draw operation.
     */
    TFT_ErrorStatus DrawImage(const uint16_t *Image, point *start, uint32_t image_width, uint32_t image_hight);


    /**
   * @brief Create a button on the TFT display.
   *
   * This function creates a button on the TFT display at the specified position
   * with the given text and colors.
   *
   * @param[in] pos Pointer to the position of the button (top-left corner).
   * @param[in] str The text to be displayed on the button.
   * @param[in] TextColor The color of the text (default is BLACK).
   * @param[in] bgColor The background color of the button (default is WHITE).
   * @return The status of the button creation operation.
   */
    TFT_ErrorStatus Button(point *pos,const char *str,Colors TextColor = Colors::BLACK, Colors bgColor = Colors::WHITE);

    /**
     * @brief Lists items from the provided array of strings.
     *
     * This function takes a list of strings and their length. 
     *
     * @param List An array of pointers to strings. Each pointer points to a C-style string.
     * @param len The number of items in the list.
     * 
     * @return The List id ,  -1 mean failed.
     */
    int OptionList(char ** List, uint8_t len);



    /**
     * @brief Displays an option list on the TFT display.
     *
     * This function displays a list of options on the TFT display based on the provided ID. 
     * 
     *
     * @param Id An identifier for the option list to be displayed. This ID determines which 
     *           option list is shown on the display.
     * 
     * @return TFT_ErrorStatus Returns an error status indicating the success or failure 
     *         of the operation. 
     */
    TFT_ErrorStatus ShowOptionList(uint8_t Id);


    /**
     * @brief Moves the iterator to the next element in the list.
     *
     * @return None
     */
    void next();


    /**
     * @brief Moves the iterator to the previous element in the list.
     *
     * @return None.
     */
    void previous();


    int getCurrenListElement();


    /** @brief Deleted destructor.
     *
     *  This destructor is deleted to prevent destruction of TFT objects.
     */
    ~TFT() = default;
  };
} /** namespace display */

/*! @} */

#endif