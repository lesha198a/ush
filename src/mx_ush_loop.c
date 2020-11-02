#include "mx_shell.h"

void mx_ush_loop (t_hash_table *hash_table) {
	int status = 0;

	while (status != 666) {
		char *stdin_line = mx_strnew(PATH_MAX);
		char *res = NULL;

		mx_change_prompt_mode(stdin_line, 0, false);
		hash_table->savetty = mx_enable_canon();
		stdin_line = mx_ush_read_line(stdin_line, &status);
		if (status == 666)
			break;
		mx_disable_canon(hash_table->savetty);
		if (stdin_line[0] != '\0') {
			res = mx_strtrim(stdin_line);
			status = mx_handle_command(res, hash_table);
		}
		mx_strdel(&stdin_line);
	}
	mx_clear_all(hash_table);
}
