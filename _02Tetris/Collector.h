#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "Entity.h"

//no longer in use
namespace CommonDefs {

	class Collector : public virtual Entity {
	protected:	//property
		static void (*full_of_cells_callback_ptr)(Collector*);		//pointer to a static or outer function

	public:	//method
		//constructor and destructor
		Collector() = default;
		virtual ~Collector() = 0 { return; }// = default;

		void printCellsListOntoConsole(void) {
			//*
			std::cout << '\n' << "cells number = " << cells_number << '\n';
			for (GLuint i = 0; i < cells_number; ++i) {
				std::cout << "i = " << i << "\tcell_id = " << cell_pointers_arr[i]->GetIndex() << std::endl;
			}
			//*/
		}
		virtual void Remove(UnitCell* _cellPtr);
		inline virtual void Add(UnitCell* _cellPtr);		
		
		//virtual void RemoveMore(UnitCell** _cellPtrArr);
		//inline virtual void AddMore(UnitCell** _cellPtrArr);
	protected:

		//deleted:
		Collector(const Collector&) = delete;
		Collector(Collector&&) = delete;
		Collector& operator= (const Collector&) = delete;
	};


	//public method
	void Collector::Add(UnitCell* _cell) {
			cell_pointers_arr[cells_number] = _cell;
			++cells_number;
			if (cells_number == max_cells)
					throw cell_pointers_arr;	//call the callback full_of_cells
	}
	/*
	void AddMore(UnitCell** _cellPtrArr) {
		//memcpy()
	}
	//*/
}

#ifdef TEST

class Collector2 : public virtual Entity2 {
protected:	//property
	void (*full_of_cells_cbptr)(Collector2*);		//pointer to a static or outer function
	void (Collector2::* cell_add_cbptr)(CellMask);	//pointer to a method of this or of a class derived from this
	void (Collector2::* cell_remove_cbptr)(CellMask);	//pointer to a method of this or of a class derived from this

public:	//method
	//constructor and destructor
	explicit Collector2() :
		full_of_cells_cbptr(nullptr),
		cell_add_cbptr(nullptr),
		cell_remove_cbptr(nullptr)
	{
		return;
	}

	virtual ~Collector2() = 0 { return; }

	//function template:
	template <typename... Ts> void Add(UnitCell& _first, Ts&... _others);
	template <typename... Ts> void Remove(UnitCell& _first, Ts&... _others);

	void printCellsListOntoConsole(void) {
		//*
		std::cout << '\n' << "cells number = " << cells_number << '\n';
		for (GLuint i = 0; i < cells_number; ++i) {
			std::cout << "i = " << i << "\tcell_id = " << mask_pointers_arr[i]->CellIndex << std::endl;
		}
		//*/
	}

private:
	//just for stopping recursion of vardiadic template
	inline void Add(void) { return; }
	inline void Remove(void) { return; }

	//deleted:
	Collector2(const Collector2&) = delete;
	Collector2(Collector2&&) = delete;
	Collector2& operator= (const Collector2&) = delete;
};

/*
//temlate definition
template <typename... Ts>
void Collector2::Add(UnitCell& _first, Ts&... _others) {


	if (POSITION_STATES_ARR[_first.cell_index] == PositionState::FREE) {
		if (cells_number < max_cells) {
			(this->*cell_add_cbptr)(_first);			//call the callback cell_add

			cell_pointers_arr[cells_number] = &_first;
			if (++cells_number == max_cells) full_of_cells_cbptr(this);	//call the callback full_of_cells
		}
	}
	Add(_others...);
	return;
}

template <typename... Ts>
void Collector2::Remove(UnitCell& _first, Ts&... _others) {
	GLint& cellLocationInThis = POSITION_STATES_ARR[_first.cell_index];

	if (cellLocationInThis != PositionState::FORBIDDEN &&
		cellLocationInThis != PositionState::FREE)
	{
		--cells_number;
		(this->*cell_remove_cbptr)(_first);			//call the callback cell_remove

		UnitCell* lastCellPtrInThis = cell_pointers_arr[cells_number];

		POSITION_STATES_ARR[lastCellPtrInThis->cell_index] = cellLocationInThis;
		cell_pointers_arr[cellLocationInThis] = lastCellPtrInThis;

		cellLocationInThis = PositionState::FREE;
		cell_pointers_arr[cells_number] = nullptr;
	}
	Remove(_others...);
	return;
}

//*/

extern template void Collector2::Remove<>(UnitCell&);
extern template void Collector2::Remove<UnitCell>(UnitCell&, UnitCell&);
extern template void Collector2::Remove<UnitCell>(UnitCell&, UnitCell&, UnitCell&);
extern template void Collector2::Remove<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&);
extern template void Collector2::Remove<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&, UnitCell&);

extern template void Collector2::Add<>(UnitCell&);
extern template void Collector2::Add<UnitCell>(UnitCell&, UnitCell&);
extern template void Collector2::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&);
extern template void Collector2::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&);
extern template void Collector2::Add<UnitCell>(UnitCell&, UnitCell&, UnitCell&, UnitCell&, UnitCell&);

#endif
#endif
