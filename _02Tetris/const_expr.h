#ifndef CONST_EXPR_H
#define CONST_EXPR_H

#include "common_lib.h"

/********** 0/ NAMESPACE **********/

namespace CommonDefs {}
namespace OpenGLMode {}
namespace ConsoleMode {}

/********** 1/ BASE CONSTANTS **********/
namespace CommonDefs {
	// constanst for retrieving location of uniform variable in GLSL such as: time, speed...
	constexpr auto TIME_LOC = 0;
	constexpr auto SPEED_LOC = 1;

	constexpr auto BASE_SPEED = 1;				//in seconds;
	constexpr auto UNIT_CELL_SIZE = 60;			//base size of unit cell, mesured in the screen solution coordinates
	constexpr auto BULLETS_NUMBER = 4;			//base size of unit cell, mesured in the screen solution coordinates

	// multiple of unit cell size
	constexpr auto HALF_VIEWPORT_WIDTH = 8;	//half of viewport's width...
	constexpr auto HALF_VIEWPORT_HEIGHT = 5;	//half of viewport's height... 
	//...the sizes of viewport always are even number

	constexpr auto SCORE_ZONE_SIZE = 0;
	constexpr auto WINDOW_BUFFER = 0;			//size of buffer which wraps around the viewpoirt

	// the constants for printing out to console
	constexpr auto MIN_WIDTH_OF_STRING = 3;		//should be at least 3

	/********** 2/ DERIVED CONSTANTS **********/

	// constants for seting up the window and viewport size. They are mesured in the screen solution coordinates		
	constexpr auto VIEWPORT_HEIGHT = 2 * HALF_VIEWPORT_HEIGHT * UNIT_CELL_SIZE;
	constexpr auto VIEWPORT_WIDTH = 2 * HALF_VIEWPORT_WIDTH * UNIT_CELL_SIZE;

	constexpr auto VIEWPORT_X_START = UNIT_CELL_SIZE * WINDOW_BUFFER;
	constexpr auto VIEWPORT_Y_START = UNIT_CELL_SIZE * WINDOW_BUFFER;

	constexpr auto WINDOW_HEIGHT = UNIT_CELL_SIZE * 2 * (HALF_VIEWPORT_HEIGHT + WINDOW_BUFFER);
	constexpr auto WINDOW_WIDTH = UNIT_CELL_SIZE * (2 * (HALF_VIEWPORT_WIDTH + WINDOW_BUFFER) + SCORE_ZONE_SIZE);

	// the constants just to make some cumbersome expressions brief
	constexpr auto VERTICES_NUMBER_IN_A_ROW = 2 * HALF_VIEWPORT_WIDTH + 3;
	constexpr auto VERTICES_NUMBER_IN_A_COL = 2 * HALF_VIEWPORT_HEIGHT + 3;

	constexpr auto VERTICES_NUMBER = VERTICES_NUMBER_IN_A_ROW * VERTICES_NUMBER_IN_A_COL;
	constexpr auto MAX_UNIT_CELLS = VERTICES_NUMBER - VERTICES_NUMBER_IN_A_ROW;		//include one layout of cells surrounding the viewport

	/* constant for calculating coordiantes system in OpenGL. They are measured in normalized coordinates according to the viewport size*/
	constexpr GLfloat UNIT_IN_XAXIS = 1.0f / (2 * HALF_VIEWPORT_WIDTH);
	constexpr GLfloat UNIT_IN_YAXIS = 1.0f / (2 * HALF_VIEWPORT_HEIGHT);
	constexpr GLfloat XUNIT_OVER_YUNIT_RATIO = (GLfloat)HALF_VIEWPORT_WIDTH / HALF_VIEWPORT_HEIGHT;

	/* the array of index of cells which form a Tetromino's default shape */
	constexpr GLint BASE_INDICES_OF_DEFAULTS[][4] = {
		{ 0, -VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW, 2 * VERTICES_NUMBER_IN_A_ROW },
		/* index map of LETTER_I shape:
											[1]
											[0]
											[2]
											[3]				*/

		{ 0, -VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW + 1 },
		/* index map of LETTER_L shape:
											[1]
											[0]
											[2] [3]			*/

		{ 0, -VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW - 1, VERTICES_NUMBER_IN_A_ROW },
		/* index map of LETTER_J shape:
												[1]
												[0]
											[2]	[3]			*/

		{ 0, 1, VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW + 1 },
		/* index map of LETTER_O shape:
											[0] [1]
											[2] [3]			*/

		{ 0, 1, VERTICES_NUMBER_IN_A_ROW - 1, VERTICES_NUMBER_IN_A_ROW },
		/* index map of LETTER_S shape:
												[0] [1]
											[2]	[3]			*/

		{ 0, -1, VERTICES_NUMBER_IN_A_ROW, VERTICES_NUMBER_IN_A_ROW + 1 },
		/* index map of LETTER_Z shape:
											[1] [0]
												[2]	[3]		*/

		{ 0, -1, 1, VERTICES_NUMBER_IN_A_ROW},
		/* index map of LETTER_T shape:
											[1]	[0]	[2]
												[3]			*/

		{ 0, -VERTICES_NUMBER_IN_A_ROW - 1, -VERTICES_NUMBER_IN_A_ROW + 1, VERTICES_NUMBER_IN_A_ROW }
		/* index map of LETTER_Y shape:
											[1]   [2]
											   [0]
											   [3]			*/
			};

	/* the arrays for OpenGL-drawing*/
	extern const GLfloat* const VERTEX_ATTRIBS_ARR;
	extern const GLsizei* const INDICES_COUNTS_ARR;
	//extern void const** const VERTEX_INDICES_OFFSETS_ARR;

	extern GLint* const POSITION_STATES_ARR;
	extern GLint* const POSITION_STATES_WITH_CELL_INDICES;
	extern GLuint const* const CELL_INDICES_QUARTETS_ARR;
}
using namespace CommonDefs;
using namespace OpenGLMode;

#endif
