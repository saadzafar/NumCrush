/*Header lists*/
#include <stdio.h>
#include <windows.h> /*For the colors*/
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h> 
#include <conio.h>
#include <dos.h>   /*Header to inlude system time */                                           
#include <sys\timeb.h> /*Header for the struct variable of time.b*/ 

#define MAXSIZE 15

/*ARRAY VARIABLE*/
typedef struct
{
	int x;	/*store the random numbers*/
	char y;	/*Store Character for pointer*/
	char z;	/*Store Character for pointer*/

}marray;


/*ALL THE OTHE VARIABLES*/
typedef struct
{
	int a, b; 	/*Store position of pointer*/
	int n; 	/*Store Size of array*/
	char name[20];	/*Store name of user*/
	char key;	/*Store the key the user press during navigation of pointer*/
	int swap;	/*Temporary strorage for swapping*/
	char direction;	/*Store the key the user press for direction to swap*/
	int fscore;	/*Store the cummulative score of user*/
	int t_diff; /*Store the time*/
	char choice1; /*Store choice to playagain*/
	int flag1;
}var;

/*Functions Prototype */
void frontcover();
void NAME_ID();
void intro();
void welcome(var *avar);
int size(var *avar); 
void initialiseboard(marray board[MAXSIZE][MAXSIZE],var *avar);
void printarray(marray board[MAXSIZE][MAXSIZE], var *avar);
void storeplayerrecord(var *avar);
void showplayerrecord(var *avar);
void clearrecord();
void check(marray board[MAXSIZE][MAXSIZE], var *avar);
void replace(marray board[MAXSIZE][MAXSIZE], var *avar);
void swapping(marray board[MAXSIZE][MAXSIZE], var *avar);
void navigation(marray board[MAXSIZE][MAXSIZE], var *avar);
void lastcover(var *avar);
char playagain (var *avar);
void endgame();
/*Global variables*/
int i,j;



/*FRONT COVER PAGE*/
void frontcover()
{	/*Functon to change the colour of text*/
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute ( h, FOREGROUND_GREEN | FOREGROUND_INTENSITY) ;

	printf("################################################################################\n");
	printf("################################################################################\n");
	printf("################################################################################\n");
	printf("###                                                                          ###\n");
	printf("## ####    ### ###      ### ###      ### #########     ########## ########### ##\n");        
	printf("## ######  ### ###      ### ####    #### ###      ##  ###         ###      ## ##\n");
	printf("## ## ###  ### ###      ### ### #  # ### ###    ###  #########    ###      ## ##\n");
	printf("## ##  ### ### ###      ### ###  ##  ### ###    ###  #########    ########### ##\n");
	printf("## ##   ######  ##########  ###      ### ###      ##  ###         ###  ####   ##\n");
	printf("## ##    #####   ########   ###      ### ##########    ########## ###   ##### ##\n");
	printf("##                                                                            ##\n");
	printf("##                                                                            ##\n");
	printf("##        ########## ############ ###      ### ########### ###      ###	      ##\n");
	printf("##       ########### ###      ### ###      ### ###         ###      ###	      ##\n");
	printf("##      ###          ###      ### ###      ### ########    ############	      ##\n");
	printf("##      ###          ############ ###      ###   ######### ############	      ##\n");
	printf("##       ########### ###  ####     ##########          ### ###      ###	      ##\n");
	printf("##        ########## ###   ######   ########   ########### ###      ###	      ##\n");
	printf("###                                                                          ###\n");
	printf("################################################################################\n");
	printf("################################################################################\n");
	printf("################################################################################\n");

	printf("\n\n***********************PRESS ANY KEY TO CONTINUE******************************\n");
	printf("--------------------------------------------------------------------------------");
	getch();
	SetConsoleTextAttribute ( h, wOldColorAttrs);/*The code to change colour should always be concluded with this particular line*/
	system("cls");
}



/*SECOND PAGE WELCOME PAGE*/
void intro()
{		
	 
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_INTENSITY) ;
	
	printf("     =====================================================================\n");
	printf("     ==========================   WELCOME   ==============================\n");
	printf("     =====================================================================\n");
	printf("     ============================   TO   =================================\n");
	printf("     =====================================================================\n");
	printf("     ============================   THE   ================================\n");
	printf("     =====================================================================\n");
	printf("     ===================== << NUMBER CRUSH GAME >> =======================\n");
	printf("     =====================================================================\n");      
	
	SetConsoleTextAttribute ( h, wOldColorAttrs);

}
/* PROMPT USER TO INPUT NAME*/
void welcome(var *avar)
{
	printf("Please enter your name to start the game: ");
	scanf("%s",avar->name);
	fflush(stdin);

	printf("\nWelcome %s\nLet's start the game\n\n", avar->name);
	printf("**************RULE***************\n\n");
	printf("Swap to MATCH 3 adjacent simialar numbers\nTime trial-TRY to match the most within Minute\n\n");

}


