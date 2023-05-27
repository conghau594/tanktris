#include "CellsManager.h"

/* inline */
/*
- OpenGLMode::CellsManager(GLuint _maxCells)
- ~OpenGLMode::CellsManager() = 0

- CellsManager(GLuint _maxCells)
- void Draw(void)
*/

namespace OpenGLMode {
	CommonDefs::BooleanMask CellsManager::is_created;

	void CellsManager::UpdateOffsets(UnitCell* const* cellPointers, GLuint _NumberOfCells) {
		if (cellPointers == nullptr) return;
		GLint cellIndex = 0;
		for (GLuint i = 0; i < _NumberOfCells; ++i) {
			cellIndex = cellPointers[i]->GetIndex();
			offsets_arr_of_cells[POSITION_STATES_WITH_CELL_INDICES[cellIndex]] = (void*)(sizeof(GLuint) * 4 * cellIndex); //VERTEX_INDICES_OFFSETS_ARR[cellIndex];
		}
		return;
	}
	
	//*
	void CellsManager::Add(CommonDefs::UnitCell* _cell) {
		GLint& positionState = POSITION_STATES_WITH_CELL_INDICES[_cell->GetIndex()];
		if (positionState != PositionState::FREE)
 			throw positionState;

		POSITION_STATES_ARR[_cell->GetIndex()] = cells_number;
		positionState = cells_number;
		
		cell_pointers_arr[cells_number] = _cell;
		offsets_arr_of_cells[cells_number] = (void*)(sizeof(GLuint) * 4 * _cell->GetIndex()); // VERTEX_INDICES_OFFSETS_ARR[_cell->GetIndex()];

		if (++cells_number == max_cells) 
			throw cell_pointers_arr;

		return;
	}
	//*/

	void CellsManager::Remove(CommonDefs::UnitCell* _cell) {
		GLint& cellLocationInThis = POSITION_STATES_WITH_CELL_INDICES[_cell->GetIndex()];
		--cells_number;

		offsets_arr_of_cells[cellLocationInThis] = offsets_arr_of_cells[cells_number];
		offsets_arr_of_cells[cells_number] = nullptr;

		GLuint lastCellIndex = cell_pointers_arr[cells_number]->GetIndex();

		cell_pointers_arr[cellLocationInThis] = cell_pointers_arr[cells_number];
		cell_pointers_arr[cells_number] = nullptr;

		POSITION_STATES_ARR[_cell->GetIndex()] = CommonDefs::PositionState::FREE;

		POSITION_STATES_WITH_CELL_INDICES[lastCellIndex] = cellLocationInThis;
		cellLocationInThis = CommonDefs::PositionState::FREE;


		return;
	}

	/*
	void CellsManager::full_store_callback(Collector* _thisPtr) {
		throw static_cast<OpenGLMode::CellsManager*>(_thisPtr)->max_cells;
		return;//in future: extend this data array and copy present data to new extended array
	}
	*/
}