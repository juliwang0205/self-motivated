#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include <memory/paddr.h> 

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  return -1;
}

static int cmd_help(char *args);

static int cmd_si(char *args);

static int cmd_info(char *args);

static int cmd_x(char *args);

static int cmd_p(char *args);

static int cmd_w(char *args);

static int cmd_d(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "si", "run N steps, default is 1 step", cmd_si },
  { "info", "show regs status", cmd_info },
  { "x", "show mem data", cmd_x },
  { "p", "p EXPR, calculate the value of EXPR",cmd_p},
  { "c", "Continue the execution of the program", cmd_c },
  { "w", "w EXPR, create watchpoint, every time the EXPR is changed, program is paused",cmd_w},
	{ "d", "d N, delete the watchpoint whose number is N",cmd_d},
  { "q", "Exit NEMU", cmd_q },

  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_si(char *args)
{
  char *arg = strtok(NULL, " ");
  int step = 0;
  char ch;

  if(arg == NULL) {
    cpu_exec(1);
    return 0;
  }
  else {
    while(*arg != '\0') {
      ch = *arg++;
      if(ch >'9' || ch < '0') {
        printf("Error N number\n");
        return 0; 
      }
      else {
        step = step * 10 + (ch - '\0');
      }
    }
  }
  if(step == 0) step = 1;
  cpu_exec(step);
  return 0;
}

static int cmd_info(char *args)
{
  char *arg = strtok(NULL, " ");

  if(arg == NULL) { 
    return 0; 
  }
  printf("%s\n", arg);
  if(strcmp(arg, "r") == 0) {
    isa_reg_display();
  }
  
  return 1;
}


static int cmd_x(char *args)
{
  uint16_t i = 0;
  uint16_t j = 0;
  uint32_t data = 0;
  int length = 0;
  int addr = 0;

  sscanf(args,"%d%x", &length, &addr);
  for(i = 0; i< length; i++) { 
    data = paddr_read(addr + i*4, 4);
    printf("0x%08x  ",addr + i*4);
    printf("0x");
    for(j = 0; j < 4; j++) { 
      printf("%02x ", data & 0xff);
      data = data >> 8; 
    }
    printf("\n");
  }

  return 1;
}

static int cmd_p(char *args)
{
	bool success=false;
	uint32_t ans=expr(args,&success);
	if(success)
		printf("%d\n",ans);
	else
		printf("function fault!");
	return 0;
}

static int cmd_w(char *args)
{
	WP *n_wp=new_wp(args);
	printf("watchpoint %d:%s is set successfully.\n",n_wp->NO,n_wp->exp);
	return 0;
}

static int cmd_d(char *args)
{
	char *arg = strtok(NULL, " ");
	int num = 0;
	sscanf(arg, "%d", &num);
	bool ans=delete_wp (num);
	if(ans)
		printf("delete watchpoint %d successfully!\n", num);
	else
		printf("There is no watchpoint whose NO. is %d.\n",num);
	return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
