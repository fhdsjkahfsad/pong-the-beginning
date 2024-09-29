
#include <iostream>
#include <raylib.h>
/*
last update: Scoring, text, working on clicker powerup
Final update: Ended the game, optimized ai, no powerups, lost or win at 12, good times were had making this game
*/
int pscore;

int enemyscore;

class Ball {
public:
    float x, y;
    float speedx, speedy;
    int radius;

    Ball() : radius(10), speedx(3), speedy(3), x(GetScreenWidth() / 2), y(GetScreenHeight() / 2) {}

    virtual void Draw() {
        DrawCircle(x, y, radius, RED);
    }

    virtual void Update() {
        x += speedx;
        y += speedy;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {


            speedy *= -1;
        }

        /*if (x + radius >= GetScreenWidth() || x - radius <= 0) {

            speedx *= -1;
        }*/
        if (x + radius >= GetScreenWidth()) {
            pscore += 1;
            speedx *= -1;
           
            
        }
        else if (x - radius <= 0) {
            enemyscore += 1;
            speedx *= -1;
           
            
        }

    }
};
class Paddle {
public:
    float w, h;
    float speed;
    float x, y;

    Paddle() : w(10), h(50), speed(7), x(0), y(0) {}

    void Draw() {
        DrawRectangle(x, y, w, h, RED);
    }

    void Update() {
        if (IsKeyDown(KEY_W)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_S)) {
            y += speed;
        }
        if (y < 0) {
            y = 0;
        }
        if (y + h > GetScreenHeight()) {
            y = GetScreenHeight() - h;
        }
        
    }
};

class Enemy {
public:
    float w, h;
    float speed;
    float x, y;

    Enemy() : w(10), h(50), speed(2.7), x(0), y(0) {}

    void Draw() {
        DrawRectangle(x, y, w, h, RED);
    }

    void Update(float ballY) {
        //follow the ypos of the ball
        if (y < ballY) {
            y += speed;
        }
        if (y > ballY) {
            y -= speed;
        }

        // Boundary checks
        if (y < 0) {
            y = 0;
        }
        if (y + h > GetScreenHeight()) {
            y = GetScreenHeight() - h;
        }
    }
};



Paddle player;
Enemy badpaddle;
Ball currentball;
bool gameover = false;
int main() {
    InitWindow(600, 600, "Pong: The Beginning");
    
    currentball.x = GetScreenWidth() / 2;
    currentball.y = GetScreenHeight() / 2;

    badpaddle.x = GetScreenWidth() - 25;
    badpaddle.y = (GetScreenHeight() / 2) - 25;

    player.x = 15; 
    player.y = (GetScreenHeight() / 2) - 25;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (gameover == false) {
            BeginDrawing();
            if (CheckCollisionCircleRec(Vector2{ currentball.x, currentball.y }, currentball.radius, Rectangle{ player.x, player.y, player.w, player.h })) {
                currentball.speedx *= -1;
            }
            if (CheckCollisionCircleRec(Vector2{ currentball.x, currentball.y }, currentball.radius, Rectangle{ badpaddle.x, badpaddle.y })) {
                currentball.speedx *= -1;
            }
            currentball.Update();
            if (pscore >= 12 || enemyscore >= 12) {
                gameover = true;
               

            }
            player.Update();
            badpaddle.Update(currentball.y);
            if (IsKeyDown(KEY_I)) {
                currentball.speedx += 1;
                currentball.speedy += 1;
            }



            ClearBackground(BLUE);
            currentball.Draw();
            badpaddle.Draw();
            player.Draw();

            DrawText(TextFormat("You: %i", pscore), 25, 25, 25, BLACK);
            DrawText(TextFormat("Me: %i", enemyscore), GetScreenWidth() - 100, 25, 25, BLACK);
            EndDrawing();
        }
        else if (gameover == true && pscore > enemyscore) {
            BeginDrawing();

            ClearBackground(GREEN);
            DrawText("You Win", 300, 300, 40, BLACK);

            EndDrawing();
        }
        else if (gameover == true && pscore < enemyscore) {
            BeginDrawing();
            ClearBackground(RED);
            DrawText("YOU LOSE LOL", 150, 300, 40, BLACK);
            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}