/*PROMPT USER TO INDICATE SIZE OF BOARD HE WANTS TO USE*/
int size(var *avar) 
{
	do
		{
			printf("Enter the size of the board you want to play in(Size range 9-15 )  ");
			scanf("%i", &avar->n);
			fflush(stdin);
		}
	while (avar->n>15 || avar->n<9 || isalpha(avar->n));/*Validation to choose only digit between 9-15 */
	return avar->n;	
}


/*Initialise most of variable to be used in game*/
void initialiseboard(marray board[MAXSIZE][MAXSIZE],var *avar)
{
	int flag;

	avar->a=avar->n/2;/*This is done so that the initial position of pointer is in the middle*/
	avar->b=avar->n/2;/*This is done so that the initial position of pointer is in the middle*/
	avar->fscore=0;/*Initial score is zero initially*/
	avar->t_diff=0;/*Initially time is zero*/

	/*This loop is use to initialise the array with a random number and also restrict the psoition of 3 adjacent similar number*/
	for(i=0;i<avar->n;i++) 
	{
		for(j=0;j<avar->n;j++)
		{
			do
			{
				flag=0;
				board[i][j].x=rand() %7 + 2; /*The validation below check for 3 adjacent similar digit both vertically and horizontally*/
				if(board[i][j].x==board[i-1][j].x && board[i-1][j].x==board[i-2][j].x ||board[i][j].x==board[i][j-1].x && board[i][j-1].x==board[i][j-2].x)
				{
					flag=1;
				} 
			}
			while(flag==1);/*repeat loop until no 3 similar adjacent*/
		}
	}

 	/*Initialise the pointer character*/
	for(i=0;i<avar->n;i++)
	{
		for(j=0;j<avar->n;j++)
		{
			board[i][j].z='|'; /*initializing the marker*/
			board[i][j].y='|';
		}
	}
}


/*Function to print the whole array board and pointer + print updated score + print the menu also*/
void printarray(marray board[MAXSIZE][MAXSIZE], var *avar)
{

	system("CLS");	  

	printf("*********************NUMBER CRUSH*********************\n");
	printf("------------------------------------------------------\n");

	for(i=0;i<avar->n;i++)
	{
		for(j=0;j<avar->n;j++)
		{
		if(i==avar->a && j==avar->b)	 /*Print character pointer at only that location*/
		printf("%c",board[avar->a][avar->b].z);
		else
		printf(" ");	
		if(board[i][j].x==0)	/*Print empty space to show the blasting of the numbers */
		printf("   ");
		else
		printf(" %i ",board[i][j].x);
		if(i==avar->a && j==avar->b)	/*Print character pointer at only that location*/	
		printf("%c",board[avar->a][avar->b].y);
		else
		printf(" ");
		}
	printf("\n\n");
	}
	
	printf("\n");
	printf("************Time : %d sec**************", avar->t_diff); /*Printing the clock*/
	printf("\n");
	printf("Your actual score is %i", avar->fscore); /*printing updated score*/
	printf("\n\n");/*Below is the menu board*/
	printf("***************Menu***************\n");
	printf("----------------------------------\n");
	printf("Press w to move up\nPress s to move down\nPress d to move right\nPress a to move left\nPress k to swap number\nPress c to clear player record\nPress e to exit\nChoose your action:\n");


}


/*Store the name and score of each player in the external file record.txt */
void storeplayerrecord(var *avar)
{

	FILE *scoreboard=fopen("record.text", "a");
	
	if(scoreboard==NULL)
	{
		printf("NO PREVIOUS RECORDS FOUND!!\n");
		exit;
	}
	else
	{
		fprintf(scoreboard, "%s\t\t\t%i\n",avar->name,avar->fscore);/*Store name and score*/
	}

	fclose(scoreboard);

}


