 //============================================================================
#include <GL/glut.h>
#include "CImg.h"
#include<fstream>

#include "util.h"
#include <iostream>
#include<string>

#include<cmath> 
#include<ctime>
#include<cstdlib>
using namespace std;

//Declaring the functions
void SetCanvasSize(int, int);
void DisplayMenu();
void MenuKeyboard(unsigned char , int , int);
void DrawGradientCircle(int , int , int, float *, float *);
void MousePressedAndMoved(int x, int y);
void randomshape(int x, int y, int cellWidth, int cellHeight, bool &candy_generated);
void displayGrid(int rows, int cols);
void DrawRectangleOutline(int x, int y, int width, int height, float *color);
void drawInputBox();
void GameDisplay();

void PrintableKeys(unsigned char key, int x, int y);
void Timer(int m);
void MouseMoved(int x, int y);
void swapLeft(int cellX, int cellY);
void swapRight(int cellX, int cellY);
void swapUp(int cellX, int cellY);
void swapDown(int cellX, int cellY);
void destroy_candy(int rows, int cols);
int getRandomCandy();
void shiftCandiesDown(int rows, int cols);
void MouseClicked(int button, int state, int x, int y);
void savePlayerName(const string& name);
string readPlayerName();
int readPlayerScore();
void savePlayerScore(const int& score);
void initGame();
void DrawString(int x, int y, string text, float *color);
void DrawTextBackground(int x, int y, int width, int height, float *fillColor, float *borderColor);
void SettingsKeyboard(unsigned char key, int x, int y);
void DisplaySettings();
void InstructionsKeyboard(unsigned char key, int x, int y);
void Instructions();
void overKeyboard(unsigned char key, int x, int y);
void over();
//global variable
int grid[8][8];

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	
}

// to save the score of the player in the file
void savePlayerScore(const int& score) {
    ofstream outFile("playerScore.txt");
    if (outFile.is_open()) {
        outFile << score;
        outFile.close();
    } else {
        cerr << "Unable to open file to save player score." << endl;
    }
}

//to read the score of the player from the file
int readPlayerScore() {
    int score = 0;
    ifstream inFile("playerScore.txt");
    if (inFile.is_open()) {
        inFile >> score;
        inFile.close();
    } else {
        cerr << "Unable to open file to read player score." << endl;
    }
    return score;
}

// to save the name of the player in the file
void savePlayerName(const string& name) {
    ofstream outFile("playerName.txt");
    if (!outFile) {
        cerr << "Unable to open file to save player name." << endl;
    } else {
        outFile << name;
        if (!outFile.good()) {
            cerr << "Error occurred while writing to the file." << endl;
        }
        outFile.close();
    }
}

//to handle the keyboard functionality of settings
void SettingsKeyboard(unsigned char key, int x, int y) {
     int g=0; //error handling
    while (g=0)
    {
        //cout<<"settings keyboard is active ";
    }

    if (key == 'b' || key == 'B' || key==27 ) {
        glutDisplayFunc(DisplayMenu);  // to go back to main menu
        glutKeyboardFunc(MenuKeyboard);  // to switch back to main menu keyboard handling
    } 
    //when user presses spacebar
    if (key == 32) {
        glutDisplayFunc(Instructions);  // to go back to main menu
        glutKeyboardFunc(InstructionsKeyboard);  // to switch back to main menu keyboard handling
    }
    glutPostRedisplay();
    glutPostRedisplay();
}

