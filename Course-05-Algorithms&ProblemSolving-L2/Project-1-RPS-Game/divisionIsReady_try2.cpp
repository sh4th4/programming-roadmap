#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

enum enChoice
{
    Stone = 1,
    Scissor = 2,
    Paper = 3
};

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

struct stRound
{
    short RoundNumber; // ترتيب الجولة كل شوية تزيد واحد
    enChoice PlayerChoice;
    enChoice ComputerChoice;
    enWinner Winner;
};

struct stGameResults
{
    short TotalRounds; // العدد الكلي للجولات ثابت طوال اللعبة ويستخدم لانهاء اللعبة لما يتساوى
                       // RoundNumber معTotalRounds
    short PlayerWins;
    short ComputerWins;
    short DrawTime;
    enWinner GameWinner;
};

short ReadRoundCount()
{
    short Number = 0;
    cout << "How many Round 1 to 10? " << endl;
    cin >> Number;
    return Number;
}

enChoice ReadPlayerChoice()
{
    int num = 0;
    cout << "Enter Your Choice,[1]Stone , [2]Scissor, [3]Paper? " << endl;
    cin >> num;

    return (enChoice)num;
}

string ChoiceToString(enChoice Choice)
{
    if (Choice == enChoice::Stone)
        return "Stone";
    else if (Choice == enChoice::Scissor)
        return "Scissor";
    else
        return "Paper";
}

int randomNumber(int from, int to)
{
    // function to generate a random number.
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

enChoice GetComputerChoice()
{
    return (enChoice)randomNumber(1, 3); // يعني ما طلع معك من رقم حوله لأينم
}

enWinner GetCurrentRoundWinner(stRound Round)
{ // تحديد الفائز بالجولة
    if (Round.PlayerChoice == Round.ComputerChoice)
        return enWinner::Draw;
    else if (Round.PlayerChoice == enChoice::Stone && Round.ComputerChoice == enChoice::Scissor)
        return enWinner::Player;
    else if (Round.PlayerChoice == enChoice::Scissor && Round.ComputerChoice == enChoice::Paper)
        return enWinner::Player;
    else if (Round.PlayerChoice == enChoice::Paper && Round.ComputerChoice == enChoice::Stone)
        return enWinner::Player;
    else
        return enWinner::Computer;
}

string WinnerToString(enWinner Winner)
{
    if (Winner == enWinner::Player)
        return "You Win";
    else if (Winner == enWinner::Computer)
        return "Computer Win";
    else
        return "Draw";
}

enWinner GetGameWinner(stGameResults GameResults)
{
    if (GameResults.PlayerWins == GameResults.ComputerWins)
    {

        return enWinner::Draw;
    }

    else if (GameResults.PlayerWins > GameResults.ComputerWins)
    {

        return enWinner::Player;
    }

    else
    {

        return enWinner::Computer;
    }
}

stRound FillCurrentRoundData(short CurrentRound)
{ // ترجع معلومات الجولة
    stRound RoundData;
    RoundData.PlayerChoice = ReadPlayerChoice();
    RoundData.ComputerChoice = GetComputerChoice();
    RoundData.RoundNumber = CurrentRound;                // لانه كل سع بتسأله كم يشتي جولةReadRoundCount() ما ينفعش
    RoundData.Winner = GetCurrentRoundWinner(RoundData); // هذي الدالة معتمدة على البيانات من الستراكت عشان تعرف من الفائز
    return RoundData;
}

void PrintCurrentRound(stRound RoundData)
{
    cout << "\n----------------------" << endl;
    cout << "Player Choice: " << ChoiceToString(RoundData.PlayerChoice) << endl;
    cout << "Computer Choice: " << ChoiceToString(RoundData.ComputerChoice) << endl;
    cout << "The Winner: " << WinnerToString(RoundData.Winner) << endl;
    cout << "----------------------" << endl;
}

stGameResults FillGameResults(short TotalRounds, short PlayerWins, short ComputerWins, short DrawTime)
{
    stGameResults GameResults;

    GameResults.TotalRounds = TotalRounds;
    GameResults.PlayerWins = PlayerWins;
    GameResults.ComputerWins = ComputerWins;
    GameResults.DrawTime = DrawTime;

    GameResults.GameWinner = GetGameWinner(GameResults);

    return GameResults;
}

void PrintGameOver(stGameResults GameResults)
{
    cout << "\n--------------------------" << endl;
    cout << "--------Game Over---------" << endl;
    cout << "You Wins: " << GameResults.PlayerWins << endl;
    cout << "Computer Wins: " << GameResults.ComputerWins << endl;
    cout << "Draw Time: " << GameResults.DrawTime << endl;
    cout << "Game Winner: " << WinnerToString(GameResults.GameWinner) << endl;
    cout << "--------------------------" << endl;
}

char ResetGame()
{
    char answer = 'n';
    cout << "Do you want to play again? " << endl;
    cin >> answer;
    return answer;
}

void StartGame()
{
    char PlayAgain = 'n';

    do
    {
        short PlayerWinsCount = 0;
        short ComputerWinsCount = 0;
        short DrawTimeCount = 0;

        int Round = ReadRoundCount();
        for (int i = 0; i < Round; i++)
        {
            cout << "Round[" << i + 1 << "]: \n";

            stRound CurrentRoundData = FillCurrentRoundData(i + 1);

            PrintCurrentRound(CurrentRoundData);

            if (CurrentRoundData.Winner == enWinner::Player)
            {
                system("color 2F");
                PlayerWinsCount++;
            }
            else if (CurrentRoundData.Winner == enWinner::Computer)
            {
                system("color 4F");
                ComputerWinsCount++;
            }

            else
            {
                system("color 6F");
                DrawTimeCount++;
            }
        }

        stGameResults GameResults = FillGameResults(Round, PlayerWinsCount, ComputerWinsCount, DrawTimeCount);
        system("cls");
        PrintGameOver(GameResults);

        PlayAgain = ResetGame();

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}