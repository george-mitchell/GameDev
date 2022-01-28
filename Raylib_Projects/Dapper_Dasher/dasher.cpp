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
    // window dimensions in an array
    int WindowDimensions[2]; 
    WindowDimensions[0] = 512;
    WindowDimensions[1] = 380;


    // begin window
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Dapper Dasher"); 

    // Initialize velocity measured in pixels per frame (p/f)
    int Velocity {0};      


    // acceleration due to gravity, measured by seconds. Therefore need delta time (measures time since last frame)
    const int Gravity {1'000};        // gravity will be 1 p/s/s constant here


    // create nebula texture
    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // create nebula animations with initializations
    AnimData NebulaData {
        {0.0, 0.0, Nebula.width/8, Nebula.height/8},    // rectangle rec
        {WindowDimensions[0], WindowDimensions[1] - Nebula.height/8.0},    // vector2 pos
        0,      // int frame
        1.0/12.0,   // float update time
        0.0       // float running time
    };


    AnimData Nebula2Data {
        {0.0, 0.0, Nebula.width/8, Nebula.height/8}, 
        {WindowDimensions[0] + 300, WindowDimensions[1] - Nebula.height/8.0}, 
        0, 
        1.0/16.0, 
        0.0
    };

    // create array of nebulae
    AnimData nebulae[2] {NebulaData, Nebula2Data};


    // Create scarfy character, including loading the sprites of scarfy from textures
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");      // load the scarfy texture
    AnimData ScarfyData {
        {0,0, Scarfy.width/6, Scarfy.height}, 
        {WindowDimensions[0]/2 - Scarfy.width/12, WindowDimensions[1] - Scarfy.height},
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
        nebulae[0].RunningTime += dT; 

        // update nebula position to make it frame rate independent
        nebulae[0].Pos.x += NebulaVelocity*dT; 

        // update second nebula 
        nebulae[1].Pos.x += NebulaVelocity*dT; 
        
        // update scarfy position with gravity taking in account
        ScarfyData.Pos.y += Velocity*dT; 

        // update nebula animation frame
        if (nebulae[0].RunningTime >= nebulae[0].UpdateTime)
        {
            nebulae[0].RunningTime = 0; 
            nebulae[0].Rec.x = nebulae[0].frame * nebulae[0].Rec.width; 
            nebulae[0].frame++; 
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        // update nebula2 animation frame
        if (nebulae[1].RunningTime >= nebulae[1].UpdateTime)
        {
            nebulae[1].RunningTime = 0; 
            nebulae[1].Rec.x = nebulae[1].frame * nebulae[1].Rec.width; 
            nebulae[1].frame++; 
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
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
        if (ScarfyData.Pos.y < WindowDimensions[1] - Scarfy.height)
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
        DrawTextureRec(Nebula, nebulae[0].Rec, nebulae[0].Pos, WHITE);

        //draw second nebula
        DrawTextureRec(Nebula, nebulae[1].Rec, nebulae[1].Pos, RED); 
        
        // draw scarfy based on frame from sprite sheet
        DrawTextureRec(Scarfy, ScarfyData.Rec, ScarfyData.Pos, WHITE);

        EndDrawing(); 
    }

    // unload the textures from the window before closing
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    CloseWindow();




}