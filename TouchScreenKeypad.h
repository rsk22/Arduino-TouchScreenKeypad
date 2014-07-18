/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 * Author: Richard Kirkpatrick
 *
 * This is the Arduino library for creating a keypad for the Seeed Studio TFT touch screen (Version 1).
 * The user can set a password through the main Arduino file.
 * See the Wiki documentation page for more info!
 *
 */

#ifndef TouchScreenKeypad_h
#define TouchScreenKeypad_h

#include "Arduino.h"
#include <TouchScreenGeometry.h>
#include <TouchScreenStrings.h>
#include <TouchScreenButtons.h>
#include <Password.h> // http://playground.arduino.cc/Code/Password



/*
----------------------------------------------------------------
				  TouchScreenText Superclass
----------------------------------------------------------------
*/
///@class TouchScreenText
///@brief Base class for drawing text to the touch screen.
class TouchScreenText {
public:

    /*!
    @brief Default constructor for the TouchScreenText superclass
    @param  xstart The x-coordinate for the text instance.
    @param  ystart The y-coordinate for the text instance.
    @param  fontSize The font size of the text instance.
    @param  textColor The color of the text instance. Default color is WHITE.
    */
    TouchScreenText();

    /*!
    @class TouchScreenText
    @brief Parameter constructor for the TouchScreenText superclass
    @param  otherTouchScreenText The text that is to be copied.
    */
    TouchScreenText(TouchScreenText& otherTouchScreenText);

    /*!
    @brief Parameter constructor for the TouchScreenText superclass
    @param  myXStart The x-coordinate for the text instance.
    @param  myYStart The y-coordinate for the text instance.
    @param  myFontSize The font size of the text instance.
    @param  myTextColor The color of the text instance. Default color is WHITE.
    */

    TouchScreenText(int, int, int, unsigned int);

    /*!
    @brief Sets the coordinates of the text.
    @param  myXStart The x-coordinate for the text instance.
    @param  myYStart The y-coordinate for the text instance.
    */

    void setTextCoord(int, int);

    /*!
    @brief Sets the font size of the text.
    @param  myFontSize The font size of the text instance.
    */
    void setFontSize(int defaultFontText = 2);

    /*!
    @brief Sets the color of the text.
    @param  myTextColor The color of the text instance.
    */
    void setTextColor(unsigned int textColor = 0xffff);  // Default color is WHITE.

    /*!
    @brief Gets the xcoordinate of the text.
    @return The x-coordinate for the text instance.
    */
    const int getXStart();

    /*!
    @brief Gets the ycoordinate of the text.
    @return The y-coordinate for the text instance.
    */
    const int getYStart();

    /*!
    @brief Gets the font size of the text.
    @return The font size for the text instance.
    */
    const int getFontSize();

    /*!
    @brief Gets the font color of the text.
    @return The font color for the text instance.
    */
    const int getTextColor();

protected:
  int xstart, ystart; /// Coordinates of the text
  int fontSize; /// Size of the text
  unsigned int textColor; /// Color of the text
};

/*
----------------------------------------------------------------
				  TouchScreenString Subclass
----------------------------------------------------------------
*/
/*!
@class TouchScreenString
@brief Subclass of TouchScreenText. Abstract class for drawing strings to the touch screen.
*/
class TouchScreenString : public TouchScreenText {
 public:
    ///@brief Default constructor for the TouchScreenString subclass.
    TouchScreenString();

    /*!
    @brief Copy constructor for the TouchScreenString superclass
    @param  otherTouchScreenString The string instance that is to be copied.
    */
    TouchScreenString(TouchScreenString& otherTouchScreenString);

    /*!
    @brief Parameter constructor for the TouchScreenString superclass.
    @param  myText The text that is to be drawn.
    @param  myXStart The x-coordinate for the text instance.
    @param  myYStart The y-coordinate for the text instance.
    @param  myFontSize The font size of the text instance.
    @param  myTextColor The color of the text instance.
    */
    TouchScreenString(char* myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor);

