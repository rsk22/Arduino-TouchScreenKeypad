/*
  TouchScreenKeypad.h - Library for creating the touch screen keypad for the Seeed Studio TFT Touch Screen (Version 1).
  21 June 2014: Created by Richard Kirkpatrick
*/
#include "Arduino.h"
#include "TouchScreenKeypad.h"

#include <stdint.h>
#include <TouchScreenGeometry.h>
#include <TouchScreenStrings.h>
#include <TouchScreenButtons.h>

#include <TouchScreen.h>
#include <TFT.h>
#include <math.h>

/*
----------------------------------------------------------------
                   TouchScreenText Superclass
----------------------------------------------------------------
*/

TouchScreenText::TouchScreenText() : xstart(0), ystart(0), fontSize(1), textColor(0xffff)
{

}

TouchScreenText::TouchScreenText(TouchScreenText& otherTouchScreenText)
{
   xstart = otherTouchScreenText.xstart;
   ystart = otherTouchScreenText.ystart;
   fontSize = otherTouchScreenText.fontSize;
   textColor = otherTouchScreenText.textColor;
}


TouchScreenText::TouchScreenText(int myXStart, int myYStart, int myFontSize, unsigned int myTextColor)
    : xstart(myXStart), ystart(myYStart), fontSize(myFontSize), textColor(myTextColor)
{

}


void TouchScreenText::setTextCoord(int myXStart, int myYStart)
{
   xstart = myXStart;
   ystart = myYStart;
}


void TouchScreenText::setFontSize(int myFontSize)
{
   fontSize = myFontSize;
}


void TouchScreenText::setTextColor(unsigned int myTextColor)
{
   textColor = myTextColor;
}


const int TouchScreenText::getXStart()
{
   return xstart;
}


const int TouchScreenText::getYStart()
{
   return ystart;
}


const int TouchScreenText::getFontSize()
{
   return fontSize;
}


const int TouchScreenText::getTextColor()
{
   return textColor;
}


/*
----------------------------------------------------------------
		Functions for the TouchScreenString Subclass
----------------------------------------------------------------
*/

TouchScreenString::TouchScreenString() : TouchScreenText(), text("")
{

}


TouchScreenString::TouchScreenString(TouchScreenString& otherTouchScreenString)
{
  text = otherTouchScreenString.text;
  xstart = otherTouchScreenString.xstart;
  ystart = otherTouchScreenString.ystart;
  fontSize = otherTouchScreenString.fontSize;
  textColor = otherTouchScreenString.textColor;
}


TouchScreenString::TouchScreenString(char* myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor)
    : text(myText), TouchScreenText(myXStart, myYStart, myFontSize, myTextColor)
{

}


void TouchScreenString::setValues(char* myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor)
{
   text = myText;
   xstart = myXStart;
   ystart = myYStart;
   fontSize = myFontSize;
   textColor = myTextColor;
}


void TouchScreenString::setText(char* myText)
{
   text = myText;
}


const char* TouchScreenString::getText()
{
   return text;
}


void TouchScreenString::drawText()
{
   Tft.drawString(text, xstart, ystart, fontSize, textColor);
}


void TouchScreenString::textButtonDisplay()
{
   setTextColor(0xf800); ///< Sets the color to red
   drawText();
   delay(100);
   setTextColor(0xffff); ///< Sets the color to white
   drawText();
}

/*
----------------------------------------------------------------
		Functions for the TouchScreenChar Subclass
----------------------------------------------------------------
*/

TouchScreenChar::TouchScreenChar() : TouchScreenText(), text('0')
{

}


TouchScreenChar::TouchScreenChar(TouchScreenChar& otherTouchScreenChar)
{
  text = otherTouchScreenChar.text;
  xstart = otherTouchScreenChar.xstart;
  ystart = otherTouchScreenChar.ystart;
  fontSize = otherTouchScreenChar.fontSize;
  textColor = otherTouchScreenChar.textColor;
}


