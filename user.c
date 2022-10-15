#include <stdio.h>
#include <stdlib.h>

#include "libraryStructures.h"
#include "user.h"
#include "utility.h"

////
// Code module for the library user
// They can look for available books,
// borrow and return books

// List the books that are available to borrow
// Input
// bookList - the array of Book structures
// numBooks - the number of books

void listAvailableBooks( Book *bookList, int numBooks ) {

  // TO DO :  

  // print out available books with format "list number - author - title" on each line
  int sh = 0;
  for (sh = 0; sh<numBooks; sh++)
  {
  	if (bookList[sh].available == 1)
  	{
  		printf("%d - %s - %s\n", sh, bookList[sh].author, bookList[sh].title);
	}
  }
  return;
}

// Borrow a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void borrowBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  
	int Availablelist[numBooks];
	int sh=0;
	while (sh<numBooks)
	{
		if (bookList[sh].available)
		{
			Availablelist[sh] = sh;
		}
		sh++;
	}
  // For any error message you should return to the menu

  // check that the user can borrow a book
  if (theUser->numBorrowed >= maxBorrowed){
  printf("You have to return a book before you can borrow another\n");
  return;}
  // request the choice of book 
  int xx = -1; 
  printf("Which book? (number):");
  xx = optionChoice();
  if (xx<0 || xx >= (numBooks-theUser->numBorrowed)){
  // check that the choice is valid 
  // error messages
  printf("Error\nInvalid choice\n");
  return;}
  if (bookList[xx].available == 0){
  printf("Book is not available\n");
  return;}
  
  // borrow the book, update the data structures
  else
  {
  	Book* Borrowed = &bookList[Availablelist[xx]];
  	theUser->borrowed[theUser->numBorrowed] = Borrowed;
  	bookList[Availablelist[xx]].available = 0;
	theUser->numBorrowed ++;
  }
  return; 
}

// List books I have borrowed 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// maxBorrowed - max books we can borrow

void listMyBooks( User *theUser, Book *bookList, int maxBorrowed ) {

  // TO DO :  

  // list my books in format "number - author - title"
  int sh=0;
  while (sh<theUser->numBorrowed)
  {
  	printf("%d - %s - %s\n", sh, theUser->borrowed[sh]->author, theUser->borrowed[sh]->title);
	sh++;
  }
  return;
}

// Return a book 
// Input
// theUser - user data structure
// bookList - the array of Book structures
// numBooks - the number of books
// maxBorrowed - max books we can borrow

void returnBook( User *theUser, Book *bookList, int numBooks, int maxBorrowed ) {

  // TO DO :  

  // For any error message you should return to the menu
  if (theUser->numBorrowed == 0){
  // check that we have borrowed books 
  // error messages
  printf("Error\nYou have not borrowed any books\n");
  return;}
  else
  // request the choice of book 
  // message
  printf("Which book? (number):");
  int xx = -1;
  xx = optionChoice();
  if (xx < 0){
  // check the choice is valid
  // error messages
  printf("Error\nInvalid choice\n");
  return;}
  if (xx > theUser->numBorrowed-1){
  // check the choice is valid
  // error messages
  printf("Error\nInvalid choice\n");
  return;}
  // return the book and update data structures 
  int n;
  for (n=0;n<numBooks;n++)
  {
  	if (bookList[n].author == theUser->borrowed[xx]->author)
  		bookList[n].available = 1;
  }
  if (xx == theUser->numBorrowed)
  	theUser->numBorrowed --;
  else
  {
  	while (xx<theUser->numBorrowed)
	{
		theUser->borrowed[xx] = theUser->borrowed[xx+1];
		xx ++;
	}
  	theUser->numBorrowed --;
  }
  return;
}

// DO NOT ALTER THIS FUNCTION

// Menu system for library user

void userCLI( Library *theLibrary ) {
    int userLoggedIn = 1;
    int option;

    while( userLoggedIn ){
        printf("\n User options\n 1 List available books\n 2 Borrow book\n 3 Return book\n 4 Log out\n Choice:");
        option = optionChoice();

        if( option == 1 ) {
            printf("\nList available books:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
        }
        else if( option == 2 ) {
            printf("\nBorrow book from library:\n");
            listAvailableBooks( theLibrary->bookList, theLibrary->numBooks );
            borrowBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 3 ) {
            printf("\nReturn book from my list:\n");
            listMyBooks( &(theLibrary->theUser), theLibrary->bookList, theLibrary->maxBorrowed );
            returnBook( &(theLibrary->theUser), theLibrary->bookList, theLibrary->numBooks, theLibrary->maxBorrowed );
        }
        else if( option == 4 ) {
            userLoggedIn = 0;
            printf("\nLogging out\n");
        }
        else
            printf("\nUnknown option\n");
    }
    return;
}

