#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start, n = 0;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int temp = start;
    while (temp < end)
    {
        temp += (temp / 3 - temp / 4);
        n++;
    }
    printf("Years: %d", n);

    // TODO: Print number of years
}