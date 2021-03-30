/*<fstream> Header which is the blend of ifstream and ofstream which specifically are used
  to read, create and  write to files respectively*/
/*<ios> header is used to call out a function streamsize, an integral type which is
 used to represent the size of input buffer*/
/*<limits> header is used to call out a function of numeric_limits<streamsize>::max(),
  which is used to adjust max no. of character that are to be ignored.*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <ios>
#include <limits>

//standard library selection
using namespace std;

/*function prototype indicates the datatype and number of
  function parameters, also specifiying the function's return type*/
void storetofile(char[], ofstream&);
//function prototype to perform encryption of a file entered by user
void EncryptionOfFile(char, fstream&, fstream&);
//function prototype tp perform decryption of a file that is previously decrypted
//by our program
void DecryptionOfFile(char, fstream&, fstream&);
void messageEncryptDecrypt(char[], char[], int, int);

/*main function of int-type specifying that the main function will
  return integer of int type at the end of program after the execution.*/
int main()
{
    //program starts
    cout << "\t\t\t\t\t\t--------------------------------------------------\n"
         << "\t\t\t\t\t\t| Welcome to SHM's encryption decryption service |\n"
         << "\t\t\t\t\t\t-------------------------------------------------- \n\n";
    //Asking the user to chose from different services that we offer
    int process{};
    /*declaring the datatype and name of the variable and array because of which
      a specific size of variable is prearranged in the memory, initially
      the variables have a garbage value stored so {} are used to
      initialize the variable*/
    char decision1{}, NameOfFile[50], character{};
    //declaring object of different files that the user will give for encryption and
    //other to store encrypted and decrypted messages
    fstream Encrypt, TemporaryEncrypt, Decrypt, DecryptedFile;
    do
    {

        do
        {
            //asking the user about the service to be used
            cout << "What would you like to do?\n"
                 << " > For encrypting a file (Press 1)\n" << " > For decrypting a file (Press 2)\n"
                 << " > For typing a message  (Press 3)\n";
            cin >> process;
            //employing error check 1 to inspect and respond to the invalid input by user.
            if (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Try Again!\n\n";
                //cin.clear() makes error flags clear, to ignore values that we dont need
                //cin.ignore() ignores anything on the line and jumps to next line
                /*numeric_limits<streamsize>::max() is used to adjust max no. of characters
                  that are to be ignored.*/
            }
            else if (process < 1 || process > 3)
            {
                cout << "Try Again!\n";
            }

        } while (!(cin) || process < 1 || process > 3);
        //if the user wants to select a file for encryption
        if (process == 1)
        {
            //asking the user to enter name of the file that is stored in the same
            //folder in which the program is stored
            cout << "\nEnter name of file (with extension only .txt compatible): ";
            do
            {
                cin >> NameOfFile;
                //opening the file entered by user to read the message
                Encrypt.open(NameOfFile, ios::in);
                //employing error check 2 to inspect and respond to the invalid input by user.
                if (!Encrypt)
                {
                    cout << "\nerror occurred; Your File cannot be found\n"
                         << "Try Again!\n" << "Enter name of file (with extension): ";
                }

            } while (!Encrypt);
            //opening the file to store the encrypted text after reading it from the
            //main file
            TemporaryEncrypt.open("TemporaryFile.txt", ios::out);
            //employing error check 3 to inspect and respond to the invalid input by user.
            if (!TemporaryEncrypt)
            {
                cout << "\nerror occurred while opening or creating the file\n";
            }
            //calling the function to perform encryption of given file
            EncryptionOfFile(character, TemporaryEncrypt, Encrypt);
            //variable declaration to store the decision if the encrypted file needs to be
            //decrypted
            int decision;
            do
            {
                //asking the user if the file is to be decrypted
                cout << "\nDo you want to decrypt the file\n"
                     << " > If 'Yes' (Press 1)" << "\n > If 'No'  (Press 2)\n";
                cin >> decision;
                //employing error check 4(same as 1) to inspect and respond to the invalid input by user.
                if (!cin)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Try Again!\n";
                }
                else if (decision < 1 || decision > 2)
                {
                    cout << "Try Again!\n";
                }

            } while (!(cin) || decision < 1 || decision > 2);
            //if the user wants to decrypt the file then
            if (decision == 1)
            {
                //opening a file to write decrypted message in it
                Encrypt.open("SHM'sManagementReport1.txt", ios::out);
                //employing error check 5 to inspect and respond to the invalid input by user.
                if (!Encrypt)
                {
                    cout << "\nerror occurred; Your file cannot be found!\n";
                    return 0;
                }
                //opening the temporary file to read encrypted text from it decrypt
                //it and store it in SHM'sManagementReport1.txt
                TemporaryEncrypt.open("TemporaryFile.txt", ios::in);
                //employing error check 6 to inspect and respond to the invalid input by user.
                if (!TemporaryEncrypt)
                {
                    cout << "\nerror occurred while opening or creating the file\n";
                    return 0;
                }
                //calling function to decrypt the encrypted file
                DecryptionOfFile(character, TemporaryEncrypt, Encrypt);
                cout << " and named as SHM'sManagementReport1.txt\n";
            }



        }
            //if the user wants to decrypt a file that has been encrypted beforehand
            //from this program
        else if (process == 2)
        {
            //asking the user to enter name of encrypted file
            cout << "\nEnter name of file (with extension): ";
            do
            {
                cin >> NameOfFile;
                //opening the file to read encrypted text from it
                Decrypt.open(NameOfFile, ios::in);
                //employing error check 7 to inspect and respond to the invalid input by user.
                if (!Decrypt)
                {
                    cout << "\nerror occurred; Your File cannot be found\n"
                         << "Try Again!\n" << "Enter name of file (with extension): ";
                }

            } while (!Decrypt);
            //opening a file to store text after decrypting the text from entered file
            DecryptedFile.open("SHM'sManagementReport2.txt", ios::out);
            //employing error check 8 to inspect and respond to the invalid input by user.
            if (!DecryptedFile)
            {
                cout << "\nerror occurred while opening or creating the file\n";
            }
            //calling function to decrypt the encrypted file
            DecryptionOfFile(character, Decrypt, DecryptedFile);
            cout << "and named as SHM'sManagementReport2.txt\n";
        }
        else if (process == 3)
        {
            /*declaring and initialising variables and arrays that are required later
              in the program*/
            char message[1000] = {};
            char encryption[1000] = {};
            int decision5 = {}, FileDecision1 = {};

            /*cin.ignore() is use to clear or disregard the characters from the
              input buffer*/
            cin.ignore();
            cout << "Enter the message: ";
            cin.getline(message, 1000);

            //calling messageEncryptDecrypt function
            messageEncryptDecrypt(message, encryption, decision5, FileDecision1);

        }
        do
        {
            cout << "\nDo you want to use our service again?\n"
                 << " 'Y' for Yes  |  'N' for no \n";
            cin >> decision1;
            //employing error check 9 to inspect and respond to the invalid input by user.
            if (decision1 != 'y' && decision1 != 'n' && decision1 != 'Y' && decision1 != 'N')
            {
                cout << "Invalid input !\n";
            }
        } while (decision1 != 'y' && decision1 != 'n' && decision1 != 'Y' && decision1 != 'N');

    } while (decision1 == 'y' || decision1 == 'Y');


    if (decision1 == 'n' || decision1 == 'N')
    {
        cout << endl << "\t\t\t\t\t----------------------------------------\n"
                     << "\t\t\t\t\t| Thank you for using our service :-)  |\n"
                     << "\t\t\t\t\t----------------------------------------\n\n";
        exit(0);
    }
    //indicates success status of program
    return 0;
}

