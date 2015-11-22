#include <stdio.h>
#include <regex.h>

int main(int argc, char* argv[])
{
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

    regi = regexec(&testReg, "test", nmatch, pmatch, 0);
    if (!regi)
    {
        printf("Match: Yes\n");
    }
    else
    {
        printf("Match: No\n");
    }

    return 0;
}