/*Retrieve the name and score stored of each player from the external file record.txt */
void showplayerrecord(var *avar)
{   
    FILE *scoreboard=fopen("record.text", "r");
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute ( h, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY) ;
	
	/*FILE *scoreboard=fopen("record.text", "r");*/

	if(scoreboard==NULL)
	{
		printf("NO PREVIOUS RECORDS FOUND!!\n");
		exit;
	}
	printf("List of previous players\n\n");
	printf("%s\t\t\t%s\n","Name", "Score");
	while (fscanf(scoreboard, "%s%i" , avar->name, &avar->fscore) == 2) /*Performs the following statement until fscanf returns a 2*/
		printf("%s\t\t\t%i\n",  avar->name, avar->fscore);/*print name and score stored initially*/
	printf("\n");


fclose(scoreboard);

SetConsoleTextAttribute ( h, wOldColorAttrs);
}

/*This option Clear all the text in the record.txt file */
void clearrecord()
{
	FILE *scoreboard=fopen("record.txt", "w");
	fclose(scoreboard);
}

/*This function will check the whole array to check for 3 adjacent numbers and gives them a value of 0 and 
each time it finds a set of 3 identical numbers it adds 5 point to actual score*/
void check(marray board[MAXSIZE][MAXSIZE], var *avar)
{
	for(i=0;i<avar->n;i++)
	{
		for(j=0;j<avar->n;j++)
		{
			if(board[i][j].x==board[i][j+1].x && board[i][j].x==board[i][j+2].x) 	/*Check for 3 identical numbers Vertically */
			{
				board[i][j].x=0;/*Assigning zero to arrays with 3 identical digit*/
				board[i][j+1].x=0;
				board[i][j+2].x=0;
				
				avar->flag1=1;
				avar->fscore=avar->fscore+5;/*Score increment by 5 each the above statemnt is satistified*/
                system("COLOR 2"); /*Changes both foregroung and background */ 
				printf("Match  found!\nYou collected 5 points\nPress any key to continue");
				getch();

			}

			if(board[i][j].x==board[i+1][j].x && board[i][j].x==board[i+2][j].x)	/*Check for 3 identical numbers Horizontally */
			{
				board[i][j].x=0;
				board[i+1][j].x=0;
				board[i+2][j].x=0;
				
				avar->flag1=1;	
				avar->fscore=avar->fscore+5;
				system("COLOR 2");  
				printf("Match found!\nYou collected 5 points\nPress any key to continue");
				getch();
			}
			
	
	
		}
	}


}


/*This function makes the grid fall down and replace blasted numbers*/
void replace(marray board[MAXSIZE][MAXSIZE], var *avar)
{
	int x;
	
	for(i=0;i<avar->n;i++)
	{
		for(j=0;j<avar->n;j++)
		{
		if(board[i][j].x==0)
		{
			for(x=i;x>0;x--)
			{
				board[x][j].x=board[x-1][j].x;	/*Make grid falls down*/
			}
			board[0][j].x=rand() %7+2; 	/*Assign random numbers to the remaining one*/
		}
		}
	}
}