//function defination
void EncryptionOfFile(char character1, fstream& TemporaryEncrypt1, fstream& Encrypt1)
{
    //variable to store encryption key of the program
    int EncryptKey = 50;
    //loop to read the data from the file character by character including the spaces hence using
    //"noskipws" that prevents the cursor to skip spaces in the text, encrypting it and storing the
    //encrypted data in a temporary file
    while (Encrypt1 >> noskipws >> character1)
    {
        //adding key to the ASCII value of the character
        character1 += EncryptKey;
        //storing the encrypted text in a temporary file
        TemporaryEncrypt1 << character1;
        //incrementing the key by 7 so that the in the ASCII value of next character an increment of
        //encrypt key + 7 can be made to achieve more promising and secure encryption
        EncryptKey += 7;
    }
    //closing the temporary file
    TemporaryEncrypt1.close();
    //closing the given user file
    Encrypt1.close();

    //printing that the file has been encrypted successfully
    cout << "\nYour file has been encrypted successfully and named as TemporaryFile.txt\n";


}

//function defination
void DecryptionOfFile(char character2, fstream& TemporaryEncrypt2, fstream& Encrypt2)
{
    //declaring a variable to store the decrypt key
    int DecryptKey = 50;
    //loop to read through the the encrypted file character by character including the spaces hence using
    //"noskipws" that prevents the cursor to skip spaces in the text, decrypting it and storing the
    //decrypted data in a report file
    while (TemporaryEncrypt2 >> noskipws >> character2)
    {
        //decrypting the character
        character2 -= DecryptKey;
        //storing it in the report file
        Encrypt2 << character2;
        //decrementing the key by 7 so that the in the ASCII value of next character a decrement of
        //encrypt key + 7 can be made to decrypt the text to its original form
        DecryptKey += 7;
    }
    //printing that the file has been decrypted successfully
    cout << "The file has been decrypted successfully ";
    //closing both the files
    Encrypt2.close();
    TemporaryEncrypt2.close();
}

