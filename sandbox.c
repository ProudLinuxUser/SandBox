#include <raylib.h>
#include <stdlib.h>
#include <time.h>

//Initing cell size
#define GRID_WIDTH 150
#define GRID_HEIGHT 150
#define CELL_SIZE 6

//Material falling speed
#define SAND_SPEED 1
#define WATER_SPEED 1
#define LAVA_SPEED 2
#define MUD_SPEED 2

//materials
typedef enum{
        EMPTY,
        SAND,
        WATER,
        STONE,
        LAVA,
        MUD,
        RESET,
}Type;

int main(void){
        //Mud color
        Color MUD_COL = (Color){106,71,10,255};
        //Window 6 * 150 (x)(900), 6 * 150(y)(900), "called:sandbox"
        InitWindow(CELL_SIZE * GRID_WIDTH,CELL_SIZE * GRID_HEIGHT, "SandBox");
        SetTargetFPS(60);
        Type grid[GRID_WIDTH][GRID_HEIGHT] = {0};
        Type CURRENT = SAND;
        //Setting time seed
        srand(time(NULL));
        const char *str;

        //Loading icon
        Image icon = LoadImage("icon.png");
        SetWindowIcon(icon);
        UnloadImage(icon);
        int frame = 0;

        while (!WindowShouldClose()){
                frame++;

                //mouse position
                Vector2 mouse = GetMousePosition();
                int x = (int)mouse.x / CELL_SIZE;
                int y = (int)mouse.y / CELL_SIZE;

                //Materials selected by number
                if (IsKeyPressed(KEY_ONE)) CURRENT = SAND;
                if (IsKeyPressed(KEY_TWO)) CURRENT = WATER;
                if (IsKeyPressed(KEY_THREE)) CURRENT = STONE;
                if (IsKeyPressed(KEY_FOUR)) CURRENT = LAVA;
                if (IsKeyPressed(KEY_FIVE)) CURRENT = MUD;
                if (IsKeyPressed(KEY_SIX)) CURRENT = RESET;

                //Current type of material
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT){
                                grid[x][y] = CURRENT;
                                for (int x = 0; x < GRID_WIDTH;x++){
                                        for (int y = 0; y < GRID_HEIGHT;y++){
                                                if (CURRENT == RESET){
                                                        grid[x][y] = EMPTY;
                                                }
                                        }
                                }
                        }
                }
                //Sand
                if (frame % SAND_SPEED == 0){
                        for (int x = 0; x < GRID_WIDTH;x++){
                                for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                        if (grid[x][y] == SAND && grid[x][y+1] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = SAND;
                                        }

                                        if (rand() % 2 == 0){
                                                if (x > 0 && grid[x][y] == SAND && grid[x-1][y+1] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x-1][y+1] = SAND;
                                                }
                                        }
                                        else {
                                                if (x < GRID_WIDTH-1 && grid[x][y] == SAND && grid[x+1][y+1] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x+1][y+1] = SAND;
                                                }
                                        }
                                }
                        }
                }
                //Water
                if (frame % WATER_SPEED == 0){
                        for (int x = 0; x < GRID_WIDTH;x++){
                                for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                        if (grid[x][y] == WATER && grid[x][y+1] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = WATER; 
                                        }
                                        if (rand() % 2 == 0){
                                                if (x > 0 && grid[x][y] == WATER && grid[x-1][y] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x-1][y] = WATER;
                                                }
                                        }
                                        else{
                                                if (x < GRID_WIDTH-1 && grid[x][y] == WATER && grid[x+1][y] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x+1][y] = WATER;
                                                }
                                        }
                                        //Making stone
                                        if (grid[x][y] == WATER && grid[x][y+1] == LAVA){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = STONE;
                                        }
                                }
                        }
                }
                //Lava
                if (frame % LAVA_SPEED == 0){
                        for (int x = 0; x < GRID_WIDTH;x++){
                                for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                        if (grid[x][y] == LAVA && grid[x][y+1] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = LAVA; 
                                        }
                                        if (rand() % 2 == 0){
                                                if (x > 0 && grid[x][y] == LAVA && grid[x-1][y] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x-1][y] = LAVA;
                                                }
                                        }
                                        else{
                                                if (x < GRID_WIDTH-1 && grid[x][y] == LAVA && grid[x+1][y] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x+1][y] = LAVA;
                                                }
                                        }
                                        //Making stone
                                        if (grid[x][y] == LAVA && grid[x][y+1] == WATER){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = STONE;
                                        }
                                }
                        }
                }
                //Mud
                if (frame % MUD_SPEED == 0){
                        for (int x = 0; x < GRID_WIDTH;x++){
                                for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                        if (grid[x][y] == MUD && grid[x][y+1] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x][y+1] = MUD; 
                                        }
                                        if (rand() % 2 == 0){
                                                if (x > 0 && grid[x][y] == MUD && grid[x-1][y+1] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x-1][y+1] = MUD;
                                                }
                                        }
                                        else {
                                                if (x < GRID_WIDTH-1 && grid[x][y] == MUD && grid[x+1][y+1] == EMPTY){
                                                        grid[x][y] = EMPTY;
                                                        grid[x+1][y+1] = MUD;
                                                }
                                        }
                                }
                        }
                }


                //Making the materials string so the program can update the current item:
                switch(CURRENT){
                        case SAND: str = "Sand"; break;
                        case WATER: str = "Water"; break;
                        case STONE: str = "Stone"; break;
                        case LAVA: str = "Lava"; break;
                        case MUD: str = "Mud"; break;
                        case RESET: str = "Reset"; break;
                }

                //Instructions on the screen
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("1|Sand\n2|Water\n3|Stone\n4|Lava\n5|Mud\n6|Reset",20,20,30,RAYWHITE);
                DrawText(TextFormat("Selected: %s",str),330,20,30,RAYWHITE);
                DrawText(TextFormat("FPS: %d",GetFPS()),750,20,30,RAYWHITE);

                //Printing out materials:
                for (int x = 0; x < GRID_WIDTH;x++){
                        for (int y = 0; y < GRID_HEIGHT;y++){
                                switch (grid[x][y]) {
                                        case SAND: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,GOLD); break;
                                        case WATER: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,DARKBLUE); break;
                                        case STONE: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,GRAY); break;
                                        case LAVA: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,MAROON); break;
                                        case MUD: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,MUD_COL); break;
                                }
                        }
                }
                EndDrawing();
        }
        CloseWindow();
}
