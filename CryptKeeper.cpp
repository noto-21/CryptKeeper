/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* May 1st, 2023
* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*---Include <directive>---*/

#include <iostream>//Includes <iostream> for In/Out
#include <string>//Includes <std::string> for linguistic input
#include <cctype>//Includes <cctype> for string/char specific logic

/*---Preprocessor Directives---*/

#ifdef _WIN32
const std::string clear_cmd = "cls";
#elif defined(__unix__)
const std::string clear_cmd = "clear";
#elif defined(__APPLE__)
const std::string clear_cmd = "clear";
#endif

/*---Functions---*/

bool Val(std::string inV)//Validates input of text for Caesar
{
	for (char c : inV)
		if ((c <= 47 || c >= 123) && c != 32)//If any unacceptable ASCII characters are detected
			return false;

	return true;
}

std::string Caesar(std::string inC, int keyC, int encdecC)
{
	std::string newStr = "";

	switch (encdecC)
	{
	case 1:
		for (char c : inC)
		{
			if (c != 32)
				newStr += (((c - '0') + keyC) % 75) + '0';
			else if (c == 32)
				newStr += " ";
			else
				newStr = "ERROR COMPUTING VALUE!";
		}

		return newStr;

		break;

	case 2:
		for (char c : inC)
		{
			if (c != 32)
				newStr += (((c - '0') + (75 - keyC)) % 75) + '0';
			else if (c == 32)
				newStr += " ";
			else
				newStr = "ERROR COMPUTING VALUE!";
		}

		return newStr;

		break;
	}
}
std::string Vigenere(std::string inV, char keyV, int encdecV)
{
	int keyVInt = std::tolower(keyV) - 'a';//Convert the key character to an integer index

	std::string newStr = "";

	switch (encdecV)
	{
	case 1://Encryption
		for (char c : inV)
		{
			if (std::isalpha(c))
			{
				char baseChar = std::isupper(c) ? 'A' : 'a';
				char shiftedChar = (c - baseChar + keyVInt) % 26 + baseChar;
				newStr += shiftedChar;
			}
			else if (std::isdigit(c))
			{
				char shiftedChar = (c - '0' + keyVInt) % 10 + '0';
				newStr += shiftedChar;
			}
			else
				newStr += c;//Preserve non-alphanumeric characters
		}

		return newStr;

	case 2://Decryption
		for (char c : inV)
		{
			if (std::isalpha(c))
			{
				char baseChar = std::isupper(c) ? 'A' : 'a';
				char shiftedChar = (c - baseChar - keyVInt + 26) % 26 + baseChar;
				newStr += shiftedChar;
			}
			else if (std::isdigit(c))
			{
				char shiftedChar = (c - '0' - keyVInt + 10) % 10;
				if (shiftedChar < 0)//Fix the negative modulus
					shiftedChar += 10;
				newStr += shiftedChar + '0';
			}
			else
				newStr += c;//Preserve non-alphanumeric characters
		}

		return newStr;
	}

	return ""; // Return an empty string if the encdecV value is invalid
}

