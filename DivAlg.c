//John Harvey
//DivAlg

#include <stdio.h> // the usual 
#include <assert.h> // a nice tool 
#include <stdlib.h>
#include <string.h>
#define DebugDivAlg 0 // for controlling debug
#define DebugMain 1
#define AvailDebug 0

char * UDEC(unsigned int ); 					// initial prototype before buffering
char *HEX(unsigned int); 					// each will return a char *
char *IP( unsigned int); 
int DivAlg(unsigned int, char*); 				// This is called from main

// MAIN 
int main() 
{ int TestValue = 0xFACECAFE;;
  char *Buffer ;  int BufferIndex;
  Buffer = (char *) malloc(600); 				// a bunch of bytes
  printf("Division Algorithm\n");
  memset(Buffer,'*',598);Buffer[599]=(char)0; 			// asterisks , null
  BufferIndex = DivAlg(TestValue,Buffer);
  if (BufferIndex == -1)printf("Buffer was too small %d\n",BufferIndex);
  else fprintf(stderr,"%s\n",&Buffer[BufferIndex]);
  
}


int DivAlg (unsigned int Val, char * Buffer)			// DivAlg which takes in an unsigned int 'Val'
{								// and a char * Buffer filled with *'s
	int StrLen, BuffLen, CurrentPlace, NextPlace;		// Declare ints for filling Buffer after conversions have been made
	BuffLen = strlen(Buffer);
	if (BuffLen < 73){					// If Buffer is too small, return -1
		return -1;	}

	char *InDec, *InHex, *InIp;		 		// Delcare char *'s and table
	char *Table = "0123456789ABCDEF";			

	InHex = malloc(35); InIp = malloc(35); InDec = malloc(35);	// Allocate memory for char *'s

//*******************DECIMAL CONVERSION*************************//
	unsigned int Valcopy2 = Val;				// Make a copy of the val
	char * YourValLit = "Your Value: ";			// Declare literals that will go in the InDec char *
	char * DecLiteral = " decimal";
	int j=21;

	strncpy(&InDec[0], YourValLit, 12);			// String copy 'Your Value' before adding the decimal digits
	while(Valcopy2 != 0)
	{		
		InDec[j--] = Table[Valcopy2 % 10];		// Use the division algo to fill the buffer with decimal digits
		Valcopy2 = Valcopy2 / 10;
	}
	strncpy(&InDec[22], DecLiteral, 8);			// String copy ' decimal' into the InDec char *
	InDec[30]='\n';						// Add a new line at the end of the InDec char * 
//*******************END DECIMAL CONVERSION*********************//


//*******************HEX CONVERSION*****************************//
   unsigned int ValCopy = Val; 					// copy Val and declare index int for while loop
   int index = 15; 							
   char * HexLiteral = "In Hex: ";				// Declare literal that will go in the InHex char *
   strncpy(&InHex[0], HexLiteral, 8);				// String copy 'In Hex: ' before adding the hex digits
   while (ValCopy > 0)			
    {								// Use the division algo along with masking and shifting to 
    	InHex[index--] = Table[(ValCopy & 0xF)];		// fill the InHex char *
    	ValCopy >>= 4;                     			// Shift >> 4 equals % 16
    }
    InHex[16] = '\n';						// Add a new line at the end of the InHex char *
//*******************END HEX CONVERSION*************************//


//*******************IP CONVERSION******************************//
    int i;							// Declare int used in for loop
    char * IpLiteral = "In IP: ";				// Declare literal 'In IP: ' that will go before the IP Digits
    strncpy(&InIp[0], IpLiteral, 7);				// String copy literal into InIp char *
    int IpBuffNdx = 22;                     
    for(i=0; i < 4; i++) 					// For loop which will mask and shift, and fill the InIp char *
    {
    	int IpDig = Val & 0xFF;					// Mask off unwanted bits
    	while(IpDig > 0)
    		{
    			InIp[IpBuffNdx--] = Table[IpDig % 10];	// Use table lookup and % 10 to get individual IP digits
    			IpDig = IpDig / 10;		
    		}

    	InIp[IpBuffNdx--] = '.';   				// Add '.' every three digits
    	Val >>= 8; 						// Shift >> 8 equals % 256					
    }
    InIp[7] = ' ';	// Clear unwanted '.'
//*******************END IP CONVERSION**************************//


//*******************FILL BUFFER********************************//	
	CurrentPlace = BuffLen;					// Get current buffer length
	StrLen = strlen(InIp);					// Get length of InIp char *
	NextPlace = CurrentPlace - StrLen+1;			// Get NextPlace digit for string copy
	strncpy(&Buffer[NextPlace], InIp, StrLen);		// String copy InIp char * into Buffer
	StrLen = strlen(InHex);					// Get length of InHex char *
	CurrentPlace = NextPlace;				// Set new current place
	NextPlace = CurrentPlace - StrLen;			// Set new NextPlace
	strncpy(&Buffer[NextPlace], InHex, StrLen);		// String copy InHex char * into Buffer
	StrLen = strlen(InDec);					// Get length of InDec char *
	CurrentPlace = NextPlace;				// Set new current place		
	NextPlace = CurrentPlace - StrLen;			// Set new NextPlace
	strncpy(&Buffer[NextPlace], InDec, StrLen);		// String copy InDec char * into Buffer
	return NextPlace;					// Return Nextplace for final Buffer output
//*******************END FILL BUFFER*****************************//
}
