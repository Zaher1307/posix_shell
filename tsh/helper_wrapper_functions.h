
/* they are helper and wrappter routines */
int parseline(const char *cmdline, char **argv); 
void sigquit_handler(int sig);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

