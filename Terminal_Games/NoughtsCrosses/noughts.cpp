// Noughts and Crosses Game

#include <iostream> 
#include <vector>
#include <cstdlib>
#include <ctime> 

using namespace std;

// Setup the game
int BeginPlay()
{
    cout << "\nNoughts and Crosses Game" << endl;
    cout << "===================================" << endl; 
    int NumOfPlayers {}; 
    do
    { 
        cout << "1.........Single Player (Player vs AI)" << endl;
        cout << "2.........Two Players (Player1 vs Player2)" << endl; 
        cout << "0.........Quit Game" << endl;
        cout << "===================================" << endl; 
        cout << "How many players: ";
        cin >> NumOfPlayers; 

    } while (NumOfPlayers != 1 && NumOfPlayers != 2 && NumOfPlayers != 0);
    
    
    return NumOfPlayers;
}


// Function that displays the current game board
void DisplayBoard (const vector <char> turns)
{
    cout << endl;
    for ( int i {1}; i <= 9; ++i)
    {
        if ((i % 3 == 0) && i != 9)
        {
            if( turns.at(i-1) == 'U')
            {
                cout << " " << endl; 
                cout << "----------" << endl;
            }
            else
            { 
                cout << turns.at(i-1) << endl;
                cout << "----------" << endl;
            }
        }
        else if (i ==9)
        {
            if (turns.at(i-1) == 'U')
            {
                cout << " " << endl;
            }
            else
            {
                cout << turns.at(i-1) << endl;
            }
        }
        else
        {
            if ( turns.at(i-1) == 'U')
             {
                cout << " " << " | "; 
            }
            else
            {
                cout << turns.at(i-1) << " | ";
            }
        }
    }
    cout << endl;
}


// Function that determines if a player has won
bool PlayerWon (vector <int> PlayerTurns)
{
    
    if (PlayerTurns.at(0) == 1 && PlayerTurns.at(1) == 1 && PlayerTurns.at(2) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(0) == 1 && PlayerTurns.at(3) == 1 && PlayerTurns.at(6) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(0) == 1 && PlayerTurns.at(4) == 1 && PlayerTurns.at(8) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(1) == 1 && PlayerTurns.at(4) == 1 && PlayerTurns.at(7) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(2) == 1 && PlayerTurns.at(5) == 1 && PlayerTurns.at(8) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(2) == 1 && PlayerTurns.at(4) == 1 && PlayerTurns.at(6) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(3) == 1 && PlayerTurns.at(4) == 1 && PlayerTurns.at(5) == 1)
    {
        return true; 
    }
    if (PlayerTurns.at(6) == 1 && PlayerTurns.at(7) == 1 && PlayerTurns.at(8) == 1)
    {
        return true; 
    }

    return false;
}


// Function used by the AI to determine where it should move, given the current state. 
int Chooser (vector <int> Spaces, vector <char> GameState)
{
    srand(time(NULL));
    bool LoopStop {false};
    do
    {
        if (Spaces.size() != 0)
        {
            int pos {Spaces.at(rand() % Spaces.size())}; 
            if (GameState.at(pos-1) == 'U')
            {
                return pos;
            }
            else
            {
                for (int i {0}; i < Spaces.size(); ++i)
                {
                    if (Spaces.at(i) == pos)
                    {
                        Spaces.erase(Spaces.begin() + i);
                    }
                }
            }
        }
        else
        {
            LoopStop = true;
        }

    } while (!LoopStop);

    return 0;
}


