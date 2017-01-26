#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>	//används av rand()
#include <windows.h> //används för Sleep()
using namespace std;

//funktioner
void startMenu();
int gamefunction();
int playdoubblefunct(int, vector<int>&);


int main()
{
	string name;
	srand((unsigned int)time(0)); //för randomisade tal

	//välkomnar och frågar efter namn
	cout << "Welcome to the number guessing game player. \n \nWhat is you name?" << endl;
	getline(cin, name);
	cout << "Welcome " << name << endl << endl;
	Sleep(500);

	startMenu(); //kallar på funktionen för huvudmenyn

	//när man vill sluta spelet lämnar man startmenyn och får detta avskedsmeddelande
	cout << "GoodBye " << name << " Please come again \n\n";
	system("pause");

	return 0;
}


void startMenu()
{
	string playMenuChoice;
	int TotPoints = 0; //totala poängen för alla rundor man har spelat
	bool playMenu = true;

	while (playMenu == true) //loopar huvudmenyn tills man vill sluta spelet
{
		cout << "What do you wish to do ?\n1 - Play new game or round \n2 - Show current number of points \n3 - Quit game" << endl;
		cin >> playMenuChoice[0];

		switch (playMenuChoice[0]) //hanterar valet från input
		{
			case '1':  
				system("cls"); //rensar skärm från text
				TotPoints += gamefunction(); //kallar på funktionen för själva spelet och lägger till vinstpoängen till variabeln
				break;
			case '2':
				cout << "You currently have: " << TotPoints << " points.\n" << endl; //visar hur många poäng man har fått totalt
				break;
			case '3':
				playMenu = false; //bryter loopen så man lämnar menyn när man vill avsluta
				break;

			default: //felhantering om man anger tecken som inte är kopplade till menyn
				cout << "Illegal input only 1 & 2 are allowed, try again" << endl;
		}
	}
}


int gamefunction() //här spelet är
{
	//alla variablerna
	string InGameMenu;
	int slumptal, gisstal, guess = 0, guesses = 0, RoundPoints = 0, TotPoints = 0;
	bool guessright, playdouble = false, validnumber = false, game = true;
	vector<int> kvittdubbeltal; //vectorn lagrar gissningarna spelaren gör

	while (game==true)
	{
		slumptal = rand() % 50 + 1; //genererar ett slumptal mellan 1-50


		/*kontrollerar så man inte har gissat samma tal tidigare och ifall inte kollar om det är 
		samma som det slumpade talet. Då man inte kan gissa samma tal 2 gånger är max antal gissningar 5*/
		for (guess = 0; guess < 50; guess++) 
		{
			cout << "Please guess a number between 1 and 50" << endl; //ber spelare gissa ett tal
			cin >> gisstal;

			if (gisstal < 1 || gisstal > 50) //kollar så talet är ett värde mellan 1-50 och om inte rensar input och frågar igen
			{
				cout << "Value must be a number between and including 1 and 50\n" << endl;
				cin.clear();
			}
			else
			{
				validnumber = true;
			}

				while (validnumber == true) //om nummret är mellan 1-50
				{
					//söker igenom vectorn och kollar om värdet redan finns där vilket indikerar man gissat talet tidigare
					if (find(kvittdubbeltal.begin(), kvittdubbeltal.end(), gisstal) == kvittdubbeltal.end())
					{
						//om det inte finns i vectorn läggs det in och antalet gissningar ökas med 1
						kvittdubbeltal.push_back(gisstal);
						guesses++;
						validnumber = false;
					}
					else
					{
						//om det redan finns får man gissa igen
						cout << "you have already guessed that number before" << endl;
						validnumber = false;
					}
				}

						//kollar om man gissat rätt eller för högt/lågt
						if (gisstal == slumptal)
						{
							//gissar man rätt får man ett gratulationsmedelande och loopen för gissningsdelen av spelet bryts
							cout << "\ncongratulations you guessed right" << endl;
							Sleep(1000);
							guessright = true;
							break;
						}
						else if (gisstal < slumptal && gisstal >= 1)
						{
							//ifall man gissade för lågt
							cout << "\nSorry, you guessed to low. Try Again\n" << slumptal << endl;
							Sleep(1000);
						}
						else if (gisstal > slumptal && gisstal <= 50)
						{
							//ifall man gissade för högt
							cout << "\nSorry, you guessed to high. Try again\n" << slumptal << endl;
							Sleep(1000);
						}
					
		}

		if (guessright == true)
		{
			//tilldelar poäng till spelare beroende på hur många gissningar hen gjort
			if (guesses == 1)
			{
				RoundPoints += 10;
			}
			else if (guesses == 2)
			{
				RoundPoints += 5;
			}
			else if (guesses >= 3 && guesses <= 9)
			{
				RoundPoints++;
			}

			//skriver ut poängen för denna omgång och frågar spelaren vad hen vill göra
			cout << "Your points fort this round is: " << RoundPoints << endl << endl;
			cout << "What do you wish to do? \n1 - Play double or nothing \n2 - return to main menu \n3 - Play another round" << endl;
			cin >> InGameMenu[0];

			switch (InGameMenu[0])
			{
			case '1':
				//vill man spella kvitt eller dubbelt kontrolerar denna if-sats att man faktiskt har fått några poäng att spela med
				if (RoundPoints > 0)
				{
					guessright = false;
					system("cls");
					//kallar på funktionen och aderar poängen man får ifrån funktionen till totala poäng variabelen så den kan returneras till startmenyn
					TotPoints += playdoubblefunct(RoundPoints, kvittdubbeltal); 
					game = false;
					RoundPoints = 0;
					break;
				}
				else if (RoundPoints == 0)
				{
					//skickar tillbaka spelaren till huvudmenyn ifall hen inte har några poäng
					system("cls");
					cout << "You have no points, You cannot play double or nothing! \nYou will now be returned to the main menu\n" << endl;
					system("pause");
				}
			case '2': //om man vill gå tillbaka till huvudmenyn
				cout << "case 2 picked" << endl;
				guessright = false;
				TotPoints += RoundPoints;
				RoundPoints = 0;
				game = false;
				system("cls");
				break;
			case '3': //om man vill spela igen omedelbart
				guessright = false;
				guesses = 0;
				TotPoints += RoundPoints; //lagrar poängen i totpoints variabeln så nästa rundas poäng inte skriver över första rundans
				RoundPoints = 0;
				kvittdubbeltal.clear();
				system("cls");
				break;

			default: //hanterar ogiltigt input
				cout << "must answer 1, 2 or 3" << endl;
			}

		}

	}

	return TotPoints; //returnerar totala poängen för denna spelomgången till huvudmenyn
}

