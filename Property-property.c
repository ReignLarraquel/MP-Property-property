/* 
   Description: This is a turn-based two-player board game. Players 
   compete to acquire wealth by buying or renting properties. 
   The game ends when a player goes bankrupt i.e he does not have enough 
   money to pay rent.
   Programmed by: Reign Elaiza Larraquel S15
   Last modified: 02/07/2022
   Version: 1
   Acknowledgements: 
    - Use of Structs: https://www.youtube.com/watch?v=7zXqMD6Fj_E
    - Use of Rand: Sir Bon Jorelle Domingo (SHS iACADEMY Teacher)
    - Use of Getch: https://www.geeksforgeeks.org/getch-function-in-c-with-examples/
*/

#include <stdio.h>
#include <stdlib.h> // To use rand() for a randomized number
#include <time.h> // To get a randomized number EVERY use of the rand()
#include <conio.h> // Allows the function of getch()

/* Type of positions the player may land on */
#define GO 'G'
#define FEELIN_LUCKY 'L'
#define JAIL 'J'
#define PROPERTY 'P'
#define ELECTRIC_COMPANY 'E'
#define RAILROAD 'R'

/* True or False */
#define TRUE 1
#define FALSE 0

/* Player Status */
typedef struct Player
{
    int nPlayer;
    int nCash;
    int nPosition;
    int nJail;
} Player;

/* Rent Value */
typedef struct Rent
{
    int nRailRent;
    int nElecRent;
} Rent;

/* Cost Value */
typedef struct Cost
{
    int nRailCost;
    int nElecCost;
    int nRenovCost;
} Cost;

/* Range of amounts in Feelin' Lucky */
typedef struct LuckyRange
{
    int nPrimeMax;
    int nPrimeMin;
    int nNonPrimeMax;
    int nNonPrimeMin;
} LuckyRange;

/* Displays the menu for the game */
void menuDisplay()
{
    printf("\n-----------------------------------------------\n");
    printf("\t     PROPERTY... PROPERTY\n");
    printf("-----------------------------------------------\n\n");

    printf(" [1] Start a New Game\n");
    printf(" [2] Settings\n");
    printf(" [3] Exit The Program\n");

}

/* Displays the settings for the game */
void settingDisplay()
{
    printf("\n-----------------------------------------------\n");
    printf("\t           SETTINGS\n");
    printf("-----------------------------------------------\n\n");

    printf("Rent:\n");
    printf(" [1] Change Railroad Rent Value\n");
    printf(" [2] Change Electric Company Rent Value\n");

    printf("\nCost:\n");
    printf(" [3] Change Railroad Cost Value\n");
    printf(" [4] Change Electric Company Cost Value\n");
    printf(" [5] Change Cost of Renovation\n");

        
    printf("\nOther Settings:\n");
    printf(" [6] Change Initial Cash Value\n");
    printf(" [7] Change Range of Amounts in Feelin' Lucky\n");

    printf("\nGame End Condition:\n");
    printf(" [8] Set Specific Cash Limit\n");
    printf("-----------------------------------------------");
    printf("\nEnter [9] to go back to menu\n\n");
}

/* Informs the user when the value they input is invalid */
void invalid()
{
    printf("\n[INVALID INPUT]\n");
}

/* 
   This function prints a text according to the settings the user
   planning to change in the settings so that it is easier to identify 
   and understand. The settings consist of:
    - Railroad Rent
    - Electric Company Rent
    - Railroad Cost
    - Electric Company Cost
    - Renovation Cost
    - Initial Cash

    This allows the program to change 6 values without repeating the same 
    line of codes due to needing different title texts

   @param nAnswer   The type of setting that the user plans to change

   @return  Title of the setting the user plans to change
*/
void changeValueDisplay(int nAnswer)
{
    switch(nAnswer)
    {
        case 1:
            printf("\t  Change Railroad Rent Value\n");
            break;
        
        case 2:
            printf("      Change Electric Company Rent Value\n");
            break;
        
        case 3:
            printf("\t  Change RailRoad Cost Value\n");
            break;
        
        case 4:
            printf("      Change Electric Company Cost Value\n");
            break;
        
        case 5:
            printf("\t Change Renovation Cost Value\n");
            break;
        
        case 6:
            printf("\t  Change Initial Cash Value\n");
            break;
    }
}

/*
   The user inputs a new cash value that will replace the original 
   values of the following settings:
    - Railroad Rent
    - Electric Company Rent
    - Railroad Cost
    - Electric Company Cost
    - Renovation Cost
    - Initial Cash

    The function will continue to loop and ask the user to input a new 
    value until the value that the user places is more than 1 
    
   Precondition: nAnswer ranges from 1 - 6

   @param nAnswer   The type of setting that the user plans to change

   @return  The new value that the user has inputted
*/
int changeSettingValue(int nAnswer)
{
    int nNewVal = 0;

    while(nNewVal < 1) 
    {
        printf("\n-----------------------------------------------\n");
        changeValueDisplay(nAnswer);
        printf("-----------------------------------------------\n\n");

        printf("Input: ");
        scanf(" %d", &nNewVal); // Inputs the new value

        if(nNewVal < 1) invalid(); 
    }

    return nNewVal;
}

