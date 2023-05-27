#ifndef UNIT_CELL_H
#define UNIT_CELL_H

#include "common_lib.h"
#include "testing.h"

/* class definition */
namespace CommonDefs {
	class UnitCell {
	//friend:
		//friend class CellMask;
		friend class Collector;
		friend class Generator;
		friend class MovableObject;
	
	private:
		GLint cell_index;	/*	The cell's ID is the index of quartet of cell's vertex indices in array 'CELL_INDICES_QUARTETS_ARR'.
								They are given below:/*
							/*
							Row	 0|  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18
							Row	 1| 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37
							Row	 2| 38 39 40...                                         #  #
							Row	 3|  #                                                  #  #
							Row	 4|  #                                                  #  #
							Row	 5|  #								                    #  #
							Row	 6|  #                                                  #  #
							Row	 7|  #                                                  #  #
							Row	 8|  #                                                  #  #
							Row	 9|  #                                                  #  #
							Row	10|  #                                                  #  #
							Row	11|  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
							*/

	public:
		//the unique contructor
		inline explicit UnitCell(GLuint _index)
			: cell_index(_index)
		{ return; }

		//public method
		inline GLint GetIndex(void) const { return cell_index; }

		//delete:
		UnitCell(UnitCell&&) = delete;
	};
}

#endif