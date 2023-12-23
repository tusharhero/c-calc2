// The GPLv3 License (GPLv3)
//
// Copyright © 2023 tusharhero
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  size_t alloc_size;
  char *string;
  size_t size;
  double value;
} Number;

typedef struct
{
  char *string;
  size_t alloc_size;
  size_t length;
} Line;

bool
is_in_set (char character, const char *set_string)
{
  for (int i = 0; i < (int)strlen (set_string); ++i)
    {
      if (character == set_string[i])
        {
          return true;
        }
    }
  return false;
}

double
evaluate (char *expression, size_t length)
{
  Number number
      = { .alloc_size = 256, .string = malloc (256), .size = 0, .value = 0 };
  char current_character;
  char previous_operation = '+';
  double solution = 0;
  for (size_t i = 0; i <= length; ++i)
    {
      current_character = expression[i];
      if (is_in_set (current_character, "+-/*") || current_character == 0)
        {
          number.string[number.size] = 0;
          number.value = strtod (number.string, NULL);
          number.size = 0;
          switch (previous_operation)
            {
            case '+':
              {
                solution += number.value;
                break;
              }
            case '-':
              {
                solution -= number.value;
                break;
              }
            case '*':
              {
                solution *= number.value;
                break;
              }
            case '/':
              {
                solution /= number.value;
                break;
              }
            }
          previous_operation = current_character;
        }
      else if (is_in_set (current_character, "0123456789."))
        {
          if (number.alloc_size < number.size)
            {
              number.alloc_size *= 2;
              number.string = realloc (number.string, number.alloc_size);
            }
          number.string[number.size++] = current_character;
        }
    }
  free (number.string);
  return solution;
}

/*
  Returns pointer to a dynamically allocated 0-terminated string.
  The pointer returned needs to be managed separately.
 */
Line
get_line ()
{
  Line line = { .alloc_size = 256,
                .string = malloc (sizeof (char) * 256),
                .length = 0 };
  int character;
  while ((character = getchar ()) != '\n' && character != EOF)
    {
      if (line.alloc_size < line.length)
        {
          line.alloc_size *= 2;
          line.string = realloc (line.string, sizeof (char) * line.alloc_size);
        }
      line.string[line.length++] = character;
    }
  line.string[line.length] = 0;
  return line;
}

int
main (void)
{
  Line expression;
  while ((expression = get_line ()).length != 0)
    {
      printf ("%f\n", evaluate (expression.string, expression.length));
      free (expression.string);
    }
  free (expression.string);
  return 0;
}
