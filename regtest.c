#include <stdio.h>
#include <regex.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("usage: ./regtest string\n");
        return 1;
    }

    char* string = argv[1];

    regex_t testReg;
    size_t nmatch = 10;
    regmatch_t pmatch[nmatch];
    int regi;

    regi = regcomp(&testReg, "\\w+", REG_EXTENDED);
    if (regi)
    {
        printf("Regex compiliation error\n");
        return 1;
    }

    regi = regexec(&testReg, string, nmatch, pmatch, 0);
    if (!regi)
    {
        printf("Match: Yes\n");
        printf("Match start index: %lld\n", pmatch[0].rm_so);
        printf("Match end index: %lld\n", pmatch[0].rm_eo);
        // This can be cleaned up so it doesn't throw warning.
        printf("Match value: %.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so, &string[pmatch[0].rm_so]);
    }
    else
    {
        printf("Match: No\n");
    }

    return 0;
}
