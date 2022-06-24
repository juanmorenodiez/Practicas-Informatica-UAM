/**
* @brief Defines the screen
*
* Composes the screen of the game which is the
* visual part where we will be seeing every
* element of the game.
*
* @file screen.h
* @author Andrés Mena
* @version 1.1
* @date 08-04-2018
*/

#ifndef __SCREEN__
#define __SCREEN__

#define SCREEN_MAX_STR 80  /*!< max str of the screen */

/**
* @brief screen of the game
*
* Struct for storing the variables
* that compose the screen of the game.
*/

typedef struct _Area Area;

/**
* @brief initialises a new screen
*
* Destroys any previous screen and allocates
* memory for a new one.
*
* @author Andrés Mena
* @return void.
*/

void  screen_init();

/**
* @brief frees memory
*
* frees the data that screen occupied.
*
* @author Andrés Mena
* @return void.
*/

void  screen_destroy();

/**
* @brief paints the screen
*
* Prints a screen in the console.
*
* @author Andrés Mena
* @return void.
*/

void  screen_paint();

/**
* @brief gets the data
*
* Gets the data typed in the ingame console (commands).
*
* @author Andrés Mena
* @param str char (data of the console).
* @return void.
*/

void  screen_gets(char *str);

/**
* @brief creates new area
*
* Allocates memory for an area, using x and y coordinates
* as a start point and width and height as the size.
*
* @author Andrés Mena
* @param x int (coord x).
* @param y int (coord y).
* @param width int (width of the area).
* @param height int (height of the area).
* @return pointer to area.
*/

Area* screen_area_init(int x, int y, int width, int height);

/**
* @brief frees memory
*
* Receives pointer to area and frees the
* memory it occupied.
*
* @author Andrés Mena
* @param area pointer to area.
* @return void.
*/

void  screen_area_destroy(Area* area);

/**
* @brief clears the area
*
* Deletes everthing in the area, leaving
* it as if it was just created.
*
* @author Andrés Mena
* @param area pointer to area.
* @return void.
*/

void  screen_area_clear(Area* area);

/**
* @brief resets cursor
*
* Resets the cursor, leaving it in the 0,0
* coordinates of the area.
*
* @author Andrés Mena
* @param area pointer to area.
* @return void.
*/

void  screen_area_reset_cursor(Area* area);

/**
* @brief puts area
*
* Starts a new line in the area.
*
* @author Andrés Mena
* @param area pointer to area.
* @param str char.
* @return void.
*/

void  screen_area_puts(Area* area, char *str);

#endif