/* 
   Changes the range of amounts in Feeling' Lucky such as the maximum 
   amount if the dice value is prime, minimum amount if the dice value 
   is prime, maximum amount if the dice value is not prime, and minimum 
   amount if the dice value is not prime.

    @param luckyRange   The range of amount in Feelin' Lucky, including 
                        the minimum and maximum amount for the dice 
                        value if the dice value is prime and the minimum 
                        and maximum amount for the dice value if the 
                        dice value is NOT prime

   @return New values to replace the original values of the range of 
   amount in Feelin' Lucky
*/
void setLuckyRange(LuckyRange* luckyRange)
{
    luckyRange -> nPrimeMax = 0; // Resets value to 0
    luckyRange -> nNonPrimeMax = 0; // Resets value to 0

    printf("\n-----------------------------------------------\n");
    printf("   Change Range of Amounts in Feelin' Lucky\n");
    printf("-----------------------------------------------\n\n");

    printf("Dice value is a prime number:\n");

    // Inputs the new maximum amount if the dice value is prime
    while(luckyRange -> nPrimeMax < 1)
    {
        printf(" Max: ");
        scanf(" %d", &luckyRange -> nPrimeMax);

        if(luckyRange -> nPrimeMax < 1)
        {
            invalid();
            printf(" New");
        }
 
    }

    // Sets the minimum amount to the maximum amount if the dice value is prime
    luckyRange -> nPrimeMin = luckyRange -> nPrimeMax; 

    // Inputs the new minimum amount if the dice value is prime
    while(luckyRange -> nPrimeMin >= luckyRange -> nPrimeMax) 
    {    
        printf(" Min: ");
        scanf(" %d", &luckyRange -> nPrimeMin);

        if(luckyRange -> nPrimeMin >= luckyRange -> nPrimeMax) 
        {
            invalid();
            printf(" New");
        }
    }

    printf("\nDice value is NOT a prime number:\n");

    // Inputs the new maximum amount if the dice value is NOT prime
    while(luckyRange -> nNonPrimeMax < 1)
    {
        printf(" Max: ");
        scanf(" %d", &luckyRange -> nNonPrimeMax);

        if(luckyRange -> nNonPrimeMax < 1)
        {
            invalid();
            printf(" New");
        }
    } 

    // Sets the minimum amount to the maximum amount if the dice value is NOT prime
    luckyRange -> nNonPrimeMin = luckyRange -> nNonPrimeMax;
    
    // Inputs the new minimum amount if the dice value is NOT prime
    while(luckyRange -> nNonPrimeMin >= luckyRange -> nNonPrimeMax)
    {    
        printf(" Min: ");
        scanf(" %d", &luckyRange -> nNonPrimeMin);

        if(luckyRange -> nNonPrimeMin >= luckyRange -> nNonPrimeMax)         
        {
            invalid();
            printf(" New");
        }
    }
}

/*
   This function allows the user to activate another game end condition
   where the game ends when a specific cash-on-hand is reached. The
   specific cash-on-hand that the user must reach should be more than 
   the initial cash to not cause the game to end instantly. The user may
   also choose between which condition (or both) must be satisfied.

   @param nInitialCash  To know the minimum amount the specific 
                        cash-on-hand must not reach.
   @param nCashLimit    The variable that will contain the specific 
                        cash-on-hand
   @param nEndCond      Will determine what end condition must be 
                        satisfied. If "1" the player losees if they do 
                        not have enough cash to pay rent, if "2" the 
                        player loses when the other player reaches a 
                        specific cash-on-hand, and if "3" the player 
                        loses when both conditions are satisfied.

   @return The specific cash-on-hand and chosen end game condition.
*/
void setCashLimit (int nInitialCash, int* nCashLimit, int* nEndCond)
{
    *nEndCond = 0; // Resets value to 0
    *nCashLimit = 0; // Resets value to 0


    while(*nCashLimit <= nInitialCash)
    {    
        printf("\n-----------------------------------------------\n");
        printf("\t  Game End Condition\n");
        printf("-----------------------------------------------\n\n");

        printf("Cash limit must not be less than %d\n", nInitialCash);
        printf("\nSet Specific Cash Limit:\n");

        // Inputs the specific cash-on-hand
        printf("Input: ");
        scanf(" %d", nCashLimit);

        if(*nCashLimit <= nInitialCash) invalid();
    }

    // Determines which end condition must be satisfied
    while(*nEndCond < 1 || *nEndCond > 3)
    {    
        printf("\n-----------------------------------------------\n");
        printf("  Choose which condition will end the game:\n");
        printf("-----------------------------------------------\n\n");

        printf(" [1] Not enough cash\n");
        printf(" [2] Specific Cash-on-hand Reached\n");
        printf(" [3] Both\n");

        printf("\nInput: ");
        scanf(" %d", nEndCond);

        if(*nEndCond < 1 || *nEndCond > 3) invalid();
    }
}

/* 
   The settings allows  the user to change zero or more of the initial 
   settings of the game. This function will call another function 
   depending on what the user plans to change specifically and it will 
   replace the initial value of the setting to what the user inputs.
   
   @param nAnswer       This will determine which setting will be edited
                        1 - Rent for Railroad
                        2 - Rent for Electric Company
                        3 - Cost for Railroad
                        4 - Cost for Electric Company
                        5 - Cost for Renovation
                        6 - Initial Cash
                        7 - Range of Amounts in Feelin' Lucky
                        8 - Game End Condition
    @param nInitialCash The initial cash of the player in the start of 
    @param rent         Contains the values of the rent for Railroad and 
                        Electric Company
    @param cost         Contains the value of the cost for Railroad, 
                        Electric Company, and the renovation
                        the game
    @param luckyRange   The range of amount in Feelin' Lucky, including 
                        the minimum and maximum amount for the dice value 
                        if the dice value is prime and the minimum and 
                        maximum amount for the dice value if the dice value 
                        is NOT prime
    @param nCashLimit   The specific cash-on-hand the players must reach
    @param nEndCond     Will determine what end condition must be 
                        satisfied

    @return The new values of the edited settings
*/
void settings(int nAnswer, int* nInitialCash, Rent* rent, Cost* cost, LuckyRange* luckyRange, int* nCashLimit, int* nEndCond)
{
    switch(nAnswer)
    {
        case 1: 
            rent -> nRailRent = changeSettingValue(nAnswer);
            break;

        case 2: 
            rent -> nElecRent = changeSettingValue(nAnswer);
            break;
            
        case 3: 
            cost -> nRailCost = changeSettingValue(nAnswer);
            break;

        case 4: 
            cost -> nElecCost = changeSettingValue(nAnswer);
            break;
        
        case 5: 
            cost -> nRenovCost = changeSettingValue(nAnswer);
            break;

        case 6: 
            *nInitialCash = changeSettingValue(nAnswer);
            break;

        case 7: 
            setLuckyRange(luckyRange); 
            break;

        case 8: 
            setCashLimit(*nInitialCash, nCashLimit, nEndCond); 
            break;      
    }
}

