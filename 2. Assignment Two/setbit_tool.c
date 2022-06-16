#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t read_arg(char * arg)
{
	char * end_ptr = arg;
	int64_t value = strtoll(arg, &end_ptr, 0);

	if(*end_ptr != '\0')
	{
		fprintf(stderr, "Please enter valid char in number %s\n", arg);
		exit(-1);
	}

	if(value < 0 || value > UINT32_MAX)
	{
		fprintf(stderr, "Number %s out of range\n", arg);
		exit(-1);
	}

	return(uint32_t) value;
}

//show_bit function
//show common bit between the two arguments
void show_bits(char * arg1, char * arg2)
{
	uint32_t x = read_arg(arg1);
	uint32_t y = read_arg(arg2);
	uint32_t z = (x & y);
	x = z;
	uint32_t i = 0;

	while(z)
	{
		if(z % 2)
		{
			printf("%u", i);
			z = z - 1;
			if(z)
				printf(", ");
		}

		z = z >> 1;
		i++;
	}

	printf("\n hex     : 0x%X\n", x);
	printf("\n signed  : %d\n", x);
	printf("\n unsigned: %u\n", x);

	exit(1);
}

//set_bits function
void set_bits(int v1, char ** v)
{
	uint32_t x[v1];
	uint32_t final = 0;
	uint32_t one = 1;

	for(int i = 0; i < v1; ++i)
	{
		x[i] = read_arg(v[i]);
		if(x[i] > 15)
		{
			fprintf(stderr, "The number is greater than 15, enter a new one that smaller than 15\n");
			exit(-1);
		}

		final = (final | (one << x[i]));
	}

	for(int i = 32768; i != 0; i = i/2)
	{
		if(i > final)
			printf("0");
		else
		{
			printf("1");
			final = final - i;
		}
	}

	printf("\n\n");

	exit(1);
}

int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "usage: setbit_tool <n> <n> [<n> ...]\n");
		return -1;
	}else if(argc == 3)
	{
		show_bits(argv[1], argv[2]);
		return 0;
	}else
		set_bits(argc - 1, argv + 1);

	return 0;
}
