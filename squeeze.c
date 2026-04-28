#include <stdio.h>

void squeeze(char string[], char c) {
	int i = 0, j = 0;
	for (i = 0; string[i] != '\0'; i ++) {
		if (string[i] != c)
			string[j++] = string[i];
	}
	string[j] = '\0';
}


int main () {
	char string[] = "Hello World";
	char c = getchar();
	squeeze(string, c);
	printf("%s\n", string);
	return 0;	
}