/*This function holds the code to allow the user to swap only when a set of 3 numbers can be formed*/
void swapping(marray board[MAXSIZE][MAXSIZE], var *avar)
{
	printf("Where do you want to swap");
	avar->swap=board[avar->a][avar->b].x;	/*Temporararilly store the value of the initial position of pointer*/
	avar->direction=getch();	/*Asks user for direction to swap*/
	switch(avar->direction)
	{
		case 'w':
		if(avar->a>0)/*Limitation to restrict marker to board*/
		{
		/*Swap numbers*/
			board[avar->a][avar->b].x=board[(avar->a-1)][avar->b].x;
			board[(avar->a-1)][avar->b].x=avar->swap;
			printarray(board,&*avar);
		}
		
		/*Condition to swap numbers that need to be matched for allowing the swap to happened*/
		if (board[avar->a-1][avar->b].x==board[avar->a-1][avar->b+1].x && board[avar->a-1][avar->b].x==board[avar->a-1][avar->b+2].x  ||
		    board[avar->a-1][avar->b].x==board[avar->a-1][avar->b+1].x && board[avar->a-1][avar->b].x==board[avar->a-1][avar->b-1].x  ||
			 board[avar->a-1][avar->b].x==board[avar->a-1][avar->b-1].x && board[avar->a-1][avar->b].x==board[avar->a-1][avar->b-2].x ||
			  board[avar->a-1][avar->b].x==board[avar->a-2][avar->b].x && board[avar->a-1][avar->b].x==board[avar->a-3][avar->b].x ||    
			  board[avar->a][avar->b].x==board[avar->a][avar->b+1].x && board[avar->a][avar->b].x==board[avar->a][avar->b+2].x  || 
			  board[avar->a][avar->b].x==board[avar->a][avar->b+1].x && board[avar->a][avar->b].x==board[avar->a][avar->b-1].x || 
			  board[avar->a][avar->b].x==board[avar->a][avar->b-1].x && board[avar->a][avar->b].x==board[avar->a][avar->b-2].x || 
			  board[avar->a][avar->b].x==board[avar->a+1][avar->b].x && board[avar->a][avar->b].x==board[avar->a+2][avar->b].x)
		{
			/*Calling functions to chack for identical set 3 of numbers, blast it and replace right after swapping */
			check(board, &*avar);
			printarray(board,&*avar);
			getch();
			replace(board,&*avar);
			}
		else
		{
			/*Undo the swap if condition not met*/
			printf("NO match found\nPress any key to continue");
			getch();
			board[(avar->a-1)][avar->b].x=board[avar->a][avar->b].x;
			board[avar->a][avar->b].x=avar->swap;
		}
		printarray(board,&*avar);
		break;
		
		case 's':
		if(avar->a<(avar->n-1))
		{
			board[avar->a][avar->b].x=board[(avar->a+1)][avar->b].x;
			board[(avar->a+1)][avar->b].x=avar->swap;
			printarray(board,&*avar);
		}
		
		if(board[avar->a+1][avar->b].x==board[avar->a+1][avar->b+1].x && board[avar->a+1][avar->b].x==board[avar->a+1][avar->b+2].x ||
		   board[avar->a+1][avar->b].x==board[avar->a+1][avar->b+1].x && board[avar->a+1][avar->b].x==board[avar->a+1][avar->b-1].x ||
		   board[avar->a+1][avar->b].x==board[avar->a+1][avar->b-1].x && board[avar->a+1][avar->b].x==board[avar->a+1][avar->b-2].x ||
		   board[avar->a+1][avar->b].x==board[avar->a+2][avar->b].x && board[avar->a+1][avar->b].x==board[avar->a+3][avar->b].x ||
		   board[avar->a][avar->b].x==board[avar->a][avar->b+1].x && board[avar->a][avar->b].x==board[avar->a][avar->b+2].x  ||
		   board[avar->a][avar->b].x==board[avar->a][avar->b+1].x && board[avar->a][avar->b].x==board[avar->a][avar->b-1].x ||
		   board[avar->a][avar->b].x==board[avar->a][avar->b-1].x && board[avar->a][avar->b].x==board[avar->a][avar->b-2].x ||
		   board[avar->a][avar->b].x==board[avar->a-1][avar->b].x && board[avar->a][avar->b].x==board[avar->a-2][avar->b].x )
		{
			check(board, &*avar);
			printarray(board,&*avar);
			getch();
			replace(board,&*avar);
			}
		else
		{
			printf("NO match found\nPress any key to continue");
			getch();
			board[(avar->a+1)][avar->b].x=board[avar->a][avar->b].x;
			board[avar->a][avar->b].x=avar->swap;
		}
		
		printarray(board,&*avar);
		break;
		
		case 'a':
		if(avar->b>0)
		{
			board[avar->a][avar->b].x=board[avar->a][(avar->b-1)].x;
			board[avar->a][(avar->b-1)].x=avar->swap;
			printarray(board,&*avar);
		}
		
		if(board[avar->a][avar->b-1].x==board[avar->a][avar->b-2].x && board[avar->a][avar->b-1].x==board[avar->a][avar->b-3].x ||
		   board[avar->a][avar->b].x==board[avar->a][avar->b+1].x && board[avar->a][avar->b].x==board[avar->a][avar->b+2].x ||
		   board[avar->a][avar->b-1].x==board[avar->a+1][avar->b-1].x && board[avar->a][avar->b-1].x==board[avar->a+2][avar->b-1].x ||
		   board[avar->a][avar->b].x==board[avar->a+1][avar->b].x && board[avar->a][avar->b].x==board[avar->a+2][avar->b].x ||
		   board[avar->a][avar->b-1].x==board[avar->a-1][avar->b-1].x && board[avar->a][avar->b-1].x==board[avar->a-2][avar->b-1].x ||
		   board[avar->a][avar->b].x==board[avar->a-1][avar->b].x && board[avar->a][avar->b].x==board[avar->a-2][avar->b].x ||
		   board[avar->a][avar->b-1].x==board[avar->a+1][avar->b-1].x && board[avar->a][avar->b-1].x==board[avar->a-1][avar->b-1].x ||
		   board[avar->a][avar->b].x==board[avar->a+1][avar->b].x && board[avar->a][avar->b].x==board[avar->a-1][avar->b].x )  
		{
			check(board, &*avar);
			printarray(board,&*avar);
			getch();
			replace(board,&*avar);
		}
		else
		{
			printf("NO match found\nPress any key to continue");
			getch();
			board[avar->a][avar->b-1].x=board[avar->a][avar->b].x;
			board[avar->a][avar->b].x=avar->swap;
		}
		
		printarray(board,&*avar);
		
		break;
		
		case 'd':
		{
			if(avar->b<(avar->n-1))
			board[avar->a][avar->b].x=board[avar->a][(avar->b+1)].x;
			board[avar->a][(avar->b+1)].x=avar->swap;
			printarray(board,&*avar);
		}
		
		if(board[avar->a][avar->b+1].x==board[avar->a][avar->b+2].x && board[avar->a][avar->b+1].x==board[avar->a][avar->b+3].x ||
		   board[avar->a][avar->b].x==board[avar->a][avar->b-1].x && board[avar->a][avar->b].x==board[avar->a][avar->b-2].x ||
		   board[avar->a][avar->b+1].x==board[avar->a+1][avar->b+1].x && board[avar->a][avar->b+1].x==board[avar->a+2][avar->b+1].x ||
		   board[avar->a][avar->b].x==board[avar->a+1][avar->b].x && board[avar->a][avar->b].x==board[avar->a+2][avar->b].x ||
		   board[avar->a][avar->b+1].x==board[avar->a-1][avar->b+1].x && board[avar->a][avar->b+1].x==board[avar->a-2][avar->b+1].x ||
		   board[avar->a][avar->b].x==board[avar->a-1][avar->b].x && board[avar->a][avar->b].x==board[avar->a-2][avar->b].x ||
		   board[avar->a][avar->b+1].x==board[avar->a+1][avar->b+1].x && board[avar->a][avar->b+1].x==board[avar->a-1][avar->b+1].x ||
		   board[avar->a][avar->b].x==board[avar->a+1][avar->b].x && board[avar->a][avar->b].x==board[avar->a-1][avar->b].x) 
		{
			check(board, &*avar);
			printarray(board,&*avar);
			getch();
			replace(board,&*avar);
		}
		else
		{
			printf("NO match found\nPress any key to continue");
			getch();
			board[avar->a][avar->b+1].x=board[avar->a][avar->b].x;
			board[avar->a][avar->b].x=avar->swap;
		}
	
		printarray(board,&*avar);
		
		break;
		
		default:
		printarray(board,&*avar);
		printf("INVALID INPUT");
		printf("\n");
		system("COLOR 47");
		getch();
		break;
	
	}
	/*Calling functions to chack for identical set 3 of numbers, blast it and replace right after the grid falls down */
	do
	{
	avar->flag1=0;
	check(board, &*avar);
	printarray(board,&*avar);
	if(avar->flag1==0)
	printf("NO MORE MATCH FOUND");
	getch();
	replace(board,&*avar);
	}
	while(avar->flag1==1);/*Loop until no 3 identical are adjacent*/

}


