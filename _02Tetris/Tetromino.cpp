#include "Tetromino.h"

namespace CommonDefs {
	
	template class Tetromino<4>;
	template Tetromino<4>::Tetromino(UnitCell*);
	template Tetromino<4>::Tetromino(UnitCell*, UnitCell*);
	template Tetromino<4>::Tetromino(UnitCell*, UnitCell*, UnitCell*);
	template Tetromino<4>::Tetromino(UnitCell*, UnitCell*, UnitCell*, UnitCell*);
	//template GLint Tetromino<4>::DeleteCellsPointer(void);

	template<> Tetromino<4>::Tetromino(GLuint _centerCellIndex, DefaultShape _shape) : Entity(4) {
		for (	; cells_number < max_cells; ++cells_number) {
			cell_pointers_arr[cells_number] = new UnitCell(_centerCellIndex + BASE_INDICES_OF_DEFAULTS[_shape][cells_number]);
		}
		return;
	};
}