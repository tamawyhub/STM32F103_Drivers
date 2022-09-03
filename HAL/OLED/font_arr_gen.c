#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_CHARS  	128
#define LINE_SIZE	2048

int find_char_width(const char* line)
{
	int count = 0;

	if(line == NULL)
		return -1;

	while(*line)
	{
		if(*line == ',')
		{
			count++;
		}
		line++;
	}

	return count;
}

void print_font_arr(int count, int* arr)
{

	printf("const uint8_t arr_%d [] = \n{\n\t", count);

	int elements_per_line = 0;

	for(int i = 0; i < count; i++)
	{
		if(elements_per_line >= 10)
		{
			printf("\n\t");
			elements_per_line = 0;
		}

		printf("0x%02X, ", arr[i]);
		elements_per_line++;
	}
	
	printf("\n};\n");
}

int main(int argc, char* argv[])
{

	int arr_size;
	int element_val;
	int char_width[NUM_OF_CHARS];
	char line[LINE_SIZE];
	FILE* file;
	char* ret;

	if(argc > 1)
	{
		file = fopen(argv[1], "r");
		if(file == NULL)
		{
			fprintf(stderr, "Cannot open file\n");
			return -1;
		}
		
		int i = 0;
		while(i < NUM_OF_CHARS)
		{
			ret = fgets(line, LINE_SIZE, file);
			if(ret == NULL)
				break;
			char_width[i] = find_char_width(line);
			i++;
		}
		print_font_arr(i, char_width);
	}
	else if(argc > 2)
	{
		arr_size = atoi(argv[1]);
		element_val = atoi(argv[2]);

		printf("const uint8_t arr_%d [] = \n{\n\t", arr_size);

		int elements_per_line = 0;

		for(int i = 0; i < arr_size; i++)
		{
			if(elements_per_line >= 10)
			{
				printf("\n\t");
				elements_per_line = 0;
			}

			printf("0x%02X, ", element_val);
			elements_per_line++;
		}

		printf("\n};\n");
	}

	return 0;
}
		
