#include <stdio.h>
#include <math.h>

typedef unsigned int * pointer;

//Prototype
void get_value(unsigned int n, unsigned int k, unsigned int hex);
float get_final_frac(pointer start, int n);
float get_frac(int frac_shift, int n);
int calculate_sign_bit(pointer start, int n, int k);
int get_sign_bit(int sign_shift, int n, int k);
int check_hex(int hex, int n, int k);

int main(int argc, char * argv[])
{
	if (argc != 4)
		printf("Usage: fp_parse <# of frac_bits><# of exp_bits><hex_to_convert>\n\n");
	else
	{
		unsigned int n, k, hex;  
		sscanf(argv[1], "%d", &n);
		sscanf(argv[2], "%d", &k);
		sscanf(argv[3], "%x", &hex);
		if (n < 2 || n > 10)
		{
			printf("%d is invaild number. Should be between 2 and 10.\n\n", n);
		}else if (k < 3 || k > 5)
		{
			printf("%d is invaild number. Should be between 3 and 5.\n\n", k);
		}else if (!(check_hex(hex, n, k)))
		{
			printf("Incompatible hex value.\n\n");    
		}else
		{  
			get_value(n, k, hex);
		}
	}
	return 0;
}

void get_value(unsigned int n, unsigned int k, unsigned int hex)
{
	float value = 0.0;
	unsigned int frac_shift = hex << (32 - n) >> (32 - n); 
	float frac = get_frac(frac_shift, n);
	unsigned int exp = hex << (32 - (n + k)) >> (32 - k);   
	unsigned int bias = (pow(2, (k - 1))) - 1;
	int sign_shift = hex << (32 - (n + k + 1)) >> 31; 
	unsigned int sign = get_sign_bit(sign_shift, n, k);
	float M; 
	signed int E;
	if (exp == 0)
	{
		E = 1 - bias;
		M = frac;
	}
	else
	{
		E = exp - bias;
		M = 1 + frac; 
	}


	if (exp == ((1 << k) - 1))
	{
		if (frac == 0)
		{
			if (sign == -1)
				printf("-inf\n\n");
			else
				printf("+inf\n\n");      
		}
		else
			printf("NaN\n\n");
	}
	else
	{        
		if (sign == -1)
			value = -1 * M * (pow(2, E));
		else
			value = M * (pow(2, E));
		printf("%f\n\n", value);
	}
}

float get_final_frac(pointer start, int n)
{
	float frac = 0.0;
	unsigned int i, j;
	unsigned int mask = 0x80000000;

	i = start[0];
	mask >>= (32 - n);
	for (j = 0; j < n; ++j)
	{
		if (i & mask)
			frac += 1/(pow(2, (j + 1)));
		mask >>= 1;
	}
	return frac;
}

float get_frac(int frac_shift, int n)
{
	float frac = get_final_frac((pointer) &frac_shift, n);
	return frac;
}

int calculate_sign_bit(pointer start, int n, int k)
{
	unsigned int i = start[0];
	unsigned int mask = 0x80000000;

	i = start[0];
	mask >>= 31;
	if (i & mask)
		return -1;
	return 0;
}

int get_sign_bit(int sign_shift, int n, int k)
{
	signed int sign = calculate_sign_bit((pointer) &sign_shift, n, k);
	return sign;
}

int check_hex(int hex, int n, int k)
{
	unsigned int value = hex >> (n + k + 1);
	if (value == 0)
		return 1;
	return 0;   
}
