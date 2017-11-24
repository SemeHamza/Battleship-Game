#include <iostream>

using namespace std;

const int ROW = 5, COL = 5;
int destroyerHits1 = 0, submarineHits1 = 0, cruiserHits1 = 0, battleshipHits1 = 0;
int destroyerHits2 = 0, submarineHits2 = 0, cruiserHits2 = 0, battleshipHits2 = 0;

void initializeBoard(char [][COL]);//To initialize the arrays with " "
void shipPosition(char [][COL]);//To let the players arrange the ships
bool hitOrMiss1(char [][COL], char [][COL]);//To let each player 'shoot' and determine whether each shot is a hit or miss
bool hitOrMiss2(char [][COL], char [][COL]);
void displayBoard(char [][COL]);//To display the 'tracking grid' of each player after every shot
void testSink1(char [][COL], char [][COL]);//To signal when a specific ship 'sinks' - returns ' ' when sink  does not happen, 'D' when a Destroyer sinks, 'S' when a Submarine sinks, and so on.
void testSink2(char [][COL], char [][COL]);
int win(char [][COL], char [][COL]);//To determine when the game ends and, also, the winner - returns 0 when nobody has yet won, returns 1 when player 1 wins, returns 2 when player 2 wins
void inputValidation(char [][COL], int &, int &);

int main()
{
    char primary1[ROW][COL];
    char primary2[ROW][COL];
    char tracking1[ROW][COL];
    char tracking2[ROW][COL];
    int player = 0,  winner = 0;
    bool hit = false;
    char sink = ' ';

    initializeBoard(primary1);
    initializeBoard(primary2);
    initializeBoard(tracking1);
    initializeBoard(tracking2);

    cout << "\t\tBATTLESHIP GAME!\n\n";

    cout << "\tPLAYER 1\n";
    cout << "Arrange your fleets  secretly!\n\n";
    displayBoard(primary1);
    shipPosition(primary1);

    cout << "\n\tPLAYER 2\n";
    cout << "Arrange your fleets  secretly!\n\n";
    displayBoard(primary2);
    shipPosition(primary2);

    do
    {
       player += 1;

       if (player % 2 == 1)//To let the players take turns making 'shots'
       {
           cout << "\n\tPLAYER 1\n";
           cout << "Make a shot!\n\n";

           displayBoard(tracking1);

           hit = hitOrMiss1(primary2, tracking1);

           cout << endl;
           displayBoard(tracking1);

           if (hit == true)
               cout << "It is a hit!\n\n";
           else
               cout << "It is a miss!\n\n";

           testSink1(primary2, tracking1);
       }
       else
       {
           cout << "\n\tPLAYER 2\n";
           cout << "Make a shot!\n\n";

           displayBoard(tracking2);

           hit = hitOrMiss2(primary1, tracking2);

           cout << endl;
           displayBoard(tracking2);

           if (hit == true)
               cout << "It is a hit!\n\n";
           else
               cout << "It is a miss!\n\n";

           testSink2(primary1, tracking2);
       }

       winner = win(tracking1, tracking2);

       if (winner == 1)
           cout << "\n\tGAME END! Player " << winner << " won.\n";
       else if (winner == 2)
           cout << "\n\tGAME END! Player " << winner << " won.\n";
    }
    while (winner == 0);

    return 0;
}

void initializeBoard(char array[][COL])
{
    for (int ir = 0; ir < ROW; ir++)
    {
        for (int ic = 0; ic < COL; ic++)
        {
            array[ir][ic] = ' ';
        }
    }
}

void displayBoard(char array[][COL])
{
    cout << "    1   2   3   4   5  \n"
         << "  -------------------- \n";

    for (int ir = 0; ir < ROW; ir++)
    {
        cout << ir + 1 << " | ";

        for (int ic = 0; ic < COL; ic++)
        {
            cout << array[ir][ic] << " | ";
        }
        cout << "\n  -------------------- \n";
    }
}


void shipPosition(char array[][COL])// Needs input validation (overlap, stepping out of bound and unallowed ship orientations)
{
    int row, col;

    cout << "\n\tPosition your Destroyer!\n";
    for (int i = 0; i < 2; i++)
    {
        cout << "Choose a spot for square #" << i + 1 << " (enter row# followed by column#): ";
        cin >> row >> col;
        inputValidation(array,  row, col);
        array[row - 1][col - 1] = 'D';
    }

    cout << endl;
    displayBoard(array);

    cout << "\tPosition your Submarine!\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "Choose a spot for square #" << i + 1 << " (enter row# followed by column#): ";
        cin >> row >> col;
        inputValidation(array,  row, col);
        array[row - 1][col - 1] = 'S';
    }

    cout << endl;
    displayBoard(array);

    cout << "\tPosition your Cruiser!\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "Choose a spot for square #" << i + 1 << " (enter row# followed by column#): ";
        cin >> row >> col;
        inputValidation(array,  row, col);
        array[row - 1][col - 1] = 'C';
    }

    cout << endl;
    displayBoard(array);

    cout << "\tPosition your Battleship!\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "Choose a spot for square #" << i + 1 << " (enter row# followed by column#): ";
        cin >> row >> col;
        inputValidation(array,  row, col);
        array[row - 1][col - 1] = 'B';
    }
}

