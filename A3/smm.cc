#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
const std::string ALPHABET = ".ALPHABET";
const std::string STATES = ".STATES";
const std::string TRANSITIONS = ".TRANSITIONS";
const std::string INPUT = ".INPUT";
const std::string EMPTY = ".EMPTY";
using namespace std;

bool isChar(std::string s)
{
  return s.length() == 1;
}
bool isRange(std::string s)
{
  return s.length() == 3 && s[1] == '-';
}

// Locations in the program that you should modify to store the
// DFA information have been marked with four-slash comments:
//// (Four-slash comment)
int main()
{
  std::istream &in = std::cin;
  std::string s;
  string state = "";
  string old_state = "";
  vector<string> acceptingStates;
  map<char, map<string, string>> transitions;
  bool accepted = true;
  string initial_state = "";
  bool failed = false;

  std::getline(in, s); // Alphabet section (skip header)
  // Read characters or ranges separated by whitespace
  while (in >> s)
  {
    if (s == STATES)
    {
      break;
    }
    else
    {
      if (isChar(s))
      {
        //// Variable 's[0]' is an alphabet symbol
      }
      else if (isRange(s))
      {
        for (char c = s[0]; c <= s[2]; ++c)
        {
          //// Variable 'c' is an alphabet symbol
        }
      }
    }
  }

  std::getline(in, s); // States section (skip header)
  // Read states separated by whitespace
  while (in >> s)
  {
    if (s == TRANSITIONS)
    {
      break;
    }
    else
    {
      static bool initial = true;
      bool accepting = false;
      if (s.back() == '!' && !isChar(s))
      {
        accepting = true;
        s.pop_back();
      }
      //// Variable 's' contains the name of a state
      if (initial)
      {
        initial_state = s;
        initial = false;
      }
      if (accepting)
      {
        acceptingStates.push_back(s);
      }
    }
  }

  std::getline(in, s); // Transitions section (skip header)
  // Read transitions line-by-line
  while (std::getline(in, s))
  {
    if (s == INPUT)
    {
      // Note: Since we're reading line by line, once we encounter the
      // input header, we will already be on the line after the header
      break;
    }
    else
    {
      std::string fromState, symbols, toState;
      std::istringstream line(s);
      line >> fromState;
      bool last;
      while (line >> s)
      {
        if (line.peek() == EOF)
        { // If we reached the last item on the line
          // Then it's the to-state
          toState = s;
        }
        else
        { // Otherwise, there is more stuff on the line
          // We expect a character or range
          if (isChar(s))
          {
            symbols += s;
          }
          else if (isRange(s))
          {
            for (char c = s[0]; c <= s[2]; ++c)
            {
              symbols += c;
            }
          }
        }
      }
      for (char c : symbols)
      {
        transitions[c][fromState] = toState;
      }
    }
  }

  // Input section (already skipped header)
  while (in >> s)
  {
    state = initial_state;
    string token = "";

    for (unsigned int i = 0; i < s.size(); i += 0)
    {
      failed = false;
      old_state = state;
      char c = s[i];

      // means if we have a valid transition
      if (transitions[c].find(state) == transitions[c].end())
      {
        // set state to failed
        failed = true;
      }
      else
      {

        state = transitions[c][state];
        old_state = state;
        token += c;
        i++;
      }

      if (i == s.size() - 1 || failed)
      {
        // old state was accepting
        if (find(acceptingStates.begin(), acceptingStates.end(), old_state) != acceptingStates.end())
        {
          cout << token << endl;
          token = "";
        }
      }
      else
      {
        std::cerr << "ERROR" << std::endl;
        return 1;
      }
    }
  }
}