/*
   This function presents the users with options in a form of a menu. 
   The user may choose to start a new game, change the settings, or exit 
   the program.

   @param nGame         The status of the game. "1" is to start a new 
                        game, "2" to change the settings, and "3" to 
                        exit the program.
    @param nInitialCash The initial cash of the player in the start of 
    @param rent         Contains the values of the rent for Railroad and 
                        Electric Company
    @param cost         Contains the value of the cost for Railroad, 
                        Electric Company, and the renovation
                        the game
    @param luckyRange   The range of amount in Feelin' Lucky, including 
                        the minimum and maximum amount for the dice value 
                        if the dice value is prime and the minimum and 
                        maximum amount for the dice value if the dice value 
                        is NOT prime
    @param nCashLimit   The specific cash-on-hand the players must reach
    @param nEndCond     Will determine what end condition must be 
                        satisfied.

    @return The new values of the edited settings and the status of the 
            game
*/
void menu(int* nGame, int* nInitialCash, Rent* rent, Cost* cost, LuckyRange* luckyRange, int* nCashLimit, int* nEndCond)
{
    int nAnswer = 0; // This will determine which setting will be edited
    *nGame = 0; // Resets the value to 0

    while(*nGame != 3 && *nGame != 1)
    {
        // Displays the menu
        menuDisplay();
        
        printf("\nInput: ");
        scanf("%d", nGame);
        
        if(*nGame == 2)
        {
            nAnswer = 0;

            // Displays the settings
            while(nAnswer != 9)
            {
                settingDisplay();

                printf("Input: ");
                scanf("%d", &nAnswer);

                // Calls the function to change the settings
                settings(nAnswer, nInitialCash, rent, cost, luckyRange, nCashLimit, nEndCond);

                if(nAnswer < 1 || nAnswer > 9) invalid();
            } 
        } 
        else if(*nGame > 3 || *nGame < 1) 
        {
            invalid();
        }
    }
}


/* Rolls the dice in the range of 1 to 6 */
int rollDice()
{
    srand(time(NULL)); // To get a randomized number every run

    printf("\n\nPress any key to roll the dice...\n");
    getch();

    return rand() % 6 + 1; //Returns a value between the range of 1 - 6
}

/* 
   Displays the title of property according to the board position 
   
   @param nPosition     The position of the property in the board

   @return  The title of the property
*/
void boardPosition(int nPosition)
{   
    switch (nPosition)
    {
    case 0: 
        printf("Go"); 
        break;

    case 1: 
        printf("Tree House\t\t\t"); 
        break;

    case 2: 
        printf("Electric Company\t\t"); 
        break;

    case 3: 
        printf("Beach House\t\t"); 
        break;

    case 4: 
        printf("Jail Time"); 
        break;

    case 5: 
        printf("Castle\t\t\t"); 
        break;

    case 6: 
        printf("Feelin' Lucky"); 
        break;

    case 7: 
        printf("Railroad\t\t\t"); 
        break;
    
    case 8: 
        printf("Igloo\t\t\t"); 
        break;

    case 9: 
        printf("Farm House\t\t\t"); 
        break;
    }
}

/* 
   Returns a character that determines the type of the position the 
   player landed on
   G - Go
   L - Feelin' Lucky
   J - Jail Time
   P - House Property
   E - Electric Company
   R - Railroad

   @param nPosition - The position of the player

   @return character determining the type of the position
*/
char positionType(int nPosition)
{
    switch (nPosition)
    {
    case 0: 
        return GO; 
        break;

    case 1: 
        return PROPERTY; 
        break;

    case 2: 
        return ELECTRIC_COMPANY; 
        break;

    case 3: 
        return PROPERTY; 
        break;

    case 4: 
        return JAIL; 
        break;

    case 5: 
        return PROPERTY; 
        break;

    case 6: 
        return FEELIN_LUCKY; 
        break;

    case 7: 
        return RAILROAD; 
        break;
    
    case 8: 
        return PROPERTY; 
        break;

    case 9: 
        return PROPERTY; 
        break;

    default: 
        return ' ';
    }
}

/* 
   Extracts the status of the needed property according to the position 
   the player lands. Status meaning:
    - If the value of the property is 0, nobody owns this property
    - If the value of the property is 1, Player 1 owns this property
    - If the value of the property is 2, Player 2 owns this property
    - If the value of the property is 3, Player 1 owns this RENOVATED 
      property
    - If the value of the property is 4, Player 2 owns this RENOVATED 
      property

   To extract the status, it uses a For-loop that will keep looping 
   until the counter has the same value as the position of the player. 
   nPlace is the place value of the property that needs to be extracted, 
   example if the function needed to extract the "4" in 110040100 then 
   the place value would be 10000. nExtNum is the place value after the 
   property that needs to be extracted, this will be used to remove all 
   the numbers that follow after the property.
    
   Precondition: nProperties is a 9 digit integer
   Precondition: nProperties must consist of only the numbers: 0, 1, 2, 
                 3, and 4

   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPosition     The position of the property the player landed

   @return  The status of the property the player landed on
*/
int getProperty(int nProperties, int nPosition)
{
    int nPlace = 1; // place value of the property
    int nExtNum = 1; // the place value following after the property
    int nCounter;
    int nProperty;

    for(nCounter = 1; nCounter <= nPosition; nCounter++)
    {
        nPlace *= 10;

        if(nCounter == nPosition) nProperty = nProperties % nPlace / nExtNum;

        nExtNum *= 10;
    }

    return nProperty;
}