//to show instructions on the menu
void Instructions() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    int g=0; //error handling
        //cout<<"read the intructions<<g ";
    

    float textBackground[3] = {0.5f, 0.0f, 0.0f}; // Maroon background
    float textBorder[3] = {0.0f, 0.0f, 0.0f};     // Black border
    float whiteColor[3] = {1.0f, 1.0f, 1.0f};      // White color for text

    // to draw "How to Play" title
    DrawTextBackground(110, 100, 800, 500, textBackground, textBorder);
    DrawString(420, 530, "HOW TO PLAY", whiteColor);

    DrawString(150, 450,"1. Start Game: Press Enter from the Main Menu.", whiteColor);
    DrawString(150, 400,"2. Objective: Match three or more candies of the same type in a row or column to score.", whiteColor);
    DrawString(150, 350,"3. Swap Candies: Click to select a candy, then another adjacent candy to swap them.", whiteColor);
    DrawString(150, 300,"4. Earn Points: Longer matches create special candies and yield higher points.", whiteColor);
    DrawString(150, 250,"5. Pause/Resume: Press 'P' to pause and go to the menu; press 'R' to resume gameplay.", whiteColor);
    DrawString(150, 200,"6. Exit Game: Press 'ESC' to quit the game instantly.", whiteColor);
    DrawString(150, 150,"7. Access Settings: Press 'S' for settings, including player profiles and game instructions.", whiteColor);

    glutSwapBuffers();
}

//to handle the keyboard inputs of instructions
void InstructionsKeyboard(unsigned char key, int x, int y){

    int g=0; //error handling
        //cout<<"keyboar<<g";
    

if (key == 'b' || key == 'B' || key==27 ) {
        glutDisplayFunc(DisplayMenu);  // to go back to main menu
        glutKeyboardFunc(MenuKeyboard);  // to switch back to main menu keyboard handling
    }
    glutPostRedisplay();

}

//to display settings
void DisplaySettings() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    int g=0; //error handling
        //cout<<"display"<<g;
    
    
    float textBackground[3] = {0.5f, 0.0f, 0.0f}; // Maroon background
    float textBorder[3] = {0.0f, 0.0f, 0.0f};     // Black border
    float whiteColor[3] = {1.0f, 1.0f, 1.0f};      // White color for text

    // Drawing "Player Profile" title
    DrawTextBackground(250, 490, 400, 50, textBackground, textBorder);
    DrawString(350, 500, "PLAYER PROFILE ", whiteColor);

    // Reading player name and score
    string playerName = readPlayerName();
    int playerScore = readPlayerScore();

    // Drawing player name
    DrawTextBackground(250, 430, 400, 50, textBackground, textBorder);
    string nameDisplay = "Name: " + playerName;
    DrawString(300, 440, nameDisplay.c_str(), whiteColor);

    // Drawing player score
    DrawTextBackground(250, 370, 400, 50, textBackground, textBorder);
    string scoreDisplay = "Score: " + to_string(playerScore);
    DrawString(300, 380, scoreDisplay.c_str(), whiteColor);

    // Drawing "Back to Menu" option
    DrawTextBackground(250, 310, 400, 50, textBackground, textBorder);
    DrawString(300, 320, "Back to Menu [B]", whiteColor);

    DrawTextBackground(250, 250, 400, 50, textBackground, textBorder);
    DrawString(300, 260, "How to Play [SPACE]", whiteColor);

    glutSwapBuffers();
}

//to read the player name in the file 
string readPlayerName() {
    string name;
    std::ifstream inFile("playerName.txt");
    if (inFile.is_open()) {
        getline(inFile, name);
        inFile.close();
    } else {
        cerr<<"Unable to open file to read player name."<<endl;
    }
    return name;
}

//to handle the keyboard inputs on the menu
void MenuKeyboard(unsigned char key, int x, int y) {
    string playerName = readPlayerName();
    
    int g=0; //error handling
    while (g=0)
    {
        //cout<<"menu board is active. ";
    }

    if (key == 13) { // Enter key pressed
        savePlayerName(playerName); // Ensuring name is saved when starting the game
        glutDisplayFunc(GameDisplay);
        glutKeyboardFunc(PrintableKeys);
        glutTimerFunc(1000.0, Timer, 0);
        glutPostRedisplay();
    } 
        if (key == 'r' || key == 'R') {
        glutDisplayFunc(GameDisplay);  // Switching back to resume the game
        glutKeyboardFunc(PrintableKeys);  // Restoring the original keyboard handler
        cout << "Game Resumed." << endl;
    }
    else if (key == 's' || key == 'S') {

            glutDisplayFunc(DisplaySettings);  // Switching to settings display
            glutKeyboardFunc(SettingsKeyboard);  // Using a different function for settings keyboard handling
    }
    else if (key == 27) { // ESC Key to exit window
        exit(0);
    }
    else {              //Backspcae Key
        if (key == 8 && !playerName.empty()) { 
            playerName.resize(playerName.size() - 1);
        } else if (isprint(key)) {
            playerName += key;
        }
        savePlayerName(playerName);
        glutPostRedisplay();
    }
}

