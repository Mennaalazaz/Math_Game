#include <iostream>
#include <cstdlib>
using namespace std;

struct stGame {
	short NumberOfQuestions = 0;
	string level = "";
	string Type = "";
	short RightAnswers = 0;
	short WrongAnswers = 0;
};

enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix_OP = 5 };

// Function prototypes
short ReadNumber(string message);
short HowManyQuestions();
enLevel AskForLevel();
enOperationType AskForOperationType();
int RandomNumber(int from, int to);
int CustomizeLevel(enLevel level);
char CustomizeOperation(enOperationType OperationType);
int MakeTheOperation(int n1, int n2, char operation);
void CheckAnswer(stGame& game, int YourAnswer, int ModelAnswer);
string GetState(stGame game);
string tabs(int number);
void Result(stGame game);
void AskForPlayAgain();
void StartMathGame();

//Implementation Of functions
short ReadNumber(string message) {
	short Number;
	cout << message << endl;
	cin >> Number;
	return Number;
}

short HowManyQuestions() {
	return ReadNumber("How many Questions do you want to answer?");
}

enLevel AskForLevel() {
	short choice = ReadNumber("Enter Questions Level [1]Easy [2]Med  [3]Hard [4]Mix ");
	return enLevel(choice);
}

enOperationType AskForOperationType() {
	short choice = ReadNumber("Enter Operation Type [1]Add [2]Sub  [3]Mul [4]Div [5] Mix ? ");
	return enOperationType(choice);
}

int RandomNumber(int from, int to) {
	int RandNum = rand() % (to - from + 1) + from;
	return RandNum;
}

int CustomizeLevel(enLevel level) {
	switch (level)
	{
	case enLevel::Easy:
		return RandomNumber(1, 10);
		break;
	case enLevel::Med:
		return RandomNumber(10, 50);
		break;
	case enLevel::Hard:
		return RandomNumber(50, 100);
		break;
	case enLevel::Mix:
		return RandomNumber(1, 100);
		break;
	default:
		return 0;
	}
}

char CustomizeOperation(enOperationType OperationType) {
	if (OperationType == Mix_OP) {
		int randOp = RandomNumber(1, 4);
		switch (randOp) {
		case 1: return '+';
		case 2: return '-';
		case 3: return '*';
		case 4: return '/';
		}
	}
	else {
		switch (OperationType) {
		case Add: return '+';
		case Sub: return '-';
		case Mul: return '*';
		case Div: return '/';
		}
	}
	return '+';
}

int MakeTheOperation(int n1, int n2, char operation) {
	switch (operation) {
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		if (n2 != 0) return n1 / n2;
		else return 0; // Avoid division by zero
	default:
		return 0;
	}
}

void CheckAnswer(stGame & game, int YourAnswer, int ModelAnswer) {
	if (YourAnswer == ModelAnswer) {
		game.RightAnswers++;
		system("color 2f"); // Turn Screen Green
		cout << "Right Answer :-) " << endl;
	}
	else {
		game.WrongAnswers++;
		system("color 4f"); // Turn Screen Red
		cout << "\a";
		cout << "Wrong Answer :-( " << endl;
		cout << "The Right Answer is :" << ModelAnswer << endl;
	}
}

string GetState(stGame game) {
	if (game.RightAnswers >= game.WrongAnswers) return " PASS :-)";
	else  return " FAIL :-)";
}

string tabs(int number,string s) {
	string tab = "";
	for(int i = 0; i < number; i++) {
		tab = tab + s;
	}
	cout << endl;
	return tab;
}

void MakeStringOfLevel(stGame  & game, enLevel level) {
	switch (level) {
	case enLevel::Easy:
		game.level= "Easy";
		break;
	case enLevel::Med:
		game.level = "Med";
		break;
	case enLevel::Hard:
		game.level = "Hard";
		break;
	case enLevel::Mix:
		game.level = "Mix";
		break;
	}
}

void MakeStringOfOperation(stGame& game, enOperationType Operation) {
	switch (Operation) {
	case enOperationType::Add:
		game.Type = "Add";
		break;
	case enOperationType::Sub:
		game.Type = "sub";
		break;
	case enOperationType::Mul:
		game.Type = "Mul";
		break;
	case enOperationType::Div:
		game.Type = "Div";
		break;
	case enOperationType::Mix_OP:
		game.Type = "Mix";
		break;
	}
}

void Result(stGame game) {
	//Reset screen
	system("cls"); 
	system("color 0F");


	cout << tabs(5, " ") << tabs(50, "_");
	cout <<tabs(5, " ")<< "Final Answer is" << GetState(game) << endl;
	cout << tabs(5, " ") << tabs(50, "_");
	cout << tabs(5, " ") << "Number of Questions :" << game.NumberOfQuestions << endl;
	cout << tabs(5, " ") << "Question Level :" << game.level << endl;
	cout << tabs(5, " ") << "OpType:" << game.Type << endl;
	cout << tabs(5, " ") << "Number of Right Answers :" << game.RightAnswers << endl;
	cout << tabs(5, " ") << "Number of Wrong Answers :" << game.WrongAnswers << endl;
	cout << tabs(5, " ") << tabs(50, "_");

}

void AskForPlayAgain() {
	char choice;
	cout << "\nDo you want to play again ? Y/N";
	cin >> choice;
	switch (choice)
	{
	case 'Y':
	case 'y':
	{
		StartMathGame();
	}
	break;
	case 'N':
	case 'n':
		break;
	}

}

void StartMathGame() {
	stGame game;

	game.NumberOfQuestions = HowManyQuestions();

	enLevel level = AskForLevel();
	MakeStringOfLevel(game,level);

	enOperationType OperationType = AskForOperationType();
	MakeStringOfOperation(game,OperationType);

	for (int i = 1; i <= game.NumberOfQuestions; i++) {
		cout << "Question [" << i << "/" << game.NumberOfQuestions << "]" << endl;
		int number1 = CustomizeLevel(level);
		int number2 = CustomizeLevel(level);
		char operation = CustomizeOperation(OperationType);
		int answer;

		cout << number1 << endl;
		cout << number2 << operation;
		cout << tabs(5,"-");
		cin >> answer;
		CheckAnswer(game, answer, MakeTheOperation(number1, number2, operation));
	}
	Result(game);
	AskForPlayAgain();
}


int main() {
	srand((unsigned)time(NULL));

	StartMathGame();

	return 0;
}