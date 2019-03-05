#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
//#include <curses.h>

//#define getch() wgetch(stdscr)

struct node
{
  int data;
  struct node *link;
};

char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void print_grid();
int winner();
int check_end();
int check_movement(int, char);

int count(struct node *);
void display(struct node *);
void append(struct node **, int);
void prepend(struct node **, int);
void insert_after(struct node *, int, int);
void delete_value(struct node **, int);

int main()
{
  system("cls");
  // system("clear");
  // clear();

  struct node *moves;
  moves = NULL;
  printf("No of elements in list = %d\n", count(moves));

  int player = 1;
  int choice;
  int result;
  char type;
  char name1[20];
  char name2[20];

  printf("\n Enter Player 1's name: ");
  scanf("%s", name1);
  printf("\n Enter Player 2's name: ");
  scanf("%s", name2);

  do
  {
    print_grid(name1, name2);

    player = player % 2;

    if (player == 1)
    {
      player = 1;
      printf("%s choose your next move: ", name1);
    }
    else
    {
      player = 2;
      printf("%s choose your next move: ", name2);
    }

    scanf("%d", &choice);
    // printf("\nChoice: %d\n", choice);
    // printf("numbers[1]: %d\n", numbers[1]);

    if (player == 1)
      type = 'X';
    else
      type = 'O';

    //check_movement(choice, type);
    //printf("\n\n-----FIRST CHECK MOVEMENT DONE-----\n\n");

    if (check_movement(choice, type) == 0)
    {
      printf("Nah bitch, try again\n");
      player--;
      getch();
    }

    result = winner();
    //printf("RESULT: %d\n", result);
    player++;
  }while (result == 3);

  print_grid(name1, name2);

  if (result == 1)
  {
    --player;
    if (player == 1)
      printf("%s won!\n", name1);
    else
      printf("%s won!\n", name2);
  }
  else
    printf("--- DRAW!!! ---");

  getch();

  return 0;
}



/*
else if (choice == 9 && numbers[8] == '9')
    numbers[8] = type;

1 - 049
2 - 050
3 - 051
4 - 052
9 - 057

https://ee.hawaii.edu/~tep/EE160/Book/chap4/subsection2.1.1.1.html
https://www.quora.com/How-can-I-compare-int-to-char-in-C
https://www.programiz.com/c-programming/examples/alphabet
*/

int check_movement(int choice, char type)
{

  for (int i = 1; i < 10; i++)
  {
    if ((choice + 48) == (int)numbers[i-1])
    {
      numbers[i-1] = type;
      return 1;
    }
  }
  return 0;
}

void print_grid(char *name1, char *name2)
{
  //system("cls");

  printf("\n\n ---- Maria Style Tic Tac Toe ----\n\n");

  printf("   X: %s         O: %s\n\n\n", name1, name2);

  printf("              |     |     \n");
  printf("           %c  |  %c  |  %c \n", numbers[0], numbers[1], numbers[2]);
  printf("         _____|_____|_____\n");
  printf("              |     |     \n");
  printf("           %c  |  %c  |  %c \n", numbers[3], numbers[4], numbers[5]);
  printf("         _____|_____|_____\n");
  printf("              |     |     \n");
  printf("           %c  |  %c  |  %c \n", numbers[6], numbers[7], numbers[8]);
  printf("              |     |     \n\n\n");
}

int winner()
{
  // 1 show winner
  // 2 no winner
  // 3 still playing

  if ((numbers[0] == numbers[1] && numbers[1] == numbers[2])      //VERTICAL 1
        || (numbers[3] == numbers[4] && numbers[4] == numbers[5]) //VERTICAL 2
        || (numbers[6] == numbers[7] && numbers[7] == numbers[8]) //VERTICAL 3
        || (numbers[0] == numbers[3] && numbers[3] == numbers[6]) //HORIZONTAL 1
        || (numbers[1] == numbers[4] && numbers[4] == numbers[7]) //HORIZONTAL 2
        || (numbers[2] == numbers[5] && numbers[5] == numbers[8]) //HORIZONTAL 3
        || (numbers[2] == numbers[4] && numbers[4] == numbers[6]) //DIAGONAL /
        || (numbers[0] == numbers[4] && numbers[4] == numbers[8]) )
      return 1; // SHOW WINNER

  else if (check_end() == 1){
    return 2; // NO WINNER
  }

  else
      return  3; // STILL PLAYING
}

int check_end()
{
  for (int i=0; i<9; i++)
  {
    if ((numbers[i] != 'X') && (numbers[i] != 'O'))
      return 0;
  }
  return 1;
}

int count(struct node * list)
{
  int count = 0;
  // check if it's not empty
  // the end of the list is indicated by NULL in both:
  //    the end of a list
  //    an empty list
  while (list != NULL)
  {
    // traversing the list to process each node
    list = list -> link;
    count++;
  }
  return count;
}

void display(struct node * list)
{
  while (list != NULL)
  {
    printf("%d ", list -> data);
    list = list -> link;
  }
  printf("\n");
}

void append(struct node **list, int num)
{

  struct node *temp, *r;

  if(*list == NULL)
  {
    temp = (struct node *) malloc (sizeof(struct node));
    temp -> data = num;
    temp -> link = NULL;
    *list = temp;
  }
  else
  {
    temp = *list;
    while (temp -> link != NULL)
      temp = temp -> link;

    r = (struct node *) malloc(sizeof(struct node));
    r -> data = num;
    r -> link = NULL;
    temp -> link = r;
  }
}

void prepend(struct node **list, int num)
{
  struct node *temp;
  temp = (struct node *) malloc(sizeof(struct node));
  temp -> data = num;
  temp -> link = *list;
  *list = temp;
}

void insert_after(struct node *list, int location, int num)
{
  struct node *temp, *r;
  int i;
  temp = list;
  for(i=0; i<location; i++)
  {
    temp = temp -> link;
    if (temp == NULL)
    {
      printf("Length of list is %d but supplied location is %d\n", i, location);
      return;
    }
  }
  r = (struct node *)malloc(sizeof(struct node));
  r -> data = num;
  r -> link = temp -> link;
  temp -> link = r;
}

void delete_value(struct node **list, int num)
{
  struct node *old, *temp;
  temp = *list;

  while(temp != NULL)
  {
    if (temp -> data == num)
    {
      if (temp == *list) // if it's the head of the list
      {
        printf("----DELETING THE HEAD----\n");
        *list = temp -> link;
      }
      else // if it's not the first node
      {
        old -> link = temp -> link;
        free(temp);
        return;
      }
    }
    else // next node bc it's not the 1 we want
    {
      old = temp;
      temp = temp -> link;
    }
  }
  printf("Element %d not found in supplied list\n", num);
}
