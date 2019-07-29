#define WORDSIZE 12
struct anagram {
    char word[WORDSIZE+1];
    char sorted[WORDSIZE+1];
};
extern struct anagram anagramlist[];
extern int anagramlistsize;