/* 
   Checks if the player has any properties owned by them

   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPlayer       The player that is being checked

    @return     1 if the player has any properties and 0 if the player 
                does not have any properties
*/
int checkProperties(int nProperties, int nPlayer)
{
    int nIsOwned = FALSE;
    int nCounter;

    for(nCounter = 1; nCounter <= 9; nCounter++)
    {
        if(getProperty(nProperties, nCounter) == nPlayer) nIsOwned = TRUE;
        else if(getProperty(nProperties, nCounter) == (nPlayer + 2)) nIsOwned = TRUE;
    }

    return nIsOwned; 
}

/*
   Checks if a player's owned house property is renovated or not.
    - "1" means the property is not renovated
    - "2" means the property is renovated

   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPosition     The specific house property that will be checked 
                        if renovated or not
   @param nPlayer       The owner of the house property

   @return The status of an owned house property if renovated or not
*/
int checkRenovation(int nProperties,int nPosition, int nPlayer)
{
    if(getProperty(nProperties, nPosition) == nPlayer) return 1;
    else if(getProperty(nProperties, nPosition) == (nPlayer + 2)) return 2;
    else return 0;
}

/*
   Gets the cost of the property according its type

   @param nPosition     The position of the property
   @param cost          A struct that contains the cost for the Electric 
                        Company and Railroad property
   
   @return The cost of the property
*/
int getPropertyCost(int nPosition, Cost cost)
{
    char cType = positionType(nPosition);

    if(cType == ELECTRIC_COMPANY) return cost.nElecCost;
    else if(cType == RAILROAD) return cost.nRailCost;
    else if(cType == PROPERTY) return nPosition % 7 * 20;
    else return 0;
}

/*
   Gets the rent of the property according its type
   
   @param nPlayer       The player that is paying the rent
   @param nPosition     The position of the property
   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nDice         The value of the dice the player rolled
   @param rent          A struct that contains the rent value for the 
                        Electric Company and Railroad property
   @param cost          A struct that contains the cost for the Electric 
                        Company and Railroad property
   
   @return The rent of the property
*/
int getPropertyRent(int nPlayer, int nPosition, int nProperties, int nDice, Rent rent, Cost cost)
{
    char cType = positionType(nPosition);

    int nCost = getPropertyCost(nPosition, cost);
    int nIsRenov = checkRenovation(nProperties, nPosition, nPlayer);
    int nRent = 0;

    if(cType == ELECTRIC_COMPANY) 
    {
        nRent = nDice * rent.nElecRent;
    }
    else if(cType == RAILROAD) 
    {
        nRent = rent.nRailRent;
    }
    else if(cType == PROPERTY) 
    {
        nRent = nCost * 0.2;

        // If the property is renovated then the rent value becomes twice the rent and add 1
        if(nIsRenov == 2) nRent = nRent * 2 + 1;
    }

    return nRent;
}

/* 
   Checks if the player owns the property that is inputted

   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPlayer       The player that is being checked
   @param nPosition     The property that is being checked

   @return      1 if the player owns the property and 0 if the player 
                does not own the property
*/
int checkOwnership(int nProperties, int nPlayer, int nPosition)
{
    if(getProperty(nProperties, nPosition) == nPlayer) return 1;
    else if(getProperty(nProperties, nPosition) == (nPlayer + 2)) return 1;
    else return 0;
}

/* Edits the values of the 9 digit integer property
   
   1 = sell property
   2 = buy property
   3 = renovate property

   precondition: nSign is either 1, 2, or 3

   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPosition     The position of the property
   @param nPlayer       The player that is making the edit
   @param nSign         The kind of edit the player would like to make

   @return A new value of the 9 digit integer property

*/
void changeOwnership(int* nProperties, int nPosition, int nPlayer, int nSign)
{
    int nNewValue = 1;
    int nProperty = getProperty(*nProperties, nPosition); //return 1, 2, 3, 4
    
    for(int x = 1; x <= nPosition; x++)
    {
        if(x == nPosition)
        {
            if(nSign == 1) // sell property 
            {
               nNewValue *= nProperty;
                *nProperties -= nNewValue; // subtracts the value of the property from the nProperties
            }
            else if(nSign == 2) // buy property
            {
                nNewValue *= nPlayer;
                *nProperties += nNewValue; // adds the value of the property to the nProperties
            }
            else if(nSign == 3) // renovate property
            {
                nNewValue *= 2;
                *nProperties += nNewValue; // adds the value of the property to the nProperties
            } 
        }
        else 
        {
            nNewValue *= 10;
        }
    }
}

/* 
   Displays all the properties owned by the player and whether or not 
   the property they own is renovated.
   
   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPlayer       The player that is currently playing
   
*/
void displayOwnership(int nProperties, int nPlayer)
{
    int nCounter;
    char cType;

    //Checks if there is a property owned by the player
    if(checkProperties(nProperties, nPlayer) == 0) printf(" N/A\n");
    else if(checkProperties(nProperties, nPlayer) == 1)
    {
        //Displays the properties owned by the player
        for(nCounter = 1; nCounter <= 9; nCounter++)
        {
            cType = positionType(nCounter);

            if(checkRenovation(nProperties, nCounter, nPlayer) == 1) 
            {
                printf(" [%d] ", nCounter);

                boardPosition(nCounter); // prints the title of the property

                if(cType == PROPERTY) printf(" (Unrenovated)");
                else printf("      N/A");

                printf("\n");
            }
            else if(checkRenovation(nProperties, nCounter, nPlayer) == 2)
            {
                printf(" [%d] ", nCounter);

                boardPosition(nCounter); // prints the title of the property

                if(cType == PROPERTY) printf("  (Renovated)");
                else printf("      N/A");
            
                printf("\n");
            }
        }
    }
}

