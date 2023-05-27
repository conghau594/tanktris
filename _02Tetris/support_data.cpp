#include "type_decl.h"

/********** the functions used only once before the main() **********/

//declaration of functions and const varible
namespace CommonDefs {
	GLint* createPositionStatesArr(GLint _0or1_);
	void printVertexAttribArray(void);
	void printCellIndicesQuartetsArray(void);
	void printGameBoardOntoConsole(void);
}

//definition of functions and const varible
namespace CommonDefs { 
	//delete the cursor of console
	BOOL cursorDeleted = SetConsoleCursorInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		new CONSOLE_CURSOR_INFO{ 1, 0 }
	);

	GLint* createPositionStatesArr(GLint _0or1_) {
		static GLint statesArr1[MAX_UNIT_CELLS] = { 0 };
		static GLint statesArr0[MAX_UNIT_CELLS] = { 0 };

		if (statesArr0[0] == 0) {
			int i;
			for (i = 0; i < MAX_UNIT_CELLS; ++i) {
				statesArr1[i] = CommonDefs::PositionState::FREE;
				statesArr0[i] = CommonDefs::PositionState::FREE;
			}
			GLsizei tmp = (VERTICES_NUMBER_IN_A_COL - 2) * VERTICES_NUMBER_IN_A_ROW;

			//* fill the array elements making up the 4 sides of game field
			for (i = 0; i < VERTICES_NUMBER_IN_A_ROW; ++i) {
				statesArr1[i] = CommonDefs::PositionState::FORBIDDEN;
				statesArr1[tmp + i] = CommonDefs::PositionState::FORBIDDEN;

				statesArr0[i] = CommonDefs::PositionState::FORBIDDEN;
				statesArr0[tmp + i] = CommonDefs::PositionState::FORBIDDEN;
			}

			for (i = 1; i < VERTICES_NUMBER_IN_A_COL - 2; ++i) {
				tmp = (i + 1) * VERTICES_NUMBER_IN_A_ROW - 2;
				statesArr1[i * VERTICES_NUMBER_IN_A_ROW] = CommonDefs::PositionState::FORBIDDEN;		//-2 means the location is forbidden (out of game field)
				statesArr0[i * VERTICES_NUMBER_IN_A_ROW] = CommonDefs::PositionState::FORBIDDEN;		//-2 means the location is forbidden (out of game field)

				statesArr1[tmp] = CommonDefs::PositionState::FORBIDDEN;
				statesArr0[tmp] = CommonDefs::PositionState::FORBIDDEN;

				++tmp;
				statesArr1[tmp] = CommonDefs::PositionState::FORBIDDEN;
				statesArr0[tmp] = CommonDefs::PositionState::FORBIDDEN;
			}
		}
		if (_0or1_ == 0) return statesArr0;
		return statesArr1;
	}

	//array of state of position
	GLint* const POSITION_STATES_ARR = createPositionStatesArr(0);
	GLint* const POSITION_STATES_WITH_CELL_INDICES = createPositionStatesArr(1);

	GLsizei const* const INDICES_COUNTS_ARR = [&](void) -> const GLsizei* {
		static GLsizei counts_arr[MAX_UNIT_CELLS];
		for (int i = 0; i < MAX_UNIT_CELLS; ++i)
			counts_arr[i] = 4;
		return counts_arr;
	}();

	//create array of coordinates of all vertices
	GLfloat const* const VERTEX_ATTRIBS_ARR = [&](void) -> GLfloat* {
		static GLfloat verticesArr[2 * VERTICES_NUMBER];
		int i, j, k;

		for (j = 0; j < VERTICES_NUMBER_IN_A_COL; ++j) {
			for (i = 0; i < VERTICES_NUMBER_IN_A_ROW; ++i) {
				k = 2 * (i + j * VERTICES_NUMBER_IN_A_ROW);		//`i + j * VERTICES_NUMBER_IN_A_ROW` is the index of cell.
				verticesArr[k] = -1.0f - (1.0f - i) / HALF_VIEWPORT_WIDTH;
				verticesArr[k + 1] = 1.0f + (1.0f - j) / HALF_VIEWPORT_HEIGHT;
			}
		}
		return verticesArr;
	}();

	//print above vertex attribute array
	void printVertexAttribArray(void) {
		// The below code snippet is to monitor the elements of 'VERTEX_ATTRIBS_ARR' created above
		int k;
		std::cout << "\n\tVERTEX_ATTRIBS_ARR" << std::endl;
		for (int j = 0; j < VERTICES_NUMBER_IN_A_COL; ++j) {
			std::cout << "j = " << j << std::endl;
			for (int i = 0; i < VERTICES_NUMBER_IN_A_ROW; ++i) {
				k = 2 * (i + j * (VERTICES_NUMBER_IN_A_ROW));
				std::cout << "\ti = " << i
					<< "\tvertID = " << (VERTICES_NUMBER_IN_A_ROW)*j + i
					<< "\t\tv_" << k << " = " << VERTEX_ATTRIBS_ARR[k]
					<< "\t\tv_" << k + 1 << " = " << VERTEX_ATTRIBS_ARR[k + 1] << std::endl;
			}
		}
	}

	//create array of quartets of cell indices
	GLuint const* const CELL_INDICES_QUARTETS_ARR = [&](void) -> const GLuint* {
		GLuint* indicesArr = new GLuint[4 * MAX_UNIT_CELLS];
		int i;
		for (i = 0; i < MAX_UNIT_CELLS; ++i) { //`4` is the number of vertices of a square/cell
			indicesArr[4 * i] = i;
			indicesArr[4 * i + 1] = i + 1;
			indicesArr[4 * i + 2] = i + VERTICES_NUMBER_IN_A_ROW + 1;
			indicesArr[4 * i + 3] = i + VERTICES_NUMBER_IN_A_ROW;
		}

		//ensure the indices of 2 right vertices not connect to 2 left vertices when draw cells
		GLint tmp;
		for (i = 0; i < VERTICES_NUMBER_IN_A_COL; ++i) {
			tmp = VERTICES_NUMBER_IN_A_ROW * 4 * (i + 1) - 4;
			indicesArr[tmp] = 0;
			indicesArr[tmp + 1] = 0;
			indicesArr[tmp + 2] = 0;
			indicesArr[tmp + 3] = 0;
		}
		return indicesArr;
	}();

	//print above cell indices' quartets array
	void printCellIndicesQuartetsArray(void) {
		// The below code snippet is to monitor the elements of 'CELL_INDICES_QUARTETS_ARR' aka the 'indicesArr' created above
		std::cout << "\n\tCELL_INDICES_QUARTETS_ARR\n"
					   "\t-------------------------" << std::endl;
		for (int i = 0; i < MAX_UNIT_CELLS; ++i) {
			std::cout << "cellID = " << i
				<< "\ti_" << std::setw(3) << 4 * i << " = " << std::setw(3) << CELL_INDICES_QUARTETS_ARR[4 * i]
				<< "\ti_" << std::setw(3) << 4 * i + 1 << " = " << std::setw(3) << CELL_INDICES_QUARTETS_ARR[4 * i + 1]
				<< "\ti_" << std::setw(3) << 4 * i + 2 << " = " << std::setw(3) << CELL_INDICES_QUARTETS_ARR[4 * i + 2]
				<< "\ti_" << std::setw(3) << 4 * i + 3 << " = " << std::setw(3) << CELL_INDICES_QUARTETS_ARR[4 * i + 3] 
				<< std::endl;

		}
	}

	void printGameBoardOntoConsole(void) {
		int i, j;

		//go to line 1 and draw: 0, 1, 2, 3, 4, 5...
		system("cls");
		printf("\033[1;1H\n\033[1;%dH", MIN_WIDTH_OF_STRING + 2);
		for (i = 0; i < VERTICES_NUMBER_IN_A_ROW; ++i) {
			std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING)) << i;
		}

		//go to line 2 and draw the string: "_____________"...
		std::cout << '\n';
		for (i = 0; i < MIN_WIDTH_OF_STRING; ++i) std::cout << ' ';
		for (i = 0; i < VERTICES_NUMBER_IN_A_ROW * (MIN_WIDTH_OF_STRING); ++i) {
			std::cout << '-';
		}

		//go to line 3, 4, 5... and draw: 0|, 1|, 2|, 3|...
		std::cout << '\n';
		for (i = 0; i < VERTICES_NUMBER_IN_A_COL - 1; ++i) {
			std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING - 1)) << i << '|' << std::endl;
		}

		//go back to line 3, 4, 5... and draw board of cell stages (values: -2, -1, 0, 1, 2, 3 or H #$)
		int stateNum, cellIndex;
		for (j = 0; j < VERTICES_NUMBER_IN_A_COL - 1; ++j) {
			printf("\033[%d;%dH", j + 3, MIN_WIDTH_OF_STRING + 1);
			for (i = 0; i < VERTICES_NUMBER_IN_A_ROW; ++i) {
				stateNum = POSITION_STATES_ARR[VERTICES_NUMBER_IN_A_ROW * j + i];
				cellIndex = POSITION_STATES_WITH_CELL_INDICES[VERTICES_NUMBER_IN_A_ROW * j + i];

				switch (stateNum) {
				case -3:
					std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING)) << '#';
					break;
				case -2:
					std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING)) << 'X' << cellIndex;
					break;
				case -1:
					std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING)) << ' ';
					break;
				default:
					std::cout << std::setw(std::streamsize(MIN_WIDTH_OF_STRING)) << stateNum;
				}
			}
			std::cout << "\n\n\n\n";
		}
	}
}