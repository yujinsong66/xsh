#include <stdio.h>
#include "smsh.h"

enum states { NEUTRAL, WANT_THEN, THEN_BLOCK};
enum results {SUCCESS, FAIL};

static int if_state = NEUTRAL;
static int if_result = SUCCESS;
static int last_stat = 0;

int syn_err(char *);
int ok_to_execute()
{

