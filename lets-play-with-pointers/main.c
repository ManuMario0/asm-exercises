// lets play with pointers
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Tree {
	long val;
	struct Tree *l, *r;
	struct Tree *old_l, *old_r;
	long	old_val;
};

extern struct Tree *order(struct Tree *t);

struct Tree *create_tree(int max_prof) {
	struct Tree *t = calloc(sizeof(struct Tree), 1);
	int lson_r = rand() % 2, rson_r = rand() % 2;
	if (lson_r && max_prof != 0) {
		t->l = create_tree(--max_prof);
		t->old_l = t->l;
	}
	if (rson_r && max_prof != 0) {
		t->r = create_tree(--max_prof);
		t->old_r = t->r;
	}
	t->val = rand() % 1000;
	t->old_val = t->val;
}

int check_integrity(struct Tree *t) {
	if (t == NULL) return 1;
	if (t->l != NULL && t->val < t->l->val) return 0;
	if (t->r != NULL && t->val > t->r->val) return 0;
	return check_integrity(t->l) && check_integrity(t->r);
}

int old_size(struct Tree *t) {
	if (t==NULL) return 0;
	return old_size(t->old_l)+old_size(t->old_r)+1;
}

long *create_tbl(struct Tree *t, long *tbl) {
	*tbl = t->old_val;
	tbl++;
	if (t->old_l) tbl = create_tbl(t->old_l, tbl);
	if (t->old_r) tbl = create_tbl(t->old_r, tbl);
	return tbl;
}

int check_values(struct Tree *t, long *tbl, int l) {
	if (t == NULL) return 1;
	for (int i=0; i<l; i++) {
		if (t->val == tbl[i]) {
			tbl[i] = -1;
			return 1;
		}
	}
	return check_values(t->l, tbl, l) && check_values(t->r, tbl, l);
}

int check_tree(struct Tree *t) {
	int l = old_size(t);
	long *tbl = malloc(l*sizeof(long));
	create_tbl(t, tbl);
	if (!check_values(t, tbl, l)) {
		printf("Have you corrupted any initial value  ???\n");
		return 0;
	}
	for (int i=0; i<l; i++) {
		if (tbl[i] != -1) {
			printf("Some values are missing, is this normal ???\n");
			return 0;
		}
	}
	if (!check_integrity(t)) {
		printf("It's almost right ! The only thing is your tree isn't correctly ordered :(\n");
		return 0;
	}
	return 1;
}

void print_tree(struct Tree *t) {
	if (t == NULL) {
		printf("V");
		return;
	}
	printf("N(%ld, ", t->val);
	print_tree(t->l);
	printf(",");
	print_tree(t->r);
	printf(")");
}

int main() {
	time_t ti;
	srand((unsigned)time(&ti));
	struct Tree *t = create_tree(5);
	printf("Old tree : ");
	print_tree(t);
	printf("\nNew tree : ");
	struct Tree *old_t = t;
	t = order(t);
	print_tree(t);
	printf("\n");
	if (t != old_t) {
		printf("Be carefull, you've changed the root !");
		return 0;
	}
	if (check_tree(t)) {
		printf("Great ! You've done it !\n");
	} else {
		printf("It's not the right anser, but you can do it !\n");
	}
	return 0;
}
