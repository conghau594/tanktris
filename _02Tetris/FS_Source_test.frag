#version 450 core


#define TIME_LOC  0u
#define SPEED_LOC 1u

#define SQR_UNIT_SIZE		50
#define GAME_BOARD_WIDTH	16
#define GAME_BOARD_HEIGHT	10
#define SCORE_ZONE_WIDTH	3
#define WND_BUFFER			1


#define VIEWPORT_HEIGHT				( SQR_UNIT_SIZE * GAME_BOARD_HEIGHT )
#define VIEWPORT_WIDTH				( SQR_UNIT_SIZE * (GAME_BOARD_WIDTH + SCORE_ZONE_WIDTH) )

in vec2 aPos_out;

layout (location = TIME_LOC)  uniform float time;
out vec4 FragColor;

//uniform float resolution;
//uniform vec2 mouse;
//uniform vec3 spectrum;

#define SQUARE_SIZE 50.0
#define TETROMINO_RIFT 0.06*SQUARE_SIZE

#define xFC (aPos_out.x*(-VIEWPORT_HEIGHT))
#define yFC (aPos_out.y*(-VIEWPORT_WIDTH)+100)

float drawSquare(vec2 coord, float size) {
    float x = coord.x, y = coord.y;
    return    step(0.0, sign(xFC - x) * sign(x + size - xFC))
    * step(0.0, sign(yFC - y) * sign(y + size - yFC));
}

float drawOldTetromino(mat4 tetroMatrix, vec2 centerCoord, float unitSize, float unitRift) {
   float sum = 0.0;

   for (int i = 0; i < 4; ++i) {
       for (int j = 0; j < 4; ++j) {
           if (tetroMatrix[i][j] == 1) {
               vec2 tmpVec = centerCoord + vec2((j - 1) * unitSize, (2 - i) * unitSize);
               sum += drawSquare(tmpVec, unitSize - unitRift);
           }
       }
   }

   return sum;
}

void main(void) {
float x = fract(time / 10) * 1000;
vec2 test1 = vec2(x      , 100.0);
vec2 test2 = vec2(x * 0.6, 250.0);
vec2 test3 = vec2(x * 0.8, 400.0);
vec2 test4 = vec2(x * 0.4, 600.0);

mat4 testGame1 = mat4 (0.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 1.0, 1.0, 0.0,
                       0.0, 1.0, 0.0, 0.0);

mat4 testGame2 = mat4 (0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0,
                       1.0, 1.0, 1.0, 1.0,
                       0.0, 0.0, 0.0, 0.0);

mat4 testGame3 = mat4 (0.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       0.0, 1.0, 0.0, 0.0,
                       1.0, 1.0, 0.0, 0.0);

mat4 testGame4 = mat4 (0.0, 0.0, 0.0, 0.0,
                       0.0, 0.0, 0.0, 0.0,
                       0.0, 1.0, 1.0, 0.0,
                       1.0, 1.0, 0.0, 0.0);

float testColor =  drawOldTetromino(testGame1, test1, 50.0, 2.5)
                 + drawOldTetromino(testGame2, test2, 50.0, 2.5)
                 + drawOldTetromino(testGame3, test3, 50.0, 2.5)
                 + drawOldTetromino(testGame4, test4, 50.0, 2.5);

   FragColor = vec4( testColor*0.5, vec2(testColor) , 1.0);
}