TouchScreenChar::TouchScreenChar(char myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor)
    : text(myText), TouchScreenText(myXStart, myYStart, myFontSize, myTextColor)
{

}


void TouchScreenChar::setValues(char myText, int myXStart, int myYStart, int myFontSize, unsigned int myTextColor)
{
   text = myText;
   xstart = myXStart;
   ystart = myYStart;
   fontSize = myFontSize;
   textColor = myTextColor;
}


void TouchScreenChar::setText(char myText)
{
   text = myText;
}


const char TouchScreenChar::getText()
{
   return text;
}


void TouchScreenChar::drawText()
{
   Tft.drawChar(text, xstart, ystart, fontSize, textColor);
}


void TouchScreenChar::textButtonDisplay()
{
   setTextColor(0xf800); ///< Sets the color to red
   drawText();
   delay(100);
   setTextColor(0xffff); ///< Sets the color to white
   drawText();
}

/*
----------------------------------------------------------------
                        TouchScreenKeypad
----------------------------------------------------------------
*/

TouchScreenKeypad::TouchScreenKeypad() : xCursor(20)
{
}

void TouchScreenKeypad::drawKeypad()
{

    const int xstartButton[] = {15, 95, 175};           // x-min for keypads
    const int ystartButton[] = {65, 127, 189, 251};     // y-min for keypads
    const int xendButton[] = {65, 145, 225};            // x-max for keypads
    const int yendButton[] = {115, 177, 239, 301};      // y-min for keypads
    const int xstartButtonText[] = {35, 115, 195};      // x-coordinate for keypad numbers
    const int ystartButtonText[] = {85, 145, 209, 271}; // y-coordinate for keypad numbers
    const int widthButton = 50;
    const int heightButton = widthButton;
    char textKeypad[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'C', '0', 'E'}; // Text for the buttons

    // Sets the xstart, ystart, width, and height of the textblock and then draws it
    Rectangle textBlock(15, 15, 216, 35, WHITE, BLACK);
    textBlock.draw();

    // Sets the coordinates and sizes of the keypad buttons, and sets all the values for the buttons' text
    const int noRows = 4;
    const int noColumns = 3;
    for(int y = 0; y < noRows; y++) {
        for(int x = 0; x < noColumns; x++) {
            int buttonNumber = noColumns * y + x;
            button[buttonNumber].setValues(xstartButton[x], ystartButton[y], widthButton, heightButton);
            buttonText[buttonNumber].setValues(textKeypad[buttonNumber], xstartButtonText[x], ystartButtonText[y], 1, WHITE);
    }
  }

    // Draws the keypads and their text
    for(int x = 0; x < 12; x++) {
        button[x].draw();
        buttonText[x].drawText();
  }
}

void TouchScreenKeypad::displayButton(const int userInput)
{
  // Only allow valid buttons to be displayed to prevent errors
  if (userInput >= 0 && userInput <= 12) {
      button[userInput].buttonDisplay();
      buttonText[userInput].textButtonDisplay();
  }
}

int TouchScreenKeypad::getButtonNumber(int xInput, int yInput)
{
    for (int i = 0; i < 12; i++) {
        if ((xInput > button[i].getXStart() && xInput < button[i].getXEnd())
            && (yInput > button[i].getYStart() && yInput < button[i].getYEnd()))
                return i;
    }

    // If no button is presed, return -1 signifying no button was pressed
    return -1;
}


void TouchScreenKeypad::displayText(char buttonText)
{
  // Ensures text input is not beyond width of screen and only a valid button.
  if (xCursor > 200) {
    // If true, it resets the input and notifies user.
    clearTextBlock();
    Tft.drawString("Too many inputs", 65, 30, 1, WHITE);
    delay(2000);
    clearTextBlock();
  } else {
    Tft.drawChar(buttonText, xCursor, 25, 2, WHITE);
    xCursor += 20;
  }
}

void TouchScreenKeypad::clearTextBlock()
{
    Tft.fillRectangle(16, 16, 214, 33, 0x0000);
    delay(10);
    xCursor = 20;
}













