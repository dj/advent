/*
As you walk through the door, a glowing humanoid shape yells in your direction. "You there! Your state appears to be idle. Come help us repair the corruption in this spreadsheet - if we take another millisecond, we'll have to display an hourglass cursor!"

The spreadsheet consists of rows of apparently-random numbers. To make sure the recovery process is on the right track, they need you to calculate the spreadsheet's checksum. For each row, determine the difference between the largest value and the smallest value; the checksum is the sum of all of these differences.

For example, given the following spreadsheet:

5 1 9 5
7 5 3
2 4 6 8

    The first row's largest and smallest values are 9 and 1, and their difference is 8.
    The second row's largest and smallest values are 7 and 3, and their difference is 4.
    The third row's difference is 6.

In this example, the spreadsheet's checksum would be 8 + 4 + 6 = 18.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int checksum(char *line)
{
	int min = 0;
	int max = 0;

	char *tokenPtr = strtok(line, "\t");
	while (tokenPtr != NULL)
	{
		intmax_t num;
		int base = 10;
		char *endptr;
		num = strtoimax(tokenPtr, &endptr, base);

		if (min == 0 || min > num)
		{
			min = num;
		}
		else if (max < num)
		{
			max = num;
		}

		// read until next number
		tokenPtr = strtok(NULL, "\t");
	}

	return max - min;
}

int main(int argc, char *argv[])
{
	int bytes_read;
	size_t nbytes = 1000;
	char *input_line;

	input_line = (char *)malloc(nbytes + 1);
	bytes_read = getline(&input_line, &nbytes, stdin);
	int sum = 0;
	while (bytes_read != -1)
	{
		// find the checksum for line and add to total
		sum += checksum(input_line);

		// read the next line
		bytes_read = getline(&input_line, &nbytes, stdin);
	}

	printf("%d", sum);

	free(input_line);

	return EXIT_SUCCESS;
}