void DrawTextBackground(int x, int y, int width, int height, float *fillColor, float *borderColor) {
    // Draw filled rectangle
    glColor3fv(fillColor);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Draw border
    glColor3fv(borderColor);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

//to display the menu
void DisplayMenu() {
    
    glClearColor(0.7f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float textBackground[3] = {0.9f, 0.9f, 0.9f}; 
    float textBorder[3] = {0.0f, 0.0f, 0.0f}; 
    // drawing a box enclosing the strings
    DrawTextBackground(250, 320, 400, 210, textBackground, textBorder);
    //main menu options
    DrawString(400, 500, "MAIN MENU", colors[BLACK]);
    DrawString(300, 450, "Press ENTER to start the game", colors[DARK_GREEN]);
    DrawString(300, 400, "Press ESC to exit", colors[DARK_SLATE_BLUE]);
    DrawString(300, 350, "Press S for Settings", colors[DARK_SALMON]);
    // game modes options
    DrawString(400, 280, "GAME MODES", colors[BLACK]);
    DrawTextBackground(250, 150, 400, 100, textBackground, textBorder);
    DrawString(300, 210, "Normal Mode [ENTER]", colors[DARK_RED]);

    DrawString(270, 50, "Press P to Pause the game. Press R to Resume.", colors[DARK_RED]);

    drawInputBox();

    glutSwapBuffers();
}

void DrawString(int x, int y, string text, float *color) {
    glColor3fv(color);
    glRasterPos2i(x, y);
    for (const char &c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void DrawGradientCircle(int x, int y, int radius, float *color1, float *color2) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3fv(color1); // Center of the color
    glVertex2f(x, y); // Center of the circle

    // Defining colors at circle edge
    float step = 1.0 / radius;
    for (float angle = 0; angle <= 360; angle += 0.1) {
        float radian = angle * (M_PI / 180.0);
        float xx = x + radius * cos(radian);
        float yy = y + radius * sin(radian);
        float factor = (yy - (y - radius)) / (2 * radius); // Linear interpolation factor
        float color[3]; // Interpolated color
        for (int i = 0; i < 3; ++i) {
            color[i] = (1 - factor) * color1[i] + factor * color2[i];
        }
        glColor3fv(color);
        glVertex2f(xx, yy);
    }

    glEnd();
}

void destroy_candy(int rows, int cols) {
    bool candy_generated = false; // Flag to indicate if any new candies were generated
    int score = readPlayerScore(); // to read the current score

      // Checking for four consecutive candies horizontally
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols - 3; ++j) {
            if (grid[i][j] != -1 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] && grid[i][j] == grid[i][j + 3]) {
                grid[i][j] = -1;
                grid[i][j + 1] = -1;
                grid[i][j + 2] = -1;
                grid[i][j + 3] = -1;
                score += 4; // Incrementing score for each 4-candy match found
                cout<<"destroyed "<<endl;
                
                candy_generated = true;
            }
        }
    }

    // Checking for four consecutive candies vertically
     for (int i = 0; i < rows - 3; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != -1 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j] == grid[i + 3][j]) {
                grid[i][j] = -1;
                grid[i + 1][j] = -1;
                grid[i + 2][j] = -1;
                grid[i + 3][j] = -1; 
                score += 4; // Incrementing score for each vertical 4-candy match
                
                cout<<"destroyed "<<endl;
                candy_generated = true;
            }
        }
    }

    // Checking for three consecutive candies horizontally
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols - 2; ++j) {
            if (grid[i][j] != -1 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]) {
                grid[i][j] = -1;
                grid[i][j + 1] = -1;
                grid[i][j + 2] = -1;
                score += 3; // Incrementing score for each horizontal 3-candy match
               
                cout<<"destroyed "<<endl; //error handling
                candy_generated = true;
            }
        }
    }

    // Checking for three consecutive candies vertically
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != -1 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]) {
                grid[i][j] = -1;
                grid[i + 1][j] = -1;
                grid[i + 2][j] = -1;
                score += 3; // Incrementing score for each vertical 3-candy match
                cout<<"destroyed "<<endl;
                
                candy_generated = true;
            }
        }
    }

    if (candy_generated) { // If any candies were destroyed and new ones generated
        glutPostRedisplay(); // Request ing redisplay to show updated candies
        savePlayerScore(score); // Saving updated score

    }
}

