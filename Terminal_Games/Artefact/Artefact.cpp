#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty)
{   
    if (Difficulty == 4)
    {
        // Print intro text explaining context for the game
    std::cout << "\n\nYou are an Alcurist of the Arcanum. Whilst exploring, you discover an ancient artefact belonging to the Creators...\n";
    std::cout << R"(       
           _----------_,
         ,"__   ---   _-:,
        /    ""--_--""    \
       /  \      |      /  \
      /    \     |     /    \
     /,     \   _'_   /     /:                 
     ! -,    _-"   "-_    ,  :
     \   -_-"         "-_/   ;
      \   \             /   /
       \   \    ---    /   /'
        '.  \         /  ,'
          "-_\_______/_-"
    )" << '\n';
    }
    
    std::cout << "\n\nThe artefact has " << Difficulty << " notches to solve.\n";
    std::cout << "You need to find the correct code to unlock the notch and release the flux trapped within...\n\n";
}

bool PlayGame(int Difficulty)
{
    PrintIntroduction(Difficulty);

    // Randomonly generate three number code, with difficulty reflecting how large the numbers can be
    const int CodeA = rand() % (6 - Difficulty) + (5 - Difficulty);
    const int CodeB = rand() % (6 - Difficulty) + (5 - Difficulty);
    const int CodeC = rand() % (6 - Difficulty) + (5 - Difficulty);


    const int CodeSum = CodeA + CodeB + CodeC;
    const int CodeProduct = CodeA * CodeB * CodeC;

    
    // Print the explanation of the game
    std::cout << "+There are three numbers in the code\n";
    std::cout << "+The numbers should add up to: " << CodeSum;
    std::cout << "\n+The product of the numbers should be: " << CodeProduct << std::endl;


    // Player enters their guess for the code
    int GuessA, GuessB, GuessC;
    std::cin >> GuessA >> GuessB >> GuessC;
    
    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;


    // Check if player guess is correct and print win/lose messages to terminal
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        if (Difficulty == 4)    // message for completing notch 1
        {
            std::cout << "\n*** You hear a soft click...the first notch opens in your hand...A melodic voice echoes from within the artefact... it says...\n";
            std::cout << "\"From Sun and Earth, are all things born.\" ***";
            return true;
        }

        if (Difficulty == 3)    // message for completing notch 2
        {
            std::cout << "\n*** The second notch opens without resistance. The voice continues...\n";
            std::cout << "\"In Truth and Logic, the world is known.\" ***";
            return true;
        }

        if (Difficulty == 2)    // message for completing notch 3
        {
            std::cout << "\n*** The voice gets louder as the third notch clicks open. The voice echoes and vibrates as if rising from a deep cavern...\n";
            std::cout << "\"In Hope and Faith, are the Gods we find.\" ***";
            return true;
        }

        if (Difficulty == 1)    //message for completing the final notch
        {
            std::cout << "\n*** The fourth notch opens. A bright apparation bursts from the artefact. It is beautiful and bathed in pure white light...\n";
            std::cout << "\"We are all but servants, to the Arrow of Time.\" ***";
            return true;
        }
    }
    else
    {
        std::cout << "\n*** The notch remains locked. You think you hear something laughing at you from within. ***";
        return false;
    }

    return false;   // The control never reaches this line, but it tells the compilier that the function will stop. 
}



int main() 
{   
    srand(time(NULL));  // create new random sequence based on the time of day

    int LevelDifficulty = 4;  // Set level difficulty
    int const MinLevel = 1;

    while (LevelDifficulty >= MinLevel)    // loop game until complete
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear();    // Clear any errors relating to input
        std::cin.ignore();   // Discards the buffer

        if (bLevelComplete)
        {
            --LevelDifficulty;  // If level is complete, decrease remaining notches by 1
        }
        
    }
    
    std::cout << std::endl;
    std::cout << "\n*** With a melancholy sigh, the apparation and artefact disintegrate to dust. What remains of the artefact slips through your fingers...but the knowledge remains. ***\n";
    return 0;      
}