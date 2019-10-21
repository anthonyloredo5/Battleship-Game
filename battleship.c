/*Programmer: Richard Loredo
Date: 4/23/19
Battleship assignment 7
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "battleshipHeader.h"


int main (){
    short player = 0;//variables for players
    short shot = 0;
    int menuSelect = 0;

    int north = 0;//Variables for direction
    int south = 0;
    int east = 0;
    int west = 0;

    int i = 0;//variables for counters
    int counter = 1;

    char shipSymbol = '\0';// variable as temporary ship symbol

    Player playerOne;
    Player playerTwo;

    srand(time(0));


    welcomeScreen();//tells the compiler to run this function
    clearScreen ();//calls for function void clearScreen

    initializePlayer(&playerOne, PLAYERONE);//calls for initializePlayer function and forms gameboard and ship date for player one
    clearScreen();

    initializePlayer(&playerTwo, PLAYERTWO);//calls for initializePlayer function and forms gameboard and ship date for player two
    clearScreen();


    menuSelect = displayMenu();//tells the compiler to run this function
    clearScreen();//calls for function void clearScreen

    switch (menuSelect)
    {//switch statement displaying the correct output based on user input
    case MANUAL:
        printf("%s selected to place ships manually\n", playerOne.name);//no matter the case player one decides how to place sips
        manualShipPlace(&playerOne);
        break;

    case RANDOM:
        printf("%s selected to place ships randomly\n", playerOne.name);
        randomShipPlace(&playerOne);
        break;
    }//end of switch statement
    randomShipPlace(&playerTwo);
    //displayGameBoard(playerOne);
    //displayGameBoard(playerTwo);
    playGame(&playerOne, &playerTwo);

    return 0;
}

void welcomeScreen()
{

    printf("BBBBB   AAAA  TTTTTT TTTTTT LL     EEEEEE  SSSSS HH  HH II PPPP\n");
    printf("BB  BB AA  AA   TT     TT   LL     EE     SS     HH  HH II PP  PP\n");
    printf("BBBBB  AA  AA   TT     TT   LL     EEEE    SSSS  HHHHHH II PPPP\n");
    printf("BB  BB AAAAAA   TT     TT   LL     EE         SS HH  HH II PP\n");
    printf("BBBBB  AA  AA   TT     TT   LLLLLL EEEEEE SSSSS  HH  HH II PP\n");
    printf("\n");
    printf("\n");
    printf("RULES OF THE GAME:\n");
    printf("1. This is a two player game.\n");
    printf("2. Player 1 is you and Player 2 is the computer.\n");
    printf("3. Player 1 will be prompted if user wants to manually input coordinates\n");
    printf("   for the game board or have the computer randomly generate a game board\n");
    printf("4. There are five types of ships to be placed by the longest length to the\n");
    printf("   shortest; [c] Carrier has 5 cell, [b] Battleship has 4 cells, [r] Cruiser\n");
    printf("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
    printf("5. The computer randomly selects which player goes first\n");
    printf("6. The game begins as each player tries to guess the location of the ships\n");
    printf("   of the opposing player's game board; [X] hit and [~] miss\n");
    printf("7. First player to guess the location of all ships wins\n");
    printf("\n");
    printf("                     Hit <ENTER> to continue!");

    char enter;//character variable declaration
    scanf("%c", &enter);
}//End of welcomeScreen function

    int displayMenu()
{
    int select;//variable declaration
    while (select != MANUAL && select != RANDOM)
 {
    printf("Select the option for human player ship placement:\n");
    printf("[1] Manually\n");
    printf("[2] Randomly\n");
    printf("Enter Option: ");
    select = getchar();

    if (select != MANUAL && select != RANDOM)//if-else function prompting what will happen if the statement is not correct
        printf("Invalid option, try again\n");
        fflush(stdin);
 }//end of "while" statement..
    return select;
}//end of display menu function

    void displayGameBoard(Player player)
{
    int row;
    int col;

    printf("\n %s's Game Board\n\n", player.name);

    printf("---------------------------------------------\n");
    printf("|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |\n");
    printf("---------------------------------------------\n");

 for (row = 0; row < ROWS; row++)
{
     printf("| %d ", row);
     for (col = 0; col < COLS; col++)
     {
      printf("| %c ", player.gameBoard.board[row][col]);
     }
    printf("|\n");
}
    printf("---------------------------------------------\n");
}//end of displayGameBoard function

    void clearScreen()
{
    system("cls");//system("clear"); would not be correct for my computer
}

    void initializeBoard(Player *player)
{
   //int row, col;

     memset(player->gameBoard.board, WATER, sizeof(player->gameBoard.board));

}
   void initializePlayer(Player *player, char *name)
   {
       char playerName[20];
       GameBoard playerBoard;
       Ship ships [NUM_SHIPS];

       printf("Enter %s's name:\n", name);
       gets(playerName);
       strcpy(player->name, playerName);
       player->gameBoard = playerBoard;
       memcpy(player->ships, ships, NUM_SHIPS);

       initializeBoard(player);
       //displayGameBoard(*player);
       //getchar();
       clearScreen();
       initializeShips(player);
       //displayShips(*player);
       //getchar();
   }
    void initializeShips(Player *player)
    {
        int i;

        for (i = 0; i < NUM_SHIPS; i++){

        Ship s;
        switch (i){
         case battleship:
             strcpy(s.name, "BATTLESHIP");
             s.length = BATTLESHIP_SZ;
             s.symbol = BATTLESHIP;
         break;

         case carrier:
             strcpy(s.name, "CARRIER");
             s.length = CARRIER_SZ;
             s.symbol = CARRIER;
         break;

         case cruiser:
             strcpy(s.name, "CRUISER");
             s.length = CRUISER_SZ;
             s.symbol = CRUISER;
         break;

         case destroyer:
             strcpy(s.name, "DESTROYER");
             s.length = DESTROYER_SZ;
             s.symbol = DESTROYER;
         break;

         case submarine:
             strcpy(s.name, "SUBMARINE");
             s.length = SUBMARINE_SZ;
             s.symbol = SUBMARINE;
         break;

        }
        s.sunk = false;
        s.start.row = -1;
        s.start.column = -1;
        player->ships[i]=s;



        }
    }
     void displayShips(Player player)
{
     int i;
     printf("%s's Ship Data\n\n", player.name);

     for (i = 0; i < NUM_SHIPS; i++){
        printf("Name: %s\n", player.ships[i].name);
        printf("Length: %d\n", player.ships[i].length);
        printf("Symbol: %c\n", player.ships[i].symbol);
        printf("It's sunk: %s\n", ((player.ships[i].sunk)? "True": "False"));
        printf("Location: row: %d col: %d\n\n", player.ships[i].start.row, player.ships[i].start.column);
     }
}

     bool isValid(Player player, int row, int col, int length, char orient)
{
	int r;
	int c;

	bool valid = true;

    if( (row < 0 || (( (row + length) > 9)&& orient == 'V') ) )
        return false;

    if( (col < 0 || ( ( (col + length) > 9) && orient == 'H' ) ))
        return false;

    if(orient != 'H' && orient != 'V')
        return false;

    switch(orient)
    {
        case HORIZONTAL:
            for(c = col; c < (length + col); c++)
            {
                if (player.gameBoard.board[row][c] != WATER)
                {
                    return false;
                }
            }
            break;
        case VERTICAL:
            for(r = row; r < (length + row); r++)
            {
                if (player.gameBoard.board[r][col] != WATER)
                {
                    return false;
                }
            }
            break;
    }

	return valid;
}

void placeShip(Player * player, int row, int col, Ship ship, char orient)
{
    int r;
    int c;

//    printf("Placing ship %s with %d cells, starting at row/column %d/%d orient %c\n ", ship.name, ship.length, row, col, orient);

    switch(orient)
    {
        case HORIZONTAL:
            for(c = col; c < (ship.length + col); c++)
            {
                player->gameBoard.board[row][c] = ship.symbol;
            }
            break;
        case VERTICAL:
            for(r = row; r < (ship.length + row); r++)
            {
                player->gameBoard.board[r][col] = ship.symbol;
            }
            break;
    }
}

void manualShipPlace (Player * player)
{
	  int shipNum;
    int row;
    int col;
    char orient;

	bool valid = false;

	for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
		while (valid == false)
        {
			displayGameBoard (*player);

			printf ("Enter the row and col (e.g. 0 0) for the first cell of ship %s:\n", player->ships[shipNum].name);
			printf ("Row col ");
			scanf("%d %d", &row, &col);

			fflush(stdin);

			printf("What is the orientation for this ship? Enter H for horizontal, V for vertical\n");
			scanf("%c", &orient);
			orient = toupper(orient);

			printf("Checking row %d col %d orient %c...\n", row, col, orient);

			valid = isValid(*player, row, col, player->ships[shipNum].length, orient);

			if (valid)
            {
                placeShip(player, row, col, player->ships[shipNum], orient);
			}
			else
			{
				valid = false;
				printf ("Invalid, try again\n");
			}
        }

        valid = false;
	}
}

void randomShipPlace (Player * player)
{
	int shipNum;
    int row;
    int col;
    int const DIR = 2;
    int const H = 0;
    int const V = 1;
    char orient;
    int o;

	bool valid = false;

	fflush (stdin);

	for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
    {
		while (valid == false)
        {
			row = (rand() % ROWS);
			col = (rand() % COLS);

			o = (rand() % DIR);

			if(o == H)
                orient = HORIZONTAL;
            else if(o == V)
                orient = VERTICAL;

			valid = isValid(*player, row, col, player->ships[shipNum].length, orient);

			if (valid)
            {
                placeShip(player, row, col, player->ships[shipNum], orient);
			}
			else
			{
				valid = false;
			}
        }

        valid = false;
	}
}

void playGame(Player *playerOne, Player *playerTwo)
{
    int currentPlayer = PLAYER1;
    Location target;

    while (true)
    {
        switch (currentPlayer)
        {
        case PLAYER1:
            printf("%s's turn\n", playerOne->name);
            displayGameBoard(*playerOne);
            target = getTarget(*playerOne);
            checkShot(playerTwo, target);
            break;

        case PLAYER2:
            printf("%s's turn\n", playerTwo->name);
            target = getRandomTarget();
            checkShot(playerOne, target);
            break;
        }
        currentPlayer = switchPlayer(currentPlayer);
        clearScreen();
    }
}

int switchPlayer(int currentPlayer)
{
    if (currentPlayer == PLAYER1)
    {
        return PLAYER2;
    }
    else if (currentPlayer == PLAYER2)
    {
        return PLAYER1;
    }
}

Location getTarget(Player player)
{
    Location target;
    fflush(stdin);
    printf("%s enter Target as row and col (ex. 3 4): ", player.name);
    scanf("%d %d", &target.row, &target.column);
    fflush(stdin);
    return target;

}

Location getRandomTarget()
{
    Location target;
    target.row = (rand() % ROWS);
    target.column = (rand() % COLS);
    return target;

}

void checkShot(Player *player, Location target)
{
    char symbol = player->gameBoard.board[target.row][target.column];

    switch(symbol)
    {
    case WATER:
        printf("row %d col %d was a miss!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, MISS, symbol);
        break;
    case CARRIER:
        printf("row %d col %d was a hit!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, HIT, symbol);
        break;
    case BATTLESHIP:
        printf("row %d col %d was a hit!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, HIT, symbol);
        break;
    case CRUISER:
        printf("row %d col %d was a hit!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, HIT, symbol);
        break;
    case SUBMARINE:
        printf("row %d col %d was a hit!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, HIT, symbol);
        break;
    case DESTROYER:
        printf("row %d col %d was a hit!\n", target.row, target.column);
        getchar();
        updatePlayerData(player, target, HIT, symbol);
        break;
    case HIT:
        printf("Already guessed that location, lost turn!\n");
        getchar();
    case MISS:
        printf("Already guessed that location, lost turn!\n");
        getchar();
    }
}

void updatePlayerData(Player *player, Location location, char result, char ship)
{
     player->gameBoard.board[location.row][location.column] = result;

     if (result == HIT)
     {
         checkShips(player, location, ship);
     }
}

void checkShips(Player *player, Location location, char ship)
{
    const int battleshipIdx=0;
    const int carrierIdx=1;
    const int cruiserIdx=2;
    const int destroyerIdx=3;
    const int submarineIdx=4;

    int sunkCount = 0;
    int shipNum;

    //for (shipNum = 0; shipNum < NUM_SHIPS; shipNum--)
    switch(ship)
    {
    case BATTLESHIP:
        player->ships[battleshipIdx].length--;
        if (player->ships[battleshipIdx].length == 0)
        {
            printf("%s's BATTLESHIP is sunk!\n", player->name);
        }
        getchar();
        break;
    case CARRIER:
        player->ships[carrierIdx].length--;
        if(player->ships[carrierIdx].length == 0)
        {
            printf("%s's CARRIER is sunk!\n", player->name);
        }
        getchar();
        break;
    case CRUISER:
        player->ships[cruiserIdx].length--;
        if(player->ships[cruiserIdx].length == 0)
        {
            printf("%s's CRUISER is sunk!\n", player->name);
        }
        getchar();
        break;
    case DESTROYER:
        player->ships[destroyerIdx].length--;
        if(player->ships[destroyerIdx].length == 0)
        {
            printf("%s's DESTROYER is sunk!\n", player->name);
        }
        getchar();
        break;
    case SUBMARINE:
        player->ships[submarineIdx].length--;
        if(player->ships[submarineIdx].length == 0)
        {
            printf("%s's SUBMARINE is sunk!\n", player->name);
        }
        getchar();
        break;
    }
    for (shipNum = 0; shipNum < NUM_SHIPS; shipNum++)
     {
       if(player->ships[shipNum].length == 0)
       {
           sunkCount == sunkCount + 1;
       }
       else if(sunkCount == NUM_SHIPS)
       {
           endGame(*player);
       }

     }
}



void endGame(Player player)
{
    printf("%s HAS LOST THE GAME!\n", player.name);
    getchar();
    exit(0);
}
