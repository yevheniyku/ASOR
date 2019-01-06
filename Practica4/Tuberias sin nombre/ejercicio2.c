#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

/*
 REHACER 
*/
int main(int argc, char const *argv[]){
	int p_h[2];
	int h_p[2];

  pipe(p_h);
  pipe(h_p);

	pid_t pid = fork();

	switch (pid) {
		case 0:
			close(p_h[1]);
			close(h_p[0]);

			char msg[257];
			char parentmsg[1] = {"l"};

			for (int i = 0; i < 10; i++) {
				ssize_t childsize = read(p_h[0], msg, 256);

				msg[childsize] = '\0';

				printf("[Hijo] Mensaje: %s", msg);
				sleep(1);

				if (i == 9)
					parentmsg[0] = 'q';

				childsize = write(h_p[1], parentmsg, 1);
			}

			close(p_h[0]);
			close(h_p[1]);
			exit(0);
		break;

		default:
			close(p_h[0]);
			close(h_p[1]);

			char usermsg[257];
			char childmsg[1] = {'l'};

			while (childmsg[0] != 'q') {
				printf("[Padre] Introduce el mensaje:\n");

				ssize_t parentsize = read(0, usermsg, 256);

				usermsg[parentsize] = '\0';
				parentsize = write(p_h[1], usermsg, parentsize + 1);

				while (childmsg[0] != 'l' && childmsg[0] != 'q') {
					parentsize = read(h_p[0], childmsg, 1);
				}
			}

			close(p_h[1]);
			close(h_p[0]);
			exit(0);
	}

	return 0;
}
