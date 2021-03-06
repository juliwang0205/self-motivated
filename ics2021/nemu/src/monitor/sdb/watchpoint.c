#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp(char * exp)
{
	assert(free_ != NULL);

	WP *temp = free_;
	free_ = free_->next;
	temp->next = NULL;

	bool success = false;
	strcpy(temp->exp, exp);
	temp->value = expr(temp->exp, &success);
	assert(success);

	if(head==NULL)
		head = temp;
	else
	{
		WP *p = head;
		while(p->next)
			p = p->next;
		p->next = temp;
	}

	return temp;
}

void free_wp(WP *wp)
{
	WP *p = head;
	while(p->next!=wp)
		p = p->next;
	p->next = wp->next;

	wp->next = free_;
	free_ = wp;

}

void check_watchpoint()
{
	if(head==NULL)
		printf("NO WATCHPOINT!\n");
  bool success;
  uint32_t n_value;
  WP *p = head;
	while(p)
	{
    n_value = expr(p->exp, &success);
    assert(success);
		printf("watch point %d: %s\n", p->NO, p->exp);
		printf("\t The value now is %d\n", p->value);
		p = p->next;
    if(n_value != p->value) {
      nemu_state.state=NEMU_STOP;
      Log("Expression has changed at watchpoint %d %s\n",p->NO, p->exp);
    }
	}
}

void print_wp()
{
	if(head==NULL)
		printf("NO WATCHPOINT!\n");
  WP *p = head;
	while(p)
	{
		printf("watch point %d: %s\n", p->NO, p->exp);
		printf("\t The value now is %d\n", p->value);
		p = p->next;
	}
}

bool delete_wp(int num)
{
	WP *p = head;
	while(p)
	{
		if (p->NO == num)
		{
			free_wp(p);
			break;
		}
		p=p->next;
	}
	if(p==NULL)
		return false;
	else
		return true;
}

int test_change()
{
	WP *p = head;
	while(p)
	{
		bool success = false;
		uint32_t n_value = expr(p->exp, &success);
		assert(success);
		if(n_value!=p->value)	
		{
			printf("watchpoint %d:%s is changed\n", p->NO, p->exp);
			printf("The old value is %d\n", p->value);
			printf("The new value is %d\n", n_value);
			p->value = n_value;
			return 1;
		}
		p=p->next;
	}
	return 0;
}


