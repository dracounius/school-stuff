#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>	//anv�nds av rand()
#include <windows.h> //anv�nds f�r Sleep()
using namespace std;

//funktioner
void startMenu();
int gamefunction();
int playdoubblefunct(int, vector<int>&);


int main()
{
	string name;
	srand((unsigned int)time(0)); //f�r randomisade tal

	//v�lkomnar och fr�gar efter namn
	cout << "Welcome to the number guessing game player. \n \nWhat is you name?" << endl;
	getline(cin, name);
	cout << "Welcome " << name << endl << endl;
	Sleep(500);

	startMenu(); //kallar p� funktionen f�r huvudmenyn

	//n�r man vill sluta spelet l�mnar man startmenyn och f�r detta avskedsmeddelande
	cout << "GoodBye " << name << " Please come again \n\n";
	system("pause");

	return 0;
}


void startMenu()
{
	string playMenuChoice;
	int TotPoints = 0; //totala po�ngen f�r alla rundor man har spelat
	bool playMenu = true;

	while (playMenu == true) //loopar huvudmenyn tills man vill sluta spelet
{
		cout << "What do you wish to do ?\n1 - Play new game or round \n2 - Show current number of points \n3 - Quit game" << endl;
		cin >> playMenuChoice[0];

		switch (playMenuChoice[0]) //hanterar valet fr�n input
		{
			case '1':  
				system("cls"); //rensar sk�rm fr�n text
				TotPoints += gamefunction(); //kallar p� funktionen f�r sj�lva spelet och l�gger till vinstpo�ngen till variabeln
				break;
			case '2':
				cout << "You currently have: " << TotPoints << " points.\n" << endl; //visar hur m�nga po�ng man har f�tt totalt
				break;
			case '3':
				playMenu = false; //bryter loopen s� man l�mnar menyn n�r man vill avsluta
				break;

			default: //felhantering om man anger tecken som inte �r kopplade till menyn
				cout << "Illegal input only 1 & 2 are allowed, try again" << endl;
		}
	}
}


int gamefunction() //h�r spelet �r
{
	//alla variablerna
	string InGameMenu;
	int slumptal, gisstal, guess = 0, guesses = 0, RoundPoints = 0, TotPoints = 0;
	bool guessright, playdouble = false, validnumber = false, game = true;
	vector<int> kvittdubbeltal; //vectorn lagrar gissningarna spelaren g�r

	while (game==true)
	{
		slumptal = rand() % 50 + 1; //genererar ett slumptal mellan 1-50


		/*kontrollerar s� man inte har gissat samma tal tidigare och ifall inte kollar om det �r 
		samma som det slumpade talet. D� man inte kan gissa samma tal 2 g�nger �r max antal gissningar 5*/
		for (guess = 0; guess < 50; guess++) 
		{
			cout << "Please guess a number between 1 and 50" << endl; //ber spelare gissa ett tal
			cin >> gisstal;

			if (gisstal < 1 || gisstal > 50) //kollar s� talet �r ett v�rde mellan 1-50 och om inte rensar input och fr�gar igen
			{
				cout << "Value must be a number between and including 1 and 50\n" << endl;
				cin.clear();
			}
			else
			{
				validnumber = true;
			}

				while (validnumber == true) //om nummret �r mellan 1-50
				{
					//s�ker igenom vectorn och kollar om v�rdet redan finns d�r vilket indikerar man gissat talet tidigare
					if (find(kvittdubbeltal.begin(), kvittdubbeltal.end(), gisstal) == kvittdubbeltal.end())
					{
						//om det inte finns i vectorn l�ggs det in och antalet gissningar �kas med 1
						kvittdubbeltal.push_back(gisstal);
						guesses++;
						validnumber = false;
					}
					else
					{
						//om det redan finns f�r man gissa igen
						cout << "you have already guessed that number before" << endl;
						validnumber = false;
					}
				}

						//kollar om man gissat r�tt eller f�r h�gt/l�gt
						if (gisstal == slumptal)
						{
							//gissar man r�tt f�r man ett gratulationsmedelande och loopen f�r gissningsdelen av spelet bryts
							cout << "\ncongratulations you guessed right" << endl;
							Sleep(1000);
							guessright = true;
							break;
						}
						else if (gisstal < slumptal && gisstal >= 1)
						{
							//ifall man gissade f�r l�gt
							cout << "\nSorry, you guessed to low. Try Again\n" << slumptal << endl;
							Sleep(1000);
						}
						else if (gisstal > slumptal && gisstal <= 50)
						{
							//ifall man gissade f�r h�gt
							cout << "\nSorry, you guessed to high. Try again\n" << slumptal << endl;
							Sleep(1000);
						}
					
		}

		if (guessright == true)
		{
			//tilldelar po�ng till spelare beroende p� hur m�nga gissningar hen gjort
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

			//skriver ut po�ngen f�r denna omg�ng och fr�gar spelaren vad hen vill g�ra
			cout << "Your points fort this round is: " << RoundPoints << endl << endl;
			cout << "What do you wish to do? \n1 - Play double or nothing \n2 - return to main menu \n3 - Play another round" << endl;
			cin >> InGameMenu[0];

			switch (InGameMenu[0])
			{
			case '1':
				//vill man spella kvitt eller dubbelt kontrolerar denna if-sats att man faktiskt har f�tt n�gra po�ng att spela med
				if (RoundPoints > 0)
				{
					guessright = false;
					system("cls");
					//kallar p� funktionen och aderar po�ngen man f�r ifr�n funktionen till totala po�ng variabelen s� den kan returneras till startmenyn
					TotPoints += playdoubblefunct(RoundPoints, kvittdubbeltal); 
					game = false;
					RoundPoints = 0;
					break;
				}
				else if (RoundPoints == 0)
				{
					//skickar tillbaka spelaren till huvudmenyn ifall hen inte har n�gra po�ng
					system("cls");
					cout << "You have no points, You cannot play double or nothing! \nYou will now be returned to the main menu\n" << endl;
					system("pause");
				}
			case '2': //om man vill g� tillbaka till huvudmenyn
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
				TotPoints += RoundPoints; //lagrar po�ngen i totpoints variabeln s� n�sta rundas po�ng inte skriver �ver f�rsta rundans
				RoundPoints = 0;
				kvittdubbeltal.clear();
				system("cls");
				break;

			default: //hanterar ogiltigt input
				cout << "must answer 1, 2 or 3" << endl;
			}

		}

	}

	return TotPoints; //returnerar totala po�ngen f�r denna spelomg�ngen till huvudmenyn
}