// This is the AI decision for where to place its mark
int AIDecision (vector <int> Player1Turns, vector <int> Player2Turns, vector <char> GameState, const int Difficulty, const char player1, const char player2)
{
    srand(time(NULL));

    // Win if possible
    vector <int> NewPlayer2Turns {Player2Turns}; 
    for (int i {1}; i <= 9; ++i)
    {
        NewPlayer2Turns.at(i-1) = 1;
        if (PlayerWon(NewPlayer2Turns) && GameState.at(i-1) == 'U')
        {
            return i;
        }
        else
        {
            NewPlayer2Turns = Player2Turns; 
        }
    }

    // Prevent Loss
    vector <int> NewPlayer1Turns {Player1Turns};
    for (int i {1}; i <= 9; ++i)
    {
        NewPlayer1Turns.at(i-1) = 1;
        if (PlayerWon(NewPlayer1Turns) && GameState.at(i-1) == 'U')
        {
            return i;
        }
        else
        {
            NewPlayer1Turns = Player1Turns; 
        }
    }

    if (Difficulty >= 3)
    {
        // Choose moves tactically
        if (GameState.at(0) == player1)
        {
            vector <int> Diags {2,4,5};
            int pos {Chooser(Diags, GameState)}; 
            if (pos != 0)
            {
                return pos;
            }
        }
        if (GameState.at(2) == player1)
        {
            vector <int> Diags {2,5,6};
            int pos {Chooser(Diags, GameState)}; 
            if (pos != 0)
            {
                return pos;
            }
        }
        if (GameState.at(6) == player1)
        {
            vector <int> Diags {4,5,8};
            int pos {Chooser(Diags, GameState)}; 
            if (pos != 0)
            {
                return pos;
            }
        }
        if (GameState.at(8) == player1)
        {
            vector <int> Diags {5,6,8};
            int pos {Chooser(Diags, GameState)}; 
            if (pos != 0)
            {
                return pos;
            }
        }
    }

    if (Difficulty >= 2)
    {
        // Choose corners if available. 
        vector <int> Corners {1,3,7,9};
        int pos {Chooser(Corners, GameState)}; 
        if (pos != 0)
        {
            return pos;
        }


        // Choose Middle if Available
        vector <int> Middle {2,4,5,6,8};
        pos = Chooser(Middle, GameState);
        if ( pos != 0)
        {
            return pos;
        }
    }
        
    // if no tactical moves are available then randomnly pick a move
    return ((rand() % 9) + 1);

}


// Function that plays the game
int GamePlay (const char player1, const char player2, const string name1, const string name2, const int Difficulty)
{
    srand(time(NULL));

    // Prepare gameplay trackers
    int PlayerTurn {(rand() % 2) + 1}; 
    vector <int> Player1Turns (9); 
    vector <int> Player2Turns (9);
    vector <char> GameState {'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U'};
    bool GameOver {false}; 
    int winner {};

    // Begin game loop
    do
    {
        if (PlayerTurn == 1)
        {
            int pos {};
            cout << name1 << ": ";
            cin >> pos; 
            if (pos > 9 || pos < 1)
            {
                cout << "Please input a position 1-9" << endl; 
                continue;
            }
            if (Player1Turns.at(pos-1) == 0 && Player2Turns.at(pos-1) == 0)
            {
                Player1Turns.at(pos-1) = 1;
                GameState.at(pos-1) = player1;
                if(PlayerWon(Player1Turns))
                {
                    GameOver = true;
                    winner = 1;
                    DisplayBoard(GameState);
                    break;
                }

                // check that there are still moves available
                int count {0};
                for (auto x: GameState)
                {
                    if (x == 'U')
                    {
                        count = count + 1; 
                    }
                }
                if ( count != 0)
                {
                    DisplayBoard(GameState);
                    PlayerTurn = 2;
                }
                else
                {
                    winner = 3; 
                    DisplayBoard(GameState);
                    break;
                }
                
            }
        }

        if (PlayerTurn == 2)
        {
            int pos {};
            if (name2 == "TuRiNg")
            {
                pos = AIDecision(Player1Turns, Player2Turns, GameState, Difficulty, player1, player2);
            }
            else if (name2 != "TuRiNg")
            {
                cout << name2 << ": ";
                cin >> pos; 
            }
            if (pos > 9 || pos < 1)
            {
                cout << "Please input a position 1-9" << endl; 
                continue;
            }

            if (Player1Turns.at(pos-1) == 0 && Player2Turns.at(pos-1) == 0)
            {
                Player2Turns.at(pos-1) = 1;
                GameState.at(pos-1) = player2; 
                if(PlayerWon(Player2Turns))
                {
                    GameOver = true;
                    winner = 2;
                    DisplayBoard(GameState);
                    break;
                }
                
                int count {0};
                for (auto x: GameState)
                {
                    if (x == 'U')
                    {
                        count = count + 1; 
                    }
                }
                if ( count != 0)
                {
                    DisplayBoard(GameState);
                    PlayerTurn = 1;
                }
                else
                {
                    winner = 3; 
                    DisplayBoard(GameState);
                    break;
                }
            }
        }

    } while (!GameOver);

    return winner;
    
}


