#include "Collector.h"

namespace CommonDefs {
	//explicitly instatiate template function
	void Collector::Remove(UnitCell* _cellPtr) {
		for (GLuint i = 0; i < cells_number; ++i) {
			if (_cellPtr == cell_pointers_arr[i]) {
				--cells_number;
				cell_pointers_arr[i] = cell_pointers_arr[cells_number];
				cell_pointers_arr[cells_number] = nullptr;
				return;
			}
		}
	}

	void (*Collector::full_of_cells_callback_ptr)(Collector*) = nullptr;
	/*
	template void Collector::Add<UnitCell>(UnitCell&, UnitCell&);
	template void Collector::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&);
	template void Collector::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&);
	template void Collector::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&, UnitCell&);
	//*/

	//monitor function
}