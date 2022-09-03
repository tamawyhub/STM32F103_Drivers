#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	int arr_size;
	int element_val;

	if(argc > 2)
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
		