int playdoubblefunct(int  RoundPoints, vector<int>& kvittdubbeltal) //funktion för kvitt eller dubbelt
{
	int playerguess, numberpicker, rightnumber = 0, neednumbers, guessnumbers[5], TotPoints = 0;
	//bool input = true;

	//kollar vectorn har minst 5 tal så det finns tillräkligt för att spela kvitt eller dubbelt
	if (kvittdubbeltal.size() < 5)
	{
		for (int i = kvittdubbeltal.size(); i < 5; i++) //om det inte finns 5 tal lägger denna loop till så många random tal som behövs för att det ska bli 5st
		{
			neednumbers = rand() % 50 + 1;

			if (find(kvittdubbeltal.begin(), kvittdubbeltal.end(), neednumbers) == kvittdubbeltal.end()) //kollar så det slumpade talet inte redan finns i vectorn
			{
				kvittdubbeltal.push_back(neednumbers); //finns det inte redan i vectorn läggs det till här
			}
			else
			{
				i--; //om talet redan finns i vectorn så minska i med 1 så loopen kan fortsätta så många gånger den behöver för att få 5 värden
			}
		}
	}

	//om vectorn är 5 eller större
	if (kvittdubbeltal.size() >= 5) 
	{
		//för enkelhets skull tar jag bara det 5 första värdena istället för att slumpa vilka som kommer med när vectorn har 6 eller mer värden
		for (int i = 0; i < 5; i++) 
		{
			guessnumbers[i] = kvittdubbeltal.at(i);
		}
	}

	//skriver ut talen och ber spelaren gissa vinnande talet
	cout << "You will now be presented with 5 numbers, \nIf you manage to pick the right one your points will be doubled\n" << endl;
	for (int i = 0; i < 5; i++) 
	{
		cout << guessnumbers[i] << ", ";
	}

	//slumpar fram ett tal mellan 1-5 och den platsen i arrayen blir vinnande talet
	numberpicker = rand() % 5;
	rightnumber = guessnumbers[numberpicker];

	//ber spelaren gissa ett av numren
	cout << "\n\nMake your guess! " << endl; 
	cin >> playerguess;

	//kontrollerar att nummret är ett av de 5 möjliga
	while (true)
	{
		if (find(begin(guessnumbers), end(guessnumbers), playerguess) != end(guessnumbers))
		{
			break; //bryter loopen om det är ett av numren i arrayen
		}
		//fortsätter be spelaren om värden tills hen anger ett som finns i arrayen
		cout << "You must guess one of the above numbers" << endl;
		cin >> playerguess;
	}

	//kontrollerar om man har gissat rätt
	if (playerguess == rightnumber)
	{
		//vid rätt gissning visas gratulationsmedelande och poängen dubbleras
		cout << "Luck is smilin on you today, you guessed right and get double points\n" << endl;
		TotPoints += RoundPoints * 2;
		RoundPoints = 0;
	}
	else
	{
		//vid fel gissning nollas poängen och rätt svar visas tillsamans med konsolations meddelande
		cout << "Bad luck today, you guessed wrong and get 0 points. \nBetter luck next time." << endl;
		cout << "The right number was: " << rightnumber << " ";
		RoundPoints = 0;
	}
	system("pause"); //pausar tills man trycker på en knapp så man hinner läsa meddelandena

	return TotPoints;
}