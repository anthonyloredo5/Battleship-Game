#ifndef BATTLESHIPHEADER_H_INCLUDED
#define BATTLESHIPHEADER_H_INCLUDED

    #define MANUAL 49 //All of the global constant variables
    #define RANDOM 50
    #define ROWS 10
    #define COLS 10
    #define WATER '~'
    #define PLAYERS 2
    #define PLAYER1 0
    #define PLAYER2 1
    #define PLAYERONE "Player 1"
    #define PLAYERTWO "Player 2"
    #define NUM_SHIPS 5
    #define HORIZONTAL 'H'
    #define VERTICAL 'V'
    #define CARRIER 'C'
    #define BATTLESHIP 'B'
    #define CRUISER 'R'
    #define SUBMARINE 'S'
    #define DESTROYER 'D'
    #define CARRIER_SZ 5
    #define BATTLESHIP_SZ 4
    #define CRUISER_SZ 3
    #define SUBMARINE_SZ 3
    #define DESTROYER_SZ 2
    #define HIT 'X'
    #define MISS '.'

    typedef struct gameboard
    {
        char board[ROWS][COLS];
    }GameBoard;

    typedef struct location
    {
        int row;
        int column;
    }Location;

    typedef struct ship
    {
        char name[11];
        char symbol;
        int length;
        bool sunk;
        Location start;
    }Ship;

    typedef struct human
    {
        char name[20];
        GameBoard gameBoard;
        Ship ships [NUM_SHIPS];
    }Player;//end of struct declarations

    enum ships {battleship=0, carrier, cruiser, destroyer, submarine};

    void clearScreen();
    void welcomeScreen ();
    int displayMenu();
    void displayGameBoard(Player player);
    void initializePlayer(Player * player, char * name);
    void initializeBoard(Player * player);
    void initializeShips(Player * player);
    void displayShips(Player player);
    void manualShipPlace (Player * player);
    bool isValid (Player player, int row, int col, int length, char orient);
    void placeShip(Player * player, int row, int col, Ship ship, char orient);
    void randomShipPlace (Player * player);
    void playGame(Player *playerOne, Player *playerTwo);
    int switchPlayer(int currentPlayer);
    Location getTarget(Player player);
    Location getRandomTarget();
    void checkShot(Player *player, Location target);
    void updatePlayerData(Player *player, Location location, char result, char ship);
    void checkShips(Player *player, Location location, char ship);
    void endGame(Player player);

#endif // BATTLESHIPHEADER_H_INCLUDED
