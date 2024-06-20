%{
#include <stdio.h>
%}

%%
[0-9+] {
    printf("That is a number");
}

%%