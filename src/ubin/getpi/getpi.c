#include <nanvix/pm.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Software versioning. */
#define VERSION_MAJOR 1 /* Major version. */
#define VERSION_MINOR 0 /* Minor version. */

pid_t pid = 0;

static void version(void)
{
	printf("get_process_info (Trabalho de SO) %d.%d\n\n", VERSION_MAJOR, VERSION_MINOR);
	printf("Sem Copyright(C), pode copiar XD\n");
	printf("This is free software under the ");
	printf("GNU General Public License Version 3.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n\n");

	exit(EXIT_SUCCESS);
}

static void usage(void)
{
	printf("Usage: get_process_info [options] <pid>\n\n");
	printf("Brief: Manda um pid pro pai que ele devolve algumas informacoes do processo.\n\n");
	printf("Options:\n");
	printf("  --help             Display this information and exit\n");
	printf("  --version          Display program version and exit\n");

	exit(EXIT_SUCCESS);
}

static void getargs(int argc, char *const argv[])
{
	int i;         /* Loop index.         */
	char *arg;     /* Current argument.   */

	/* Read command line arguments. */
	for (i = 1; i < argc; i++)
	{
		arg = argv[i];

		/* Parse command line argument. */
		if (!strcmp(arg, "--help")) {
			usage();
		}
		else if (!strcmp(arg, "--version")) {
			version();
		}
		else {
			pid = atoi(arg);
		}
	}
}

int main(int argc, char *const argv[]) {

	struct process_buf buffer;

	getargs(argc, argv);

	if (get_process_info(pid, &buffer) < 0) {
		
		printf("Deu erro chefe!\n");
		return (errno);

	}

	printf("    Id do Processo: %d\n", buffer.idProcesso);
	printf("    Nome do Processo: %s\n", buffer.nomeProcesso);
	printf("    Estado do Processo: %u\n", buffer.estado);
	printf("    Prioridade do Processo: %d\n", buffer.prioridade);
	printf("    Quantum do Processo: %d\n", buffer.quantum);
	printf("    Tempo de usuario do Processo: %u\n", buffer.tempoUsuario);
	printf("    Tempo de Kernel do Processo: %u\n", buffer.tempoKernel);

	return (EXIT_SUCCESS);
}
