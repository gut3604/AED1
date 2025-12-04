#include <stdio.h>
#include <string.h>

void build_and_print_post(const char *pre, int pl, int pr, const char *in, int il, int ir){
    if(pl > pr) return;
    char root = pre[pl];
    int pos = il;
    while(pos <= ir && in[pos] != root) pos++;
    int left_size = pos - il;
    build_and_print_post(pre, pl+1, pl+left_size, in, il, pos-1);
    build_and_print_post(pre, pl+left_size+1, pr, in, pos+1, ir);
    putchar(root);
}

int main(void){
    char pre[2005], in[2005];
    while(scanf("%s %s", pre, in) == 2){
        int n = (int)strlen(pre);
        build_and_print_post(pre, 0, n-1, in, 0, n-1);
        putchar('\n');
    }
    return 0;
}