void inputValidation(char array[][COL], int &row, int &col)
{
   while (row < 1 || row > 5 || col < 1 || col > 5)
   {
       cout << "Error! Enter a number between 1 and 5 (inclusive).\n";
       cout << "Choose a spot again (enter row# followed by column#): ";
       cin >> row >> col;
   }
   while (array[row - 1][col - 1] != ' ')
   {
       cout << "Error! The square you chose is already occupied.\n";
       cout << "Choose a different square (enter row# followed by column#): ";
       cin >> row >> col;
       while (row < 1 || row > 5 || col < 1 || col > 5)
       {
       cout << "Error! Enter a number between 1 and 5 (inclusive).\n";
       cout << "Choose a spot again (enter row# followed by column#): ";
       cin >> row >> col;
       }
   }
}

bool hitOrMiss1(char primary[][COL], char tracking[][COL])
{
    int row, col;
    bool hit;

    cout << "Choose a target square (enter row# followed by column#): ";
    cin >> row >> col;
    inputValidation(tracking, row, col);

    if (primary[row - 1][col - 1] == ' ')
    {
        tracking[row - 1][col - 1] = 'M';
        hit = false;
    }
    else if (primary[row - 1][col - 1] == 'D')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        destroyerHits1  += 1;
    }
    else if (primary[row - 1][col - 1] == 'S')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        submarineHits1  += 1;
    }
    else if (primary[row - 1][col - 1] == 'C')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        cruiserHits1 += 1;
    }
    else if (primary[row - 1][col - 1] == 'B')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        battleshipHits1 += 1;
    }

    return hit;
}

bool hitOrMiss2(char primary[][COL], char tracking[][COL])
{
    int row, col;
    bool hit;

    cout << "Choose a target square (enter row# followed by column#): ";
    cin >> row >> col;
    inputValidation(tracking, row, col);

    if (primary[row - 1][col - 1] == ' ')
    {
        tracking[row - 1][col - 1] = 'M';
        hit = false;
    }
    else if (primary[row - 1][col - 1] == 'D')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        destroyerHits2  += 1;
    }
    else if (primary[row - 1][col - 1] == 'S')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        submarineHits2  += 1;
    }
    else if (primary[row - 1][col - 1] == 'C')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        cruiserHits2 += 1;
    }
    else if (primary[row - 1][col - 1] == 'B')
    {
        tracking[row - 1][col - 1] = 'H';
        hit = true;
        battleshipHits2 += 1;
    }

    return hit;
}



void testSink1(char primary[][COL], char tracking[][COL])
{
    if (destroyerHits1 == 2)
    {
        cout << "You have sunk opponent's destroyer!\n";
    }
    if (submarineHits1 == 3)
    {
        cout << "You have sunk opponent's submarine!\n";
    }
    if (cruiserHits1 == 3)
    {
         cout << "You have sunk opponent's cruiser!\n";
    }
    if (battleshipHits1 == 4)
    {
        cout << "You have sunk opponent's battleship!\n";
    }
}

void testSink2(char primary[][COL], char tracking[][COL])
{
    if (destroyerHits2 == 2)
    {
        cout << "You have sunk opponent's destroyer!\n";
    }
    if (submarineHits2 == 3)
    {
        cout << "You have sunk opponent's submarine!\n";
    }
    if (cruiserHits2 == 3)
    {
         cout << "You have sunk opponent's cruiser!\n";
    }
    if (battleshipHits2 == 4)
    {
        cout << "You have sunk opponent's battleship!\n";
    }
}

int win(char tracking1[][COL], char tracking2[][COL])
{
    int totalHits1 = 0;
    int totalHits2 = 0;

    for (int ir = 0; ir < ROW; ir += 1)
    {
        for (int ic = 0; ic < COL; ic += 1)
        {
             if (tracking1[ir][ic] ==  'H')
                 totalHits1 += 1;
        }
    }
    for (int ir = 0; ir < ROW; ir += 1)
    {
        for (int ic = 0; ic < COL; ic += 1)
        {
             if (tracking2[ir][ic] == 'H')
                 totalHits2 += 1;
        }
    }

    if (totalHits1 == 12)
        return 1;
    else if (totalHits2 == 12)
        return 2;
    else
        return 0;
}


