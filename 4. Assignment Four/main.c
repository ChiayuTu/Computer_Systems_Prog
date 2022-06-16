#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void add(int argc,char **argv);
void subtract(int argc,char **argv);
void multiplication(int argc,char **argv);
void division(int argc,char **argv);
void modulo(int argc, char **argv);
char * revString(char *word);
void reverseInput(int argc, char **argv);
int getOption();

int main(int argc, char **argv)
{
	int userOption;
	do{
		userOption = getOption();

		if(userOption == 0){
			break;
		}else if(userOption == 1){
			//add function
			add(argc,argv); //add function
		}else if(userOption == 2){
			//subtract function
			subtract(argc,argv); //subtract function
		}else if(userOption == 3){
			//multiply function
			multiplication(argc,argv); //multiply function
		}else if(userOption == 4){
			//division function
			division(argc,argv); //division function
		}else if(userOption == 5){
			//modulo function
			modulo(argc,argv); //modulo function
		}else if(userOption == 6){
			//reverse input function
			reverseInput(argc,argv); //reverse input function
		}else{
			printf("Invalid selection. Try again!\n");
		}
	}while(userOption != 0);
}

//function to add hex/decimal values
void add(int argc,char **argv){
	int result = 0;
	for(int i=0;i<argc;++i){
		result = result + strtoul(argv[i],NULL,0);
	}

	printf("Result = %d\n\n",result);
}

//function to subtract hex/decimal values
void subtract(int argc,char **argv){
	int result = strtoul(argv[1],NULL,0);
	for(int i=2;i<argc;++i){
		result = result - strtoul(argv[i],NULL,0);
	}

	printf("Result = %d\n\n",result);
}

//function to multiply hex/decimal values
void multiplication(int argc,char **argv){
	int result = strtoul(argv[1],NULL,0);

	for(int i=2;i<argc;i++){
		result = result * strtoul(argv[i],NULL,0);
	}

	printf("Result = %d\n\n",result);

}

//function to divide first two values
void division(int argc,char **argv){

	if(strtoul(argv[1],NULL,0) == 0 && strtoul(argv[2],NULL,0) == 0){
		printf("-nan\n");
	}else{
		double result = (double)strtoul(argv[1],NULL,0)/(double)strtoul(argv[2],NULL,0);
		printf("Result = %f\n\n",result);
	}
}

//function to find the modulo of the first two values
void modulo(int argc, char **argv){
	int result = strtoul(argv[1],NULL,0) % strtoul(argv[2],NULL,0);
	printf("Result = %d\n\n",result);
}

//function to reverse a single string
char * revString(char *word){
	char *output = malloc(strlen(word) + 1);

	int k = 0;
	for(int i=strlen(word)-1;i>=0;--i){
		output[k] = word[i];
		++k;
	}

	output[k] = '\0';
	return output;

}

//function to reverse all values inputed
void reverseInput(int argc, char **argv){

	for(int i=argc-1;i>0;--i){
		char *temp = revString(argv[i]);
		printf("%s  ",temp);
		free(temp);
	}

	printf("\n\n");

}

//function to get option from user
int getOption(){
	int userInput;
	int val;

	do{
		printf("(0)Exit\n");
		printf("(1)Addition\n");
		printf("(2)Subtraction\n");
		printf("(3)Multiplication\n");
		printf("(4)Division\n");
		printf("(5)Modulo\n");
		printf("(6)Reverse Input\n");
		printf("Select One Of The Options: ");

		val = scanf("%d",&userInput);


		if(val == 0){
			printf("Please Enter A Number!\n");
			while((getchar()) != '\n');
		}

	}while(val == 0);

	return userInput;
}
