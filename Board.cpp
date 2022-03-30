#include "Board.h"
constexpr auto WHITE = 1;
constexpr auto BLACK = 0;
constexpr auto BLANK = -1;
int Board::Color(char ch)
{
   if (ch > 64 && ch < 91) return 1;
   else if (ch > 96 && ch < 123) return 0;
   else return -1;
}
int Board::toNumber(char ch)
{
   if (ch > 64 && ch < 73)
   {
      return ch - 65;
   }
   else if (ch > 96 && ch < 105)
   {
      return ch - 97;
   }
   else if (ch > 47 && ch < 58)
   {
      return ch - 48;
   }
   return -1;
}

char Board::Set(const char* pos, char piece)
{
   char pieceRemoved = '1';

   int col = toNumber(*pos) + 1; pos++;
   int row = 9 - toNumber(*pos);

   int line = 0;
   int count = 0;
   for (unsigned int i = 0; i < buffer.size(); i++)
   {
      char c = buffer.at(i);
      if (c == '/' || c == ' ') { line++; }

      if (line == row)
      {
         if (count == col)
         {
            pieceRemoved = c;
            buffer.replace(i, 1, 1, piece);
         }
         count++;
      }
   }

   return pieceRemoved;
}

char Board::Retrieve(const char* pos)
{
   char pieceRetrieved = '1';

   int col = toNumber(*pos) + 1; pos++;
   int row = 9 - toNumber(*pos);

   int line = 0;
   int count = 0;
   for (unsigned int i = 0; i < buffer.size(); i++)
   {
      char c = buffer.at(i);
      if (c == '/' || c == ' ') { line++; }

      if (line == row)
      {
         if (count == col)
         {
            pieceRetrieved = c;
            buffer.replace(i, 1, 1, '1');
         }
         count++;
      }
   }

   return pieceRetrieved;
}

char Board::Peek(const char* pos)
{
   char piecePeeked = '1';

   int col = toNumber(*pos) + 1; pos++;
   int row = 9 - toNumber(*pos);

   int line = 0;
   int count = 0;
   for (unsigned int i = 0; i < buffer.size(); i++)
   {
      char c = buffer.at(i);
      if (c == '/' || c == ' ') { line++; }

      if (line == row)
      {
         if (count == col)
         {
            piecePeeked = c;
         }
         count++;
      }
   }

   return piecePeeked;
}

