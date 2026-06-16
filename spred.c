#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

struct String {
	char *str;
	size_t sz; // Size
	size_t szu; // Size Used
};

const char *prompt = "*";
const char *error = "?\n";

static struct termios terminalConfig;

// Options
static char optionPrompt = 0;
static char optionHelp = 0;

static char saved = 1;
static char fq = 0;

static int
processCommand(struct String inLine)
{
	switch (*inLine.str) {
		case 'Q':
			if (inLine.str[1] == '\n') return 1;
			else {
				fputs(error, stderr);
				return 0;
			}
			
		case 'q':
			if ((saved || fq) && inLine.str[1] == '\n') return 1;
			else {
				if (inLine.str[1] == '\n') fq = 1;
				fputs(error, stderr);
				return 0;
			}
	
		default:
			fq = 0;
			fputs(error, stderr);
			return 0;
	}
}

static int
input(struct String *inLine)
{
	if (inLine->str != NULL) free(inLine->str);
	inLine->str = (char*) malloc(20 * sizeof(char));
	if (inLine->str == NULL) return 2;
	inLine->sz = 20;
	inLine->szu = 0;

	int c = 0;
	
	for (; c != EOF && c != '\n'; c = getc(stdin)) {
		if (c == '\r' || c == '\0') continue;
		
		inLine->str[inLine->szu] = (char) c; ++inLine->szu;
		
		//if (inLine->szu == inLine->sz) {
		//	char *p = malloc((inLine->sz + 20) * sizeof(char));
		//	if (p == NULL) return 2;
		//	
		//	memcpy((void*) p, (void*) inLine->str, (inLine->sz + 20) * sizeof(char));
		//	free(inLine->str); inLine->str = p;
		//	inLine->sz = inLine->sz + 20;
		//}
	}
	
	if (c == EOF) return 2;
	else {
		inLine->str[inLine->szu] = '\n';
		++inLine->szu;
		
		return 0;
	}
}

static int
edit(void)
{
	struct String inLine = {NULL, 0, 0};
	
	for (;;) {
		if (optionPrompt) {
			fputs(prompt, stdout);
			fflush(stdout);
		}

		{
			int r = input(&inLine);
			if(r) return r;
			
			r = processCommand(inLine);
			if(r) return r;
		}
	}
}

static int
init(void)
{
	// TODO: Should only apply when inputing data
	// if (tcgetattr(fileno(stdin), &terminalConfig)) return 1;
	// terminalConfig.c_cc[VEOL] = '\t';
	// if (tcsetattr(fileno(stdin), TCSANOW, &terminalConfig)) return 1;

	// TODO: Register Signal Handlers

	return 0;
}
	

int
main (int argc, char *argv[])
{
	// TODO: Handle Arguments

	{
		int r = init();
		if (r) return r;
	}

	return (edit() - 1);
}
