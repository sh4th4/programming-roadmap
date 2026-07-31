#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enOperationType
{
    add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};
enum enQuestionslevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    MixLev = 4
};

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mul:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

string GetQuestionLevelText(enQuestionslevel QuestionLevel)
{
    string arrQuestionLevel[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionLevel[QuestionLevel - 1];
}
struct stQuestion
{
    int num1 = 0;
    int num2 = 0;
    enOperationType OpType;
    enQuestionslevel Questionlevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion = 0;
    enOperationType OpType;
    enQuestionslevel QuestionsLevel;
    short NumberOfWrongAnswer = 0;
    short NumberOfRightAnswer = 0;
    bool isPass = false;
};

int randomNumber(int from, int to)
{
    // function to generate a random number.
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

short HowManyQuestions()
{
    short NumberOfQuestions = 0;
    do
    {
        cout << "How many question do you want to answer? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionslevel ReadQuestionLevel()
{
    short QuestionLevel = 0;
    do
    {
        cout << "Enter questions level [1] Easy , [2] Med , [3] Hard , [4] Mix ? ";
        cin >> QuestionLevel;

    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionslevel)QuestionLevel;
}

enOperationType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "Enter questions Operation Type [1] add , [2] sub , [3] mul , [4] div , [5] mix ? ";
        cin >> OpType;

    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

int SimpleCalculator(int num1, enOperationType Op, int num2)
{
    switch (Op)
    {
    case enOperationType::add:
        return num1 + num2;
    case enOperationType::Sub:
        return num1 - num2;
    case enOperationType::Mul:
        return num1 * num2;
    case enOperationType::Div:
        return num1 / num2;
    default:
        return num1 + num2;
    }
}

enOperationType GetRandomOperationType()
{
    int Op = randomNumber(1, 4);
    return (enOperationType)Op;
}

stQuestion GenerateQuestion(enQuestionslevel Questionslevel, enOperationType OpType)
{
    stQuestion Question;

    if (Questionslevel == enQuestionslevel::MixLev)
    {
        Questionslevel = (enQuestionslevel)randomNumber(1, 3);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OpType = OpType;

    switch (Questionslevel)
    {
    case enQuestionslevel::Easy:
        Question.num1 = randomNumber(1, 10);
        Question.num2 = randomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.num1, Question.OpType, Question.num2);
        Question.Questionlevel = Questionslevel;
        return Question;

    case enQuestionslevel::Med:
        Question.num1 = randomNumber(10, 50);
        Question.num2 = randomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.num1, Question.OpType, Question.num2);
        Question.Questionlevel = Questionslevel;
        return Question;

    case enQuestionslevel::Hard:
        Question.num1 = randomNumber(50, 100);
        Question.num2 = randomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.num1, Question.OpType, Question.num2);
        Question.Questionlevel = Questionslevel;
        return Question;
    }
    return Question; // or default case
}

void GenerateQuizzQuestion(stQuizz &Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    }
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz &Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question[" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]:\n\n";
    cout << Quizz.QuestionList[QuestionNumber].num1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].num2 << endl;
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OpType) << endl;
    cout << "--------" << endl;
}

void CorrectTheQuestionAnswer(stQuizz &Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :(\n";
        cout << "The Rigth Answer is:";
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :)\n";
    }
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswer(stQuizz &Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "Pass :-)";
    else
        return "Fail :-(";
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "-------------------------------\n\n";
    cout << "Final Results: " << GetFinalResultsText(Quizz.isPass) << endl;
    cout << "-------------------------------\n\n";

    cout << "Number of Question: " << Quizz.NumberOfQuestion << endl;
    cout << "Question Levels: " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType: " << GetOpTypeSymbol(Quizz.OpType) << endl;

    cout << "Number Of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number Of Wrong Answer: " << Quizz.NumberOfWrongAnswer << endl;
    cout << "-------------------------------\n";
}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestion = HowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestion(Quizz);

    AskAndCorrectQuestionListAnswer(Quizz);

    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << "\nDo you want to play again? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}