int getRandomCandy() {
    
    return rand() % 5; // Generating a random number between 0 and 4 
}

void randomshape(int x, int y, int cellWidth, int cellHeight, bool &candy_generated) {
    if (!candy_generated) {
        // Generating candies for each cell in the grid
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                grid[i][j] = getRandomCandy();
            }
        }
        
        // Checking for consecutive candies and reshuffling if found
        bool foundChain = true;
        while (foundChain) {
            foundChain = false; // Reset the flag
            // Checking for consecutive candies horizontally
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]) {
                        foundChain = true;
                        // Reshuffle the candies in this row
                        for (int k = j; k < j + 3; ++k) {
                            grid[i][k] = getRandomCandy();
                        }
                    }
                }
            }
            // Checking for consecutive candies vertically
            for (int j = 0; j < 8; ++j) {
                for (int i = 0; i < 5; ++i) {
                    if (grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]) {
                        foundChain = true;
                        // Reshuffle the candies in this column
                        for (int k = i; k < i + 3; ++k) {
                            grid[k][j] = getRandomCandy();
                        }
                    }
                }
            }
        }
        
        // Refilling any empty cells with new candies
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (grid[i][j] == -1) { // If the cell is empty
                    grid[i][j] = getRandomCandy(); // Refill it with a new candy
                }
            }
        }
        
        // Setting the  flag to indicate that candies have been generated
        candy_generated = true;
    }
}

void MousePressedAndMoved(int x, int y) {
   // cout << x << " " << y << endl;
    glutPostRedisplay();
}

void displayGrid(int rows, int cols) {
    // Declaring  flag
    static bool candy_generated = false;
    
    // Calculating cell width and height based on the cwindow size and number of rows and columns
    int cellWidth = glutGet(GLUT_WINDOW_WIDTH) / cols;
    int cellHeight = glutGet(GLUT_WINDOW_HEIGHT) / rows;
   
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            // Calculating the position of the cell
            int x = j * cellWidth;
            int y = i * cellHeight;
            
            // Drawing the cell
            DrawRectangle(x, y, cellWidth, cellHeight, colors[BLACK]);
            
            // Drawing grid lines
            DrawLine(x, y, x + cellWidth, y, 1, colors[WHITE]); // Horizontal line
            DrawLine(x, y, x, y + cellHeight, 1, colors[WHITE]); // Vertical line
            
           //to generate random candy
            randomshape(x, y, cellWidth, cellHeight, candy_generated);
           
            // Drawing candies based on the generated grid
            int candyType = grid[i][j];
            switch (candyType) {
                case 0: {
                    // Draw triangle
                    //to adjust the triangle size according to my window
                    int a1 = x + cellWidth / 2; // Top vertex
                    int b1 = y + cellHeight - (cellHeight / 4);
                    int a2 = x + (cellWidth / 4); 
                    int b2 = y + (cellHeight / 4); 
                    int a3 = x + cellWidth - (cellWidth / 4); 
                    int b3 = y + (cellHeight / 4); 
                    DrawTriangle(a1, b1, a2, b2, a3, b3, colors[RED]); 
                    break;
                }
                case 1:
                    DrawGradientCircle(x + cellWidth / 2, y + cellHeight / 2, cellWidth / 4, colors[DARK_BLUE], colors[WHITE]);
                    break;
                case 2: {
                    // Draw triangle
                    int x1 = x + cellWidth / 2; 
                    int y1 = y + cellHeight - (cellHeight / 4); 
                    int x2 = x + (cellWidth / 4); 
                    int y2 = y + (cellHeight / 4); // Adjusted based on grid size
                    int x3 = x + cellWidth - (cellWidth / 4); 
                    int y3 = y + (cellHeight / 4); 
                    DrawTriangle(x1, y1, x2, y2, x3, y3, colors[DARK_GOLDEN_ROD]);  
                    break;
                }
                case 3:
                    DrawGradientCircle(x + cellWidth / 2, y + cellHeight / 2, cellWidth / 4, colors[ORANGE], colors[RED]);
                    break;
                case 4:
                    DrawGradientCircle(x + cellWidth / 2, y + cellHeight / 2, cellWidth / 4, colors[BLUE_VIOLET], colors[DEEP_PINK]);
                    break;
            }
            MousePressedAndMoved(x, y);
        }
    }
}