//function defination
void storetofile(char encryption[], ofstream& encryptionfile)
{
    for (int copying = 0; encryption[copying] != '\0'; copying++)
    {
        encryptionfile << encryption[copying];
    }
}

//function defination
void messageEncryptDecrypt(char message[], char encryption[], int decision5, int filedecision1)
{
    //for loop for encrypting the message entered with the Encrypt-Key
    for (int index = 0, EncryptKey1 = 50;message[index] != '\0';index++, EncryptKey1 += 7)
    {
        message[index] += EncryptKey1;
    }
    //for loop for  storing the encrypted message in another array as per requirement
    for (int storing = 0; message[storing] != '\0';storing++)
    {
        encryption[storing] = message[storing];
    }
    cout << endl;
    cout << "Encrypted Message: " << message << endl << endl;
    do
    {
        cout << "Do you want to store this in file:\n > If Yes (Press 1)\n > If No  (press 2)\n";
        cin >> filedecision1;
        //employing error check 10(same as 1) to inspect and respond to the invalid input by user.
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Try Again!\n";
        }
        else if (filedecision1 < 1 || filedecision1 > 2)
        {
            cout << "Try Again!\n";
        }
    } while (!(cin) || filedecision1 < 1 || filedecision1 > 2);
    if (filedecision1 == 1)
    {
        //ofstream function opens the file
        ofstream encryptionfile("SHM'sManagementReport.txt");
        cout << "Your message has been encrypted and stored in SHM'sManagementReport.txt successfully\n";
        //calling storetofile function
        storetofile(encryption, encryptionfile);
        //close function to close the file
        encryptionfile.close();
    }

    do
    {
        cout << "Do you want to Decrypt the Encrypted string\n > If Yes (Press 1)\n > If No  (press 2) \n";
        cin >> decision5;
        //employing error check 11(same as 1) to inspect and respond to the invalid input by user.
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Try Again!\n";
        }
        else if (decision5 < 1 || decision5 > 2)
        {
            cout << "Try Again!\n";
        }
    } while (!(cin) || decision5 < 1 || decision5 > 2);

    if (decision5 == 1)
    {
        cout << "\nYour message has been Decrypted successfully\n";
        int filedecision2;
        cout << "Decrypted String: ";
        //for loop used to decrypt the encrypted message with Decrypt-Key
        for (int index = 0, DecryptKey1 = 50;encryption[index] != '\0';index++, DecryptKey1 += 7)
        {
            encryption[index] -= DecryptKey1;
            cout << encryption[index];
        }
        cout << endl << endl;
        do
        {
            cout << "Do you want to make another file to store your encrypted and decrypted message:\n"
                 << "[NOTE:This file cannot be decrypted with our system as it contains non - cyphered text] "
                    "\n > If Yes (Press 1)\n > If No  (press 2)\n";
            cin >> filedecision2;
            //employing error check 12(same as 1) to inspect and respond to the invalid input by user.
            if (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Try Again!\n";
            }
            else if (filedecision2 < 1 || filedecision2 > 2)
            {
                cout << "Try Again!\n";
            }
        } while (!(cin) || filedecision2 < 1 || filedecision2 > 2);
        if (filedecision2 == 1)
        {
            cout << "Your message has been stored in SHM'sManagementReport3.txt successfully.\n";
            //ofstream function opens the file
            ofstream reportfile("SHM'sManagementReport3.txt");
            reportfile << "Encrypted Text:" << endl;
            //calling storetofile function
            storetofile(message, reportfile);
            reportfile << endl;
            reportfile << "Decrypted Text:" << endl;
            //calling storetofile function
            storetofile(encryption, reportfile);
            //close function to close the file
            reportfile.close();
        }
    }
}