    /*!
    @brief Sets the text, coordinates, font size, and text color of the instance.
    @param  myText The text that is to be drawn.
    @param  myXStart The x-coordinate for the text instance.
    @param  myYStart The y-coordinate for the text instance.
    @param  myFontSize The font size of the text instance.
    @param  myTextColor The color of the text instance. Default color is WHITE.
    */
    void setValues(char* myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor);

    /*!
    @brief Sets the text of the string instance.
    @param  myText The text that is to be drawn.
    */
    void setText(char*);

    /*!
    @brief Returns the text of the string instace.
    @return text The text that is to be drawn.
    */
    const char* getText();

    /*!
    @brief Uses the TFT library to draw the string instance.
    */
    void drawText();

    /*!
    @brief Highlights the button text when pressed.
    */
    void textButtonDisplay();

 private:
    char* text;
};

/*
----------------------------------------------------------------
				  TouchScreenChar Subclass
----------------------------------------------------------------
*/

///@class TouchScreenChar
///@brief Subclass of TouchScreenText.  Abstract class used for drawing char's to the touch screen.
class TouchScreenChar : public TouchScreenText {
 public:
    /*!
    @brief Default constructor for the TouchScreenString subclass.
    */
    TouchScreenChar();

    /*!
    @brief Copy constructor for the TouchScreenString subclass.
    @param  otherTouchScreenChar The char instance that is being copied.
    */
    TouchScreenChar(TouchScreenChar& otherTouchScreenChar);

    /*!
    @brief Parameter constructor for the TouchScreenString superclass.
    @param  myText The char that is to be drawn.
    @param  myXStart The x-coordinate for the char instance.
    @param  myYStart The y-coordinate for the char instance.
    @param  myFontSize The font size of the char instance.
    @param  myTextColor The color of the char instance.
    */
    TouchScreenChar(char myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor);

    /*!
    @brief Sets the char, cooordinates, font size, and char color.
    @param  myText The char that is to be drawn.
    @param  myXStart The x-coordinate for the char instance.
    @param  myYStart The y-coordinate for the char instance.
    @param  myFontSize The font size of the char instance.
    @param  myTextColor The color of the char instance.
    */
    void setValues(char myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor);

    /*!
    @brief Sets the text of the char instance.
    @param  myText The char that is to be drawn.
    */
    void setText(char myText);

    /*!
    @brief Returns the char of the char instance.
    @return The char that is to be drawn.
    */
    const char getText();

    ///@brief Uses the Seeed Studio library to draw the char.
    void drawText();

    ///@brief Highlights the button text when pressed.
    void textButtonDisplay();

 private:
    char text;
};



/*
----------------------------------------------------------------
                        TouchScreenKeypad
----------------------------------------------------------------
*/


///@class TouchScreenKeypad
///@brief Class for handling all the TFT Touch Screen keypad functions
class TouchScreenKeypad {
 public:
    ///@brief Default constructor for the Keypad class
    TouchScreenKeypad();

    ///@brief Draws the keypad to the scree
    void drawKeypad();

    ///@brief Highlights the button when pressed
    ///@param  userInput    The button that was selected by the user.
    void displayButton(const int userInput);

    /**
    @brief Gets the button number that was pressed.  Returns -1 if no button was pressed.
    @param  xInput   The x-coordinate of the user's input.
    @param  yInput   The y-coordinate of the user's input.
    */
    int getButtonNumber(int xInput, int yInput);

    /**
    @brief Displays the text to the screen
    @param  buttonText  The text for the button
    */
    void displayText(char buttonText);

    ///@brief Clears the textblock and resets the cursor to the original position.
    void clearTextBlock();

 private:
    Button button[12];
    TouchScreenChar buttonText[12];
    Rectangle textBlock;
    int xCursor; ///< Used for positioning the text on the screen
};

#endif
