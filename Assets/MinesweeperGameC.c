#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define MAP_SIZE 30 // Maximum Size of the Map //
#define MAX_HITS 9999 // Moves or Hits the user can use //
#define BOMB 'X' // Symbol of the Bomb //
#define HIDDEN '-' // Symbol of the Hidden Tiles //

void loading(); // function for the loading screen //
void commence(); // Start of the Game //
void end(); // End of the Game | Program //

char map[MAP_SIZE][MAP_SIZE];
char bombs[MAP_SIZE][MAP_SIZE];
int revealed[MAP_SIZE][MAP_SIZE];
int num_revealed, num_bombs;
int hits, lives = 3, try_count = 0;

void loading() // Starts the loading sequence //
{
    char a = 177, b = 219;
    system("Color F3");
    printf("\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t.......... |LOADING| ...........\n\n");
    printf("\t\t\t\t\t");
            // Prints the Loading Bar //
    for (int i = 0; i < 32; i++)
        printf("%c", a);
            // Set the cursor again starting //
            // point of loading bar //
    printf("\r");
    printf("\t\t\t\t\t");
    for (int i = 0; i < 32; i++)
    {
        printf("%c", b);
        Sleep(50);
    }
}


int main() // main function of the program // | // Displays the overall Menu //
{
    int option;
    loading();
    system("Color f0");
    do{
        system("cls");
        puts("\n\n\t\t       ===========================================================================================================================");
        puts("\t\t       ===========================================================================================================================");
        puts("\t\t       ===                                                                                                                     ===");
        puts("\t\t       ===   ====     ====  ==========  ====      ==  =========  ==========  ==         ==  =========  =========   =========   ===");
        puts("\t\t       ===   ==  =   =  ==      ==      ==  =     ==  ==         ==          ==         ==  ==         ==          ==      =   ===");
        puts("\t\t       ===   ==   = =   ==      ==      ==   =    ==  ==         ==          ==         ==  ==         ==          ==      =   ===");
        puts("\t\t       ===   ==    =    ==      ==      ==    =   ==  ======     ==========  ==    =    ==  ======     ======      =========   ===");
        puts("\t\t       ===   ==         ==      ==      ==     =  ==  ==                 ==  ==   = =   ==  ==         ==          ==          ===");
        puts("\t\t       ===   ==         ==      ==      ==      = ==  ==                 ==  ==  =   =  ==  ==         ==          ==          ===");
        puts("\t\t       ===   ==         ==  ==========  ==       ===  =========  ==========  ====     ====  =========  =========   ==          ===");
        puts("\t\t       ===                                                                                                                     ===");
        puts("\t\t       ===========================================================================================================================");
        puts("\t\t       ===========================================================================================================================");

        puts("\n\t\t\t\t\t\t                     -=[!]=- TEAM F | Members -=[!]=- ");
        puts("\n\t\t\t\t\t\t                      [!] Esquejo, John Victor [!]");
        puts("\n\t\t\t\t\t\t                      [!] Balbon, Kenneth [!]");
        puts("\n\t\t\t\t\t\t                      [!] Almaden, Aliya Beyonce [!]");
        puts("\n\t\t\t\t\t\t                      [!] Celestra, Diana Lee [!]");
        puts("\n\t\t\t\t\t\t                      [!] Cordon, John [!]");
        puts("\n\t\t\t\t\t\t                      [!] Isleta, Kherwin [!]");

         puts("\n\t\t       ===========================================================================================================================");
        printf("\n\t\t                                                          Press [1] to Start");
        printf("\n\t\t                                                          Press [0] to Exit\n");
         puts("\n\t\t       ===========================================================================================================================");
        scanf("%d", &option);
        switch(option)
        {
            case 1: commence(); break; // Option 1 Leads to the Commence/Start function //
            case 0: end(0); break; // Option 2 Ends the game immediately //
        }
    }while(option >= 2 || option <= 0); // Repeats the loop when the user enters an integer below 0, and above 2 //
}


void gotoxy(int x, int y) // Declaration of the Gotoxy Function //
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void genbomb() // Generates the 10 Bombs and Positions them randomly across the Map //
{
    int i, j, k;
    int x, y;
    int bombs_count = 0; // Initial Bomb Count //

    for (i = 0; i < MAP_SIZE; i++)
    {
        for (j = 0; j < MAP_SIZE; j++)
        {
            bombs[i][j] = HIDDEN; // Stores the Bomb //
        }
    }

    while (bombs_count < 25)
    {
        i = rand() % MAP_SIZE;
        j = rand() % MAP_SIZE;

        if (bombs[i][j] != BOMB) {
            bombs[i][j] = BOMB;
            bombs_count++;

            // calculate x and y position for the cursor
            x = (j * 3) + 1;
            y = i + 2;

            // move cursor to the position
            gotoxy(x, y);

            // print the bomb symbol
            printf("X");
        }
    }
}


