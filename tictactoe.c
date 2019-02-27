#include <stdio.h>
// #include <conio.h>
#include <curses.h>

#define getch() wgetch(stdscr)

char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void print_grid();
int winner();
int check_end();
void check_movement(int, char);

int main()
{
  // system("cls");
  // system("clear");
  // clear();

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

    if (player = (player % 2))
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

      if (choice == 1 && numbers[0] == '1')
          numbers[0] = type;

      else if (choice == 2 && numbers[1] == '2')
        numbers[1] = type;

      else if (choice == 3 && numbers[2] == '3')
          numbers[2] = type;

      else if (choice == 4 && numbers[3] == '4')
          numbers[3] = type;

      else if (choice == 5 && numbers[4] == '5')
          numbers[4] = type;

      else if (choice == 6 && numbers[5] == '6')
          numbers[5] = type;

      else if (choice == 7 && numbers[6] == '7')
          numbers[6] = type;

      else if (choice == 8 && numbers[7] == '8')
          numbers[7] = type;

      else if (choice == 9 && numbers[8] == '9')
          numbers[8] = type;

      else
      {
        printf("Nah bitch, try again\n");

        player--;
        getch();
      }

      result = winner();
      printf("RESULT: %d\n", result);
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

void check_movement(int choice, char type)
{
  for (int i = 0; i < 10; i++)
  {
    if ((choice + 48) == numbers[i-1])
      numbers[i-1] = type;
  }
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
