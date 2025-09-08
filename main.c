#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 256
#define CELL_COUNT 256 

typedef unsigned char uchar;

void execute(char *program)
{
	int stack[STACK_SIZE] = {0};
	int stack_index = 0;
	uchar cells[CELL_COUNT] = {0};
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
			default: break;
		}

		instr_ptr++;
	}
}

int validate_arguments(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Missing input file.\n");
		printf("Usage: \n%s <input_file>\n", argv[0]);
		return 1;
	}

	return 0;
}

char *read_program_from_file(char *filename)
{
	FILE *fptr = fopen(filename, "r");
	
	if (fptr == NULL)
	{
		printf("Unable to find file '%s'\n", filename);
		exit(1);
	}

	fseek(fptr, 0, SEEK_END);
	long file_size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	char *program = malloc(sizeof(char) * (file_size + 1));

	fread(program, file_size, sizeof(char), fptr);

	fclose(fptr);

	return program;
}

int main(int argc, char **argv)
{
	if (validate_arguments(argc, argv) == 1)
		return 1;

	char *program = read_program_from_file(argv[1]);

	execute(program);

	printf("\n\nProgram ended successfully\n");

	free(program);
	return 0;
}

