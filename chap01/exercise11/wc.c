/**
 * Exercise 1-11. How would you teste the word count program? What kinds of
 * input are most likely to uncover bugs if there are any?
 *
 * Answer: I would test with inputs with words separated by different kinds of
 * blank characters.
 */
#include <stdio.h>

#define IN  1
#define OUT 0

int
main(void)
{
    int c, state;
    unsigned nl, nw, nc;

    state = OUT;
    nl = nw = nc = 0;

    while ((c = getchar()) != EOF) {
        ++nc;

        if (c == '\n')
            ++nl;

        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT)
            state = IN, ++nw;
    }
    printf("lines: %u, words: %u, characters: %u\n", nl, nw, nc);
    return 0;
}
