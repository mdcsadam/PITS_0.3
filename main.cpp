// Programming I, Final Project
// PIT System - Development Edition
// Author: Adam Kittilson
// 
/* Pet Inventory Tracking System. This application will undoubtedly be highly subject to change.
*/
//Required includes
#include <iostream> // Provides cout/cin functionality
#include <string> // Provides string tools, probably not necessary
#include <iomanip> // provides formatting tools
#include <fstream> //allows file access
using namespace std;
//Declare global variables
//logic has been added to test for existence of files and if not present, build them
//if files are present, the values below will be overwritten via the load arrays function
string invID[25] = {"tank1", "tank2", "tank3"}; //Inventory ID Array
double invCap[25] = {10, 20, 30}; //Inventoried item capacity array
int invCount = 3; //invCount will keep track of the number of entries in the DB, for use when generating reports
string invDesc[25] = {"10 gallon tank", "20 gallon tank", "30 gallon tank"}; //Inventoried item description array
string invPet[25] = {"--", "--", "--"}; //Current pet in inventoried item array
//Declare IO objects and files for inventory arrays
//inventory ID files
ifstream invIDin;
ofstream invIDout;
string invIDfile = "invIDfile.txt";
//inventory description files
ifstream invDescin;
ofstream invDescout;
string invDescfile = "invDescfile.txt";
//inventory capacity files
ifstream invCapin;
ofstream invCapout;
string invCapfile = "invCapfile.txt";
//inventory animal type files
ifstream invPetin;
ofstream invPetout;
string invPetfile = "invPetfile.txt";
//inventory count files
ifstream invCountin;
ofstream invCountout;
string invCountfile = "invCountfile.txt";
//End inventory array-related declarations
ifstream infile; //used in main
ofstream outfile; //used in printMess
string namestor = "namestor.txt"; // filename for name storage
//End global variable declarations
//Begin Function Prototypes
void showInvFull(); //Full Inventory Listing
void showInvPart(); //ID and Description only listing
void showInvMenu(); //Same as part but as a numbered list
void showInvPetMenu(); //Menu with inventory ID and current pet
void loadInvArrayFunction(); //Load inventory arrays function
void buildInvArrayFiles(); //Function to build and update stored arrays
void invCapCalc(double, double); //Inventoried Item Capacity Calculator
void noinvCapCalc(double); //non-Inventoried Item Capacity Calculator
void zodiacDCFull();
int numberGame(string); //Irritating number game function
int menuSelVal(int); //Tool used for validating numerical menu selections
string zodiacDeChina(int); //Tool to calculate user's Cinese Zodiac sign
string printMess(string); //Function initially designed to explore passing info between
//functions, now serves as a proving ground for other concepts
//End Function Prototypes
//============================================================================
//============================================================================
// Begin Add Pet to Inventory Item functionality
void invAddPet() {
	//initialize variables
	int addPetTrip = 0;
	int addPetInv;
	int addPetTValue;
	int addPetInvRun;
	int addPetRepeat;
	bool exitAddPet = false;
	string addPetType;
	string addPetTValueString;
	cin.ignore();
	//The following sets the addPetType variable which will be stored in the invPet array
	do {
		if (addPetTrip == 0) cout << "Welcome to the Add a Pet to an Inventory Item module!\n";
		else if (addPetTrip != 0) cout << "Wasn't that fun!?! Please make another selection\n";
			cout << "Please select an animal type from the list below:\n\n";
			cout << "\t1) Turtle\n";
			cout << "\t2) Tree Frog\n";
			cout << "\t3) Aquatic Frog\n";
			cout << "\t4) Fish\n";
			addPetTValue = menuSelVal(4);
			switch (addPetTValue) {
				case 1:
					addPetType = "Turtle";
					break;
				case 2:
					addPetType = "TreeFrog";
					break;
				case 3:
					addPetType = "AquaticFrog";
					break;
				case 4:
					addPetType = "Fish";
					break;
				} //This closes the switch
			cout << endl << "Great! Now please select the enclosure in which you'll be keeping your " << addPetType << ":\n" << endl;
			showInvPetMenu();
			addPetInv = menuSelVal(invCount); //verify the menu selection was valid
			addPetInvRun = addPetInv - 1; //convert menu selection to array position
			invPet[addPetInvRun] = addPetType;
			cout << "You have chosen to designate " << invID[addPetInvRun] << " as a " << invPet[addPetInvRun] << " habitat, excellent!\n";
			cout << endl << "\t\tWould you like to add another?\n";
			cout << "\t\t1) Yes\n";
			cout << "\t\t2) No\n";
			cin >> addPetRepeat;
			while (cin.fail()) {
				cout << "Please enter a number\n\n";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> addPetRepeat;
			}
      addPetRepeat = addPetRepeat == 1 ? 1 : 2;
				if (addPetRepeat == 2) exitAddPet = true;
		} // this ends the Do loop
 while (exitAddPet == false);
	cout << "Enjoy your new pet!\n";
}
// End Add Pet to Inventory Item functionality
//============================================================================
//============================================================================
//Capacity Calculator - Select a pet type, enter a tank capacity and get back the volume of water required to fill the tank
//Begin Capacity Calculator code
void capCalc() {
	//Variable declaration
	double tankSize;
	int calcPerc;
	bool capRetMenu = false;
	int ccTrip = 0;
	int petMenuSel;
	int frogType;
	int invOpt;
	int calcInvOption;
	int calcInvSel;
	int calcInvRun;
	//Below constants are tank-fill percentages for various animals
	const double FISHFILLPERC = 0.85;
	const double TURTFILLPERC = 0.45;
	const double TFRGFILLPERC = 0.15;
	const double AFRGFILLPERC = 0.35;
  string petMenuSelString;
	bool madeitpastmenu;
  bool tryAgain;
		do {
		if (ccTrip == 0) cout << "Welcome to the Aquarium Capacity Calcuator\n";
		else if (ccTrip != 0) cout << "Wasn't that fun!?! Please make another selection\n";
    cin.ignore();
		do {
		//print the pet menu
    madeitpastmenu = true;
		cout << "Please enter the number that corresponds with the kind of animal for which we will be performing this calculation?\n";
		cout << "\t1) Turtle\n";
		cout << "\t2) Frog\n";
		cout << "\t3) Fish\n";
		petMenuSel = menuSelVal(3);
		} while (madeitpastmenu == false);
		//
		if (petMenuSel == 1) {
			cout << "A turtle, great!\n";
			calcPerc = TURTFILLPERC * 100;
			cout << "The fill percentage used for this exercise will be: " << calcPerc << "%.\n" << endl;
			cout << "\nWill you be using an already inventoried item, or a new one?\n";
			cout << "\t1) Use an existing enclosure\n";
			cout << "\t2) Use an unregistered capacity\n";
			cin >> calcInvOption;
      while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> calcInvOption;
      }
      calcInvOption = calcInvOption >0 && calcInvOption < 3 ? calcInvOption : 2;
			if (calcInvOption == 1) {
				cout << "\nYou selected to calculate using an inventoried item, joyous!\n";
				do {
          cout << "Please select an item from the inventory below:\n" << endl;
				  cout << "\r";
				  showInvMenu();
				  cout << endl;
				  cin >> calcInvSel;
          while (cin.fail()) {
            cin.clear();
            cin.ignore(256, '\n');
            cout << "Please select a valid option:\n";
            cin >> calcInvSel;
          }
        calcInvSel = calcInvSel > 0 && calcInvSel <= invCount ? calcInvSel : 99;
        if (calcInvSel == 99) {
          cout << "Please try again\n";
          tryAgain = true;
        }
        } while (tryAgain == true);
				calcInvRun = calcInvSel - 1;
				tankSize = invCap[calcInvRun];
				invCapCalc(tankSize, TURTFILLPERC);
			}
			else noinvCapCalc(TURTFILLPERC);
			cout << "We are having so much fun!\n";
			cin.get();
		}
		else if (petMenuSel == 2) {
			cout << "A frog, how wonderful!\n";
			cout << "Will this be a tree frog or an aquatic variety?\n";
			cout << "\t1) Tree Frog\n";
			cout << "\t2) Aquatic Frog\n";
			cin >> frogType;
      while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> frogType;
      }
      frogType = frogType >0 && frogType < 3 ? frogType : 2;
			if (frogType == 1) {
				calcPerc = TFRGFILLPERC * 100;
				cout << "Tree frogs need a little less water. The fill percentage used for this exercise will be: " << calcPerc << "%.\n" << endl;
				cout << "\nWill you be using an already inventoried item, or a new one?\n";
				cout << "\t1) Use an existing enclosure\n";
				cout << "\t2) Use an unregistered capacity\n";
				cin >> calcInvOption;
        while (cin.fail()){
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Please try again\n";
          cin >> calcInvOption;
        }
        calcInvOption = calcInvOption >0 && calcInvOption < 3 ? calcInvOption : 2;
				if (calcInvOption == 1) {
					cout << "\nYou selected to calculate using an inventoried item, joyous!\n";
					cout << "Please select an item from the inventory below:\n" << endl;
					cout << "\r";
					showInvMenu();
					cout << endl;
          calcInvSel = menuSelVal(invCount);
					calcInvRun = calcInvSel - 1;
					tankSize = invCap[calcInvRun];
					invCapCalc(tankSize, TFRGFILLPERC);
				}
				else noinvCapCalc(TFRGFILLPERC); {
					cout << "We are having so much fun!\n\n";
					cin.get();
				}
			}
			if (frogType == 2) {
				calcPerc = AFRGFILLPERC * 100;
				cout << "Aquatic frogs need a little more water. The fill percentage used for this exercise will be: " << calcPerc << "%.\n" << endl;
				cout << "\nWill you be using an already inventoried item, or a new one?\n";
				cout << "\t1) Use an existing enclosure\n";
				cout << "\t2) Use an unregistered capacity\n";
				cin >> calcInvOption;
        while (cin.fail()){
          cin.clear();
          cin.ignore(256, '\n');
          cout << "Please try again\n";
          cin >> calcInvOption;
        }
        calcInvOption = calcInvOption >0 && calcInvOption < 3 ? calcInvOption : 2;
				if (calcInvOption == 1) {
					cout << "\nYou selected to calculate using an inventoried item, joyous!\n";
					cout << "Please select an item from the inventory below:\n" << endl;
					cout << "\r";
					showInvMenu();
					cout << endl;
          calcInvSel = menuSelVal(invCount);
					calcInvRun = calcInvSel - 1;
					tankSize = invCap[calcInvRun];
					invCapCalc(tankSize, AFRGFILLPERC);
				}
				else noinvCapCalc(AFRGFILLPERC);
				cout << "Press any key -as long as that key is followed by the enter key- to continue:\n";
				cin.get();
			}
			else cout << "Please try again using a valid selection.\n";
		}
		else if (petMenuSel == 3) {
			cout << "Oh happy day, a fish!\n";
			calcPerc = FISHFILLPERC * 100;
			cout << "The fill percentage used for this exercise will be: " << calcPerc << "%.\n" << endl;
			cout << "\nWill you be using an already inventoried item, or a new one?\n";
			cout << "\t1) Use an existing enclosure\n";
			cout << "\t2) Use an unregistered capacity\n";
			cin >> calcInvOption;
      while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> calcInvOption;
      }
      calcInvOption = calcInvOption >0 && calcInvOption < 3 ? calcInvOption : 2;
			if (calcInvOption == 1) {
				cout << "\nYou selected to calculate using an inventoried item, joyous!\n";
				cout << "Please select an item from the inventory below:\n" << endl;
				cout << "\r";
				showInvMenu();
				cout << endl;
        calcInvSel = menuSelVal(invCount);
				calcInvRun = calcInvSel - 1;
				tankSize = invCap[calcInvRun];
				invCapCalc(tankSize, FISHFILLPERC);
			}
			else noinvCapCalc(FISHFILLPERC);
			cout << "Press any key -as long as that key is followed by the enter key- to continue:\n";
			cin.get();
		}
		else cout << "Please try again using a valid selection\n";
		cout << "Would you like to determine another capacity?\n";
		cout << "\t 1) Yes, Please!\n";
		cout << "\t 2) I'm good for now, thanks!\n";
		cin >> invOpt;
    while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> invOpt;
      }
		if (invOpt == 1) {
			ccTrip++;
			capRetMenu = false;
		}
		if (invOpt == 2) {
			capRetMenu = true;
		}
		if (capRetMenu == false) cout << "Well thank goodness I've learned about loops!\n";
	} while (capRetMenu == false);
	cout << "Thanks for participating!\n\n";
}
//============================================================================
//============================================================================
//Begin inventory add
void addInvItem() {
	//declare variables for this function
	//variables received from main: invID, invDesc
	int invOpt;
	bool retMenu = false;
  int invCapTemp;
	do {
		cout << "Please enter an inventory name:\n";
		cin >> invID[invCount];
		cout << "Please enter a description:\n";
		cin.ignore();
		getline(cin, invDesc[invCount]);
		cout << "Please enter the capacity of the enclosure, in gallons:\n";
    cin >> invCap[invCount];
    while (cin.fail()) {
      cout << "? Please try a number next time\n\n";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> invCap[invCount];
    }
    invPet[invCount] = "--";
		cout << "You entered " << invID[invCount] << " and " << invDesc[invCount] << " and " << invCap[invCount] << ".\n";
		cout << "\n\n";
		cout << setw(20) << left << "Inventory ID" << setw(30) << left << "\tDescription" << setw(3) << left << "\tCapacity" << "\n";
		for (int i = 0; i <= invCount; i++) {
			cout << setw(20) << left << invID[i] << "\t" << setw(30) << left << invDesc[i] << "\t" << setw(3) << left << invCap[i] << "\n";
		}
		cout << endl;
		invCount++;
		cout << "Would you like to add another?\n";
		cout << "\t 1) Add another\n";
		cout << "\t 2) Return to menu\n";
		cin >> invOpt;
    while (cin.fail()) {
      cout << "Please try again using a number:\n\n";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> invOpt;
    }
		if (invOpt == 1) {
			retMenu = false;
		}
		if (invOpt == 2) {
			retMenu = true;
		}
	} while (retMenu == false);
}
//end inventory add function
//==============================================================================
//==============================================================================
//==============================================================================
//begin main
int main() {
	string first_name; //variable for getting name input to send to printMess
	string tempName; //variable for receiving feedback from printMess
	string name2; //variable for reading name from file
	int optMenuSelect; //For tracking menu selection
	int trip = 1; //for changing main menu prompt after first visit
  int birthYear;
  int yearConf;
  bool keepTrying;
  string zsign;
  int punkedTimes;
	//Check for the existence of invCountfile
	//If count file is found, load inventory file contents into arrays
	//If count file is NOT found, use current arrays to build files
	invCountin.open(invCountfile);
	if (!invCountin) {
		cout << "building initial arrays...\n";
		buildInvArrayFiles();
		cout << "...done!\n";
	}
	else {
		invCountin.close();
	cout << "Calling the load array function...\n";
	loadInvArrayFunction();
  cout << "Arrays loaded, the inventory count is: " << invCount << ".\n";
	}
  bool exitProg = false; //flag for continued execution. When true, the do loop will terminate and the program will exit
  cout << "\n\n\n\n\t\tWelcome to the Pet Inventory Tracking System: Development Edition!\n";
  cout << "\nPlease enter your name: \n";
  getline(cin, first_name);
  do {
  keepTrying = false;
  cout << "\nPlease provide the 4-digit year of your birth: \n";
  cin >> birthYear;
  while (cin.fail()){
    cout << "\n\nPlease enter a 4-digit year of your birth.\n";
    cout << "For example, if you were born in the year 1976, enter: 1976";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> birthYear;
  }
  cout << "\nYou entered " << birthYear << ", is that correct?\n\n";
	cout << "\t 1) Yes, that's correct!\n";
	cout << "\t 2) No, let me try that again...\n";
	cin >> yearConf;
    while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> yearConf;
      }
    yearConf = yearConf >0 && yearConf < 3 ? yearConf : 2;
    if (yearConf == 2) {
      cout << "No problem, we can try again...\n\n";
      keepTrying = true;
    }
  } while (keepTrying == true);
  zsign = zodiacDeChina(birthYear);
  cout << "\nOh, how exciting! " << first_name << ", you were born in the year of the " << zsign << "!\n\n";
  // cout << "Leaving main for printMess function.\n"; //For troubleshooting the transition to printMess
 tempName = printMess(first_name);
  cout << "\n\nYou are now back in main, printing the contents of namestor\n" << endl;
  infile.open(namestor); //opening namestor.txt for reading as infile
  //check the presence of infile
  if (!infile) {
    cout << "File open failure!";
  }
  getline(infile, name2);
  cout << "\n\t\t***" << name2 << "***\n\n";
  //cout << "hopefully that worked\n\n";
  cout << "ALSO printing name as returned from printMess: " << tempName << " ...Excellent!\n\n";
  cout << "press enter to continue...\n\n";
  cin.get();
	do {
		if (trip == 1) cout << "So what would you like to do?\n";
		if (trip != 1) cout << "And NOW what would you like to do?\n";
		cout << "\n\n\t==============================================\n";
		cout << "\t 1) Create a new inventory item\n";
		cout << "\t 2) Add a pet to an inventory item\n";
		cout << "\t 3) Use the Capacity Calculator\n";
		cout << "\t 4) Print current inventory\n";
		cout << "\t 5) Play the number game\n";
		cout << "\t 6) Find your Chinese Zodiac Sign\n";
		cout << "\t 7) Exit program\n";
		optMenuSelect = menuSelVal(7);
		optMenuSelect = optMenuSelect > 0 && optMenuSelect < 8 ? optMenuSelect : 7;
		cout << "You chose " << optMenuSelect << ".\n";
		switch (optMenuSelect)
		{
		case 1:
			cout << "\n\tYou have selected 'New Inventory Item', launching...\n";
			addInvItem();
			trip++;
			break;
		case 2:
			cout << "\n\tYou have selected 'Add Pet to Inventory Item', launching...\n";
			invAddPet();
			trip++;
			break;
		case 3:
			cout << "\n\tYou have selected 'Capacity Calculator', launching...\n";
			capCalc();
			trip++;
			break;
		case 4:
			cout << "\n\tDisplaying the Current Inventory...\n";
			showInvFull();
			cout << "\n";
			trip++;
			break;
		case 5:
			cout << "\n\tYou have selected 'Number Game', launching...\n";
			punkedTimes = numberGame(name2);
			cout << "Oh man, you are a glutton for punishment! You were punked " << punkedTimes << " times!\n\n"; 
			trip++;
			break;
		case 6:
			cout << "\n\tYou have selected 'Chinese Zodiac', launching...\n";
			zodiacDCFull();
			trip++;
			break;
		case 7:
			cout << "You have selected 'Exit Program', later!\n";
			exitProg = true;
			break;
		}
	} while (exitProg == false);
  cout << "Saving your work...\n";
  buildInvArrayFiles();
  cout << "\n\t\t...Done!";
	return 0;
}
//End of Main
//============================================================================
//============================================================================
//Begin Inventory Display Functions
//Full Inventory Listing
void showInvFull() {
	cout << "\n";
	cout << setw(20) << left << "Inventory ID" << setw(30) << left << "\tDescription" << setw(3) << left << "\tCapacity" << setw(20) << left << "\tPet Type" << "\n";
	for (int i = 0; i < invCount; i++) {
		cout << setw(20) << left << invID[i] << "\t" << setw(30) << left << invDesc[i] << "\t" << setw(3) << left << invCap[i] << "\t\t\t" << setw(20) << left << invPet[i] << "\n";
	}
}
//ID and Description only listing
void showInvPart() {
	cout << "\n";
	cout << setw(20) << left << "Inventory ID" << setw(30) << left << "\tDescription" << "\n";
	for (int i = 0; i < invCount; i++) {
		cout << setw(20) << left << invID[i] << "\t" << setw(30) << left << invDesc[i] << "\n";
	}
}
//Same as part but as a numbered list
void showInvMenu() {
	cout << "\n";
	cout << "\t" << setw(20) << left << "Inventory ID" << setw(30) << left << "\tDescription" << "\n";
	for (int i = 0; i < invCount; i++) {
		cout << "\t" << i + 1 << ") " << setw(20) << left << invID[i] << "\t" << setw(30) << left << invDesc[i] << "\n";
	}
}
void showInvPetMenu() {
	cout << "\n";
	cout << "\t" << setw(20) << left << "Inventory ID" << setw(20) << left << "\tPet Type" << "\n";
	for (int i = 0; i < invCount; i++) {
		cout << "\t" << i + 1 << ") " << setw(20) << left << invID[i] << "\t" << setw(20) << left << invPet[i] << "\n";
	}
}
//End Inventory Display Functions
//============================================================================
//==============================================================================
//Load inventory arrays function
void loadInvArrayFunction(){
	int abc; // Array Builder Counter
	//load current inventory count into variable
	cout << "Loading inventory arrays...\n";
	invCountin.open(invCountfile); //inventory count
	invCountin >> invCount;
	invCountin.close();
	//load current Inventory IDs into array
	invIDin.open(invIDfile); //invID
	for (abc = 0; abc <=invCount; abc++) {
		invIDin >> invID[abc];
	}
	invIDin.close();
	//load current capacities into array
	invCapin.open(invCapfile);
	for (abc = 0; abc <= invCount; abc++){
		invCapin >> invCap[abc];
	}
	invCapin.close();
  //load current pets into array
  invPetin.open(invPetfile);
  for (abc = 0; abc < invCount; abc++) {
    invPetin >> invPet[abc];
  }
	invPetout.close();
	cout << "... done!\n";
}
//run the following one time to build initial arrays
void buildInvArrayFiles(){
	int abc; // Array Builder Counter
	invCountout.open(invCountfile);
	invCountout << invCount;
	invCountout.close();
	invIDout.open(invIDfile);
	for (abc = 0; abc < invCount; abc++){
		invIDout << invID[abc] << " ";
	}
	invIDout.close();
	invCapout.open(invCapfile);
	for (abc = 0; abc < invCount; abc++){
		invCapout << invCap[abc] << " ";
	}
	invCapout.close();
	invDescout.open(invDescfile);
	for (abc = 0; abc < invCount; abc++) {
		invDescout << invDesc[abc] << " | ";
	}
	invDescout.close();
	invPetout.open(invPetfile);
  for (abc = 0; abc < invCount; abc++) {
    invPetout << invPet[abc] << " ";
  }
	invPetout.close();
}
//end load inventory arrays function
//==============================================================================
//==============================================================================
//Begin Inventoried Item Capacity Calculator
void invCapCalc(double invSize, double invFillPerc) {
	double invFilledCap;
	invFilledCap = invSize * invFillPerc;
	cout << "\n\tTo fill a " << invSize << " gallon aquarium to the recommended capacity,\n\tyou will need " << invFilledCap << " gallons of water.\n" << endl;
}
//Begin non-Inventoried Item Capacity Calculator
void noinvCapCalc(double noinvFillPerc) {
	double noinvtankSize, noinvfilledCap;
	cout << "\n\tTo find out the amount of water needed to bring your aquarium to the appropriate \n\tcapacity, please tell us the size of the tank you are working with, in gallons: \n";
	cin >> noinvtankSize;
  while (cin.fail()) {
    cout << "This application accepts integers only, please try again:\n";
    cin.clear();
    cin.ignore(256, '\n');
    cin >> noinvtankSize;
  }
	noinvfilledCap = noinvtankSize * noinvFillPerc;
	cout << "\n\tTo fill a " << noinvtankSize << " gallon aquarium to the recommended capacity,\n\tyou will need " << noinvfilledCap << " gallons of water.\n" << endl;
}
//End Inventoried Item Capacity Calcuator
//==============================================================================
//==============================================================================
//begin Number game function
int numberGame(string gameName) {
  cin.ignore();
  bool repeat;
	int numPick;
	do {
		repeat = false;
		cout << "\tOkay, " << gameName << ", pick a number between 1 and 5: \n";
		string numPickString;
		getline(cin, numPickString);
		if (numPickString == "1") numPick = 1;
		else if (numPickString == "2") numPick = 2;
		else if (numPickString == "3") numPick = 3;
		else if (numPickString == "4") numPick = 4;
		else if (numPickString == "5") numPick = 5;
		else {
			cout << "\n\n\tYou entered \"" << numPickString << "\" when asked to enter a number between 1 and 5. That's a pretty poor performance. You deserve this...\n";
      cout << "press enter to continue...\n";
      cin.get();
			numPick = 10;
			repeat = true;
		}
		numPick = numPick*2;
		for (int i = 0; i <= numPick; i++){
			cout << "\n\n\tAm I bugging you? I'm not touching you...\n";
		}
  }
	while (repeat == true);
	cout << "\n\n\nWasn't that fun?\n";
	numPick++;
  return numPick;
}
//End Number game function
//==============================================================================
//==============================================================================
//Begin Chinese Zodiac Sign Calculator
string zodiacDeChina(int byear) {
  string zodiacSigns[12] = {"Rat", "Ox", "Tiger", "Rabbit", "Dragon", "Snake", "Horse", "Goat", "Monkey", "Rooster", "Dog", "Pig"};
  string zodiacSign;
  const int BASEYEAR = 1924;
  int yearDiff;
  int yearOffset;
  //cout << "Using " << BASEYEAR << " as the base year\n";
  //cout << "Received " << byear << ".\n";
  yearDiff = byear - BASEYEAR;
  //cout << "Difference of: " << yearDiff << " years.\n";
  yearOffset = yearDiff % 12;
  //cout << "Offset of " << yearOffset << " years.\n";
  zodiacSign = zodiacSigns[yearOffset];
  //cout << "which makes you a " << zodiacSign << "!\n";
  return zodiacSign;
}
//End Chinese Zodiac Sign Calculator
//==============================================================================
//==============================================================================
//Begin Chinese Zodiac Sign Calculator /w intro
void zodiacDCFull(){
  int birthYear;
  int yearConf;
  string zsign;
  bool keepTrying;
  do {
    keepTrying = false;
    cout << "\nPlease provide the 4-digit year of your birth: \n";
    cin >> birthYear;
    while (cin.fail()){
      cout << "\n\nPlease enter a 4-digit year of your birth.\n";
      cout << "For example, if you were born in the year 1976, enter: 1976";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> birthYear;
    }
    cout << "\nYou entered " << birthYear << ", is that correct?\n\n";
	  cout << "\t 1) Yes, that's correct!\n";
	  cout << "\t 2) No, let me try that again...\n";
	  cin >> yearConf;
    while (cin.fail()){
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Please try again\n";
        cin >> yearConf;
      }
    yearConf = yearConf >0 && yearConf < 3 ? yearConf : 2;
    if (yearConf == 2) {
      cout << "No problem, we can try again...\n\n";
      keepTrying = true;
    }
  } while (keepTrying == true);
  zsign = zodiacDeChina(birthYear);
  cout << "\nOh, how exciting! You were born in the year of the " << zsign << "!\n\n";
}
  // END Chinese Zodiac Sign Calculator /w intro
