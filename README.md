File Structure

Clmg.h: Header file containing class definitions and declarations.
game: Executable file for the game.
game.cpp: Source file containing the main game logic.
game.o: Object file generated from the game source code.
install-libraries.sh: Shell script for installing necessary libraries.
Makefile: Makefile for compiling the project.
playerName.txt: Text file storing player names.
playerScore.txt: Text file storing player scores.
util.cpp: Utility functions used in the game.
util.h: Header file for utility functions.
util.o: Object file generated from the utility source code.

Getting Started
Prerequisites
C++ compiler (e.g., g++)
Make
Installation
cd candy-crush-game

Install the necessary libraries:
./install-libraries.sh

Compile the project using Make:
make

Run the game:
./game

Usage
Launch the game and follow the on-screen instructions to start playing.
Swap candies by entering the coordinates of the candies you want to swap.
Match three or more candies to score points and clear them from the grid.
Try to achieve the highest score possible and advance through the levels.

Contributing
Contributions are welcome! Feel free to submit a pull request or open an issue to suggest improvements or report bugs.
