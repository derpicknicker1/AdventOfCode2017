/*
--- Day 4: High-Entropy Passphrases ---
A new system policy has been put in place that requires all accounts to use a passphrase instead of simply a password. A passphrase consists of a series of words (lowercase letters) separated by spaces.

To ensure security, a valid passphrase must contain no duplicate words.

For example:

aa bb cc dd ee is valid.
aa bb cc dd aa is not valid - the word aa appears more than once.
aa bb cc dd aaa is valid - aa and aaa count as different words.
The system's full passphrase list is available as your puzzle input. How many passphrases are valid?

Your puzzle answer was 325.

--- Part Two ---
For added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged to form any other word in the passphrase.

For example:

abcde fghij is a valid passphrase.
abcde xyz ecdab is not valid - the letters from the third word can be rearranged to form the first word.
a ab abc abd abf abj is a valid passphrase, because all letters need to be used when forming another word.
iiii oiii ooii oooi oooo is valid.
oiii ioii iioi iiio is not valid - any of these words can be rearranged to form any other word.
Under this new system policy, how many passphrases are valid?

Your puzzle answer was 119.
*/
#include "advent.h"

static int lines;
static char **M;


static int getInput(char *f) {
	char * line = NULL;
    size_t len = 0;

	M = NULL; 
	lines = 0;

	FILE *file=fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}
	
	while (getline(&line, &len, file) != -1) {
		if(line[strlen(line)-1] == '\n')
				line[strlen(line)-1] = 0;
        M = (char**)realloc(M, ++lines * sizeof(char*));
        M[lines-1] = NULL;
        M[lines-1] = (char*)malloc((strlen(line) + 1) * sizeof(char));
        strcpy(M[lines-1],line);
       }
       
	fclose(file);
    free(line);
	return 1;
}


static int findDouble(char **w, char *s, int c) {
	for (int j = 0; j < c; j++)
		if (!strcmp(s,w[j]))
			return 1;
	return 0;
}


static int findAna(char **w, char *s, int c) {
	int tmp = c;
	for (int j = 0; j < c; j++)
		if (strlen(s) == strlen(w[j]) ) {
			int a[26] = {0}, b[26] = {0}, cnt = 0;
			while(s[cnt++] != 0)
				a[s[cnt-1]-'a']++;
			cnt = 0;
			while(w[j][cnt++] != 0)
				b[w[j][cnt-1]-'a']++;
			for (cnt = 0; cnt < 26; cnt++)
		      	if (a[cnt] != b[cnt]) {
		         	tmp--;
		         	break;
		   		}
		}
		else
			tmp--;		
	if(tmp)
		return 1;
	else
		return 0;
}


static int solve(int choose, char *f) {

	if(!getInput(f))
		return 0;

	int cnt = lines;

	for(int i = 0; i < lines; i++) {
		
		int wordCnt = 0;
		for (int j = 0; j < strlen(M[i]); j++)
	        if (M[i][j] == ' ')
	            wordCnt++;

		char **words = (char**)malloc( (wordCnt + 1) * sizeof(char*) );
		int c = 0, dFound = 0, aFound = 0;
		char *ptr = strtok(M[i], " ");
		
		while(ptr != NULL) {

			words[c] = (char*)malloc( (strlen(ptr) + 1) * sizeof(char) );
			

			strcpy(words[c++], ptr);
			if( !choose && findDouble(words, ptr, c-1) && !dFound++ )
				cnt--;
			else if( choose && findAna(words, ptr, c-1) && !aFound++ )
				cnt--;

			ptr = strtok(NULL, " ");
		}
		
		for(int j = 0; j < c; j++)
			free(words[j]);
		free(words);
	}

	for(int i = 0; i < lines; i++)
    	free(M[i]);
    free(M);

    return cnt;
}



void get4a(char *f) {
	printf("4a: %d\n", solve(0, f));
}


void get4b(char *f) {
	printf("4b: %d\n\n", solve(1, f));
}


