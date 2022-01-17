#include "raylib.h"                  


// declare custom compound data type for animation
struct AnimData 
{
    Rectangle Rec; 
    Vector2 Pos; 
    int frame;
    float UpdateTime; 
    float RunningTime; 
};





int main() 
{
    // window dimensions
    const int WindowWidth {512}; 
    const int WindowHeight {380}; 

    // begin window
    InitWindow(WindowWidth, WindowHeight, "Dapper Dasher"); 

    // Initialize velocity measured in pixels per frame (p/f)
    int Velocity {0};      


    // acceleration due to gravity, measured by seconds. Therefore need delta time (measures time since last frame)
    const int Gravity {1'000};        // gravity will be 1 p/s/s constant here


    // create nebula texture
    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // create nebula animations with initializations
    AnimData NebulaData {
        {0.0, 0.0, Nebula.width/8, Nebula.height/8},    // rectangle rec
        {WindowWidth, WindowHeight - Nebula.height/8.0},    // vector2 pos
        0,      // int frame
        1.0/12.0,   // float update time
        0.0       // float running time
    };


    AnimData Nebula2Data {
        {0.0, 0.0, Nebula.width/8, Nebula.height/8}, 
        {WindowWidth + 300, WindowHeight - Nebula.height/8.0}, 
        0, 
        1.0/16.0, 
        0.0
    };


    // Create scarfy character, including loading the sprites of scarfy from textures
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");      // load the scarfy texture
    AnimData ScarfyData {
        {0,0, Scarfy.width/6, Scarfy.height}, 
        {WindowWidth/2 - Scarfy.width/12, WindowHeight - Scarfy.height},
        0,
        1.0/12.0,
        0.0
    };   


    // Nebula X velocity (pixels/second)
    int NebulaVelocity {-250};      

    

    // create boolean to decide if object is in the air 
    bool IsInAir {false}; 


    // jump velocity (pixels/second)
    const int JumpVelocity {-600}; 

    


    // Set target FPS and begin while loop
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing(); 
        ClearBackground(WHITE); 

        // delta time (time since last frame)
        const float dT {GetFrameTime()};

        // update RunningTimes with delta time to make it frame independent
        ScarfyData.RunningTime += dT; 
        NebulaData.RunningTime += dT; 

        // update nebula position to make it frame rate independent
        NebulaData.Pos.x += NebulaVelocity*dT; 

        // update second nebula 
        Nebula2Data.Pos.x += NebulaVelocity*dT; 
        
        // update scarfy position with gravity taking in account
        ScarfyData.Pos.y += Velocity*dT; 

        // update nebula animation frame
        if (NebulaData.RunningTime >= NebulaData.UpdateTime)
        {
            NebulaData.RunningTime = 0; 
            NebulaData.Rec.x = NebulaData.frame * NebulaData.Rec.width; 
            NebulaData.frame++; 
            if (NebulaData.frame > 7)
            {
                NebulaData.frame = 0;
            }
        }

        // update nebula2 animation frame
        if (Nebula2Data.RunningTime >= Nebula2Data.UpdateTime)
        {
            Nebula2Data.RunningTime = 0; 
            Nebula2Data.Rec.x = Nebula2Data.frame * Nebula2Data.Rec.width; 
            Nebula2Data.frame++; 
            if (Nebula2Data.frame > 7)
            {
                Nebula2Data.frame = 0;
            }
        }

        // update animation frame so long as Scarfy is on the ground
        if (ScarfyData.RunningTime >= ScarfyData.UpdateTime && !IsInAir)
        {
            ScarfyData.RunningTime = 0;        // now timer restarts
            ScarfyData.Rec.x = ScarfyData.frame * ScarfyData.Rec.width;      // move along the sprite sheet to next frame 
            ScarfyData.frame++; 
            if (ScarfyData.frame > 5)  // once we get passed sprite sheet width, return back to the start
            {
                ScarfyData.frame = 0;
            }
            
        }

        // This is the ground check. We prevent performing double jump with IsInAir
        if (ScarfyData.Pos.y < WindowHeight - Scarfy.height)
        {
            Velocity += Gravity*dT;        // rectangle is in the air, multiply by dT to convert to per second, not per frame
            IsInAir = true;
        }
        else 
        {
            Velocity = 0;   // rectangle is on the ground
            IsInAir = false;
        }

        // perform a jump
        if (IsKeyPressed(KEY_SPACE) && !IsInAir)
        {
            Velocity += JumpVelocity;
        }

        
        
        // draw Nebula texture
        DrawTextureRec(Nebula, NebulaData.Rec, NebulaData.Pos, WHITE);

        //draw second nebula
        DrawTextureRec(Nebula, Nebula2Data.Rec, Nebula2Data.Pos, RED); 
        
        // draw scarfy based on frame from sprite sheet
        DrawTextureRec(Scarfy, ScarfyData.Rec, ScarfyData.Pos, WHITE);

        EndDrawing(); 
    }

    // unload the textures from the window before closing
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    CloseWindow();




}