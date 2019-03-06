#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
//#include <curses.h>

//#define getch() wgetch(stdscr)
#define MAX 30

struct stack
{
  int array[MAX]; // study this
  int top;
};

char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void print_grid();
int winner();
int check_end();
int check_movement(int, char);

unsigned concatenate(unsigned, unsigned);

void init_stack(struct stack *);
void push(struct stack*, int);
int *pop(struct stack *);

int main()
{
  system("cls");
  // system("clear");
  // clear();

  struct stack first; // where all moves will go
  struct stack second; // where moves will go if player decis to undo
  init_stack(&first);
  init_stack(&second);

  int player = 1;
  int choice;
  int result;
  int *move = NULL; // to pop from stack
  int last_move;
  int player_move;
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

    if (player == 1) // print name and options
    {
      player = 1;
      printf("%s choose a number your next move, 10 for undo or 20 for redo: ", name1);
    }
    else
    {
      player = 2;
      printf("%s choose a number your next move, 10 for undo or 20 for redo: ", name2);
    }

    scanf("%d", &choice);

    if (player == 1) // set X or O
    {
      type = 'X';
      player_move = 1;
    }
    else //player 2
    {
      type = 'O';
      player_move = 2;
    }

    if (choice == 10) // undo - pop item from first and push into second
    {
      move = pop(&first); // pop from first
      if (move)
      {
        printf("Item popped from first: %d\n", *move);
        push(&second, *move); // push into second

        // set grid as top in first - pop second, change first X or O for first number, push it back to second
        move = pop(&second);

        if (move)
        {
          last_move = *move;
          printf("Last move: %d\n", last_move); //31

          // get first digit of last_move to find what space to change
          while(last_move >= 10)
            last_move = last_move / 10;

          // from X or O to 3
          printf("numbers[last_move-1]: %c\n", numbers[last_move-1]); // this is a char
          printf("last_move: %d\n", last_move);
          numbers[last_move-1] = last_move + '0';
          print_grid(name1, name2);

          printf("*move: %d\n", *move);
          push(&second, *move);
          printf("Pushed to second: %d\n", *move);
        }
      }
    }
    if (choice == 20) // redo
    {
      printf("You chose the redo option.\n");
    }

    // if movement is unvalid
    if ((check_movement(choice, type) == 0) && (choice != 10) && (choice != 20))
    {
      printf("Nah bitch, try again\n");
      player--;
      getch();
    }
    else // add movement to history of moves
    {
      /*
         51 means 5 for choice and 1 for X
         1 for X (player 1)
         2 for O (player 2)
         3 for - not played yet
      */
      if ((choice != 10)&&(choice != 20))
      {
        int moves_number = concatenate(choice, player_move);
        push(&first, moves_number); // push to first - add move to stack
        printf("Pushed to first: %d\n", moves_number);
      }
    }

    result = winner();
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
  check if movement is valid
  return 0 for invalid, 1 for valid, 2 for undo, 3 for redo
*/
int check_movement(int choice, char type)
{
  // for the numbers in the grid
  for (int i = 1; i < 10; i++)
  {
    /*
      choice is an int and numbers is a list of chars so
      when converting a char to int it will give the ASCII
      value, therefore i need to add 48 to choide to get
      the ASCII value of the choice
      1 - 049
      2 - 050
      3 - 051
      4 - 052
      9 - 057
      https://ee.hawaii.edu/~tep/EE160/Book/chap4/subsection2.1.1.1.html
      https://www.quora.com/How-can-I-compare-int-to-char-in-C
      https://www.programiz.com/c-programming/examples/alphabet
    */
    if ((choice + 48) == (int)numbers[i-1])
    {
      numbers[i-1] = type;
      return 1; // valid
    }
  }
  return 0; // invalid
}

unsigned concatenate(unsigned x, unsigned y)
{
    unsigned pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;
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

/*
  accessing the variable that points to the top of the Stack
  setting it to -1 to indicate that the stack is empty
*/
void init_stack(struct stack *s)
{
  s->top = -1;
}

/*
  check the position of the variable that indicates the top
  of the stack
  */
void push(struct stack *s, int item)
{
  // if top = max size, taking into account zero indexing
  if(s->top == MAX-1)
  {
    // then stack is full
    printf("Stack is full. Couldn't push '%d' onto stack\n", item);
    return;
  }
  // otherwise we alter where the variable pointing to top points to
  s->top++;
  // then place the item into the stack
  s->array[s->top] = item;
}

int *pop(struct stack *s)
{
  // temprary storage for item to pop
  int *data;

  // check position of top indicator variable
  // if it points to the bottom of the array...
  if (s->top == -1)
  {
    // stack is empty and there is nothing to pop
    printf("There are no moves to undo.\n");
    // if pop() == NULL then stack is empty
    return NULL;
  }
  // access the value stored in the current location
  data = &s->array[s->top];
  // alter top pointer to point to the item below the current item
  // so that next time pop is called it will retrieve the next item
  s->top--;

  return data;
}
