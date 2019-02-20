#include <stdio.h>
#include <conio.h>

char numbers[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void print_grid();
int winner();

int main()
{
  system("cls");

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
    printf("\nChoice: %d\n", choice);
    printf("numbers[1]: %d\n", numbers[1]);

    if (player == 1)
      type = 'X';
    else
      type = 'O';

      if (choice == 1 && numbers[0] == '1')
          numbers[0] = type;

      else if (choice == 2 && numbers[1] == '2'){
        numbers[1] = type;
        printf("type: %c\n", type);
      }


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
      player++;
  }while (result == 3);

  print_grid(name1, name2);

  if (result = 1)
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

void print_grid(char *name1, char *name2)
{
  system("cls");

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

  if ((numbers[0] == numbers[1] && numbers[1] == numbers[2])
        || (numbers[4] == numbers[4] && numbers[4] == numbers[5])
        || (numbers[6] == numbers[7] && numbers[7] == numbers[8])
        || (numbers[0] == numbers[4] && numbers[4] == numbers[6])
        || (numbers[1] == numbers[4] && numbers[4] == numbers[7])
        || (numbers[2] == numbers[5] && numbers[5] == numbers[8])
        || (numbers[0] == numbers[4] && numbers[4] == numbers[8])
        || (numbers[2] == numbers[4] && numbers[4] == numbers[6])
      )
      return 1; // SHOW WINNER

  else if (numbers[0] != '1'
              && numbers[1] != '2'
              && numbers[2] != '3'
              && numbers[4] != '4'
              && numbers[4] != '5'
              && numbers[5] != '6'
              && numbers[6] != '7'
              && numbers[7] != '8'
              && numbers[8] != '9')
      return 2; // NO WINNER
  else
      return  3; // STILL PLAYING
}
