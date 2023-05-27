#ifndef ENTITY_H
#define ENTITY_H

#include "UnitCell.h"
#include "const_expr.h"

/* abstract class definition */
namespace CommonDefs {

	class Entity {
	protected:	/* property */
		GLuint max_cells;
		GLuint cells_number;
		UnitCell** cell_pointers_arr;

	public:		/* method */

		//contructors and destructor
		Entity() = default;
		inline explicit Entity(GLuint _maxCells) :
			cell_pointers_arr( new UnitCell*[_maxCells] {nullptr} ),
			cells_number(0),
			max_cells(_maxCells)
		{ return; }

		inline virtual ~Entity() = 0 { 
			delete[] cell_pointers_arr; 
			return;
		}

		inline UnitCell* const* const& GetCellPointers(void) { return cell_pointers_arr; }
		inline GLuint const& GetCellsNumber(void) { return cells_number; }

		//deleled:
		Entity(const Entity&) = delete;
		Entity(Entity&&) = delete;
		Entity& operator=(const Entity&) = delete;
	};
}


#endif