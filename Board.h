#pragma once
#include <iostream>
#include <cstring>

/**
 * @section DESCRIPTION
 * 
 * The Board class represents the chess board, along with the functionality
 * required to move pieces on the board.
 * 
 * @section PIECE INFORMATION
 * 
 * The following characters are representations of pieces used for the program.
 * Capital characters are white pieces and lowercase or black pieces
 * 
 * ROOK     - r R
 * KNIGHT   - n N
 * BISHOP   - b B
 * QUEEN    - q Q
 * KING     - k K
 * PAWN     - p P
 * 
 */

class Board
{
private:

   std::string buffer;

   /**
   * Function that converts a number from a character using ASCII values.
   * 
   * @param  ch is the character that needs to be converted
   * @return the integer value.
   */
   int toNumber(char ch);

   /**
   * Function that sets a piece on the board.
   * 
   * @param  pos is the position where the piece is to be set
   *         It is expected that input is a string with 2 characters.
   * @param  piece is the char representation of the piece.
   * @return the char representation of the piece that was 
             previously in that position.
   */
   char Set(const char* pos, char piece);

   /**
   * Function that retrieves a piece from the board and removes that piece.
   * 
   * @param  pos is the position where the user wishes to retrieve a piece.
   * @return the char representation of the piece that is in that position.
   */
   char Retrieve(const char* pos);

   /**
   * Function that peeks in the board. Similar functionality to
   * Retrieve().
   * 
   * @param  pos is the position where the user wishes to look in at the board.
   * @return the char representation of the piece in that position.
   */
   char Peek(const char* pos);

   /**
   * Function that checks whether a move is possible or not given a specific piece.
   * 
   * @param  fromPos is the initial position.
   * @param  toPos is the desired position.
   * @param  piece is the char representation of the piece to move.
   * @param  player is the char representation of the player ('b' or 'w').
   * @return true if the move is possible, else false.
   */
   bool MovePossible(const char* fromPos, const char* toPos, char piece, char player);

   /**
   * Function that determines the color of a certain piece
   * 
   * @param  ch is the piece
   * @return 1 = WHITE, 0 = BLACK, -1 = BLANK/UNDETERMINED
   */
   int Color(char ch);

public:

   /**
   * Constructor that creates the initial FEN buffer.
   * 
   * @param FEN is a string of characters ending with zero (sz) that represents
   *        the board state of any particular game.
   * 
   * Deconstructor that cleans up the memory.
   */
   Board(const char* FEN) { buffer = FEN; }
   ~Board() { }

   /**
   * Function that tries to move a piece from a position to another position
   * 
   * @param  player is the current player ('w' or 'b') that is trying to move.
   *         If the player is trying to move a black piece while it is white's
   *         turn to move, the move will not happen and vice versa.
   * @param  fromPos is the position of the piece the player is trying to move.
   * @param  toPos is the position that the player is trying to move the piece
   *         from fromPos to.
   */
   void Move(char player, const char* fromPos, const char* toPos);

   /**
   * Function that prints the board out to the screen
   */
   void Print();
};

