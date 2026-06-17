#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

struct Address {
	int fr; // First Row
	int lr; // Last Row
	int fc; // First Column
	int lc; // Last Column
};

struct String {
	char *str;
	size_t sz; // Size
	size_t szu; // Size Used
};

static char *prompt = "*";
const char *error = "?\n";
const char *errors[3] = {"", "Invalid address\n", "Warning: buffer modified\n"};

static struct termios terminalConfig;

// Options
static char optionPrompt = 0;
static char optionHelp = 0;

static char saved = 1;
static char fq = 0;
static int lastError = 0;

/*
 * ERRORS
 * 0	No error
 * 1	Invalid address
 * 2	Warning: Buffer Modified
 */
 
static void
doError(int err)
{
		if (!err) {
			fq = 0;
			return;
		}
		
		lastError = err;
		fputs(error, stderr);
		if (optionHelp) fputs(errors[err], stderr);
		
		if (err != 2) fq = 0;
		else fq = 1;
		
}
 
static int
makeAddress(char* str, struct Address *address)
{
	return 0;
}

static int
processCommand(struct String inLine)
{

	struct Address address;
	
	if (inLine.szu == 2) {
		switch (*inLine.str) {
			case 'H':
				optionHelp = !optionHelp;
				doError(0);
				return 0;
				
			case 'h':
				fputs(errors[lastError], stderr);
				return 0;

			case 'P': 
				optionPrompt = !optionPrompt;
				doError(0);
				return 0;
		
			case 'Q':
				return 1;

			case 'q':
				if (saved || fq) return 1;
				else {
					doError(2);
					return 0;
				}
	
			default:
				doError(1);			
				return 0;
		}
	} else if ((*inLine.str > '/' && *inLine.str < ':') || *inLine.str == '^' || *inLine.str == '$') {
		int index = makeAddress(inLine.str, &address);
		if (!index) doError(1);
		return 0;
	} else {
		doError(1);
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
		
		if (inLine->szu == inLine->sz) {
			char *p = malloc((inLine->sz + 20) * sizeof(char));
			if (p == NULL) return 2;
			
			memcpy((void*) p, (void*) inLine->str, (inLine->sz + 20) * sizeof(char));
			free(inLine->str); inLine->str = p;
			inLine->sz = inLine->sz + 20;
		}
	}
	
	if (c == EOF) return 2;
	else {
		inLine->str[inLine->szu] = '\0';
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

int
main (int argc, char *argv[])
{
	// TODO: Handle Arguments

	// TODO: Register Signal Handlers
	
	// TODO: Should only apply when inputing data
	// if (tcgetattr(fileno(stdin), &terminalConfig)) return 1;
	// terminalConfig.c_cc[VEOL] = '\t';
	// if (tcsetattr(fileno(stdin), TCSANOW, &terminalConfig)) return 1;

	return (edit() - 1);
}
