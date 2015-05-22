#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#ifndef OMIT_GETOPT_LONG
#include <getopt.h>
#endif

struct command {
	char *command_name;
	void (*command_function)(int argc, char **argv);
};

void command_init(int argc, char **argv)
{
}

void command_using(int argc, char **argv)
{
}

void command_track(int argc, char **argv)
{
}

void command_forget(int argc, char **argv)
{
}

void command_go(int argc, char **argv)
{
}

void command_restore(int argc, char **argv)
{
}

void command_history(int argc, char **argv)
{
}

void command_status(int argc, char **argv)
{
}

void execute_command(char *command_name, int argc, char **argv)
{
	int c;

	static struct command commands[] = {
		{ "init", command_init },
		{ "using", command_using },
		{ "track", command_track },
		{ "forget", command_forget },
		{ "go", command_go },
		{ "restore", command_restore },
		{ "history", command_history },
		{ "status", command_status },
		{ 0, 0 }
	};

	for (c = 0; commands[c].command_name != 0; ++c)
	{
		if (strcmp(commands[c].command_name, command_name) == 0)
		{
			commands[c].command_function(argc, argv);
			return;
		}
	}

	printf("keep: '%s' is not a keep command.\n", command_name);
}

int main(int argc, char **argv)
{
	int opt;

	static char *options = "";

#ifndef OMIT_GETOPT_LONG
	static struct option long_options[] = 
	{
		{ 0, 0, 0, 0 }
	};

	while ((opt = getopt_long(argc, argv, options, long_options, NULL)) != EOF)
#else
	while ((opt = getopt(argc, argv, options)) != EOF)
#endif
	{
		switch (opt)
		{
			default:
				fprintf(stderr, "Try `keep --help' for more information.\n");
				exit(1);
		}
	}

	if (optind >= argc)
	{
		printf("keep: No command given.\n");
		return 1;
	}

	execute_command(argv[optind], argc - optind - 1, argv + optind + 1);

	return 0;
}