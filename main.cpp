//
//  Garrett Heisey
//  1337.010 - Prof Doug DeGroot
//  Date Created - 25 Mar 2023
//
//  Changelog:
//          25Mar2023 - created program and defined the AnimalNode struct, started work on the output to get the
//                      first animal from the user along with the correct output if the program guessed right or wrong.
//          28Mar2023 - Created functions to create new question and guess nodes to expand the tree when the program doesn't
//                      guess the user animal correctly, created functions to get the user's guess and traverse the binary
//                      tree recursively to ask questions until it gets to a leaf node. I also reorganized the program to have
//                      functions that only accomplish a certain task. I ran into a bug where the binary tree wasn't being processed
//                      correctly.
//          29Mar2023 - I fixed the bug in my program regarding the tree traversal and the program now works as expected, I separated
//                      some larger functions into multiple.
//          2Apr2023  - Added finishing touches to game.
//
//
//  Notes:
//          I added user input validation, it wasn't in the instructions but I found that the program acted unpredictably
//          when receiving input other than Y/N.

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct AnimalNode
{
    string questionOrGuess;
    AnimalNode* yesAnswer;
    AnimalNode* noAnswer;
};

AnimalNode* rootNode;

AnimalNode* newGuessNode(string guess)
{
    AnimalNode* guessNode = new AnimalNode;
    guessNode->questionOrGuess = guess;
    guessNode->noAnswer = nullptr;
    guessNode->yesAnswer = nullptr;
    return guessNode;
}

//AnimalNode*
AnimalNode* newQuestionNode(string question, AnimalNode* yesAnswer, AnimalNode* noAnswer)
{
    AnimalNode* questionNode = new AnimalNode;
    questionNode->questionOrGuess = question;
    questionNode->yesAnswer = yesAnswer;
    questionNode->noAnswer = noAnswer;
    return questionNode;
}

bool MakeGuess(AnimalNode* curNode)
{
    char yesOrNo;
    cout << "Is your animal a " << curNode->questionOrGuess << "? Enter Y/N:" << endl;
    cin >> yesOrNo;
    while(yesOrNo!='N'&&yesOrNo!='Y')
    {
        cout << "Unusual character detected. Enter Y/N:" << endl;
        cin >> yesOrNo;
    }
    if(yesOrNo=='N')
    {
        return false;
    }
    else
    {
        return true;
    }
}

void AskQuestion(AnimalNode*& curNode)
{
    // this if statement makes sure that the current node is not a leaf (node which contains a guess)
    if(curNode->noAnswer!=nullptr)
    {
        char answer;
        cout << curNode->questionOrGuess << " Enter Y/N:" << endl;
        cin >> answer;
        while(answer!='Y' && answer!='N')
        {
            cout << "Unusual input detected. Enter Y/N:" << endl;
            cin >> answer;
        }
        if(answer=='Y')
        {
            curNode = curNode->yesAnswer;
            AskQuestion(curNode);
        }
        else
        {
            curNode = curNode->noAnswer;
            AskQuestion(curNode);
        }
    }
}

void GetUserAnimal(string& userAnimal)
{
    cin.ignore();
    cout << "Bummer! What animal were you thinking of?" << endl;
    getline(cin, userAnimal);
}

void GetUserQuestionAndAnswer(AnimalNode* curNode, string userAnimal, string& userQuestion, string& questionAnswer)
{
    cout << "What is a yes/no question that I can use to tell a " << curNode->questionOrGuess << " from a " << userAnimal << "?" << endl;
    getline(cin, userQuestion);
    cout << "For a " << userAnimal << ", is the answer yes or no?" << endl;
    cin >> questionAnswer;
}

void ValidateInput(string& str)
{
    while(str!="yes"&&str!="no")
    {
        cout << "Unusual input detected. Enter yes/no:" << endl;
        cin >> str;
    }
}

void PlayAgainChoice(bool& playing)
{
    char ch;
    cout << "Try again? Enter Y/N" << endl;
    cin >> ch;
    if(ch=='N')
    {
        playing = false;
    }
}

int main() {
    
    string enterKeyPressed;
    string firstGuess;
    string userAnimal;
    string userQuestion;
    string userQuestionAnswer;
    bool playing = true;
    AnimalNode* curNode;
    
    cout << "Let's play the \"Guess the Animal\" game." << endl;
    cout << "Think of an animal and hit enter when you're ready." << endl;
    getline(cin, enterKeyPressed);
    
    curNode = newGuessNode("Lizard");
    rootNode = curNode;
    
    while(playing)
    {
        // set the current node to the top of the tree for each iteration of the loop
        curNode = rootNode;
        // if a node pointer is null, meaning it is a leaf
        if(curNode->noAnswer==nullptr)
        {
            if(!MakeGuess(curNode))
            {
                GetUserAnimal(userAnimal);
                GetUserQuestionAndAnswer(curNode, userAnimal, userQuestion, userQuestionAnswer);
                ValidateInput(userQuestionAnswer);
                
                if(userQuestionAnswer=="no")
                {
                    curNode->noAnswer = newGuessNode(userAnimal);
                    //cout << "curNode->noAnswer was pointed to a new node containing " << userAnimal << endl;
                    curNode->yesAnswer = newGuessNode("Lizard");
                    //cout << "curNode->yesAnswer was pointed to a new node containing Lizard" << endl;
                    curNode->questionOrGuess = userQuestion;
                    //cout << "curNode->questionOrGuess was set to " << userQuestion << endl;
                }
                else
                {
                    curNode->noAnswer = newGuessNode("Lizard");
                    //cout << "curNode->noAnswer was pointed to a new node containing Lizard" << endl;
                    curNode->yesAnswer = newGuessNode(userAnimal);
                    //cout << "curNode->yesAnswer was pointed to a new node containing " << userAnimal << endl;
                    curNode->questionOrGuess = userQuestion;
                    //cout << "curNode->questionOrGuess was set to " << userQuestion << endl;
                }
            }
            else
            {
                cout << "Good! I guessed your animal!" << endl;
            }
        }
        else
        {
            AskQuestion(curNode);
            if(!MakeGuess(curNode))
            {
                GetUserAnimal(userAnimal);
                GetUserQuestionAndAnswer(curNode, userAnimal, userQuestion, userQuestionAnswer);
                ValidateInput(userQuestionAnswer);
                
                if(userQuestionAnswer=="no")
                {
                    curNode->noAnswer = newGuessNode(userAnimal);
                    //cout << "curNode->noAnswer was pointed to a new node containing " << userAnimal << endl;
                    curNode->yesAnswer = newGuessNode(curNode->questionOrGuess);
                    //cout << "curNode->yesAnswer was pointed to a new node containing " << curNode->questionOrGuess << endl;
                    curNode->questionOrGuess = userQuestion;
                    //cout << "curNode->questionOrGuess was set to " << userQuestion << endl;
                }
                else
                {
                    curNode->noAnswer = newGuessNode(curNode->questionOrGuess);
                    //cout << "curNode->noAnswer was pointed to a new node containing " << curNode->questionOrGuess << endl;
                    curNode->yesAnswer = newGuessNode(userAnimal);
                    //cout << "curNode->yesAnswer was pointed to a new node containing " << userAnimal << endl;
                    curNode->questionOrGuess = userQuestion;
                    //cout << "curNode->questionOrGuess was set to " << userQuestion << endl;
                }
            }
            else
            {
                cout << "Good! I guessed your animal!" << endl;
            }
        }
        PlayAgainChoice(playing);
    }
    
    return 0;
}
