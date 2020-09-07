#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <ctype.h>
#include<string.h>
struct phone {
	char caller[11];
	char receiver[11];
	int duration;
};
typedef struct phone Phone;

void callInfo(FILE *,Phone p,int);
void calls(FILE *, Phone p);
void longestDuration(FILE *, Phone p);
void totalCalls(FILE *, Phone p);
void TotalreceivedDuration(FILE *, Phone p);
int main() {

	FILE *fr = NULL,*fw=NULL;
	int no, i=0;
	int selection,counter=0;
	Phone p;

	printf("----------MENU------------\n");
	printf("1-Enter call information\n");
	printf("2-Find all the calls made by a given phone number\n");
	printf("3-Find the phone call with the longest duration from a given phone number\n");
	printf("4-Find the total call time made from a given phone number\n");
	printf("5-Find the total call time made to a given phone number\n");
	printf("6-Display the phone bill for a given phone number.\n");
	printf("7-Exit the switchboard program\n");
	printf("--------------------------\n");
	printf("Enter your choice which will be applied : ");
	scanf("%d", selection);

	while (1) {

		if (selection == 1) {
			counter = counter + 1;
			if(counter<100)
			callInfo(fw, p,counter);
		}

		if (selection == 2) {
			calls(fr, p);
		}

		if (selection == 3) {
			longestDuration(fr, p);
		}
		if (selection == 4) {
			totalCalls(fr, p);
		}
		if (selection == 5) {
			TotalreceivedDuration(fr, p);
		}
		if (selection == 7) {
			break;
		}

	}

	return 0;
}
void callInfo(FILE *fw, Phone p,int counter) {

	int i = 0;
	int duration;
	fw = fopen("switchboard.dat", "ab+");
	if (fw == NULL) {
		printf("ERRORR");
		return -1;
	}
	
	fseek(fw, (counter-1)*(long int)(sizeof(struct phone)),SEEK_SET);

	printf("Please enter the caller phone number : ");
	scanf("%s", p.caller);
	printf("Please enter the called phone number : ");
	scanf("%s", p.receiver);
	printf("Please enter duration of the call : ");
	scanf("%d", &p.duration);

	fwrite(&p, sizeof(struct phone), 1, fw);

	fclose(fw);
}
void calls(FILE *fr, Phone p) {

	char caller[11];
	int no = 0;

	fr = fopen("switchboard.dat", "rb");
	if (fr == NULL) {
		printf("ERRORR");
		return -1;
	}

	printf("Please enter the caller phone number : ");
	scanf("%s", caller);

	fseek(fr, (long int)(sizeof(struct phone)), SEEK_SET);

	while (!feof(fr)) {
		no = fread(&p, sizeof(struct phone), 1, fr);
		if (no == 0)
			break;
		else {
			if (strcmp(caller, p.caller) == 1)
				printf("%s %d \n", p.receiver, p.duration);
		}

	}
	fclose(fr);
}
void longestDuration(FILE *fr, Phone p) {

	char caller[11];
	int no=0;
	Phone max;
	max.duration = 0;

	fr = fopen("switchboard.dat", "rb");
	if (fr == NULL) {
		printf("ERRORR");
		return -1;
	}

	printf("Please enter the caller phone number : ");
	scanf("%s", caller);

	fseek(fr, (long int)(sizeof(struct phone)), SEEK_SET);
	while (!feof(fr)) {
		no = fread(&p, sizeof(struct phone), 1, fr);
		if (no == 0)
			break;
		else {
			if (strcmp(caller, p.caller) == 1) {
				if (p.duration >= max.duration) {
					max.duration = p.duration;
					strcpy(max.caller, p.caller);
					strcpy(max.receiver, p.receiver);
				}
			}
		}
	}

	printf("The call which has the longest duration : ");
	printf("%s %d\n", max.receiver, max.duration);

	fclose(fr);
}
void totalCalls(FILE *fr, Phone p) {

	char caller[11];
	int no = 0;
	int total=0;

	fr = fopen("switchboard.dat", "rb");
	if (fr == NULL) {
		printf("ERRORR");
		return -1;
	}

	printf("Please enter the caller phone number : ");
	scanf("%s", caller);

	fseek(fr, (long int)(sizeof(struct phone)), SEEK_SET);

	while (!feof(fr)) {
		no = fread(&p, sizeof(struct phone), 1, fr);
		if (no == 0)
			break;
		else {
			if (strcmp(caller, p.caller) == 1) {
				total = total+p.duration;
			}
		}

	}

	printf("Total calls made from that number is %d\n",total);

	fclose(fr);
}
void TotalreceivedDuration(FILE *fr, Phone p) {

	char caller[11];
	int no = 0;
	int total = 0;

	fr = fopen("switchboard.dat", "rb");
	if (fr == NULL) {
		printf("ERRORR");
		return -1;
	}

	printf("Please enter the caller phone number : ");
	scanf("%s", caller);

	fseek(fr, (long int)(sizeof(struct phone)), SEEK_SET);

	while (!feof(fr)) {
		no = fread(&p, sizeof(struct phone), 1, fr);
		if (no == 0)
			break;
		else {
			if (strcmp(caller, p.receiver) == 1) {
				total = total + p.duration;
			}
		}

	}

	printf("Total duration of all the calls made to that number is %d\n", total);

	fclose(fr);
}