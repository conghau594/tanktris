#include "Shader.h"
#include "VertexArray.h"
#include "CellsClub.h"
#include "Tank.h"

extern GLFWwindow* win;

extern CellsManager cells;
extern CellsClub* lines[VERTICES_NUMBER_IN_A_ROW];

extern Tetromino<4>* originalTetro;
extern MovableObject* tetroCoat;

extern GameState GAME_STATE;
extern EntityState TETRO_STATE;
extern EntityProperty TETRO_PROP;

namespace CommonDefs {
	GLint indicesOfFullLines[4];	//array of indices of the line that is full of cells in ascending order
	GLint minLineIndex = VERTICES_NUMBER_IN_A_ROW;

	void hangOn(double _Sec);
	void updateScreen(void);

	/* group of functions for handling the event when a cell lands on side */
	void putFullLineIndexToArr(GLint indexOfLine);				//put the index of line that is full of cells to `indicesOfFullLines[4]` array
	void tryToAddCellToLine(UnitCell* _Cell, GLint indexOfLine);
	void moveLinesDownAfterScoring(void);
	void handleCellLandOnEvent(void);

	/* group of function for handling the event when player presses a key*/
	void moveTetroOneStep(CompassDirection _Direction);
	void tryToRotateTetro(void);
	void speedUpTetro(void);
	void shootBullet(void);
	void keyPressCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _modes);

	//external function for supporting debug
	void printGameBoardOntoConsole(void);
}

