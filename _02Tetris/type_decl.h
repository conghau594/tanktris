#ifndef CLASS_DECL_H
#define CLASS_DECL_H

#include "const_expr.h"

/********** BASE CLASS **********/
namespace OpenGLMode {
	class Buffer;
	class CellsManager;
	class Shader;			//and class Shader::Program;
	class VertexArray;
}

//same as OpenGLMode
namespace ConsoleMode {
	class Buffer;
	class CellsManager;
	class Shader;			//and class Shader::Program;
	class VertexArray;
}


namespace CommonDefs {
	//common class that are used for any mode	
	class CellsClub;
	class Collector;
	class Entity;
	class Generator;
	class MovableObject;
	template <GLuint> class Tank;
	template <GLuint> class Tetromino;	//	extern template class Tetromino<4>;
	class UnitCell;

	using OpenGLMode::CellsManager;

	//enum definition
	enum PositionState { FORBIDDEN = -3, ENGAGED = -2, FREE = -1 };
	enum RotationDirection { CLOCKWISE = -1, COUNTER_CLOCKWISE = 1 };

	enum DefaultShape { UNDEFINED_SHAPE = -2, LETTER_I = 0, LETTER_L, LETTER_J, LETTER_O, LETTER_S, LETTER_Z, LETTER_T, LETTER_Y };
	enum CompassDirection {	//the differences of index of 8 around cells to one cell
		UNDEFINED_DIRECTION = -2,
		S = VERTICES_NUMBER_IN_A_ROW,		//of northern direction
		N = -S,								//of southern direction
		E = 1,								//of eastern direction
		W = -E,								//of western direction
		NE = N + E,			//of noth eastern direction
		NW = N + W,			//of north western direction
		SE = S + E,			//of south eastern direction
		SW = S + W			//of south western direction
	};
}

/********** OTHER CLASS **********/
namespace CommonDefs {
	//this class is made to design a singleton class (CellsManager) but it is not important
	class BooleanMask {
	private:
		bool value;
	public:
		BooleanMask() : value(false) { return; }

		operator bool(void) const { return value; }
		void operator!(void) {
			value = !value;
			return;
		}
	};
}

/********** USER DEFINED TYPE JUST FOR MAIN() **********/
namespace CommonDefs {

	//at a time, there is one instance of tetromino created, so 2 below classes will be commomly used for them...
	struct EntityState {
		//bool speeded_up;				//check if the current tetromino has already speeded up or not
		bool fired;						//check if the current tetromino has already fired or not
		bool failed_to_fire;				//check if the current tetromino has fired bullet to forbidden or engaged location
	};

	struct EntityProperty {
		CompassDirection move_direction;//move direction of entity, default is northern direction,...
										//...but if fireable tetromino, it can be change for the bullets entity.
		DefaultShape shape_type;		//the current tetromino are what type
	};

	//property for handling state of the game
	struct GameState {
		double speed;		//just for changing speed of game
		bool paused;		//check if the game is paused or not
		bool game_over;		//check if the game is over or not
		bool restarted;		//check if the game is restarted or not
	};
}

/********** NO LONGER IN USE -> trash types **********/
template<typename T, GLuint dim> struct Coordinates { T x[dim]; };
template<typename T> struct Coordinates<T, 2> { T x, y; };
template<typename T> struct Coordinates<T, 3> { T x, y, z; };

struct Count {
	//property:
	Count* next;
	GLuint value;
		
	//contructor
	Count(Count* _nextCountPtr, GLuint _val) :
		next(_nextCountPtr),
		value(_val)
	{ return; }
};

class SmartCount {
private://property
	Count* base_count_ptr;
	Count* head_count_ptr;
	GLuint used_value;

public://method
	SmartCount() :
		base_count_ptr(new Count(nullptr, 0)),
		used_value(0)
	{
		head_count_ptr = base_count_ptr;
		return;
	}

	void ReuseValue(GLuint _newVal) {
		if (_newVal <= base_count_ptr->value) {
			Count* newHead = new Count(head_count_ptr, _newVal);
			head_count_ptr = newHead;
			used_value = _newVal;
		}
		return;
	}

	operator GLuint(void) {
		GLuint tmp = used_value;
		operator++();
		return tmp;
	}

private://method
	void operator++(void) {
		if (head_count_ptr->next == nullptr)
			used_value = ++(base_count_ptr->value);
		else {
			Count* oldHead = head_count_ptr;
			head_count_ptr = head_count_ptr->next;
			used_value = head_count_ptr->value;

			delete oldHead;
		}
	}
};

#endif
