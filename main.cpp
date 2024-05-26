#include <iostream>
#include <raylib.h>

using namespace std;

Color CAROLINA_BLUE = Color{75, 156, 211, 255};

int playerScore = 0;
int player2Score = 0;

class Ball {
    public:
        float x, y;
        int speedX = 5, speedY = 5;
        const int radius = 15;

        void Draw() {
            DrawCircle(x, y, radius, ORANGE);
        }

        void Update() {
            x += speedX;
            y += speedY;

            if(y + radius >= GetScreenHeight() || y - radius <= 0) {
                speedY *= -1;
            }

            if(x + radius >= GetScreenWidth()) {
                player2Score += 1;
                speedX *= -1;
            }

            if(x - radius <= 0) {
                playerScore += 1;
                speedX *= -1;
            }
        }
};

class Paddle {
    protected:

    void LimitMovement() {
        if(y <= 0) {
            y = 0;
        }

        if(y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

    public:
        const float width = 30;
        const float height = 200;
        float x, y;
        int speed = 5;

        void Draw() {
            DrawRectangleRounded(Rectangle{ x, y, width, height }, 0.8, 0, WHITE);
        }

        void Update() {
            if(IsKeyDown(KEY_UP)) {
                y -= speed;
            }

            if(IsKeyDown(KEY_DOWN)) {
                y += speed;
            }

            LimitMovement();
        }
};

class PaddleTwo: public Paddle {
    public:
        void Update(int ballY) {
            if(IsKeyDown(KEY_W)) {
                y -= speed;
            }

            if(IsKeyDown(KEY_S)) {
                y += speed;
            }

            LimitMovement();
        }
};

int main () {

    const int screenWidth = 1280;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Must's Pong");
    SetTargetFPS(60);
    int enterClicked = 0;
    Ball ball;
    PaddleTwo player2;
    Paddle player;

    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;

    player2.x = 20;
    player.x = screenWidth - player.width - 20;

    player2.y = screenHeight / 2 - player2.height / 2;
    player.y = screenHeight / 2 - player2.height / 2;

    while(enterClicked == 0 && WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);

        DrawText("Must's Pong", screenWidth / 8, screenHeight / 4, 150, WHITE);
        DrawText("Press Enter to begin!", screenWidth / 3.5, screenHeight*3 / 4, 50, WHITE);

        if(IsKeyDown(KEY_ENTER)) {
            enterClicked += 1;
        }

        EndDrawing();
    }

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);
        DrawText(TextFormat("%d", player2Score), screenWidth / 4, 20, 100, WHITE);
        DrawText(TextFormat("%d", playerScore), (screenWidth*3) / 4, 20, 100, WHITE);

        player2.Draw();
        ball.Draw();
        player.Draw();

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        ball.Update();
        player.Update();
        player2.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, 
        Rectangle{ player.x, player.y, player.width, player.height })) {
            ball.speedX *= -1;
        }

        if(CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
        Rectangle{ player2.x, player2.y, player2.width, player2.height })) {
            ball.speedX *= -1;
        }

        if(playerScore >= 10 || player2Score >= 10) {
            break;
        }

        EndDrawing();
    }

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(CAROLINA_BLUE);
        if (playerScore > player2Score) {
            DrawText("Player 1 won!", screenWidth / 4, screenHeight / 2 - 100, 100, WHITE);
        } else if(playerScore < player2Score) {
            DrawText("Player 2 won!", screenWidth / 4, screenHeight / 2 - 100, 100, WHITE);
        }

        EndDrawing();
    }            


    CloseWindow();
    return 0;
}