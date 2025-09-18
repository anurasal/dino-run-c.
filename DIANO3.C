 #include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>



    // Body (approximation of Chrome Dino pixel art)
    // Row by row (1 = block, 0 = empty)
    int dino[16][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0},
    {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0},
    {1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0},
    {1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0},
    {0,0,1,1,1,1,0  ,1,0,0,0,0,1,0,0,0},
    {0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0}
};
void drawPixelDino(int x, int y)
{
    int size = 5; // pixel block size (increase for bigger dino)
    int i,j;
    setfillstyle(SOLID_FILL, WHITE);
    // Draw each block
    for ( i=0; i<16; i++) {
	for (j=0; j<16; j++) {
	    if (dino[i][j] == 1) {
		bar(x + j*size, y + i*size,
		    x + j*size + size, y + i*size + size);
	    }
	}
    }

    // Eye (small black square)
    setfillstyle(SOLID_FILL, BLACK);
    bar(x + 8*size, y + 2*size, x + 9*size, y + 3*size);
}



void drawCactus(int x, int y) {
    // Main trunk
    rectangle(x, y-50, x+20, y);
    // Left arm
    line(x, y-30, x-15, y-30);
    line(x-15, y-30, x-15, y-10);
    line(x-15, y-10, x, y-10);
    // Right arm
    line(x+20, y-40, x+35, y-40);
    line(x+35, y-40, x+35, y-15);
    line(x+35, y-15, x+20, y-15);
}
int main() {
    int gd = DETECT, gm;
     int dinoY = 50;    // Dino position
    int cactusX = 600;  // Cactus position
    int jump = 0;       // Jump state
    int score = 0;
    char scr[10];
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    while (!kbhit()) {
	cleardevice();

	// Ground line
	line(0, 380, 640, 380);

	// Dinosaur
	drawPixelDino(40,dinoY);

	//cactus
	drawCactus(cactusX,380);

	// Display score
	outtextxy(10, 10, (char*)("Score: "));

	sprintf(scr, "%d", score);
	outtextxy(70, 10, scr);

	// Move cactus
	cactusX -= 10;
	if (cactusX < 0) {
	    cactusX = 640;
	    score++;
	}

	// Dino jump
	if (jump > 0) {
	    dinoY -= 10;
	    jump--;
	} else if (dinoY < 300) {
	    dinoY += 10;
	}

	// Collision detection
	if (cactusX < 100 && cactusX > 50 && dinoY > 250) {
	    outtextxy(200, 200, (char*)"GAME OVER!");
	    break;
	}

	delay(50);

	// Check for key press
	if (kbhit()){
	char ch=getch();
	    if (dinoY == 300) {
		jump = 10; // jump strength
	    }
	}
    }

    getch();
    closegraph();
    return 0;
}