/*This function prompt user to ke in the direction to navigate the pointer though board and moves the pointer accordingly*/
void navigation(marray board[MAXSIZE][MAXSIZE], var *avar)
{                                                
    int flag;	  
	struct timeb t_start, t_current; /*The struct timeb consist among other a long integer time and short integer millitm which is a fractional number in ms*/                          
                                                   
    ftime(&t_start);/*fetch time from system clock constant*/
	    
	do
	{
	   	flag=0;                                        
                                                   
                                                                                                 
      	ftime(&t_current);/*fetch time store as current since in a for loop it will fetch at each point in the loop*/                                    
      	avar->t_diff = (int) ((t_current.time - t_start.time)); /*calculation for the time difference in sec*/
                                                                                               

		if(avar->t_diff>120)/*Time limitation*/
		{
			flag=1;/*loop loops out at flag=1*/
		}
		system("COLOR 07");
		avar->key=getch();
		switch(avar->key)
		{
			case 'e':case 'E': /*EXIT GAME*/
			flag=1;
			break;
			
			case 'c':case 'C':/*CLEAR RECORD*/
			clearrecord();
			printarray(board, &*avar);
			printf("Record cleared");
			break;
			
			case 'w':/*MOVE marker UP*/
			{
				if(avar->a>0)
				avar->a=avar->a-1;
			}
			printarray(board, &*avar);
			break;
			
			case 's':/*move marker down*/
			{
				if(avar->a<(avar->n-1))
				avar->a=avar->a+1;
			}
			printarray(board, &*avar);
			break;
			
			case 'a':/*move marker left*/
			{
				if(avar->b>0)
				avar->b=avar->b-1;
			}
			printarray(board, &*avar);
			break;
			
			case 'd':/*move marker right*/
			{
				if(avar->b<(avar->n-1))
				avar->b=avar->b+1;
			}
			printarray(board, &*avar);
			break;
			
			case 'k':
			swapping(board, &*avar); /*Call function for swapping*/
			break;
			
			default:
			printarray(board,&*avar);
			printf("INVALID INPUT");
			printf("\n");
			system("COLOR 47");/*Changes color each time to indicate  invalid button pressed*/
			getch();
			break;
			
		}
	}
	while(flag!=1); /*repeat loop until user key in E:e*/
	system("CLS");
	endgame(&*avar);
}