/* 
   Display Player's Cash and properties that they own
   
   @param nProperties   A 9 digit integer containing the status of all 
                        properties
   @param nPlayer       The player that is currently playing
   @param nCash         The current cash of the player. This will update 
                        whenever the player earns or loses money
*/
void playerStatus(int nProperties, int nPlayer, int nCash)
{
    printf("\n[PLAYER %d]\n", nPlayer);
    printf("-----------------------------------------------\n");
    printf("Cash: %d\n", nCash);
    printf("-----------------------------------------------\n");
    printf("Properties:\n");
    displayOwnership(nProperties, nPlayer);
    printf("-----------------------------------------------\n");
}

/* Displays the new position of the player depending on the dice roll
   
   @param nDice         The number of times the player moves
   @param nPosition     Changes according to the dice roll
                        If the player exceeds the 9th position, the 
                        player returns to position 0
   @param nCash         Player gets 200 cash for passing the position 0

   @return      The new position of the player and the cash
*/
void displayPosition(int nDice, int* nPosition, int* nCash)
{
    int nReceived = FALSE;

    *nPosition += nDice; // adds the dice roll to the current position

    if(*nPosition > 9) 
    {
        *nCash += 200; // adds 200 cash to the player's cash for passing the position 0
        *nPosition -=10; //Subtracts 10 to make the player start from 0 again
        nReceived = TRUE;
    }

    printf("\n> Player rolled on a %d\n", nDice);
    printf("> Moving player to position %d\n", *nPosition);
    printf("> You have landed on the ");
    boardPosition(*nPosition);

    if(nReceived == TRUE) printf("\n\n> You have received 200 cash from the bank for passing Go.");
}

/*
   Checks if the player has enough cash to pay for the cost

   @param nCash     The current cash of the player
   @param nCost     The cost of what the player has to pay

   @return      1 if the player has enough cash and 0 if the player 
                does not have enough cash
   */
int isEnoughCash(int nCash, int nCost)
{
    if(nCash >= nCost) return TRUE;
    else return FALSE;
}

/* 
   Displays a message if the player's cash is enough to pay for the cost 
   and subtracts the cost from the player's cash
   
   @param nCash     The player cash increases or decreases according to 
                    the decision of the user to pay or sell
   @param nCost     The cost of what will be paid by the player

   @return      updated cash value of the player
*/
void cashPay(int* nCash, int nCost)
{
    int nCheckCash = isEnoughCash(*nCash, nCost);

    if(nCheckCash == TRUE)
    {
        printf("\nPayment successful\n");
        printf("\n> You paid %d cash\n", nCost);

    }
    else if(nCheckCash == FALSE)
    {
        printf("\nInsufficient Cash\n");
    }

    *nCash -= nCost;
}

/*
   Places the player in jail when they land on the position 4 (Jail 
   Time). When in jail, the player lose their next turn
   
   precondition: nPosition is 4

   @param player1       The jail status of player 1
   @param player2      The jail status of player 2
   @param nPlayer      The player that is currently playing

   @return     Updated jail status of the player
*/
void jail(Player* player1, Player* player2, int nPlayer)
{
    printf("\n> You cannot play for your next turn.\n");

    if(nPlayer == player1 -> nPlayer) player1 -> nJail = 1;
    else if(nPlayer == player2 -> nPlayer) player2 -> nJail = 1;
}

/*
   This function allows the user to resell a property to the bank and 
   updates the status of the ownership by changing the value of the 
   property that was sold to 0. The resell value is half the cost of the 
   property

   @param nPosition     The position of the property that the player 
                        wants to resell
   @param nPlayer       The player that is currently playing
   @param nProperties   Changes value when the player resells a property
   @param nCash         The player cash increases according to the 
                        decision of the user to resell
   @param cost          The cost of the property that the player wants 
                        to resell

   @return      Updated cash value of the player and updated status of 
                the ownership of the properties
*/
void resellProperty(int nPosition, int nPlayer, int* nProperties, int *nCash, Cost cost)
{
   int nNewCash = getPropertyCost(nPosition, cost) / 2;

   printf("\n> You have received %d.\n", nNewCash);

   *nCash += nNewCash; // adds the cash to the player's cash

   changeOwnership(nProperties, nPosition, nPlayer, 1); // nSign = 1 means the property is sold
}

/* 
   Displays a menu that shows the player all the properties they own 
   that they can resell so they can earn enough cash to pay for rent

   precondition: nProperties is not empty

   @param nCash         The player cash increases according to the 
                        decision of the user to resell
   @param nCost         The cost of the rent that the player has to pay
   @param nProperties   a 9 digit integer containing the status of all 
                        properties
   @param nPlayer       The player that owns the properties
   @param cost          The cost of the property that the player wants 
                        to resell

   @return      Updated cash value of the player and updated status of 
                the ownership of the properties
*/
void displaySellProperty(int* nCash, int nCost, int* nProperties, int nPlayer, Cost cost)
{
    int nAnswer;

    while(checkProperties(*nProperties, nPlayer) == 1 && isEnoughCash(*nCash, nCost) == 0)
    {
        printf("\n-----------------------------------------------\n");
        printf(" Would you like to sell a property?\n");
        printf("-----------------------------------------------\n");

        displayOwnership(*nProperties, nPlayer);
        printf("\nInput: ");
        scanf(" %d", &nAnswer);

        // checks if the user input is their owned property
        if(checkOwnership(*nProperties, nPlayer, nAnswer) == 1) resellProperty(nAnswer, nPlayer, nProperties, nCash, cost);
    }
}

