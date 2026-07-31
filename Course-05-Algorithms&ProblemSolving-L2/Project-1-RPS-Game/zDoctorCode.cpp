#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

enum enWinner
{
    Player = 1,
    Computer = 2,
    Draw = 3
};

enum enGameChoice
{
    Stone = 1,
    Paper = 2,
    Scissors = 3
};

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner; 
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWinTime = 0;
    short ComputerWinTime = 0;
    short DrawTime = 0;
    enWinner GameWinner;    // return number from enum
    string WinnerName = ""; // convert number of enum to string
};

int randomNumber(int from, int to)
{
    // function to generate a random number.
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[] = {"Player", "Computer", "No Winner"};
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        return enWinner::Player;
    }
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[] = {"Stone", "Paper", "Scissors"};
    return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        break;
    case enWinner::Draw:
        system("color 2F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "________________Round Info_____________________" << endl;
    cout << "________________Round[" << RoundInfo.RoundNumber << "]:" << endl;
    cout << "Player Choice   : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    : " << RoundInfo.WinnerName << endl;
}

enWinner WhoWonTheGame(short PlayerWinTime, short ComputerWinTime)
{
    if (PlayerWinTime > ComputerWinTime)
        return enWinner::Player;
    else if (PlayerWinTime < ComputerWinTime)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(int GameRound, short PlayerWinTimes, short ComputerWinTime, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRound;
    GameResults.PlayerWinTime = PlayerWinTimes;
    GameResults.ComputerWinTime = ComputerWinTime;
    GameResults.DrawTime = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTime);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enGameChoice ReadPlayerChoice()
{
    short Choice = 0;
    do
    {
        cout << "Enter Your Choice:[1]Stone , [2]Paper , [3]Scissors" << endl;
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)randomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{

    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "]: Begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds , PlayerWinTimes , ComputerWinTimes , DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void showGameOverScreen()
{
    cout << Tabs(2) << "-----------------------------------------------\n\n";
    cout << Tabs(2) << "       ***G a m e O v e r***\n\n";
    cout << Tabs(2) << "-----------------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "------------------[Game Results]----------------\n\n";
    cout << Tabs(2) << "Player Win Times  : " << GameResults.PlayerWinTime << endl;
    cout << Tabs(2) << "Computer Win Times: " << GameResults.ComputerWinTime << endl;
    cout << Tabs(2) << "Draw Times        : " << GameResults.DrawTime << endl;
    cout << Tabs(2) << "Final Winner      : " << GameResults.WinnerName << endl;

    SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;
    do
    {
        cout << "How Many Round Do you Want? " << endl;
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        showGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl
             << Tabs(3) << "Do you want to play Again? Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}