//============================================================================================
//Destination sort algorythm, originally written for a bellringing programme.
//By Ray Houghton
//10 May 2025
//This algorythm was written by me and any similarities to other existing code is coincidental
//except for the Array_cmp function Posted by ShadowX on Arduino forum "Thank's ShadowX"
//Anyone who wishes to, can use or modify this code free of charge but please don't try 
//and pass it off as your own work. Use this software at your own risk.

//Any order can be inserted in the initialOrder and destination arrays as long as both arrays
//contain the same elements and the array size reflects this.
//"elementNumber" should reflect the number of elelments in the arrays -1. 
//You can have as many elements in the arrays as your hardware supports.   
//============================================================================================
int initialOrder[20] = {12, 23, 34, 45, 56, 67, 78, 89}; //Array containing initial order
int destination[20]= {89, 67, 45, 23, 78, 56, 34, 12};  //Array containing target order
int intermediateOrder[20]; //Array containing intermediate order
int*ptrInitialOrder; int*ptrIntermediateOrder; int *ptrDestination;
//Pointers for functions to work on arrays
int elementNumber = 7; //Figure used to index arrays, Number of elements in the array -1
int a; //variable to show when operations are complete
int element; //Marker that points to the array elemnt that is currently 
//being worked on in the "destination" array
int m; //Marker that counts through the "initial order" array to find 
//the element being worked on

void PrintArray(int [], int); //Function to print array contents
// prints contents of array
void InitArray(int [], int [], int);
//writes "initialOrder" elements to "intermediateOrder" array 
void SwapElement(int[], int[], int);
//swaps the two elements corresponding to the third argument
boolean Array_cmp(int[], int[], int); //Compares array contents

void setup() {
  Serial.begin(115200);
delay(10000);  //Time to open serial monitor
for(uint8_t l = 0; l <= elementNumber; l++) //prints array contents
    {
    Serial.print(initialOrder[l]);
    Serial.print(", ");
    }
 Serial.println();
}

void loop() 
{
ptrInitialOrder = &initialOrder[0]; //assign pointers to array addresses
ptrIntermediateOrder = &intermediateOrder[0];
ptrDestination = &destination[0];
InitArray(ptrInitialOrder, ptrIntermediateOrder, elementNumber);
while(Array_cmp(ptrInitialOrder, ptrDestination, elementNumber) == false)
{//While loop that runs until current order = destination order
for(element = elementNumber; element>=1; element --)
 //For loop that counts down from the elementNumber to 1. 
 //element refers to the position of the number being worked on in the destination array. 
  { 
  a = 0; //a is a value that is set to one when an element is in the correct position.
  m = element; 
  //Assigns the starting point to look for the current element 
  //"Destination" in the "initialOrder" array
 while(a != 1) //while loop to find current "destination[]" element in the "initialOrder" 
 {
 
 if(initialOrder[m]!=destination[element])//find equivalent element
   {  
    m--;
   }
   else
    {
     a = 1;   //exit loop with "m" at the correct value 
    } 
 }
 int b = (m); //assigns equivalent element pos'n to variable "b"
 for(int j = b; j <= (element-1); j++)
 //loop to move selected "element" into correct position
{

SwapElement(ptrInitialOrder, ptrIntermediateOrder, j); 
//move misplaced element towards correct position
PrintArray(ptrInitialOrder, elementNumber);//print order of "initialOrder" after swap

}
}  
}
}

//==============================================================
//Writes the contents of the first array perameter into the second
//The third perameter reflects the number of elements in use in 
//the arrays
//==============================================================
void InitArray(int a[], int b[], int numBells) 
{
  for(uint8_t l = 0; l <= numBells; l++)  //loop to print bell order
    {
    b[l] = a[l]; //ensures arrays are equal
    }
}

//==============================================================
//Prints the contents of the array (first perameter)
//The second perameter reflects the number of elements in use in 
//the array
//==============================================================

void PrintArray(int c[], int d)
{
  
   for(uint8_t l = 0; l <= d; l++) //prints array contents
    {
    Serial.print(c[l]);
    Serial.print(", ");
    }
 Serial.println();
    
}
//================================================================
//Function to compare two arrays
//Posted by ShadowX on Arduino forum "Thank's ShadowX"
//================================================================
boolean Array_cmp(int *a, int *b, int len_a)
    {
         uint8_t n;

         // test each element to be the same. if not, return false
         for (n=0;n<len_a;n++) if (a[n]!=b[n]) return false;

         //ok, if we have not returned yet, they are equal :)
         return true;
    }

//==============================================================
//swaps the array element corresponding to the third parameter
//with the next element
//the change is written to both arrays 
//==============================================================

void SwapElement(int FirstArr[], int SecondArr[], int Index) 
{
  SecondArr[Index+1] = FirstArr[Index]; //swap routine
        SecondArr[Index] = FirstArr[Index+1];
        FirstArr[Index] = SecondArr[Index];     
        //writes the newly exchanged elements into the current array
        FirstArr[Index+1] = SecondArr[Index+1];
}
//==============================================================
