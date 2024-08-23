#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include <map>

using namespace std;

/*
 * C++ Starter code for CS241 A3
 * All code requires C++14, so if you're getting compile errors make sure to
 * use -std=c++14.
 *
 * This file contains the main function of your program. By default, it just
 * prints the scanned list of tokens back to standard output.
 */

void outputBinary(int instr)
{
  unsigned char c = instr >> 24;
  cout << c;
  c = instr >> 16;
  cout << c;
  c = instr >> 8;
  cout << c;
  c = instr;
  cout << c;
}

int main()
{
  std::string line;
  vector<string> lines;
  int pc = 0;
  // map for labels
  map<string, int> labels;
  map<string, int>::iterator it;
  int maxInstructions = 0;

  try
  {
    while (getline(std::cin, line))
    {
      lines.push_back(line);
      std::vector<Token> tokenLine = scan(line);
      // if valid instructions on the line we store the labels in the map
      if (tokenLine.size() > 0)
      {
        bool onlyLabel = true;
        for (int i = 0; i < tokenLine.size(); i++)
        {
          // cout << tokenLine[i] << endl;
          if (tokenLine[i].getKind() == Token::LABEL)
          {
            string l = tokenLine[i].getLexeme();
            l = l.substr(0, l.length() - 1);
            if (labels.find(l) != labels.end())
            {
              throw ScanningFailure("ERROR");
            }
            labels.insert(std::pair<string, int>(l, pc));
            // cout << l << " " << pc << endl;
          }
          else
          {
            onlyLabel = false;
          }
        }
        if (!onlyLabel)
        {
          pc += 4;
        }
      }
    }
    maxInstructions = pc / 4;
    pc = 0;
    for (int j = 0; j < lines.size(); j++)
    {
      line = lines[j];
      // This example code just prints the scanned tokens on each line.
      std::vector<Token> tokenLine = scan(line);

      // This code is just an example - you don't have to use a range-based
      // for loop in your actual assembler. You might find it easier to
      // use an index-based loop like this:
      // for(int i=0; i<tokenLine.size(); i++) { ... }
      for (int i = 0; i < tokenLine.size(); i++)
      {
        Token::Kind kind = tokenLine[i].getKind();
        string lex;
        int size = tokenLine.size();
        // cout << tokenLine[i] << endl;

        if (kind == Token::WORD)
        {
          pc += 4;
          i++;
          if (i >= size)
          {
            throw ScanningFailure("ERROR");
          }
          kind = tokenLine[i].getKind();

          if (kind == Token::INT || kind == Token::HEXINT)
          {
            if (tokenLine[i].toNumber() <= 4294967296 && tokenLine[i].toNumber() >= -2147483648)
            {

              outputBinary(tokenLine[i].toNumber());
            }
            else
            {
              throw ScanningFailure("ERROR");
            }
          }
          else if (kind == Token::ID)
          {
            if (labels.find(tokenLine[i].getLexeme()) == labels.end())
            {
              throw ScanningFailure("ERROR");
            }
            outputBinary(labels[tokenLine[i].getLexeme()]);
            // cout << labels[tokenLine[i].getLexeme()] << endl;
          }
          else
          {
            throw ScanningFailure("ERROR");
          }
        }

        else if (kind == Token::ID)
        {

          lex = tokenLine[i].getLexeme();

          if (lex == "add")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (op << 26) | (num2 << 21) | (num3 << 16) | (num1 << 11) | 32;
            outputBinary(instr);
          }

          else if (lex == "sub")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (op << 26) | (num2 << 21) | (num3 << 16) | (num1 << 11) | 34;
            outputBinary(instr);
          }

          else if (lex == "slt")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (op << 26) | (num2 << 21) | (num3 << 16) | (num1 << 11) | 42;
            outputBinary(instr);
          }

          else if (lex == "sltu")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (op << 26) | (num2 << 21) | (num3 << 16) | (num1 << 11) | 43;
            outputBinary(instr);
          }

          else if (lex == "mult")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | 24;
            outputBinary(instr);
          }

          else if (lex == "multu")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | 25;
            outputBinary(instr);
          }

          else if (lex == "div")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | 26;
            outputBinary(instr);
          }

          else if (lex == "divu")
          {
            pc += 4;
            int op = 0;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | 27;
            outputBinary(instr);
          }

          else if (lex == "mfhi")
          {
            pc += 4;
            i++;

            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();

            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (0 << 16) | (num1 << 11) | 16;
            outputBinary(instr);
          }

          else if (lex == "mflo")
          {
            pc += 4;
            i++;

            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();

            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (0 << 16) | (num1 << 11) | 18;
            outputBinary(instr);
          }

          else if (lex == "jr")
          {
            pc += 4;
            i++;
            int64_t num1 = 0;
            if (i >= size)
            {
              throw ScanningFailure("ERROR");
            }
            if (tokenLine[i].getKind() == Token::REG)
            {
              num1 = tokenLine[i].toNumber();

              if (num1 > 31 || num1 < 0)
              {
                throw ScanningFailure("ERROR");
              }
            }
            else if (tokenLine[i].getKind() == Token::LABEL)
            {
              if (labels.find(tokenLine[i].getLexeme()) == labels.end())
              {
                throw ScanningFailure("ERROR");
              }
              int addy = labels[tokenLine[i].getLexeme()];
              num1 = (addy - pc) / 4;
            }
            else
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (0 << 26) | (num1 << 21) | 8;
            outputBinary(instr);
          }

          else if (lex == "jalr")
          {
            pc += 4;
            i++;
            int64_t num1 = 0;
            if (i >= size)
            {
              throw ScanningFailure("ERROR");
            }
            if (tokenLine[i].getKind() == Token::REG)
            {
              num1 = tokenLine[i].toNumber();

              if (num1 > 31 || num1 < 0)
              {
                throw ScanningFailure("ERROR");
              }
            }
            else if (tokenLine[i].getKind() == Token::LABEL)
            {
              if (labels.find(tokenLine[i].getLexeme()) == labels.end())
              {
                throw ScanningFailure("ERROR");
              }
              int addy = labels[tokenLine[i].getLexeme()];
              num1 = (addy - pc) / 4;
            }
            else
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (0 << 26) | (num1 << 21) | 9;
            outputBinary(instr);
          }

          else if (lex == "lis")
          {
            pc += 4;
            i++;

            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();

            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            int instr = (0 << 16) | (num1 << 11) | 20;
            outputBinary(instr);
          }

          else if (lex == "lw")
          {
            pc += 4;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || (tokenLine[i].getKind() != Token::INT && tokenLine[i].getKind() != Token::HEXINT))
            {
              throw ScanningFailure("ERROR");
            }
            // num2 is i
            if (tokenLine[i].toNumber() > 1844674407370955161)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::LPAREN)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::RPAREN)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (35 << 26) | (num3 << 21) | (num1 << 16) | (num2 & 0xFFFF);
            outputBinary(instr);
          }

          else if (lex == "sw")
          {
            pc += 4;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || (tokenLine[i].getKind() != Token::INT && tokenLine[i].getKind() != Token::HEXINT))
            {
              throw ScanningFailure("ERROR");
            }
            // num2 is i
            if (tokenLine[i].toNumber() > 1844674407370955161)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::LPAREN)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::RPAREN)
            {
              throw ScanningFailure("ERROR");
            }
            if (num3 > 31 || num3 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (43 << 26) | (num3 << 21) | (num1 << 16) | (num2 & 0xFFFF);
            outputBinary(instr);
          }

          else if (lex == "beq")
          {
            pc += 4;
            int op = 4;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            i++;
            // cout << tokenLine[i] << endl;
            if (i >= size)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = 0;
            kind = tokenLine[i].getKind();
            // cout << "H";
            if (kind == Token::ID || kind == Token::INT || kind == Token::HEXINT)
            {
              if (kind == Token::INT || kind == Token::HEXINT)
              {

                if (tokenLine[i].toNumber() > 1844674407370955161)
                {
                  throw ScanningFailure("ERROR");
                }
                num3 = tokenLine[i].toNumber();
              }
              else
              {
                if (labels.find(tokenLine[i].getLexeme()) == labels.end())
                {
                  throw ScanningFailure("ERROR");
                }
                int addy = labels[tokenLine[i].getLexeme()];
                num3 = (addy - pc) / 4;
              }
            }
            else
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | (num3 & 0xFFFF);
            outputBinary(instr);
          }
          else if (lex == "bne")
          {
            pc += 4;
            int op = 5;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            i++;
            // cout << tokenLine[i] << endl;
            if (i >= size)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = 0;
            kind = tokenLine[i].getKind();
            // cout << "H";
            if (kind == Token::ID || kind == Token::INT || kind == Token::HEXINT)
            {
              if (kind == Token::INT || kind == Token::HEXINT)
              {

                if (tokenLine[i].toNumber() > 1844674407370955161)
                {
                  throw ScanningFailure("ERROR");
                }
                num3 = tokenLine[i].toNumber();
              }
              else
              {
                if (labels.find(tokenLine[i].getLexeme()) == labels.end())
                {
                  throw ScanningFailure("ERROR");
                }
                int addy = labels[tokenLine[i].getLexeme()];
                num3 = (addy - pc) / 4;
              }
            }
            else
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | (num3 & 0xFFFF);
            outputBinary(instr);
          }
          else if (lex == "beq")
          {
            pc += 4;
            int op = 4;
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num1 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::REG)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num2 = tokenLine[i].toNumber();
            i++;
            if (i >= size || tokenLine[i].getKind() != Token::COMMA)
            {
              throw ScanningFailure("ERROR");
            }
            if (num1 > 31 || num1 < 0)
            {
              throw ScanningFailure("ERROR");
            }
            if (num2 > 31 || num2 < 0)
            {
              throw ScanningFailure("ERROR");
            }

            i++;
            // cout << tokenLine[i] << endl;
            if (i >= size)
            {
              throw ScanningFailure("ERROR");
            }
            int64_t num3 = 0;
            kind = tokenLine[i].getKind();
            // cout << "H";
            if (kind == Token::ID || kind == Token::INT || kind == Token::HEXINT)
            {
              if (kind == Token::INT || kind == Token::HEXINT)
              {

                if (tokenLine[i].toNumber() > 1844674407370955161)
                {
                  throw ScanningFailure("ERROR");
                }
                num3 = tokenLine[i].toNumber();
              }
              else
              {
                if (labels.find(tokenLine[i].getLexeme()) == labels.end())
                {
                  throw ScanningFailure("ERROR");
                }
                int addy = labels[tokenLine[i].getLexeme()];
                num3 = (addy - pc) / 4;
              }
            }
            else
            {
              throw ScanningFailure("ERROR");
            }
            int instr = (op << 26) | (num1 << 21) | (num2 << 16) | (num3 & 0xFFFF);
            outputBinary(instr);
          }
          else
          {
            throw ScanningFailure("ERROR");
          }
        }
        else if (kind == Token::LABEL)
        {
          // empty
        }
        else
        {
          throw ScanningFailure("ERROR");
        }
      }
    }
  }
  catch (ScanningFailure &f)
  {
    std::cerr << f.what() << std::endl;
    return 1;
  }
  // You can add your own catch clause(s) for other kinds of errors.
  // Throwing exceptions and catching them is the recommended way to
  // handle errors and terminate the program cleanly in C++. Do not
  // use the std::exit function, which may leak memory.

  return 0;
}

