#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

const char* prompt = "*";

static struct termios terminalConfig;

static char optionPrompt = 0;

static void
edit(void)
{
	for (;;) {
		if (optionPrompt) {
			fputs(prompt, stdout);
			fflush(stdout);
		}

		getc(stdin);
	}
}

static int
init(void)
{
	if (tcgetattr(fileno(stdin), &terminalConfig)) return 1;
	terminalConfig.c_cc[VEOL] = '\t';
	if (tcsetattr(fileno(stdin), TCSANOW, &terminalConfig)) return 1;

	// TODO: Register Signal Handlers

	return 0;
}
	

int
main (int argc, char** argv)
{
	// TODO: Handle Arguments

	if (int t = init()) return t;

	edit();

	// Never Reached
	return 0;
}
