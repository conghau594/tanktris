#ifndef TETROMINO_H
#define TETROMINO_H

#include "MovableObject.h"

namespace CommonDefs {

	template <GLuint CELLS_NUMBER> class Tetromino : public MovableObject {
	public:
		//contructor template and destructor
		template <typename... Ts> Tetromino(UnitCell* _lastAdd, Ts*... _others);
		
		//able to use only if the case is Tetromino<4>
		Tetromino(GLuint _centerCellIndex, DefaultShape _shape);

		inline ~Tetromino() = default;
	private:
		//just for finishing the variadic contructor template
		inline Tetromino() : Entity(CELLS_NUMBER) { return; }		
	};


	//template definition
	template <GLuint CELLS_NUMBER> 
	template<typename... Ts> 
	Tetromino<CELLS_NUMBER>::Tetromino(UnitCell* _lastAdd, Ts*... _others) : Tetromino<CELLS_NUMBER>::Tetromino(_others...) {
		if (cells_number < max_cells) {
			cell_pointers_arr[cells_number] = _lastAdd;
			++cells_number;
		}
		return;
	}

	/*
	template<GLuint CELLS_NUMBER>
	void Tetromino<CELLS_NUMBER>::add_cell_to_manager(UnitCell& _cell) {
		if (ExManagerPtr != nullptr) {
			GLuint& cellsNumInManager = ExManagerPtr->cells_number;

			if (cellsNumInManager < ExManagerPtr->max_cells) {
				(ExManagerPtr->*(ExManagerPtr->cell_add_cbptr_2))(_cell);			//call the callback cell_add
				ExManagerPtr->cell_pointers_arr[cellsNumInManager] = &_cell;

				if (++cellsNumInManager == ExManagerPtr->max_cells)
					ExManagerPtr->full_of_cells_callback_ptr(ExManagerPtr);	//call the callback full_of_cells
			}
		}
	}
	//*/

	/*
	template<GLuint CELLS_NUMBER> 
	GLint Tetromino<CELLS_NUMBER>::DeleteCellsPointer(void) {
		try {
			for (int i = 0; i < MAX_UNIT_CELLS; ++i) 
				delete cell_pointers_arr[i];
		}
		catch (...) {
			return -1;
		}
		return 0;
	}
	//*/
	
	extern template class Tetromino<4>;
	extern template Tetromino<4>::Tetromino(UnitCell*);
	extern template Tetromino<4>::Tetromino(UnitCell*, UnitCell*);
	extern template Tetromino<4>::Tetromino(UnitCell*, UnitCell*, UnitCell*);
	extern template Tetromino<4>::Tetromino(UnitCell*, UnitCell*, UnitCell*, UnitCell*);
	extern template Tetromino<4>::Tetromino(GLuint, DefaultShape);
	//extern template GLint Tetromino<4>::DeleteCellsPointer(void);


}
#endif