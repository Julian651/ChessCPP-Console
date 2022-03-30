#include "Board.h"

int main()
{
   Board* b = new Board("w rnbqkbnr/pppppppp/11111111/11111111/11111111/11111111/PPPPPPPP/RNBQKBNR KQkq - 0 1");

   bool isRunning = true;
   char currentPlayer = 'w';
   while (isRunning)
   {

      b->Print();
      std::cout << "Enter your command: ";

      char in[100];
      std::cin >> in;
      if (strcmp(in, "Move") == 0)
      {

         std::cout << "Enter from tile: ";
         char from[100];
         std::cin >> from;

         std::cout << "Enter to tile: ";
         char to[100];
         std::cin >> to;

         b->Move(currentPlayer, from, to);

         if (currentPlayer == 'w') currentPlayer = 'b';
         else currentPlayer = 'w';
      }

      if (strcmp(in, "Exit") == 0) isRunning = false;
   }

   delete b;
   b = NULL;
   return 0;
}