//==============================================================================
//==============================================================================
//starting print message
//Below function started as an experiment in shifting between functions. It now prints the name entered in main and then plays a little game.
string printMess(string fname){
  string garbageCollection;
	char playGame;
	cout << "You are now in the printMess function.\n";
	cout << "\n\n\tSince we're here, why not play a game?\n";
	cout << "\n\t\tY) Yes, I would love to play a game!\n";
	cout << "\t\tN) Take a hike!\n";
	cin >> playGame;
	if (playGame == 'Y' || playGame == 'y') {
		cout << "You chose to play the game, that's great!\n";
		int punkedTimes = numberGame(fname);
		cout << "Oh man! You were punked, like, " << punkedTimes << " times!\n\n";
	}
	else if (playGame == 'N' || playGame == 'n') cout << "Maybe next time!\n\n";
  else {
    getline(cin, garbageCollection);
    cout << garbageCollection << "??? Maybe next time enter a valid response!\nYou can try again later from the main menu, if you like.\n\n";
  }
  outfile.open(namestor); //opening namestor.txt for writing as outfile
  outfile << fname; //copying contents of fname, which came from main.first_name, to outfile
  outfile.close(); //closing outfile, saving contents to namestor.txt
	cout << "I am now printing the name " << fname << " to outfile as requested.\n" << endl;
	return fname;
 }
 //End print message function
//==============================================================================
//==============================================================================
//Begin Menu Selection validation
int menuSelVal(int options){
  int selection;
  bool letMeGo;
  do {
  letMeGo = true;
  cin >> selection;
  while (cin.fail()) {
      cout << "Please try again\n\n";
      cin.clear();
      cin.ignore(256, '\n');
      cin >> selection;
    }
selection = selection > 0 && selection <= options ? selection : 99;
if (selection == 99) {
  cout << "Please choose a menu option 1 through " << options << ":\n";
  letMeGo = false;
}
} while (letMeGo == false);
return selection;
}
//End Menu Selection validation
//==============================================================================
//==============================================================================
//Copy section for function space
//End section for function space
//==============================================================================
//==============================================================================
//END OF PROGRAM
//==============================================================================