# DVDLogo

This is a fun demonstration of the ASCII graphics 'engine' I wrote for the Windows terminal in C++. I wrote this to eventually use it to implement the classic mobile game 'Snake'. It scans across the grid of cells and populates the 'pixels' (which are displayed as different characters) according to predefined 'textures'. 

## How to use

Download and launch the dvdlogo.exe file from the releases tab. You can adjust the dvd logo's velocity with the WASD keys, and the f key stops the movement. The q and e keys adjust the speed of the program, and the r key adjusts the randomness that is put into the velocity on each collision with the walls. The randomness is called 'spice' in the program and it is there to make sure the dvd logo doesn't get stuck bouncing between two walls in the same direction indefinitely.