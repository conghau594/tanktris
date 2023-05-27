#ifndef TANK_H
#define TANK_H

#include "Tetromino.h"

namespace CommonDefs{

	template<GLuint MAX_BULLETS> class Tank : public Tetromino<4> {
	public:
		Tank(GLuint _CenterCellIndex) :
			used_bullets_number(0),
			Entity(4),
			Tetromino<4>(_CenterCellIndex, DefaultShape::LETTER_Y) 
		{ return; }

		inline GLuint GetRemainingBulletsNumber(void) { return MAX_BULLETS - used_bullets_number; }

		inline Tetromino<1>* Fire(void) {
			if (used_bullets_number == MAX_BULLETS)
				return nullptr;

			GLint bulletIndex = 2 * cell_pointers_arr[3]->GetIndex() - cell_pointers_arr[0]->GetIndex();
			if (POSITION_STATES_ARR[bulletIndex] == PositionState::FORBIDDEN || POSITION_STATES_ARR[bulletIndex] == PositionState::ENGAGED)
				throw bulletIndex;
			
			++used_bullets_number;
			UnitCell* newCell = new UnitCell(bulletIndex);
			return new Tetromino<1>(newCell);
		}

		inline CompassDirection GetFiringDirection(void) {
			GLint deltaRowCoords = cell_pointers_arr[3]->GetIndex() / VERTICES_NUMBER_IN_A_ROW - cell_pointers_arr[0]->GetIndex() / VERTICES_NUMBER_IN_A_ROW;
			
			if (deltaRowCoords > 0) 
				return CompassDirection::S;
			else if (deltaRowCoords < 0) 
				return CompassDirection::N;
			else if (cell_pointers_arr[3]->GetIndex() > cell_pointers_arr[0]->GetIndex()) 
				return CompassDirection::E;
			else 
				return CompassDirection::W;
		}
	private:
		GLuint used_bullets_number;
	};
}

#endif