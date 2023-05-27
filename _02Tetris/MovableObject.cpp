#include "MovableObject.h"

namespace CommonDefs {

	//private:
	void MovableObject::change_position_states(GLint* cellOldIndices, GLint* cellNewIndices, GLint cells_number) {
		GLint* cellLocsInManager = new GLint[cells_number];
		GLint* oldLocStates = new GLint[cells_number];
		GLint i = 0;
		for (; i < cells_number; ++i) {
			cellLocsInManager[i] = POSITION_STATES_WITH_CELL_INDICES[cellOldIndices[i]];
			oldLocStates[i] = POSITION_STATES_ARR[cellOldIndices[i]];

			POSITION_STATES_ARR[cellOldIndices[i]] = PositionState::FREE;
			POSITION_STATES_WITH_CELL_INDICES[cellOldIndices[i]] = PositionState::FREE;
		}

		for (i = 0; i < cells_number; ++i){
			POSITION_STATES_ARR[cellNewIndices[i]] = oldLocStates[i];
			POSITION_STATES_WITH_CELL_INDICES[cellNewIndices[i]] = cellLocsInManager[i];
		}

		delete[] cellLocsInManager;
	}

	//public:
	void MovableObject::Step(CompassDirection _toWhere) { // step in one pace
		//if (disabled) return;
		
		GLuint i = 0;
		GLint newIndex = 0;

		for (; i < cells_number; ++i) {
			newIndex = _toWhere + cell_pointers_arr[i]->cell_index;
			if (POSITION_STATES_ARR[newIndex] == PositionState::FORBIDDEN || POSITION_STATES_ARR[newIndex] == PositionState::ENGAGED)
				throw newIndex;
		}

		GLint* cellNewIndices = new GLint[cells_number];
		GLint* cellOldIndices = new GLint[cells_number];
		for (i = 0; i < cells_number; ++i) {
			cellNewIndices[i] = (cell_pointers_arr[i]->cell_index += _toWhere);
			cellOldIndices[i] = cellNewIndices[i] - _toWhere;
		}

		change_position_states(cellOldIndices, cellNewIndices, cells_number);
		delete[] cellOldIndices;
		delete[] cellNewIndices;
		return;
	}

	/*
	inline GLint get_index_after_rotating(const GLfloat& _CentralXCoord, const GLfloat& _CentralYCoord, const GLint& _RotatedCellIndex, const RotationDirection& _Direction) {
		GLfloat oldX = -1.0f - (1.0f - GLfloat(_RotatedCellIndex % VERTICES_NUMBER_IN_A_ROW)) / HALF_VIEWPORT_WIDTH;
		GLfloat oldY = +1.0f + (1.0f - GLfloat(_RotatedCellIndex / VERTICES_NUMBER_IN_A_ROW)) / HALF_VIEWPORT_WIDTH;

		GLfloat newX = _CentralXCoord - _Direction / XUNIT_OVER_YUNIT_RATIO * (oldY - _CentralYCoord);
		GLfloat newY = _CentralYCoord + _Direction * XUNIT_OVER_YUNIT_RATIO * (oldX - _CentralXCoord);

		return GLint(round((1 + newX) * HALF_VIEWPORT_WIDTH + 1)) + GLint(round((1 - newY) * HALF_VIEWPORT_HEIGHT + 1)) * VERTICES_NUMBER_IN_A_ROW;
	}
	//*/

	void MovableObject::Rotate(const UnitCell& _CentralCell, RotationDirection _Direction) {
		//if (disabled) return;

		GLfloat const x0 = VERTEX_ATTRIBS_ARR[2 * _CentralCell.cell_index];
		GLfloat const y0 = VERTEX_ATTRIBS_ARR[2 * _CentralCell.cell_index + 1];

		GLint* cellNewIndices = new GLint[cells_number];
		GLint* cellOldIndices = new GLint[cells_number];

		GLfloat newX, newY;
		GLuint i = 0;
		GLint newIndex = 0;
		for (; i < cells_number; ++i) {
			cellOldIndices[i] = cell_pointers_arr[i]->cell_index;
			newX = x0 - _Direction / XUNIT_OVER_YUNIT_RATIO * (VERTEX_ATTRIBS_ARR[2 * (cellOldIndices[i]) + 1] - y0);
			newY = y0 + _Direction * XUNIT_OVER_YUNIT_RATIO * (VERTEX_ATTRIBS_ARR[2 * (cellOldIndices[i])] - x0);
			
			newIndex = 	GLint(round((1 + newX) * HALF_VIEWPORT_WIDTH + 1))
					  + GLint(round((1 - newY) * HALF_VIEWPORT_HEIGHT + 1)) * VERTICES_NUMBER_IN_A_ROW;

			//throw exception for invalid new location
			if (POSITION_STATES_ARR[newIndex] == PositionState::ENGAGED || POSITION_STATES_ARR[newIndex] == PositionState::FORBIDDEN) {
				delete[] cellOldIndices;
				delete[] cellNewIndices;
				throw newIndex;
			}
			
			cellNewIndices[i] = newIndex;
		}

		for (i = 0; i < cells_number; ++i)
			cell_pointers_arr[i]->cell_index = cellNewIndices[i];

		change_position_states(cellOldIndices, cellNewIndices, cells_number);
		delete[] cellOldIndices;
		delete[] cellNewIndices;
		return;
	}

	void MovableObject::Teleport(GLuint _location) {
		//if (disabled) return;
		
		GLint distance = _location - cell_pointers_arr[0]->cell_index;
		GLuint i = 0;
		GLint* cellNewIndices = new GLint[cells_number];
		GLint newIndex;

		for (; i < cells_number; ++i) {
			newIndex = distance + cell_pointers_arr[i]->cell_index;
			if (POSITION_STATES_ARR[newIndex] == PositionState::FORBIDDEN || POSITION_STATES_ARR[newIndex] == PositionState::ENGAGED) {
				delete[] cellNewIndices;
				throw newIndex;
			}
			cellNewIndices[i] = newIndex;
		}

		GLint* cellOldIndices = new GLint[cells_number];

		for (i = 0; i < cells_number; ++i) {
			cellNewIndices[i] = (cell_pointers_arr[i]->cell_index += distance);
			cellOldIndices[i] = cellNewIndices[i] - distance;
		}

		change_position_states(cellOldIndices, cellNewIndices, cells_number);
		delete[] cellOldIndices;
		delete[] cellNewIndices;
		return;
	}

	void MovableObject::DisableMoving(void) {
		//disabled = true;
		for (GLuint i = 0; i < cells_number; ++i) {
			POSITION_STATES_ARR[cell_pointers_arr[i]->cell_index] = PositionState::ENGAGED;
		}
	}
}