// Setting up the game with the number of players
void Noughts (const int players) 
{
    int winner {};

    if (players == 1)
    {
        string name {}; 
        cout << "Enter name for Player: "; 
        cin >> name; 

        cout << "\nHere is the board: " << endl; 
        vector <char> board {'1','2','3','4','5','6','7','8','9'}; 
        DisplayBoard(board);

        cout << "The Player will place their mark by using the corresponding number (1-9) on the board" << endl;

        cout << "\nIs " << name << " playing as noughts 'O' or crosses 'X'? "; 
        char OorX {}; 
        cin >> OorX; 

        char player1 {}; 
        char player2 {}; 

        if (OorX == 'O' || OorX == 'o')
        {
            player1 = 'O';
            player2 = 'X';
        }
        else
        {
            player1 = 'X';
            player2 = 'O';
        }

        cout << endl;
        cout << "Select Difficulty (1-Easy, 2-Medium, 3-Hard): ";
        int Difficulty {1}; 
        cin >> Difficulty; 

        cout << endl;
        cout << "Let's play!" << endl;
        cout << "=====================" << endl; 

        // Play the game
        winner = GamePlay(player1, player2, name, "TuRiNg", Difficulty); 

        // Display who won the game
        if (winner == 1)
        {
            cout << name << " is the winner!" << endl;
        }

        if (winner == 2)
        {
            cout << "Sorry, you lost." << endl;
        }

        if (winner == 3)
        {
            cout << "It's a draw!" << endl; 
        }
    }


    if (players == 2)
    {
        string name1 {}, name2{}; 
        cout << "Enter name for Player 1: "; 
        cin >> name1; 
        cout << "Enter name for Player 2: "; 
        cin >> name2; 

        cout << "\nHere is the board: " << endl; 
        vector <char> board {'1','2','3','4','5','6','7','8','9'}; 
        DisplayBoard(board);
        
        
        cout << "Players will place their mark by using the corresponding number (1-9) on the board" << endl; 

        cout << "\nIs " << name1 << " playing as noughts 'O' or crosses 'X'? "; 
        char OorX {}; 
        cin >> OorX; 

        char player1 {}; 
        char player2 {}; 

        if (OorX == 'O' || OorX == 'o')
        {
            player1 = 'O';
            player2 = 'X';
        }
        else
        {
            player1 = 'X';
            player2 = 'O';
        }

        cout << endl;
        cout << "Let's play!" << endl;
        cout << "=====================" << endl; 

        winner = GamePlay(player1, player2, name1, name2, 1); 

        if (winner == 1)
        {
            cout << name1 << " is the winner!" << endl;
        }

        if (winner == 2)
        {
            cout << name2 << " is the winner!" << endl;
        }

        if (winner == 3)
        {
            cout << "It's a draw!" << endl; 
        }
    }

}


int main () 
{
    int GameSetting {BeginPlay()}; 

    Noughts(GameSetting); 

    return 0;
}