/* Checks if the dice value is a prime number or not

   precondition: a number is a prime number if it has ONLY 2 factors
   
   @param nDice     the value of the dice roll

   @return      1 if the number is a prime number and 0 if the number 
                is not a prime number
*/
int isPrime(int nDice)
{
    int nPrime = FALSE;
    int nDivCount = 0;
    int nResult;
    int nCounter;

      for(nCounter = 1; nCounter <= nDice; nCounter++)
      {
        nResult = nDice % nCounter;
        
        if(nResult == 0)  nDivCount++; //Counts how many times it was divisible to a number
      }

      if(nDivCount == 2) nPrime = TRUE; //Automatically a prime number if it only has 2 prime numbers, not more not less

        return nPrime;
}

/* 
   Determines the action that happens when the player lands in Position 
   6 (Feelin' Lucky).
   
    - If dice value is a prime number, player receives a cash from the 
      bank
    - If dice value is NOT a prime number, the player pays the bank
    - If dice value is 1, player goes to jail, thus losing his next turn

   precondition: current nPosition is 6

   @param nCash         The player cash increases or decreases according 
                        to the dice roll
   @param player1       If the dice value is 1 on their roll, player1 is 
                        sent to jail
   @param player2       If the dice value is 1 on their roll, player2 is 
                        sent to jail
   @param luckyRange    The maximum and minimum range if the dice value 
                        is a prime number or NOT a prime number
   @param nPosition     The position of the player changes to 4 when the 
                        dice lands on a 1
   @param nPlayer       The player that is currently playing

   @return      Updated cash value of the player or updated position of 
                the player 
*/
void feelingLucky(int* nCash, Player* player1, Player* player2, LuckyRange luckyRange, Cost cost, int* nPosition, int nPlayer, int* nProperties)
{
    int nBank = 0;
    int nDice; //Player rolls dice to determine their luck

    printf("\n\nRULES: \n");
    printf("NOT Prime: player pays cash to the bank\n");
    printf("Prime: player receives cash from the bank\n");
    printf("1: player goes to jail and loses their next turn");
    
    nDice = rollDice();
    
    printf("\n> Player rolled on a %d\n", nDice);

    if(isPrime(nDice) == 1 && nDice != 1) // if the dice value is a prime number
    {
        nBank = (rand() % (luckyRange.nPrimeMax - luckyRange.nPrimeMin + 1)) + luckyRange.nPrimeMin;

        *nCash += nBank; // adds the received cash to the player's cash
        
        printf("\n> You have received %d cash from the bank.\n", nBank); // displays the amount of cash received   
    }
    else if(isPrime(nDice) == 0 && nDice != 1) // if the dice value is NOT a prime number
    {
        nBank = (rand() %(luckyRange.nNonPrimeMax - luckyRange.nNonPrimeMin + 1)) + luckyRange.nNonPrimeMin;

        printf("\n> You must pay the Bank for the amount of %d.\n", nBank); // displays the amount of cash the player must pay
        
        printf("Press any key to pay the bank...\n"); // waits for user to press any key before paying the bank
        getch();

        if(checkProperties(*nProperties, nPlayer) == 1 && isEnoughCash(*nCash, nBank) == 0) // if player does not have enough cash to pay rent
        {
            printf("Insufficient cash\n");
            printf("\nYou do not have enough cash to pay rent\n");

            displaySellProperty(nCash, nBank, nProperties, nPlayer, cost); //player can sell property until they have enough to pay rent
        }

        cashPay(nCash, nBank); // pays the bank
    }
    else if(nDice == 1) // if the dice value is 1
    {
        jail(player1, player2, nPlayer); //player loses their next turn

        *nPosition = 4; // player position is set to 4 (jail)
    }
}

/*
   Displays a menu that asks the user if they would like to buy the 
   unclaimed property they've landed on. If the player decides to buy 
   the property, this subtracts the property's cost from the player's 
   cash and adds the property to the player's ownership.

   precondition: the value of the property in nProperties is 0

   @param nCash         The player cash decreases according to the 
                        decision of the user to buy the property
   @param nProperties   a 9 digit integer containing the status of all 
                        properties
   @param nPosition     The current position of the player
   @param nPlayer       The player that is currently playing
   @param cost          The cost of the property that the player wants 
                        to buy
   
   @return      Updated cash value of the player and updated status of 
                the ownership of the properties
*/
void buyProperty(int* nCash, int* nProperties, int nPosition, int nPlayer, Cost cost)
{
    int nCost = getPropertyCost(nPosition, cost);
    int nAnswer = 0;
        
    printf("\n\n-----------------------------------------------\n");
    printf(" Would you like to buy this property?\n");
    printf("-----------------------------------------------\n");
    printf(" [1] Yes\n");
    printf(" [2] No\n");
    
    while(nAnswer != 1 && nAnswer != 2)
    {        
        printf("\nInput: "); 
        scanf(" %d", &nAnswer);

        if(nAnswer == 1)
        {
            if(isEnoughCash(*nCash, nCost) == 1) changeOwnership(nProperties, nPosition, nPlayer, 2); // changes ownership of the property to the player

            cashPay(nCash, nCost); // subtracts the cost of the property from the player's cash
        }
        else if(nAnswer != 1 && nAnswer != 2)
        {
            invalid();
        }
    }
}

