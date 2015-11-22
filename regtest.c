#include <regex.h>
#include <stdio.h>

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./regtest http-request-line\n");
        return 1;
    }

    char* request = argv[1];

    printf("Checking: %s\n", request);

    regex_t requestReg;
    regex_t methodReg;
    regex_t testReg;
    // Testing the initialization of nmatch and pmatch in two different ways.
    size_t nmatch = 2;
    regmatch_t pmatch[2];
    size_t testNmatch = 6;
    regmatch_t testPmatch[testNmatch];
    int regi;

    // Compile request regex.
    regi = regcomp(&requestReg, "\\w* /[a-zA-Z\\.?=&]* \\w*[/0-9\\.]*", REG_EXTENDED);
    if (regi)
    {
        printf("Regex compilation error\n");
        return 1;
    }

    // Compile method regex.
    regi = regcomp(&methodReg, "^GET", REG_EXTENDED);
    if (regi)
    {
        printf("Regex compilation error\n");
        return 1;
    }

    // Check request regex.
    regi = regexec(&requestReg, request, 0, NULL, 0);
    if (!regi)
    {
        printf("Match: Yes\n");
    }
    else
    {
        printf("Match: No\n");
    }

    // Check method regex.
    regi = regexec(&methodReg, request, nmatch, pmatch, 0);
    if (!regi)
    {
        printf("Method GET: Yes\n");
        // This can be cleaned up so it doesn't throw warning.
        printf("%.*s\n", pmatch[0].rm_eo - pmatch[0].rm_so, &request[pmatch[0].rm_so]);
    }
    else
    {
        printf("Method GET: No\n");
    }

    regi = regcomp(&testReg, "\\w+", REG_EXTENDED);
    if (regi)
    {
        printf("Regex compilation error\n");
        return 1;
    }

    regi = regexec(&testReg, request, testNmatch, testPmatch, 0);
    if (!regi)
    {
        printf("Test match: Yes\n");
        printf("Match Start: %lld\n", testPmatch[0].rm_so);
        printf("Match End: %lld\n", testPmatch[0].rm_eo);
        // This can be cleaned up so it doesn't throw warning.
        printf("Match Value: %.*s\n", testPmatch[0].rm_eo - testPmatch[0].rm_so, &request[testPmatch[0].rm_so]);
    }
    else
    {
        printf("Test match: No\n");
    }

    return 0;
}
