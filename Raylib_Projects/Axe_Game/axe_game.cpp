#include "raylib.h"         // include external library raylib (therefore we dont use the angle brackets)

int main()
{
    // Define and initialize the window width, height, then open window
    int WindowWidth {1000};
    int WindowHeight {600};
    InitWindow(WindowWidth, WindowHeight, "Axe Game");       // make pop-up window: width, height, name

    // circle coords
    int Circle_X {WindowWidth/2}; 
    int Circle_Y {WindowHeight/2}; 
    float Circle_Radius {25};
    // Circle Edges
    int LeftCircleEdge {Circle_X - Circle_Radius};
    int RightCircleEdge {Circle_X + Circle_Radius};
    int TopCircleEdge {Circle_Y - Circle_Radius}; 
    int BottomCircleEdge {Circle_Y + Circle_Radius};

    // axe values
    int Axe_X {WindowWidth/2}; 
    int Axe_Y {0}; 
    int Axe_Height {50};
    int Axe_Width {50};
    int Direction {6};
    // Axe Edges
    int LeftAxeEdge {Axe_X}; 
    int RightAxeEdge {Axe_X + Axe_Width}; 
    int TopAxeEdge {Axe_Y}; 
    int BottomAxeEdge {Axe_Y + Axe_Height}; 

    // set frames per second. 
    SetTargetFPS(60);

    // set circle movespeed
    int MoveSpeed {5}; 

    // Endgame detector
    bool CollisionWithAxe {false}; 
    bool StartGame {false}; 

    // To keep the window open, we use function WindowShouldClose(), which gives false until user hits the "x" or esc
    while(!WindowShouldClose())
    {
        
        BeginDrawing(); 
        // This washes the window with the same color to prevent the double buffer from causing flickering
        ClearBackground(WHITE);

        // Opening Menu Screen
        if (StartGame == false)
        {
            DrawText("Welcome to the Axe Game!", WindowWidth/3, WindowHeight/2, 20, BLUE );
            DrawText("Press Spacebar to begin playing...", WindowWidth/3, WindowHeight/2 + 20, 20, BLUE); 

            if (IsKeyDown(KEY_SPACE))
            {
                StartGame = true; 
            }
        }

        else 
        {

            // detect a loss
            if (CollisionWithAxe == true)
            {
                DrawText("Game Over!", WindowWidth/3, WindowHeight/2, 20, RED); 
                DrawText("Press N to start a new game...", WindowWidth/3, WindowHeight/2 + 20, 20, GREEN); 
                DrawText("Press ESC to exit...", WindowWidth/3, WindowHeight/2 + 40, 20, GREEN); 

                if (IsKeyDown(KEY_N))
                {
                    Circle_X = WindowWidth/2; 
                    Circle_Y = WindowHeight/2; 
                    Axe_X = WindowWidth/2; 
                    Axe_Y = 0; 
                    CollisionWithAxe = false; 
                    continue;
                }
            }
            else  
            {
                // update circle edges
                LeftCircleEdge  = Circle_X - Circle_Radius;
                RightCircleEdge = Circle_X + Circle_Radius;
                TopCircleEdge = Circle_Y - Circle_Radius;
                BottomCircleEdge = Circle_Y + Circle_Radius;

                //update axe edges 
                LeftAxeEdge = Axe_X; 
                RightAxeEdge = Axe_X + Axe_Width; 
                TopAxeEdge = Axe_Y; 
                BottomAxeEdge = Axe_Y + Axe_Height;

                // draw circle in window with x-coord, y-coord, radius and color. When y-coord starts top left and moves down. 
                DrawCircle(Circle_X, Circle_Y, 25, BLUE);
                
                // draw the axe to the screen
                DrawRectangle(Axe_X, Axe_Y, Axe_Width, Axe_Height, RED);
                
                // Move the axe 
                Axe_Y += Direction;
                if (Axe_Y + Axe_Height > WindowHeight || Axe_Y < 0)
                {
                    Direction = -Direction;
                }

                // We now want to move our circle with keys. We use WASD controls  
                if (IsKeyDown(KEY_D) && Circle_X + Circle_Radius < WindowWidth)
                {
                    Circle_X += MoveSpeed; 
                }
                else if (IsKeyDown(KEY_W) && Circle_Y - Circle_Radius > 0)
                {
                    Circle_Y -= MoveSpeed;
                }
                else if (IsKeyDown(KEY_A)&& Circle_X - Circle_Radius > 0)
                {
                    Circle_X -= MoveSpeed; 
                }
                else if (IsKeyDown(KEY_S) && Circle_Y + Circle_Radius < WindowHeight)
                {
                    Circle_Y += MoveSpeed; 
                }


                // Detect Endgame
                if ((TopAxeEdge < BottomCircleEdge) && (BottomAxeEdge > TopCircleEdge) && (LeftAxeEdge < RightCircleEdge) && (RightAxeEdge > LeftCircleEdge)) 
                {
                    CollisionWithAxe = true; 
                } 


            }

        }

        // Game Logic Ends
        EndDrawing(); 
    }
}