/*
   The player has to pay the other player the rent cost for landing in 
   their owned property. If the player does not have enough cash to pay
   the rent, the player will need to keep selling his properties.

   precondition: the player is in the other player's owned property

   @param nCash         The player cash decreases according to the 
                        rent cost
   @param nProperties   a 9 digit integer containing the status of all 
                        properties
   @param player1       Receives cash from player2 if player2 is in 
                        player1's owned property
   @param player2       Receives cash from player1 if player1 is in 
                        player2's owned property
   @param nPosition     The current position of the player
   @param nDice         The dice value of the player's roll
   @param nPlayer       The player that is currently playing\
   @param rent          The rent cost of the property that the player 
                        is in
   @param cost          The cost of the property that will be used to 
                        determine the rent cost 

   @return      decreased cash value of the player and increased cash 
                of the other player
*/
void payRent(int* nCash, int* nProperties, Player* player1, Player* player2, int nPosition, int nDice, int nPlayer, Rent rent, Cost cost)
{
    int nCost = getPropertyRent(nPlayer, nPosition, *nProperties, nDice, rent, cost);

    printf("\n\nThis property is owned by another player\n");
    printf("\nPress any key to pay for rent...\n");
    getch();

    if(checkProperties(*nProperties, nPlayer) == 1 && isEnoughCash(*nCash, nCost) == 0) // if player does not have enough cash to pay rent
    {
        printf("Insufficient cash\n");
        printf("\nYou do not have enough cash to pay rent\n");

        displaySellProperty(nCash, nCost, nProperties, nPlayer, cost); //player can sell property until they have enough to pay rent
    }
    
    cashPay(nCash, nCost); // subtracts the rent cost from the player's cash

    if(nPlayer == player1 -> nPlayer) player2 -> nCash += nCost; // player1 pays player2
    else if(nPlayer == player2 -> nPlayer) player1 -> nCash += nCost; // player2 pays player1

}

/* 
   If the player lands on their own property, they can choose to 
   renovate their property or not. If they choose to renovate, the rent
   value of the property increases but the player would need to pay the
   renovation cost.

   precondition: the player is in their own property

   @param nCash         The player cash decreases according to the 
                        renovation cost
   @param nProperties   The value of the property in nProperties is 
                        changes to a renovated property.
   @param nPosition     The current position of the player
   @param nPlayer       The player that is currently playing
   @param cost          The renovation cost of the property

   @return      Updated cash value of the player and updated status of 
                the ownership of the properties
*/
void renovateProperty(int* nCash, int* nProperties, int nPosition, int nPlayer, Cost cost)
{
    int nAnswer = 0;

    printf("\n\n-----------------------------------------------\n");
    printf(" Would you like to renovate your property?\n");
    printf("-----------------------------------------------\n");
    printf(" [1] Yes\n");
    printf(" [2] No\n");

    while(nAnswer != 1 && nAnswer != 2)
    {
        printf("\nInput: ");
        scanf(" %d", &nAnswer);

        if(nAnswer == 1)
        {
            if(isEnoughCash(*nCash, cost.nRenovCost) == 1) changeOwnership(nProperties, nPosition, nPlayer, 3); // changes property to renovated

            cashPay(nCash, cost.nRenovCost); // subtracts the renovation cost from the player's cash
        }
        else if(nAnswer != 1 && nAnswer != 2) 
        {
            invalid();
        }
    }
}

/*
    Displays a message to the player that the player has landed on a 
    property that is either already renovated or cant be renovated.
*/
void displayCannotRenovate()
{
    printf("\n\nThis property cannot be renovated anymore.\n");
    printf("Press any key to end your turn...\n");

    getch();
}

/* 
   Determines the action that happens when the player lands on a Property

    - If the property is unowned, the player may choose to buy the 
      property from the bank
    - If the property is owned by another player, the player pays the 
      rent
    - If the property is owned by the player, the player can choose to 
      renovate the property
    - If the property is not a house property and is a renovated 
      property, the player does nothing
   
   @param nProperties   A 9 digit integer to keep track on the ownership 
                        of the properties
   @param nCash         The player cash increases or decreases according 
                        to the actions of the player
   @param player1       A struct containing the information of player1
   @param player2       A struct containing the information of player2
   @param nPosition     The position of the player in the board
   @param nPlayer       The player that is currently playing
   @param nDice         the value of the dice roll
   @param rent          The rent cost of the property
   @param cost          The cost of the property
*/
void property(int* nProperties, int* nCash, Player* player1, Player* player2, int nPosition, int nPlayer, int nDice, Rent rent, Cost cost)
{
    int nProperty = getProperty(*nProperties, nPosition);
    char cType = positionType(nPosition);

    if(nProperty == 0) buyProperty(nCash, nProperties, nPosition, nPlayer, cost);
    else if(nProperty != 0 && nProperty != nPlayer && nProperty != (nPlayer + 2)) payRent(nCash, nProperties, player1, player2, nPosition, nDice, nPlayer, rent, cost);
    else if(nProperty == nPlayer && cType == PROPERTY) renovateProperty(nCash, nProperties, nPosition, nPlayer, cost);
    else displayCannotRenovate();
}

/*
   Stores the information of the player in the struct Player and changes 
   the current player to the next player

   @param nCash         The cash value during the turn of the player
   @param nPosition     The last position of the player in the board
   @param nPlayer       The player that is currently playing
   @param player1       A struct containing the information of player1
   @param player2       A struct containing the information of player2
   
   @return      The updated information of the player and change of the 
                current player
*/
void changePlayer(int* nCash, int* nPosition, int* nPlayer, Player* player1, Player* player2)
{
    // resets the jail status of the players if both players are in jail
    if(player1 -> nJail == 1 && player2 -> nJail == 1) player1 -> nJail = player2 -> nJail = 0;
    
    // changes the current player to the next player
    if(*nPlayer == player1 -> nPlayer && player2 -> nJail != 1) // if player1 is the current player and player2 is NOT in jail, player2 is the next player
    {
        // stores the values of player1 and changes the current player to player2
        player1 -> nCash = *nCash; 
        *nCash = player2 -> nCash; 
        player1 -> nPosition = *nPosition; 
        *nPosition = player2 -> nPosition; 
        *nPlayer = player2 -> nPlayer; 
    }
    else if(*nPlayer == player2 -> nPlayer && player1 -> nJail != 1) // if player2 is the current player and player1 is NOT in jail, player1 is the next player
    {
        // stores the values of player2 and changes the current player to player1
        player2 -> nCash = *nCash; 
        *nCash = player1 -> nCash; 
        player2 -> nPosition = *nPosition; 
        *nPosition = player1 -> nPosition; 
        *nPlayer = player1 -> nPlayer; 
    }
    else if(*nPlayer == player1 -> nPlayer && player2 -> nJail == 1) // if player1 is the current player and player2 is in jail, player1 is the next player
    {
        player2 -> nJail = 0; // player2 is not in jail anymore
    }
    else if(*nPlayer == player1 -> nPlayer && player2 -> nJail == 1) // if player2 is the current player and player1 is in jail, player2 is the next player
    {
        player1 -> nJail = 0; // player1 is not in jail anymore
    }
}

