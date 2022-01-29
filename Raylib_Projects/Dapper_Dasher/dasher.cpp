#include "raylib.h"                  




///////////////////////// PRELIM DATA AND METHODS ////////////////////////////

// declare custom compound data type for animation
struct AnimData 
{
    Rectangle Rec;                      // rectangle to cut out of sprite sheet
    Vector2 Pos;                        // (x,y) coords of data in the window
    int frame;                          // which frame in sprite sheet to use
    float UpdateTime;                   // time since last animation update
    float RunningTime;                  // time since last frame
};

// create ground check function
bool isOnGround(AnimData data, int windowHeight) {
    return data.Pos.y >= windowHeight - data.Rec.height;
}

// create update animation method
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame) {
    // update running time
    data.RunningTime += deltaTime; 
    if (data.RunningTime >= data.UpdateTime) {
        data.RunningTime = 0.0;
        //update animation frame
        data.Rec.x = data.frame * data.Rec.width;
        data.frame++;
        if (data.frame > maxFrame) {
            data.frame = 0;
        }
    }
    return data;
}







/////////////////////// BEGIN MAIN FUNCTION ////////////////////////////////

int main() 
{
    // window dimensions in an array
    int WindowDimensions[2]; 
    WindowDimensions[0] = 512;
    WindowDimensions[1] = 380;


    // begin window
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Dapper Dasher"); 


        


    // acceleration due to gravity, measured by seconds. Therefore need delta time (measures time since last frame)
    const int Gravity {1'000};        // gravity will be 1 pixels/second/second constant here


    // create nebula texture
    Texture2D Nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    



    // initialize nebulas in an array
    const int sizeofNebulae {10};
    AnimData nebulae[sizeofNebulae] {};
    for (int i {0}; i < sizeofNebulae; ++i) {
        nebulae[i].Rec.x = 0.0;
        nebulae[i].Rec.y = 0.0;
        nebulae[i].Rec.width = Nebula.width/8.0;
        nebulae[i].Rec.height = Nebula.height/8.0;
        nebulae[i].Pos.y = WindowDimensions[1] - Nebula.height/8.0;
        nebulae[i].frame = 0;
        nebulae[i].RunningTime = 0.0;
        nebulae[i].UpdateTime = 0.0;
        // start each nebula further away from the player start to arrive later
        nebulae[i].Pos.x = WindowDimensions[0] + (300*i);
    }

    // endgame finish line
    // once this passes final nebula then Scarfy wins
    float finishLine {nebulae[sizeofNebulae-1].Pos.x};


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
    int NebulaVelocity {-200};              // negative as nebula moves right-left

    
    // create boolean to decide if object is in the air 
    bool IsInAir {false}; 


    // jump velocity (pixels/second)
    const int JumpVelocity {-600}; 

    // Initialize velocity measured in pixels per frame (p/f)
    int Velocity {0};  


    // load in background pictures
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png"); 
    Texture2D foreground = LoadTexture("textures/foreground.png"); 
    // create scrolling values
    float mgX {};
    float fgX {}; 
    float bgX {}; 

    // check if scarfy hits any nebula
    bool collision {false}; 

    


    ///////////////////////// INITIALIZE WINDOW ///////////////////////////////////

    // Set target FPS and begin while loop
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dT {GetFrameTime()};

        BeginDrawing(); 
        ClearBackground(WHITE); 

        // background has two of the same image whose x pos moves to the left and then resets to 0
        // update background scrolling
        bgX -= 20 * dT;      
        mgX -= 40*dT; 
        fgX -= 80*dT;            
        // reset background x position to 0.0 once it has reached as far left as possible. 
        if (bgX <= -background.width*2) {
            bgX = 0.0;
        }
        if (mgX <= -midground.width*2){
            mgX = 0.0;
        }
        if (fgX <= -foreground.width*2){
            fgX = 0.0;
        }

        // draw background, midground and foreground
        // use two of each image, placed side by side
        // scroll to the left and then reset back to zero.
        Vector2 bg1Pos {bgX,0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE); 
        Vector2 bg2Pos {bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos,0.0, 2.0, WHITE);
        Vector2 mg1Pos {mgX, 0.0}; 
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE); 
        Vector2 mg2Pos {mgX + midground.width*2, 0.0}; 
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        Vector2 fg1Pos {fgX, 0.0}; 
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE); 
        Vector2 fg2Pos {fgX + foreground.width*2, 0.0}; 
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        // update RunningTimes with delta time to make it frame independent
        ScarfyData.RunningTime += dT; 
        nebulae[0].RunningTime += dT; 


        // update position of each nebula
        for (int i {0}; i < sizeofNebulae; ++i) {
            nebulae[i].Pos.x += NebulaVelocity*dT;
        }

        // update position of finish line
        finishLine += NebulaVelocity*dT;
        
        // update scarfy position with gravity taking in account
        ScarfyData.Pos.y += Velocity*dT; 

        // update animation frame for the nebulae
        for (int i {0}; i < sizeofNebulae; ++i){
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }


        // update animation frame so long as Scarfy is on the ground
        if (!IsInAir){
            ScarfyData = updateAnimData(ScarfyData, dT, 5);
        }


        // This is the ground check. We prevent performing double jump with IsInAir
        if (isOnGround(ScarfyData, WindowDimensions[1]))
        {
            Velocity = 0;   // rectangle is on the ground
            IsInAir = false;
        }
        else 
        {
            Velocity += Gravity*dT;   // rectangle is in the air
            IsInAir = true;
        }


        // perform a jump
        if (IsKeyPressed(KEY_SPACE) && !IsInAir)
        {
            Velocity += JumpVelocity;
        }

        // detect if scarfy hit the nebula
        
        for (AnimData nebula : nebulae) {
            float pad {50}; 
            // nebula rectangle
            Rectangle nebRec {
                nebula.Pos.x + pad, 
                nebula.Pos.y + pad, 
                nebula.Rec.width - 2*pad,
                nebula.Rec.height - 2*pad
            };
            // scarfy rectanggle
            Rectangle scarfyRec {
                ScarfyData.Pos.x,
                ScarfyData.Pos.y,
                ScarfyData.Rec.width,
                ScarfyData.Rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec)) {
                collision = true;
            }
        }

        // if collision then stop all drawing 
        if (collision) {
            DrawText("Game Over!", WindowDimensions[0]/4, WindowDimensions[1]/2.0, 40, RED);
            
        } else if (ScarfyData.Pos.x >= finishLine) {
                DrawText("You Win!", WindowDimensions[0]/3, WindowDimensions[1]/2.0, 40, GREEN);
        } else {
             // draw nebula textures 
            for (int i {0}; i < sizeofNebulae; i++) {
                DrawTextureRec(Nebula, nebulae[i].Rec, nebulae[i].Pos, WHITE);
            }
            // draw scarfy based on frame from sprite sheet
            DrawTextureRec(Scarfy, ScarfyData.Rec, ScarfyData.Pos, WHITE);
        }
        EndDrawing();
    }

    // unload the textures from the window before closing
    UnloadTexture(Scarfy);
    UnloadTexture(Nebula);
    UnloadTexture(background);
    UnloadTexture(midground); 
    UnloadTexture(foreground);
    CloseWindow();




}