namespace CommonDefs {
	//draw and update window's screen if any change
	void updateScreen(void) {
		cells.Draw();
		glfwSwapBuffers(win);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	//delete all cell's pointers in manager
	void deleteCellPointers(void) {
		UnitCell* const* deleted_cells = cells.GetCellPointers();
		GLuint cells_number = cells.GetCellsNumber();
		for (GLuint i = 0; i < cells_number; ++i) {
			delete deleted_cells[i];
		}

	}

	//wait a second
	void hangOn(double _Sec) {
		if (glfwWindowShouldClose(win)) return;
		if (GAME_STATE.game_over) return;

		double now = glfwGetTime();
		while (glfwGetTime() < now + _Sec) {
			if (GAME_STATE.paused) {
				_Sec -= (glfwGetTime() - now);
				while (GAME_STATE.paused) {
					glfwPollEvents();
					if (glfwWindowShouldClose(win)) return;
				}
			}
		}
		return;
	}

	/********** group of functions for handling the event when a cell lands on side **********/
	void handleCellLandOnEvent(void) {
		GLint indexOfLine = 0;
		GLuint i = 0;

		tetroCoat->DisableMoving();

		for (; i < tetroCoat->GetCellsNumber(); ++i)
			indicesOfFullLines[i] = -1;

		for (i = 0; i < tetroCoat->GetCellsNumber(); ++i) {
			indexOfLine = tetroCoat->GetCellPointers()[i]->GetIndex() % VERTICES_NUMBER_IN_A_ROW;
			if (indexOfLine < minLineIndex) minLineIndex = indexOfLine;

			if (lines[indexOfLine] == nullptr) {
				lines[indexOfLine] = new CellsClub(2 * HALF_VIEWPORT_HEIGHT);
			}
			tryToAddCellToLine(tetroCoat->GetCellPointers()[i], indexOfLine);
		}

		moveLinesDownAfterScoring();

		delete tetroCoat;
		tetroCoat = nullptr;
		if (TETRO_STATE.failed_to_fire) originalTetro = nullptr;
		return;
	}
	
	void putFullLineIndexToArr(GLint indexOfLine) {
		//store the indices of full-cell line in ascending order, 4 is the elements number of indicesOfFullLine[4]
		for (GLuint j = 0; j < tetroCoat->GetCellsNumber(); ++j) {
			if (indicesOfFullLines[j] == -1) {
				indicesOfFullLines[j] = indexOfLine;
				break;
			}
			if (indexOfLine > indicesOfFullLines[j]) continue;

			GLint tmVar;
			tmVar = indicesOfFullLines[j];
			indicesOfFullLines[j] = indexOfLine;
			indexOfLine = tmVar;
		}
		return;
	}

	void tryToAddCellToLine(UnitCell* _Cell, GLint indexOfLine) {
		//check if we have gotten score
		try {
			lines[indexOfLine]->Add(_Cell);
		}
		catch (UnitCell** cellPtrInLine) {
			//TETRO_STATE.speeded_up = false;

			for (GLint j = 0; j < 2 * HALF_VIEWPORT_HEIGHT; ++j) {
				cells.Remove(cellPtrInLine[j]);
				delete cellPtrInLine[j];

				//erase the removed cells
				updateScreen();
				hangOn(0.01);
			}

			delete lines[indexOfLine];
			lines[indexOfLine] = nullptr;

			putFullLineIndexToArr(indexOfLine);
			hangOn(0.05);
		}
		return;
	}

	void moveLinesDownAfterScoring(void) {
		//move remaining lines down if we got scored
		for (GLuint i = 0; i < tetroCoat->GetCellsNumber(); ++i) {
			if (indicesOfFullLines[i] == -1) break;
			if (lines[indicesOfFullLines[i] - 1] == nullptr) break;

			while (indicesOfFullLines[i] > minLineIndex) {
				if (lines[--indicesOfFullLines[i]] == nullptr) continue;
				CellsClub*& tmpLine = lines[indicesOfFullLines[i]];

				tmpLine->Step(CompassDirection::E);
				cells.UpdateOffsets(tmpLine->GetCellPointers(), tmpLine->GetCellsNumber());

				lines[indicesOfFullLines[i] + 1] = tmpLine;
				tmpLine = nullptr;
			}
			++minLineIndex;
			//draw the effect of dropping
			updateScreen();
			hangOn(0.075);
		}
		return;
	}

	/********** group of function for handling the event when player presses a key **********/
	void tryToRotateTetro(void) {
		bool jumped_for_rotating = false;
		CompassDirection jumpedDirection = CompassDirection::UNDEFINED_DIRECTION;
		GLuint oldCenterIndex = tetroCoat->GetCellPointers()[0]->GetIndex();

		while (1) {
			//try to rotate by any way
			try {
				tetroCoat->Rotate(*tetroCoat->GetCellPointers()[0], COUNTER_CLOCKWISE);
				cells.UpdateOffsets(tetroCoat->GetCellPointers(), tetroCoat->GetCellsNumber());
				updateScreen();
				return;
			}
			catch (GLint engagedIndex) {
				//compute the direction to jump
				if (!jumped_for_rotating) {
					GLint deltaQuotient = engagedIndex / VERTICES_NUMBER_IN_A_ROW - tetroCoat->GetCellPointers()[0]->GetIndex() / VERTICES_NUMBER_IN_A_ROW;
					jumped_for_rotating = true;

					if (deltaQuotient > 0)
						jumpedDirection = CompassDirection::N;
					else if (deltaQuotient < 0)
						jumpedDirection = CompassDirection::S;
					else if (engagedIndex < tetroCoat->GetCellPointers()[0]->GetIndex())
						jumpedDirection = CompassDirection::E;
					else { return; }
				}

				//try to jump
				try {
					moveTetroOneStep(jumpedDirection);
				}
				catch (GLint) {
					if (jumped_for_rotating) {
						tetroCoat->Teleport(oldCenterIndex);
						cells.UpdateOffsets(tetroCoat->GetCellPointers(), tetroCoat->GetCellsNumber());
						updateScreen();
					}
					return;
				}
			}
		}
	}

	inline void moveTetroOneStep(CompassDirection _Direction) {
		tetroCoat->Step(_Direction);
		cells.UpdateOffsets(tetroCoat->GetCellPointers(), tetroCoat->GetCellsNumber());
		cells.Draw();

		glfwSwapBuffers(win);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}

	void shootBullet(void) {
		Tank<BULLETS_NUMBER>* newTank = (Tank<BULLETS_NUMBER>*)(tetroCoat);
		if (newTank->GetRemainingBulletsNumber() == 0) {
			TETRO_STATE.fired = false;
			return;
		}
		TETRO_PROP.move_direction = newTank->GetFiringDirection();
		Tetromino<1>* bullet = nullptr;
		for (;;) {
			try {
				//try to shoot bullet
				bullet = newTank->Fire();
				cells.Add(bullet->GetCellPointers()[0]);
				updateScreen();

				if (TETRO_STATE.failed_to_fire) {
					speedUpTetro();
					TETRO_PROP.move_direction = CompassDirection(-TETRO_PROP.move_direction);
				}

				tetroCoat = bullet;
				return;
			}
			catch (GLint) {
				//if failed to shoot bullet, the tetro will be reflected 
				TETRO_STATE.failed_to_fire = true;
				TETRO_PROP.move_direction = CompassDirection(-TETRO_PROP.move_direction);

				try {
					originalTetro->Step(TETRO_PROP.move_direction);
					cells.UpdateOffsets(originalTetro->GetCellPointers(), originalTetro->GetCellsNumber());
					updateScreen();
				}
				catch (GLint) {
					GAME_STATE.game_over = true;
					GAME_STATE.paused = true;
					return;
				}
			}
		}
	}

	//cause the tetro or bullet speed up until they land on the side
	void speedUpTetro(void) {
		while (tetroCoat != nullptr) {
			try {
				tetroCoat->Step(TETRO_PROP.move_direction);
				cells.UpdateOffsets(tetroCoat->GetCellPointers(), tetroCoat->GetCellsNumber());
				updateScreen();

				hangOn(0.01);
			}
			catch (GLint) {
				handleCellLandOnEvent();
				return;
			}
		}
	}

	void keyPressCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _modes) {
		if (_action == GLFW_RELEASE) return;

		//press ENTER key when game is paused to quit game
		if (_key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(win, GLFW_TRUE);
		}

		if (GAME_STATE.game_over) {
			/*
			if (_key == GLFW_KEY_R)
				GAME_STATE.restarted = true;
			//*/
			return;
		}

		//handle pressing ESC key for pausing game or exit when game over
		if (_key == GLFW_KEY_ENTER) {
			GAME_STATE.paused = !GAME_STATE.paused;
			return;
		}


		if (GAME_STATE.paused) return;
		//press P key to print state of location onto console (and pause game)
		if (_key == GLFW_KEY_P) {
			system("cls");
			printGameBoardOntoConsole();
			GAME_STATE.paused = !GAME_STATE.paused;
			return;
		}

		if (tetroCoat == nullptr) return;
		//handle pressing the S or LEFT ARROW key for rotating tetromino
		if (_key == GLFW_KEY_LEFT || _key == GLFW_KEY_S) {
			tryToRotateTetro();
			return;
		}

		try {
			//handle pressing RIGHT ARROW (or F), UP ARROW (or E), DOWN ARROW (or D) for moving tetromino
			if (_key == GLFW_KEY_RIGHT || _key == GLFW_KEY_F) {
				moveTetroOneStep(CompassDirection::E);
				return;
			}
			if (_key == GLFW_KEY_DOWN || _key == GLFW_KEY_D) {
				moveTetroOneStep(CompassDirection::S);
				return;
			}
			if (_key == GLFW_KEY_UP || _key == GLFW_KEY_E) {
				moveTetroOneStep(CompassDirection::N);
				return;
			}
		}
		catch (GLint) {}

		//handle pressing SPACE key for doing ultimate
		if (_key == GLFW_KEY_SPACE) {
			if (TETRO_STATE.fired) return; 
			//check if the tetro is fireable then fire bullet
			if (TETRO_PROP.shape_type == DefaultShape::LETTER_Y) {
				TETRO_STATE.fired = true;
				shootBullet();
			}

			//cause the tetro/bullet speed up until they land on the side
			if (!GAME_STATE.game_over) speedUpTetro();
			return;
		}
	};
}