/*
   prints a text that indicates the player that has won the game

    @param nPlayer       The player that has won the game
*/
void printWinnerMessage(int nWinner)
{
    if(nWinner == 1) printf("\nCongratulations Player 1!\nYou have won the game!\n\n\n");
    else if(nWinner == 2) printf("\nCongratulations Player 2!\nYou have won the game!\n\n\n");
}

/*
   Determines if the game is over once a player has won or lost
    
   @param nCash         The status of the player's cash
   @param nProperties   The status of the player's properties
   @param nPlayer       The player that is currently playing
   @param nEndCond      The condition that must be satisfied to end the 
                        game
    @param nCashLimit   The cash limit that must be met to end the game
    
    @return      The status of the game (continue or end)
*/
int checkEndCondition(int nCash, int nProperties, int nPlayer, int nEndCond, int nCashLimit)
{
    int nBankrupt;
    int nReachLimit;

    // Checks if the player has no properties and is bankrupt
    if(checkProperties(nProperties, nPlayer) == 0 && nCash <= 0) nBankrupt = 1;

    // Checks if the player has reached the cash limit
    if(nCash >= nCashLimit) nReachLimit = 1;

    // Checks if the end condition has been met
    if(nEndCond == 1 && nBankrupt == 1) 
    {
        printf("\nPlayer %d has no properties and is bankrupt.\n", nPlayer);
        
        if(nPlayer == 1) printWinnerMessage(2);
        else if(nPlayer == 2) printWinnerMessage(1);

        return 1;
    }
    else if(nEndCond == 2 && nReachLimit == 1)
    {
        printf("\nPlayer %d has reached the cash limit.\n", nPlayer);

        printWinnerMessage(nPlayer);

        return 1;
    }
    else if(nEndCond == 3 && (nBankrupt == 1 || nReachLimit == 1))
    {
        if(nBankrupt == 1) 
        {
            printf("\nPlayer %d has no properties and is bankrupt.\n", nPlayer);
        
            if(nPlayer == 1) printWinnerMessage(2);
            else if(nPlayer == 2) printWinnerMessage(1);
        }
        else if(nReachLimit == 1)
        {
            printf("\nPlayer %d has reached the cash limit.\n", nPlayer);

            printWinnerMessage(nPlayer);
        }

        return 1;
    }
    else return 0;
}

int main()
{
    // Initial values for the game
    int nPlayer; 
    int nCash;
    int nProperties = 0;
    int nPosition = 0;
    int nInitialCash = 200;
    int nDice = 0;
    char cType = ' '; //Type of property

    // Game Status
    int nGame = 1;
    int nCashLimit = 0;
    int nEndCond = 1;
    int nLose = 0;

    // Initial rent values
    Rent rent;
    rent.nRailRent = 35;
    rent.nElecRent = 8;

    // Initial cost values
    Cost cost;
    cost.nRailCost = 150;
    cost.nElecCost = 100;
    cost.nRenovCost = 50;

    // Initial range of amount for Feelin' Lucky
    LuckyRange luckyRange;
    luckyRange.nPrimeMax = 200;
    luckyRange.nPrimeMin = 100;
    luckyRange.nNonPrimeMax = 150;
    luckyRange.nNonPrimeMin = 50;

    // Initializes player1
    Player player1;
    player1.nPlayer = 1;
    player1.nPosition = 0;
    player1.nJail = 0;

    // Initializes player2
    Player player2;
    player2.nPlayer = 2;
    player2.nPosition = 0;
    player2.nJail = 0;

    // Repeats until the user chooses to Exit the Game
    while(nGame == 1)
    {
        // Displays the menu of the game  
        menu(&nGame, &nInitialCash, &rent, &cost, &luckyRange, &nCashLimit, &nEndCond);

        // Initial Cash-on-hand
        player1.nCash = nInitialCash;
        player2.nCash = nInitialCash;

        // Sets the current player to player1
        nPlayer = player1.nPlayer;
        nCash =  player1.nCash;
        nPosition = player1.nPosition;

        nLose = 0;

        while(nGame == 1 && nLose == 0)
        {
            playerStatus(nProperties, nPlayer, nCash);

            nDice = rollDice(); //Gives a random number between 1 - 6

            displayPosition(nDice, &nPosition, &nCash); //Gets the new position of the player depending on the dice roll

            cType = positionType(nPosition);

            // The different actions that takes place according to what the player lands on
            if (cType == JAIL) jail(&player1, &player2, nPlayer);
            else if(cType == FEELIN_LUCKY) feelingLucky(&nCash, &player1, &player2, luckyRange, cost, &nPosition, nPlayer, &nProperties);
            else if(cType == PROPERTY || cType == ELECTRIC_COMPANY || cType == RAILROAD) property(&nProperties, &nCash, &player1, &player2, nPosition, nPlayer, nDice, rent, cost);

            //Indication that the player's turn has ended 
            printf("\n[END OF TURN]\n");

            // Checks if a player has won or lost
            nLose = checkEndCondition(nCash, nProperties, nPlayer, nEndCond, nCashLimit);
            
            // Changes the current player to the next player
            changePlayer(&nCash, &nPosition, &nPlayer, &player1, &player2);
        }
    }

    return 0;
}

/*
    This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
    learned. I have constructed the functions and their respective algorithms and corresponding code all by myself. The
    program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole
    or otherwise plagiarized the work of other students and/or persons.
    
    Larraquel, Reign Elaiza D.
    DLSU ID 12119768
*/