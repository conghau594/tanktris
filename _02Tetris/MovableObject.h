#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include "CellsManager.h"

namespace CommonDefs {

	class MovableObject : public virtual Entity {
	private:	/* property */

	public:		/* method */
		//static CellsManager* ExManagerPtr;	// "External Manager Pointer" for managing all cells
		//contructor
		MovableObject() = default;
		inline virtual ~MovableObject() = 0 { return; }

		void Step(CompassDirection _toWhere);
		void Rotate(const UnitCell& _centralCell, RotationDirection _direction);
		void DisableMoving(void);

		// bring the cell[0] to _location and other cells following it
		void Teleport(GLuint _location);

		//inline bool CheckIfDisabled(void) { return disabled; }
	private:
		static void change_position_states(GLint* cellOldIndices, GLint* cellNewIndices, GLint cells_number);
		/*
		inline static void cell_move_callback(GLint _cellOldIndex, GLint _cellNewIndex) {
			if (ExManagerPtr != nullptr)
				ExManagerPtr->offsets_arr_of_cells[POSITION_STATES_ARR[_cellOldIndex]] = VERTEX_INDICES_OFFSETS_ARR[_cellNewIndex];
			return;
		}
		//*/

		//deleted:
		MovableObject(const MovableObject&) = delete;
		MovableObject(MovableObject&&) = delete;
		MovableObject& operator=(const MovableObject&) = delete;
	};
}

#endif