/*Print an ending mesage*/
void lastcover(var *avar)
{
	printf("\nEND OF THE GAME\nGOOD BYE %s!!\nHave a nice day.", avar->name);
	getch();
	system ("COLOR A4");
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n");	  	 
	   	     
	printf("   @@@@@@@  @   @  @@@@@  @     @  @   @     @     @   @@@@   @    @     @@  \n");
	printf("      @     @   @  @   @  @@    @  @  @       @   @   @    @  @    @     @@  \n");
	printf("      @     @   @  @   @  @ @   @  @ @         @ @    @    @  @    @     @@  \n");
    printf("      @     @@@@@  @@@@@  @  @  @  @@           @     @    @  @    @     @@  \n");
    printf("      @     @   @  @   @  @   @ @  @ @          @     @    @  @    @     @@  \n");
    printf("      @     @   @  @   @  @    @@  @  @         @     @    @  @    @         \n");
    printf("      @     @   @  @   @  @     @  @   @        @      @@@@    @@@@      @@  \n");
   
   
	
	printf("\n\n***********************PRESS ANY KEY TO EXIT**********************************\n");
	printf("--------------------------------------------------------------------------------");
	getch();		  	

}



/*Asks user if the latter wants to replay*/
char playagain (var *avar)
{
	int flag=0;
	do
	{
		printf("DO you want to play again y/n\n");
		scanf("%c",&avar->choice1);
		fflush(stdin);
		if(avar->choice1=='y')
		{
			flag=1;
		}
		if(avar->choice1=='n')
		{
			flag=1;
		}
	}
	while(flag!=1);/*The loop accepts only two values y and n*/
	
	return avar->choice1; 
}

/*Print end message when gameover*/
void endgame(var *avar)
{
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute ( h, FOREGROUND_GREEN |FOREGROUND_BLUE | FOREGROUND_INTENSITY) ;

	printf("####### #     # ######     ####### #######     #####     #    #     # #######\n");
	printf("#       ##    # #     #    #     # #          #     #   # #   ##   ## #      \n");
	printf("#       # #   # #     #    #     # #          #        #   #  # # # # #      \n"); 
	printf("#####   #  #  # #     #    #     # #####      #  #### #     # #  #  # #####  \n"); 
	printf("#       #   # # #     #    #     # #          #     # ####### #     # #      \n"); 
	printf("#       #    ## #     #    #     # #          #     # #     # #     # #      \n");
	printf("####### #     # ######     ####### #           #####  #     # #     # #######\n");
	
	printf("\n%s\nYour score is %i points\n", avar->name,avar->fscore);
	
	SetConsoleTextAttribute ( h, wOldColorAttrs);

}







/*MAIN FUNCTION*/

int main()
{
	marray array[MAXSIZE][MAXSIZE];
	var nv;
	
	srand(time(NULL));/*SEED WITH TIME FOR A  DIFFERENT RANDOM NUMBER EACH GAME IS STARTED */
	
	frontcover();
	
	intro();
	
	showplayerrecord(&nv);
	
	welcome(&nv);
	
	do
	{	
		nv.n=size(&nv);
	
		system("CLS");	
		
		initialiseboard(array,&nv);
	
		printarray(array,&nv);
	
		navigation(array, &nv);
		 
		storeplayerrecord(&nv);
		
		nv.choice1=playagain(&nv);
	}
	while(nv.choice1!='n');/*Repeats loop if y is the choice only n as a choice will end game*/
	
	lastcover(&nv);
	

	return 0;
}