bool Board::MovePossible(const char* fromPos, const char* toPos, char piece, char player)
{
   if (piece > 96 && piece < 123 && player == 'w') return false;
   if (piece > 64 && piece < 91 && player == 'b') return false;

   int fromCol = toNumber(*fromPos) + 1; fromPos++;
   int fromRow = 9 - toNumber(*fromPos); fromPos--;

   int toCol = toNumber(*toPos) + 1; toPos++;
   int toRow = 9 - toNumber(*toPos); toPos--;

   switch (piece)
   {
   case 'P':

   case 'p':

   {
      char pieceAtPos = Peek(toPos);

      int sign = 1;
      if (piece == 'P') sign = -1;

      if ((fromPos[1] == '2' || fromPos[1] == '7') && toPos[1] + 0 == fromPos[1] - (sign * 2)) //double forward
      {
         char pieceForward[3];
         strcpy_s(pieceForward, fromPos);
         pieceForward[1] -= sign;
         std::cout << toPos[1] + 0 << " " << fromPos[1] - (sign * 2) << std::endl;
         if (pieceAtPos == '1' && Peek(pieceForward) == '1') return true;
      }
      else if (toPos[1] + 0 == fromPos[1] + 0 - sign) // single forward
      {
         if (toPos[0] == fromPos[0]) // straight
         {
            if (pieceAtPos == '1') return true; // only move forward if blank
         }
         else if (toPos[0] + 0 == fromPos[0] - 1 || toPos[0] + 0 == fromPos[0] + 1) // diagonal
         {
            if (pieceAtPos == '1') return false;
            if (Color(pieceAtPos) == Color(piece)) return false; // if the piece is the same color, cant go there
            return true;
         }
      }
   }

   break;

   case 'R':

   case 'r':

   {
      int index = 0;
      if (fromPos[0] == toPos[0] && fromPos[1] != toPos[1]) index = 1;
      else if (fromPos[1] == toPos[1] && fromPos[0] != toPos[0]) index = 0;
      else
      {
         bool one = fromPos[0] == toPos[0];
         bool two = fromPos[1] != toPos[1];
         std::cout << one << " " << two << index << std::endl;
         return false;
      }

      std::cout << "index: " << index << std::endl;

      char currentPos[3];
      strcpy_s(currentPos, fromPos);

      int sign = -1;
      if (fromPos[1] - toPos[1] < 0 || fromPos[0] - toPos[0] < 0) sign = 1;

      while (!(strcmp(currentPos, toPos) == 0))
      {
         currentPos[index] = currentPos[index] + sign;
         if (Color(Peek(currentPos)) == Color(piece)) return false;
      }
      return true;
   }

   break;

   case 'N':

   case 'n':

   {
      // knight movement
      bool one = toPos[0] + 0 == fromPos[0] + 2 && toPos[1] + 0 == fromPos[1] + 1;
      bool two = toPos[0] + 0 == fromPos[0] + 2 && toPos[1] + 0 == fromPos[1] - 1;
      bool three = toPos[0] + 0 == fromPos[0] - 2 && toPos[1] + 0 == fromPos[1] + 1;
      bool four = toPos[0] + 0 == fromPos[0] - 2 && toPos[1] + 0 == fromPos[1] - 1;

      bool five = toPos[0] + 0 == fromPos[0] + 1 && toPos[1] + 0 == fromPos[1] + 2;
      bool six = toPos[0] + 0 == fromPos[0] + 1 && toPos[1] + 0 == fromPos[1] - 2;
      bool seven = toPos[0] + 0 == fromPos[0] - 1 && toPos[1] + 0 == fromPos[1] + 2;
      bool eight = toPos[0] + 0 == fromPos[0] - 1 && toPos[1] + 0 == fromPos[1] - 2;
      if (Color(Peek(toPos)) == Color(piece)) return false;
      if (one || two || three || four || five || six || seven || eight) return true;
   }

   break;

   case 'B':

   case 'b':

   {
      if (abs(toPos[0] - fromPos[0]) == abs(toPos[1] - fromPos[1])) // diagonal
      {
         char currentPos[3];
         strcpy_s(currentPos, fromPos);

         int up = 1;
         int right = 1;
         if (toPos[1] - fromPos[1] < 0) up = -1;
         if (toPos[0] - fromPos[0] < 0) right = -1;

         while (!(strcmp(currentPos, toPos) == 0))
         {
            currentPos[0] += right;
            currentPos[1] += up;
            std::cout << currentPos << std::endl;
            if (Color(Peek(currentPos)) == Color(piece)) return false;
         }
         return true;
      }
   }

   break;

   case 'Q':

   case 'q':

   {
      if (abs(toPos[0] - fromPos[0]) == abs(toPos[1] - fromPos[1])) // diagonal
      {
         char currentPos[3];
         strcpy_s(currentPos, fromPos);

         int up = 1;
         int right = 1;
         if (toPos[1] - fromPos[1] < 0) up = -1;
         if (toPos[0] - fromPos[0] < 0) right = -1;

         while (!(strcmp(currentPos, toPos) == 0))
         {
            currentPos[0] += right;
            currentPos[1] += up;
            std::cout << currentPos << std::endl;
            if (Color(Peek(currentPos)) == Color(piece)) return false;
         }
         return true;
      }
      else // horizontal or vertical
      {
         int index = 0;
         if (fromPos[0] == toPos[0] && fromPos[1] != toPos[1]) index = 1;
         else if (fromPos[1] == toPos[1] && fromPos[0] != toPos[0]) index = 0;
         else
         {
            bool one = fromPos[0] == toPos[0];
            bool two = fromPos[1] != toPos[1];
            std::cout << one << " " << two << index << std::endl;
            return false;
         }

         std::cout << "index: " << index << std::endl;

         char currentPos[3];
         strcpy_s(currentPos, fromPos);

         int sign = -1;
         if (fromPos[1] - toPos[1] < 0 || fromPos[0] - toPos[0] < 0) sign = 1;

         while (!(strcmp(currentPos, toPos) == 0))
         {
            currentPos[index] = currentPos[index] + sign;
            if (Color(Peek(currentPos)) == Color(piece)) return false;
         }
         return true;
      }
   }

   break;

   case 'K':

   case 'k':

   {
      if (abs(toPos[0] - fromPos[0]) > 1 || abs(toPos[1] - fromPos[1]) > 1) return false;
      else if (Color(Peek(toPos)) == Color(piece)) return false;
      return true;
   }

   break;
   }

   return false;
}

void Board::Move(char player, const char* fromPos, const char* toPos)
{
   if (player == buffer.at(0))
   {
      char piece = Retrieve(fromPos);

      if (MovePossible(fromPos, toPos, piece, player))
      {
         Set(toPos, piece);
         if (player == 'w') buffer.replace(0, 1, 1, 'b');
         else buffer.replace(0, 1, 1, 'w');
      }
      else
      {
         std::cout << "\nMove impossible.\n";
         Set(fromPos, piece);
      }

   }
}

void Board::Print()
{
   std::cout << "\n====================================================================================\n";
   std::cout << "\n" << buffer << "\n";

   int line = 0;
   for (unsigned int i = 0; i < buffer.size(); i++)
   {
      char c = buffer.at(i);
      if (c == '/' || c == ' ') { line++; std::cout << std::endl; continue; }

      //0st line - who's to move

      if (line == 0)
      {
         if (c == 'w') std::cout << "\nWhite to move.\n";
         else std::cout << "\nBlack to move.\n";
      }

      //1nd - 9th lines - board state

      else if (line < 9) std::cout << c;

      //9th line - castle viability

      else if (line == 9)
      {
         if (c == 'K') std::cout << "\nWhite King side castle avaliable.";
         else if (c == 'Q') std::cout << "\nWhite Queen side castle avaliable.";
         else if (c == 'k') std::cout << "\nBlack King side casle avaliable.";
         else if (c == 'q') std::cout << "\nBlack Queen side castle avaliable.";
      }

      // 10th line, en passant target square
      else if (line == 10)
      {
         if (i - 1 >= 0 && buffer.at(i-1) == ' ')
         {
            std::cout << "\nEn passant target square ";
         }
         std::cout << c;
      }

      // 11th line, halfmove clock

      // 12th line, fullmove number
   }
}
