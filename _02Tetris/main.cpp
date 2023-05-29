#include "Shader_Program.h"
#include "VertexArray.h"
#include "CellsClub.h"
#include "Tank.h"

namespace CommonDefs {
	//function from main_supporter.cpp
	//void hangOn(double _Sec);
	void deleteCellPointers(void);
	void keyPressCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _modes);
	void updateScreen(void);
	void handleCellLandOnEvent(void);

	//function from data_supporter.cpp
	const GLuint* createCellIndicesArr(void);
	void printGameBoardOntoConsole();
}

GLFWwindow* win;							//the window which performs the game

CellsManager cells(MAX_UNIT_CELLS);			//all cells would be stored into this
CellsClub* lines[VERTICES_NUMBER_IN_A_ROW]{ nullptr };	//array of the cell collections,...
															//...each of them is made of the cells when they form a column

Tetromino<4>* originalTetro = nullptr;		//the original tetromino. It plays a poll if the tetro can fire bullet.
MovableObject* tetroCoat = nullptr;			//use to assign to pointers of any movable object such as... 
											//...a Tetromino<4>, Bullet (Tetromino<1>) or even a Line (CellsClub)

EntityState TETRO_STATE{ false };
EntityProperty TETRO_PROP{ CompassDirection::UNDEFINED_DIRECTION, DefaultShape::UNDEFINED_SHAPE };
GameState GAME_STATE{ 0.75, false, false };

//BOOL removeConsole = ShowWindow(GetConsoleWindow(), SW_HIDE);

#ifndef TEST
int WinMain(
	HINSTANCE   hInstance,
	HINSTANCE   hPrevInstance,
	LPSTR       lpCmdLine,
	int         nCmdShow
){

	if (!glfwInit()) {
		std::cerr << "ERROR!... Failed to initialize GLFW library\n";
		exit(EXIT_FAILURE);
	}

	const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris  |  OpenGL  |  Cong Hau", nullptr, nullptr);

	if (!win) {
		std::cerr << "ERROR!... Failed to create GLFW window\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(win, (videoMode->width - WINDOW_WIDTH) / 2, (videoMode->height - WINDOW_HEIGHT) / 2);
	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "ERROR!... Failed to load GLAD library\n";
		glfwDestroyWindow(win);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//glViewport(VIEWPORT_X_START, VIEWPORT_Y_START, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	glfwSetWindowSizeLimits(win, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);

	Shader::Program prog;
	prog.AttachShaders(
		Shader(GL_VERTEX_SHADER, "VertexShader.glsl"),
		Shader(GL_FRAGMENT_SHADER, "FragmentShader.glsl"));
	prog.Use();

	VertexArray VAO;
	Buffer VBO(GL_ARRAY_BUFFER), EBO(GL_ELEMENT_ARRAY_BUFFER);

	VAO.Bind();
	VBO.SetData(sizeof(GLfloat) * 2 * VERTICES_NUMBER, VERTEX_ATTRIBS_ARR, GL_STATIC_DRAW);
	{
		EBO.SetData(GLsizeiptr(4 * (MAX_UNIT_CELLS + VERTICES_NUMBER_IN_A_COL)) * sizeof(GLuint), CELL_INDICES_QUARTETS_ARR, GL_STATIC_DRAW);
		delete[] CELL_INDICES_QUARTETS_ARR;
	}
	VAO.SetVertexAttribute(VBO, 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0); // `2`s are the number of components of vertex attribute
	VAO.EnableVertexAttribute(VAO, 0);

	glfwSetKeyCallback(win, keyPressCallback);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	GLuint i = 0, j = 0;
	constexpr GLuint DEBUT_INDEX = HALF_VIEWPORT_HEIGHT * VERTICES_NUMBER_IN_A_ROW + 2;

//MAIN_PLAY:
	double now = 0.0;
	while (!GAME_STATE.game_over && !glfwWindowShouldClose(win)) {
		 srand(static_cast<unsigned>(time(nullptr)));

		 TETRO_PROP.shape_type =  DefaultShape(rand() % 8);

		 if (TETRO_PROP.shape_type == DefaultShape::LETTER_Y)
			 originalTetro = new Tank<BULLETS_NUMBER>(DEBUT_INDEX);
		 else
			 originalTetro = new Tetromino<4>(DEBUT_INDEX, TETRO_PROP.shape_type);

		 tetroCoat = originalTetro;

		 TETRO_PROP.move_direction = CompassDirection::E;
		 TETRO_STATE.fired = false;
		 TETRO_STATE.failed_to_fire = false;
		 for (i = 0; i < tetroCoat->GetCellsNumber(); ++i) {
			 try {
				 cells.Add(tetroCoat->GetCellPointers()[i]);
				 cells.UpdateOffsets(tetroCoat->GetCellPointers() + i, 1);
			 }
			 catch (GLint) {
				 GAME_STATE.game_over = true;
			 }

		 }

		 updateScreen();
		 if (GAME_STATE.game_over) {
			 GAME_STATE.paused = true;
			 delete originalTetro;
			 break;
		 }

		 
		 while (originalTetro != nullptr) {

			 if (!TETRO_STATE.fired) {
				 now = glfwGetTime();
			 }
			 else {
				 tetroCoat = originalTetro;
				 
				 TETRO_PROP.move_direction = CompassDirection::E;
				 TETRO_STATE.fired = false;
			 }

			 //TETRO_STATE.speeded_up = false;

			 //main loop
			 while ( (glfwGetTime() < GAME_STATE.speed * BASE_SPEED + now) 
					&& !GAME_STATE.game_over 
					&& !glfwWindowShouldClose(win)) 
			 {
				 glfwWaitEventsTimeout(GAME_STATE.speed * BASE_SPEED + now - glfwGetTime());		//this function must be excuted before updating offsets arr				 
				 updateScreen();
				 if (tetroCoat == nullptr) break;
			 }
			 
			 if (TETRO_STATE.fired) continue;
			  
			 if (tetroCoat == nullptr || GAME_STATE.game_over || glfwWindowShouldClose(win)) break;

			 try {
				 tetroCoat->Step(TETRO_PROP.move_direction);
				 cells.UpdateOffsets(tetroCoat->GetCellPointers(), tetroCoat->GetCellsNumber());
				 updateScreen();
			 }
			 catch (GLint) {
				 handleCellLandOnEvent();
				 break;
			 }
		 }
		 //
	}

	deleteCellPointers();
	while (!glfwWindowShouldClose(win)) {
		glfwWaitEvents();
		/*
		if (GAME_STATE.restarted) {
			glClear(GL_COLOR_BUFFER_BIT);
			GAME_STATE.game_over = false;
			GAME_STATE.paused = false;
			goto MAIN_PLAY;
		}
		//*/
	}

	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}
#endif