int playdoubblefunct(int  RoundPoints, vector<int>& kvittdubbeltal) //funktion f�r kvitt eller dubbelt
{
	int playerguess, numberpicker, rightnumber = 0, neednumbers, guessnumbers[5], TotPoints = 0;
	//bool input = true;

	//kollar vectorn har minst 5 tal s� det finns tillr�kligt f�r att spela kvitt eller dubbelt
	if (kvittdubbeltal.size() < 5)
	{
		for (int i = kvittdubbeltal.size(); i < 5; i++) //om det inte finns 5 tal l�gger denna loop till s� m�nga random tal som beh�vs f�r att det ska bli 5st
		{
			neednumbers = rand() % 50 + 1;

			if (find(kvittdubbeltal.begin(), kvittdubbeltal.end(), neednumbers) == kvittdubbeltal.end()) //kollar s� det slumpade talet inte redan finns i vectorn
			{
				kvittdubbeltal.push_back(neednumbers); //finns det inte redan i vectorn l�ggs det till h�r
			}
			else
			{
				i--; //om talet redan finns i vectorn s� minska i med 1 s� loopen kan forts�tta s� m�nga g�nger den beh�ver f�r att f� 5 v�rden
			}
		}
	}

	//om vectorn �r 5 eller st�rre
	if (kvittdubbeltal.size() >= 5) 
	{
		//f�r enkelhets skull tar jag bara det 5 f�rsta v�rdena ist�llet f�r att slumpa vilka som kommer med n�r vectorn har 6 eller mer v�rden
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

	//kontrollerar att nummret �r ett av de 5 m�jliga
	while (true)
	{
		if (find(begin(guessnumbers), end(guessnumbers), playerguess) != end(guessnumbers))
		{
			break; //bryter loopen om det �r ett av numren i arrayen
		}
		//forts�tter be spelaren om v�rden tills hen anger ett som finns i arrayen
		cout << "You must guess one of the above numbers" << endl;
		cin >> playerguess;
	}

	//kontrollerar om man har gissat r�tt
	if (playerguess == rightnumber)
	{
		//vid r�tt gissning visas gratulationsmedelande och po�ngen dubbleras
		cout << "Luck is smilin on you today, you guessed right and get double points\n" << endl;
		TotPoints += RoundPoints * 2;
		RoundPoints = 0;
	}
	else
	{
		//vid fel gissning nollas po�ngen och r�tt svar visas tillsamans med konsolations meddelande
		cout << "Bad luck today, you guessed wrong and get 0 points. \nBetter luck next time." << endl;
		cout << "The right number was: " << rightnumber << " ";
		RoundPoints = 0;
	}
	system("pause"); //pausar tills man trycker p� en knapp s� man hinner l�sa meddelandena

	return TotPoints;
}