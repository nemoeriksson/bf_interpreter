#include <stdio.h>

#define STACK_SIZE 100
#define CELL_skips 100

typedef unsigned char uchar;

void execute(char *program)
{
	int stack[STACK_SIZE] = {0};
	int stack_index = 0;
	uchar cells[CELL_skips] = {0};
	char *instr_ptr = program;
	int cell_index = 0;

	while (*instr_ptr)
	{
		switch (*instr_ptr)
		{
			case '>':
				cell_index++;
				break;
			case '<':
				cell_index--;
				break;
			case '+':
				cells[cell_index]++;
				break;
			case '-':
				cells[cell_index]--;
				break;
			case '.':
				printf("%c", cells[cell_index]);
				break;
			case ',':
				cells[cell_index] = getchar();
				break;
			case '[':
				if (stack[stack_index] != instr_ptr - program)
					stack[++stack_index] = instr_ptr - program;

				instr_ptr++;

				if (cells[cell_index] != 0)
					continue;

				else 
				{
					int skips = 1;
					
					while (skips > 0 || *instr_ptr != ']')
					{
						instr_ptr++;
						if (*instr_ptr == '[') skips++;
						else if (*instr_ptr == ']') skips--;
					}
					stack_index--;
				}


				break;
			case ']':
				instr_ptr = stack[stack_index] + program;
				continue; // Skip incrementing instr_ptr
		}

		instr_ptr++;
	}
}

int main(void)
{
	// Print "Hello, World!"
	execute(">++++++++[<+++++++++>-]<.>++++[<+++++++>-]<+.+++++++..+++.>>++++++[<+++++++>-]<++.------------.>++++++[<+++++++++>-]<+.<.+++.------.--------.>>>++++[<++++++++>-]<+.");

	printf("\n\nProgram ended successfully\n");
	return 0;
}

