#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enOperation
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};

enum enLevels
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    Mix = 4
};

struct stResultData
{
    short NumberOfQuesions = 0;
    enLevels Levels;
    enOperation OpType;
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
};

int randomNumber(int from, int to)
{
    // function to generate a random number.
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

short HowManyQuesions()
{
    short num;
    do
    {
        cout << "How many Quesions do you want to answer? \n";
        cin >> num;
    } while (num < 0);
    return num;
}

enLevels QuesionsLevels()
{
    short num = 0;
    do
    {
        cout << "Enter Quesions Level [1]Easy ,[2]Medium ,[3]Hard ,[4]Mix ?\n";
        cin >> num;
    } while (num <= 0 || num > 4);
    return (enLevels)num;
}

enOperation QuesionsOpType()
{
    short Op = 0;
    cout << "Enter Operation Type [1]+ ,[2]- ,[3]* ,[4]/ ,[5]Mix ?\n";
    cin >> Op;
    return (enOperation)Op;
}

int Calculation(int num1, char operation, int num2)
{
    switch (operation)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    }
}

int GetLevelsGame(enLevels Levels)
{
    if (Levels == enLevels::Mix)
    {
        Levels = (enLevels)randomNumber(1, 3);
    }
    switch (Levels)
    {
    case enLevels::Easy:
        return randomNumber(1, 10);
    case enLevels::Med:
        return randomNumber(10, 50);
    case enLevels::Hard:
        return randomNumber(50, 100);
    }
}

int Number1Generation(enLevels Level)
{
    int number = GetLevelsGame(Level);
    return number;
}

char FactorGeneration(enOperation Factor)
{
    if (Factor == enOperation::MixOp)
    {
        Factor = (enOperation)randomNumber(1, 4);
    }
    switch (Factor)
    {
    case enOperation::Add:
        return '+';
    case enOperation::Sub:
        return '-';
    case enOperation::Mul:
        return '*';
    case enOperation::Div:
        return '/';
    }
}

string LevelsOfString(enLevels Level)
{
    string choice[] = {"Easy", "Medium", "Hard", "Mix"};
    return choice[Level - 1];
}

string OperatoinOfString(enOperation Op)
{
    string choice[] = {"+", "-", "*", "/", "Mix"};
    return choice[Op - 1];
}

int UsersAnswer()
{
    int answer = 0;
    cout << "Your Answer: ";
    cin >> answer;
    return answer;
}

bool CheckTheAnswer(int UserAnswer, int RightAnswer)
{
    return UserAnswer == RightAnswer;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void Print()
{
    char playAgain = 'y';
    do
    {
        ResetScreen();
        stResultData Data;
        Data.NumberOfQuesions = HowManyQuesions();
        Data.Levels = QuesionsLevels();
        Data.OpType = QuesionsOpType();

        int right = 0;
        int wrong = 0;

        for (int i = 1; i <= Data.NumberOfQuesions; i++)
        {

            cout << "Q[" << i << "/" << Data.NumberOfQuesions << "]: \n\n";

            int num1 = Number1Generation(Data.Levels);
            int num2 = Number1Generation(Data.Levels);

            char Op = FactorGeneration(Data.OpType);

            cout << num1 << Op << num2 << endl;

            int answer = UsersAnswer();

            int RightAnswer = Calculation(num1, Op, num2);

            if (!CheckTheAnswer(answer, RightAnswer))
            {
                cout << "wrong, the right answer is:" << RightAnswer << endl;
                system("color 4F");
                wrong = ++Data.NumberOfWrongAnswer;
            }
            else
            {
                cout << "Right Answer :)" << endl;
                system("color 2F");
                right = ++Data.NumberOfRightAnswer;
            }
        }

        cout << "\n\n-----------------------------\n";
        if (right > wrong)
        {
            cout << "Final Result is Pass :)\n";
            system("color 2F");
        }
        else
        {
            cout << "Final Result is Fail :(\n";
            system("color 4F");
        }

        cout << "Number Of Quesions    : " << Data.NumberOfQuesions << endl;
        cout << "Quesions Levels       : " << LevelsOfString(Data.Levels) << endl;
        cout << "OpType                :" << OperatoinOfString(Data.OpType) << endl;
        cout << "Number Of Right Answer: " << Data.NumberOfRightAnswer << endl;
        cout << "Number Of Wrong Answer:" << Data.NumberOfWrongAnswer << endl;

        cout << "\n\nDo you want play again[Y/N]? ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    Print();
    return 0;
}