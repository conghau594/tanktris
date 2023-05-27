#ifndef CELLS_CLUB_H
#define CELLS_CLUB_H

#include "MovableObject.h"

namespace CommonDefs {

	/* class definition */
	class CellsClub : public Collector, public MovableObject {
	public:
		//contructor
		inline explicit CellsClub(GLuint _maxCells) : Entity(_maxCells)
		{
			return;
		}

	private:

		CellsClub(const CellsClub&) = delete;
		CellsClub(CellsClub&&) = delete;
		CellsClub& operator=(const CellsClub&) = delete;
	};
}
#endif