int countAdjacentBombs(int x, int y) // Displays the Adjacent Bombs from the Chosen Tile //
{
    int i, j;
    int count = 0;

    for (i = x-1; i <= x+1; i++)
    {
        for (j = y-1; j <= y+1; j++)
        {
            if (i >= 0 && i < MAP_SIZE && j >= 0 && j < MAP_SIZE && bombs[i][j] == BOMB) {
                count++;
            }
        }
    }

    return count;
}

void initmap() // Displays the HIDDEN Tiles '-' //
{
    int i, j;

    for (i = 0; i < MAP_SIZE; i++)
    {
        for (j = 0; j < MAP_SIZE; j++)
        {
            map[i][j] = HIDDEN;
            revealed[i][j] = 0;
        }
    }
}

void printmap() // Prints the Numerical positions of the Columns and Rows // | // Sets the Symbol for Revealed Bombs //
{
    int i, j;
    int x, y;

    // calculate x position to center the game board
    x = (60 - (MAP_SIZE * 3)) / 2;

    // calculate y position to center the game board
    y = (20 - MAP_SIZE) / 2;

    gotoxy(x, y); // move cursor to the upper left corner

    // print column numbers
    printf("  ");
    for (j = 0; j < MAP_SIZE; j++)
    {
        printf("%2d ", j); // adjust the width to 2 characters
    }
    printf("\n");

    for (i = 0; i < MAP_SIZE; i++)
    {
        printf("%2d ", i); // print the row number followed by a space character

        for (j = 0; j < MAP_SIZE; j++)
        {
            if (map[i][j] == HIDDEN) {
                if (revealed[i][j] == 1 && bombs[i][j] == BOMB) {
                    printf("X  "); // display the "X" mark for revealed bombs
                } else {
                    printf("-  ");
                }
            } else {
                printf("%d  ", map[i][j]);
            }
        }
        printf("\n");
        gotoxy(x, y + i + 2); // move cursor to the next line
    }
}



void revealTile(int x, int y) // Reveals the tiles chosen by the User // | // Can either be a numerical value or the 'x' symbol //
{
    if (bombs[x][y] == BOMB)
    {
        // Game over, player hit a bomb
        printf("\n\n\t [!] Bomb Detected [!]\n\n\t [!] -1 Life [!]\n\n\t [?] Bomb Location | (%d, %d) [?].\n\n", x+1, y+1);
        revealed[x][y] = 1; // set revealed[x][y] to 1
        lives--;
        system("pause");
    }
    else
    {
        // Update the tile to show the number of adjacent bombs
        int adjacentBombs = countAdjacentBombs(x, y);
        map[x][y] = adjacentBombs;
        hits++;
        try_count++;
    }
}


void commence() // Start of the Game // | // Background Color/Font Color is set to White/Light Blue Respectively //
{
    srand(time(0));
    system("Color F3");
    genbomb(); // Calls the genbomb Function //
    initmap(); // Calls the initmap Function //

    while(hits < MAX_HITS)
    {
        system("cls");
        printf("\t\t\t\t\-=- | -=- [ Minesweeper ] -=- | -=-\n"); // Displays the title of the game //
        printf("\n\t\t\t\t      -=[ %d LIVES Left. ]=-\n\n", lives); // Displays the Lives //
        printf("\n\t\t\t\t      -=[ %d Input Count ]=-\n\n", try_count); // Counts the amount of input entered by the user //
        printmap();

        if (lives == 0) // Activates when the user loses all of their Lives //
        {
            char choice;
            printf("\n\t\t [!] Critical [!] \n\t\t [-] Your lives have ran out [-] \n\t\t [=] Total Input(s): %d [=]\n", try_count);
            system("pause");
            printf("\n\n\t\t You ran out of lives! Do you want to try again? (Y/N): ");
            fflush(stdin);
            scanf("%c", &choice);
            if (choice == 'Y' || choice == 'y') {
            // Restarts the Game //
            lives = 3;
            hits = 0;
            num_revealed = 0;
            num_bombs = 0;
            try_count = 0;
            initmap();
            genbomb();
            printmap();
            commence();
        } else {
            // Terminates the Program //
            end(0);
            }
        }

        int x, y;
        printf("\n\t-=[ Enter coordinates (x | y) to reveal ]=- : "); // Accepts the coordinate input of the user //
        scanf("%d %d", &x, &y);

        if (x >= MAP_SIZE || y >= MAP_SIZE || x < 0 || y < 0) // Anything above or Below the MAP SIZE is disregarded //
        {
            printf("Invalid coordinates.\n");
            continue;
        }

        revealTile(x, y); // Calls the revealTile Function //

        if (hits == MAX_HITS) // In the event the user uses all of their Hits //
        {
            printf("\n\t\t-=[ !WARNING! ]=-\n\n    [!] Maximum amount of Hits has been reached [Game Over]!");
            break;
        }

        printf("\n\tPress any key to continue..."); // For Continuance Sake //
        // wait for user to press Enter
    }
    return 0;
}
