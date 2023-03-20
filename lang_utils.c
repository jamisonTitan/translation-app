#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "langs.h"

int init_langs_strings(char** dest) {
	for(int i = 0; i < sizeof(langs) / sizeof(Lang); i++){
		if(langs[i].string == NULL) {
			printf("%s\n", "bad thing");
			return 0;
		} else {
			dest[i] = langs[i].string;
		}
	}
	return 1;
}

char* get_lang_code(char* string) {
	char* out = malloc(9);
	for(int i = 0; i < sizeof(langs) / sizeof(Lang); i++){
		if(langs[i].string == NULL) {
			printf("bad thing\n");
			break;
		} else {
			if(strcmp(string, langs[i].string) == 0) {
				snprintf(out, sizeof(langs[i].code), "%s", langs[i].code);
				break;
			}
		}
	}
	return out;
}

