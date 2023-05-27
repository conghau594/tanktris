#ifndef CELLS_MANAGER_H
#define CELLS_MANAGER_H

#include "Collector.h"
#include "type_decl.h"

/* class definition */
namespace OpenGLMode {
	class CellsManager : public CommonDefs::Collector {
	//friend:
		friend class CommonDefs::MovableObject;

		static CommonDefs::BooleanMask is_created;
		void const** offsets_arr_of_cells;	// the offsets of quartet of cell vertex indices...
											// ...that were stored in 'CELL_INDICES_QUARTETS_ARR' for drawing the cell by glMultiDrawElements
	public:
		//the unique contructor and destructor
		inline explicit OpenGLMode::CellsManager(GLuint _maxCells)
			: CommonDefs::Entity(_maxCells),
			offsets_arr_of_cells(new void const* [_maxCells] {nullptr})
		{
			if (is_created == true) throw "Fail to create more than one of this";
			!is_created;
			return;
		}

		inline ~CellsManager() { delete[] offsets_arr_of_cells; }

		//public method
		inline void Draw(void) {
			glMultiDrawElements(GL_QUADS, INDICES_COUNTS_ARR, GL_UNSIGNED_INT, offsets_arr_of_cells, cells_number);
			return;
		}

		void UpdateOffsets(UnitCell* const* cellPointers, GLuint _NumberOfCells);

		
		void Add(CommonDefs::UnitCell*);
		void Remove(CommonDefs::UnitCell*);

	private:
		
		//delete:
		CellsManager(const CellsManager&) = delete;
		CellsManager(CellsManager&&) = delete;
		CellsManager& operator= (const CellsManager&) = delete;
	};

}


namespace ConsoleMode {
	class CellsManager : public CommonDefs::Collector {
	public:
		inline CellsManager(GLuint _maxCells) : CommonDefs::Entity(_maxCells) { return; }
		inline void Draw(void);
	};
}

#endif
