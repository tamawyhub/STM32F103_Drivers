#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_CHARS  	128
#define LINE_SIZE	2048

int find_char_size(const char* line)
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

void print_font_char_size_arr(int count, int* arr)
{

	printf("const uint8_t font_%d_char_size [] = \n{\n\t", count);

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
	int char_size[NUM_OF_CHARS];
	char line[LINE_SIZE];
	FILE* file;
	char* ret;
	int i;

	if(argc == 2)
	{
		file = fopen(argv[1], "r");
		if(file == NULL)
		{
			fprintf(stderr, "Cannot open file\n");
			return -1;
		}
		
		while(i < NUM_OF_CHARS)
		{
			ret = fgets(line, LINE_SIZE, file);
			if(ret == NULL)
				break;
			char_size[i] = find_char_size(line);
			i++;
		}
		print_font_char_size_arr(i, char_size);
	}

	return 0;
}
		