void DrawRectangleOutline(int x, int y, int width, int height, float *color) {
    glColor3fv(color);
    glLineWidth(1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

//to draw the input box where the user will enter his/her name
void drawInputBox() {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int inputBoxY = windowHeight - 200; // Adjust as necessary for visibility

    string playerName = readPlayerName(); // Read player name from file

    DrawRectangle(250, inputBoxY, 400, 50, colors[WHITE]); // Assuming colors[WHITE] is defined
    DrawRectangleOutline(250, inputBoxY, 400, 50, colors[RED]);
    DrawString(280, inputBoxY + 20, "Enter your name: " + playerName, colors[BLACK]);
}

//for the progress bar shown at the top right of the window
void DrawProgressBar(int score,int maxScore) {
   // const int maxScore = 100; 
    const int progressBarWidth = 200;
    const int progressBarHeight = 20;
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // Calculate progress based on the updated score
    float progress = (float)score / maxScore;
    int targetBarLength = progress * progressBarWidth;
    static int currentBarLength = 0;
    int barX = windowWidth - progressBarWidth - 20; 
    int barY = windowHeight - 40; 
    if (score == 0) { //whenever the score becomes zero the progressbar restarts
        currentBarLength = 0;
    }

    // Animating the progress bar filling up
    if (currentBarLength < targetBarLength) {

        currentBarLength += 2;
    }
    
    // Drawing the progress bar outline
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2i(barX, barY);
    glVertex2i(barX + progressBarWidth, barY);
    glVertex2i(barX + progressBarWidth, barY + progressBarHeight);
    glVertex2i(barX, barY + progressBarHeight);
    glEnd();

    // Drawing the filled part of the progress bar
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_QUADS);
    glVertex2i(barX, barY);
    glVertex2i(barX + currentBarLength, barY);
    glVertex2i(barX + currentBarLength, barY + progressBarHeight);
    glVertex2i(barX, barY + progressBarHeight);
    glEnd();
}

//initialize game state and variables
void initGame() {
    savePlayerScore(0); // Reset the score at the start of the game
    savePlayerName(""); // Reset the player name at the start of the game
    glutPostRedisplay(); // Redraw the display to reflect these changes
}

//to display the window after the last level is completed
void over(){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    float textBackground[3] = {0.5f, 0.0f, 0.0f}; // Maroon background
    float textBorder[3] = {0.0f, 0.0f, 0.0f};     // Black border
    float whiteColor[3] = {1.0f, 1.0f, 1.0f};      // White color for text
    
    DrawTextBackground(200, 100, 300, 100, textBackground, textBorder);
    DrawString(226, 141, "CONGRATULATIONS! YOU HAVE WON", whiteColor);

    glutSwapBuffers();
    glutPostRedisplay();  
}

//for the over window shown when the game ends
void overKeyboard(unsigned char key, int x, int y) {
if (key == 27) {  // Escape key
       exit(1);
    }
}

void GameDisplay() {
    static int level = 1;
    int score = readPlayerScore();
    string scoreText = "Score: " + to_string(score);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    displayGrid(8, 8);

    DrawString(85, 800, scoreText.c_str(), colors[MISTY_ROSE]);

    int maxscore = 0;
    //for levels
    switch (level) {
        case 1:
            maxscore = 50;
            break;
        case 2:
            maxscore = 100;
            break;
            //game ends
        case 3:
            glutDisplayFunc(over);
            glutKeyboardFunc(overKeyboard);
            break;
    }
   
    if (score >= maxscore) {
        level++;
        savePlayerScore(0);
    }

    DrawProgressBar(score, maxscore); // Draw the progress bar

    glutSwapBuffers();
    glutPostRedisplay(); // Keep updating the display
}

void PrintableKeys(unsigned char key, int x, int y) {
    string playerName = readPlayerName();  // Read current name from file

    if (key == 'p' || key == 'P') {
        glutDisplayFunc(DisplayMenu);  // Switching to menu display
        glutKeyboardFunc(MenuKeyboard);  // Changing the keyboard function to handle menu operations
        cout << "Switched to Menu. Press R to resume." << endl;
    } 
    else if (key == 'r' || key == 'R') {
        glutDisplayFunc(GameDisplay);  // Switching back to game display
        glutKeyboardFunc(PrintableKeys);  // Restoring the original keyboard handler
        cout << "Game Resumed." << endl;
    }
    else if (key == 's' || key == 'S') {
        glutDisplayFunc(DisplaySettings); //switching to settings
        glutKeyboardFunc(SettingsKeyboard); 
    }
    
    else if (key == 13) {  // Enter key
        glutKeyboardFunc(NULL);  // Optionally switch to another state or screen
    } else if (key == 8 && !playerName.empty()) {  // Backspace key
        playerName.resize(playerName.size() - 1);
    } else if (isprint(key)) {
        playerName += key;
    }

    savePlayerName(playerName);  // Saving updated name back to file

    if (key == 27) {  // Escape key
       exit(1);
    }

    glutPostRedisplay();  
}

void MouseMoved(int x, int y) {
	
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

void swapLeft(int cellX, int cellY) {
    bool swapleft=false;
    if (cellX > 0) { // Checking boundary conditions
        int temp = grid[cellY][cellX];
        grid[cellY][cellX] = grid[cellY][cellX - 1];
        grid[cellY][cellX - 1] = temp;
        swapleft=true;
    }
   // cout<<"swapleft"<<swapleft<<endl;
}

// Function to perform swapping to the right
void swapRight(int cellX, int cellY) {
    bool swapright=false;
    if (cellX < 7) { 
        int temp = grid[cellY][cellX];
        grid[cellY][cellX] = grid[cellY][cellX + 1];
        grid[cellY][cellX + 1] = temp;
        swapright=true;
    }
    // cout<<"swapright"<<swapright<<endl;
}

// Function to perform swapping upwards
void swapUp(int cellX, int cellY) {
    bool swapup=false;
    if (cellY > 0) { // Checking to make sure the cell is not on the first row
        int temp = grid[cellY][cellX];
        grid[cellY][cellX] = grid[cellY - 1][cellX];
        grid[cellY - 1][cellX] = temp;
        swapup=true;
    }
    // cout<<"swapup"<<swapup<<endl;
}

// Function to perform swapping downwards
void swapDown(int cellX, int cellY) {
    bool swapdown=false;
    if (cellY < 7) { 
        int temp = grid[cellY][cellX];
        grid[cellY][cellX] = grid[cellY + 1][cellX];
        grid[cellY + 1][cellX] = temp;
        swapdown=true;
    }
    // cout<<"swapdown"<<swapdown<<endl;
}

void shiftCandiesDown(int rows, int cols) {
    bool candy_generated = false; // Flag to indicate if any new candies were generated
    
   
    for (int j = 0; j < cols; ++j) {
        // Starting from the bottom of the column and move upwards
        int emptyRow = -1; // Track the last empty row found
        int emptyRow2=-1;
        for (int i = 0; i < rows; ++i) {
            if (grid[i][j] == -1) { // If the current cell is empty
                emptyRow = i; // Update empty row
            } else if (emptyRow != -1) { // If there was an empty cell below
                grid[emptyRow][j] = grid[i][j]; // Move the candy down to the empty cell
                grid[i][j] = getRandomCandy(); // Fill the current cell with a new random candy
                emptyRow++; // Update empty row
                candy_generated = true;
            }
        }
    }
    
    if (candy_generated) { // If any candies were moved down
        glutPostRedisplay(); 
    }
    else if(!candy_generated){
          for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (grid[i][j] == -1) { // If the cell is empty
                    grid[i][j] = getRandomCandy(); // Refill it with a new candy
                }
            }
        }
        
    }
    glutPostRedisplay();
}

