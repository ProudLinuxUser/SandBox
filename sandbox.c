#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define GRID_WIDTH 150
#define GRID_HEIGHT 150
#define CELL_SIZE 6

//materials
typedef enum{
        EMPTY,
        SAND,
        WATER,
        STONE,
        CLEAR,
}Type;

int main(void){
        InitWindow(CELL_SIZE * GRID_WIDTH,CELL_SIZE * GRID_HEIGHT, "SandBox");
        SetTargetFPS(60);
        Type grid[GRID_WIDTH][GRID_HEIGHT] = {0};
        Type CURRENT = SAND;
        srand(time(NULL));
        const char *str;

        Image icon = LoadImage("icon.png");
        SetWindowIcon(icon);
        UnloadImage(icon);

        while (!WindowShouldClose()){

                //mouse position
                Vector2 mouse = GetMousePosition();
                int x = (int)mouse.x / CELL_SIZE;
                int y = (int)mouse.y / CELL_SIZE;

                //Materials selected by number
                if (IsKeyPressed(KEY_ONE)) CURRENT = SAND;
                if (IsKeyPressed(KEY_TWO)) CURRENT = WATER;
                if (IsKeyPressed(KEY_THREE)) CURRENT = STONE;
                if (IsKeyPressed(KEY_FOUR)) CURRENT = CLEAR;

                //Current type of material
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                        if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT){
                                grid[x][y] = CURRENT;
                                for (int x = 0; x < GRID_WIDTH;x++){
                                        for (int y = 0; y < GRID_HEIGHT;y++){
                                                if (CURRENT == CLEAR){
                                                        grid[x][y] = EMPTY;
                                                }
                                        }
                                }
                        }
                }

                //Sand
                for (int x = 0; x < GRID_WIDTH;x++){
                        for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                if (grid[x][y] == SAND && grid[x][y+1] == EMPTY){
                                        grid[x][y] = EMPTY;
                                        grid[x][y+1] = SAND; 
                                }
                                else if (grid[x][y] == SAND && grid[x-1][y+1] == EMPTY){
                                        grid[x][y] = EMPTY;
                                        grid[x-1][y+1] = SAND;
                                }
                                else if (grid[x][y] == SAND && grid[x+1][y+1] == EMPTY){
                                        grid[x][y] = EMPTY;
                                        grid[x+1][y+1] = SAND;
                                }
                        }
                }
                //Water
                for (int x = 0; x < GRID_WIDTH;x++){
                        for (int y = GRID_HEIGHT-2;y >= 0;y--){
                                if (grid[x][y] == WATER && grid[x][y+1] == EMPTY){
                                        grid[x][y] = EMPTY;
                                        grid[x][y+1] = WATER; 
                                }
                                if (rand() % 2 == 0){
                                        if (grid[x][y] == WATER && grid[x-1][y] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x-1][y] = WATER;
                                        }
                                        else if (grid[x][y] == WATER && grid[x+1][y] == EMPTY){
                                                grid[x][y] = EMPTY;
                                                grid[x+1][y] = WATER;
                                        }
                                }
                        }
                }

                //Making string so the program can print them out.
                switch(CURRENT){
                        case SAND: str = "Sand"; break;
                        case WATER: str = "Water"; break;
                        case STONE: str = "Stone"; break;
                        case CLEAR: str = "Clear"; break;
                }

                //Printing out materials on the screen
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("1|Sand\n2|Water\n3|Stone\n4|Clear",20,20,30,RAYWHITE);
                DrawText(TextFormat("Selected: %s",str),200,20,30,RAYWHITE);

                for (int x = 0; x < GRID_WIDTH;x++){
                        for (int y = 0; y < GRID_HEIGHT;y++){
                                switch (grid[x][y]) {
                                        case SAND: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,YELLOW); break;
                                        case WATER: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,BLUE); break;
                                        case STONE: DrawRectangle(x * CELL_SIZE,y * CELL_SIZE,CELL_SIZE,CELL_SIZE,GRAY); break;
                                }
                        }
                }
                EndDrawing();
        }
        CloseWindow();
}