//main method - returns '0'
int main()
{
	/*---Declarations---*/

	int keyC = 7, choice[2];//Declares all necessary integers

	std::string in, keyV;//Declares all necessary strings

	char repeat = 'C';//Declares all necessary characters

	//Menu
	do
	{
		/*---Operations---*/

		system(clear_cmd.c_str());//Clear console

		//Prints list of acceptable characters for the user
		std::cout << "/*\nFor reference, acceptable characters include:\n";
		for (int c = 48; c <= 122; c++/*lol*/)
			std::cout << char(c) << "\t";
		std::cout << "\n\nPlease enjoy the program :]\n*/";

		//Intro
		std::cout << "\n\nGreetings, and welcome to Crypt-Keeper!\nCrypt-Keeper can encrypt and decrypt\nCaesar and Vigen\x8Are cipher-text\nincluding characters ranging between\ndecimal-values >48-122< on the ASCII table."
			<< "\n\nWould you like to:\n\n[1]Encrypt input, or\n[2]Decrypt input?\nPlease make your selection of [1]/[2] below:\n-->";
		std::cin >> choice[0];
		while (choice[0] != 1 && choice[0] != 2)//Prevents erroneous input
		{
			std::cout << "\n\nINVALID INPUT!  Please input only those values which correspond to given options [i.e. 1 or 2]: --> ";
			std::cin >> choice[0];
		}

		switch (choice[0])//Switch for encrypt/decrypt
		{
		case 1://Encrypt
		{
			std::cout << "\n\nWould you like to use:\n\n[1]Caesar Cypher, or\n[2]Vigen\x8Are Cypher?\nPlease make your selection of [1]/[2] below:\n-->";
			std::cin >> choice[1];
			while (choice[1] != 1 && choice[1] != 2)//Prevents erroneous input
			{
				std::cout << "\n\nINVALID INPUT!  Please input only those values which correspond to given options [i.e. 1 or 2]: --> ";
				std::cin >> choice[1];
			}

			switch (choice[1])//Switch for Caesar/Vigenere
			{
			case 1://Caesar
				std::cout << "\n\nPlease input your text to be encrypted via Caesar Cypher:" << std::endl;
				std::getline(std::cin >> std::ws, in);//Gets whole input on line
				//Action contingent on correct/incorrect input
				if (Val(in))
					std::cout << "\nYour Caesar-encrypted text is: " << Caesar(in, keyC, choice[0]);//Output final value
				else
					std::cout << "\nINVALID!  Please input expected characters only [i.e. ASCII values 48-122]!";//Output error message and restart

				break;

			case 2://Vigenere
				std::cout << "\n\nPlease input your chosen encryption key [ASCII Char. 97-122; lowercase letters a-z]: --> ";
				std::cin >> keyV;
				while (keyV[0] < 'a' || keyV[0] > 'z' || keyV[0] == ' ' || keyV.length() != 1)
				{
					std::cout << "\nINVALID!  Please input a key corresponding to ASCII Char. 97-122: --> ";
					std::cin >> keyV;
				}
				std::cout << "\nPlease input your text to be encrypted via Vigen\x8Are Cypher:" << std::endl;
				std::getline(std::cin >> std::ws, in);//Gets whole input on line
				//Action contingent on correct/incorrect input
				if (Val(in))
					std::cout << "\nYour Vigen\x8Are-encrypted text is: " << Vigenere(in, keyV[0], choice[0]);//Output final value
				else
					std::cout << "\nINVALID!  Please input expected characters only [i.e. ASCII values 48-122]!";//Output error message and restart

				break;
			}
		}
		break;

		case 2://Decrypt
		{
			std::cout << "\n\nWould you like to use:\n\n[1]Caesar Cypher, or\n[2]Vigen\x8Are Cypher?\nPlease make your selection of [1]/[2] below:\n-->";
			std::cin >> choice[1];
			while (choice[1] != 1 && choice[1] != 2)
			{
				std::cout << "\n\nINVALID INPUT!  Please input only those values which correspond to given options [i.e. 1 or 2]: ";
				std::cin >> choice[1];
			}

			switch (choice[1])//Switch for Caesar/Vigenere
			{
			case 1://Caesar
				std::cout << "\n\nPlease input your text to be decrypted via Caesar Cypher:" << std::endl;
				std::getline(std::cin >> std::ws, in);//Gets whole input on line
				//Action contingent on correct/incorrect input
				if (Val(in))
					std::cout << "\nYour Caesar-decrypted text is: " << Caesar(in, keyC, choice[0]);//Output final value
				else
					std::cout << "\nINVALID!  Please input expected characters only [i.e. ASCII values 48-122]!";//Output error message and restart

				break;

			case 2://Vigenere
				std::cout << "\n\nPlease input your chosen decryption key [ASCII Char. 97-122; lowercase letters a-z]: --> ";
				std::cin >> keyV;
				while (keyV[0] < 'a' || keyV[0] > 'z' || keyV[0] == ' ' || keyV.length() != 1)
				{
					std::cout << "\nINVALID!  Please input a key corresponding to ASCII Char. 97-122: --> ";
					std::cin >> keyV;
				}
				std::cout << "\n\nPlease input your text to be decrypted via Vigen\x8Are Cypher:" << std::endl;
				std::getline(std::cin >> std::ws, in);//Gets whole input on line
				//Action contingent on correct/incorrect input
				if (Val(in))
					std::cout << "\nYour Vigen\x8Are-decrypted text is: " << Vigenere(in, keyV[0], choice[0]);//Output final value
				else
					std::cout << "\nINVALID!  Please input expected characters only [i.e. ASCII values 48-122]!";//Output error message and restart

				break;
			}
		}
		break;

		default:
			std::cout << "\n\nERROR ENCRYPTING/DECRYPTING!  RESTART NOW!";

			break;
		}

		/*---Final Output---*/

		//Ask user if they want to repeat the program
		std::cout << "\n\n\nBegin again? [C/E]: ";
		std::cin >> repeat;

		switch (repeat)
		{
		case 'C':case 'c':case 'E':case 'e':
			break;
		default:
			while (repeat != 'C' && repeat != 'c' && repeat != 'E' && repeat != 'e')
			{
				std::cout << "\nINVALID!  Please enter either [C/E]: ";
				std::cin >> repeat;
			}
		}
	}while (repeat == 'C' || repeat == 'c');

	std::cout << "\n\nThank you for choosing Crypt-Keeper! :]\n\n" << std::endl;//Final message

	/*---Concluding operations---*/

	return 0;//Returns '0' to 'main()'
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