void Timer(int m) {  // to control the timely execution of functions
    int rows=8,cols=8;
	//to show smooth transition
    destroy_candy(rows,cols);
    shiftCandiesDown( rows, cols);
      
	
	glutTimerFunc(500.0, Timer, 0);
}

void MouseClicked(int button, int state, int x, int y) {
    //to keep track of initial movements
    static int initialX = -1, initialY = -1;
    int cols = 8, rows = 8;
    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int cellWidth = windowWidth / cols;
    int cellHeight = windowHeight / rows;

    if (button == GLUT_LEFT_BUTTON) {
        int cellX = x / cellWidth;
        int cellY = (windowHeight - y) / cellHeight;
        cout<<"CellX "<<cellX<<" CellY "<<cellY<<endl; 
        if (state == GLUT_DOWN) {
            // Start dragging
            initialX = cellX;
            initialY = cellY;
            cout<<"initialX "<<initialX<<" initialY "<<initialY<<endl;
        } else if (state == GLUT_UP) {
            // Determine the drag direction and perform swap
            int finalX = cellX;
            int finalY = cellY;
            cout<<"finalX "<<finalX<<" finalY "<<finalY<<endl;
            int deltaX = finalX - initialX;
            int deltaY = finalY - initialY;
            cout<<"deltX "<<deltaX<<" deltaY "<<deltaY<<endl;
            cout<<endl;
            // Swap based on direction
            if (deltaX > 0 && abs(deltaX) > abs(deltaY)) {  // Move right
                swapRight(initialX, initialY);
            } else if (deltaX < 0 && abs(deltaX) > abs(deltaY)) {  // Move left
                swapLeft(initialX, initialY);
            } else if (deltaY > 0 && abs(deltaY) > abs(deltaX)) {  // Move up
                swapUp(initialX, initialY);
            } else if (deltaY < 0 && abs(deltaY) > abs(deltaX)) {  // Move down
                swapDown(initialX, initialY);
            }
          
        }
       glutPostRedisplay(); 
    }
}

int main(int argc, char*argv[]) {
    int width = 1020, height = 840; // Set window size to be 1020 x 840
    
   // savePlayerScore(0);  Reset the score at the start of the game
    // savePlayerName("");  Reset the player name at the start of the game
    
    glutInit(&argc, argv); // Initialize the graphics library
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // Using color display mode
    glutInitWindowPosition(50, 50); // Set the initial position of the window
    glutInitWindowSize(width, height); // Set the size of the window
    glutCreateWindow("Candy Crush Game"); // Set the title of the game window
    SetCanvasSize(width, height); // Set the number of pixels

    // Initialize the random number generator
    srand(time(NULL));
    initGame(); // Initialize the game state

    // Initially set to display the menu
    glutDisplayFunc(DisplayMenu);
    glutKeyboardFunc(MenuKeyboard);

    // Register other event handlers
   
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);
    glutMotionFunc(MousePressedAndMoved);
    //glutTimerFunc(1000.0, Timer, 0);

    // Start the GLUT main loop
    glutMainLoop();
    return 1;
}
