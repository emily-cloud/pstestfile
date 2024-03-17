
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>

long int	ft_atoi(const char *str)
{
	long int	number;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
		break ;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	uc1;
	unsigned char	uc2;
	size_t			i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (uc1 != uc2)
			return (uc1 - uc2);
		i++;
	}
	return (0);
}


int digitalCheck(char **av)
{
    int i;
    int j;

    i = 1;
    while(av[i])
    {
        j = 0;
        if(av[i][j] != '+' && av[i][j] != '-' && !(av[i][j] >= '0' && av[i][j] <= '9'))
            return (1);
        if((av[i][j] == '+' || av[i][j] == '-') && !(av[i][j+1] >= '0' && av[i][j+1] <= '9'))
            return (1);
        while(av[i][++j])
        {
            if(!(av[i][j] >= '0' && av[i][j] <= '9'))
                return (1);
        }
        i++;
    }
    return (0);
}

int dupCheck(char **av)
{
   int i;
   int j;

    i = 1;
    while(av[i])
    {
        j = i+1;
        while(av[j])
        {
            if(ft_strcmp(av[i], av[j]) == 0)
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int exceedlimit(char **av)
{
    int i;
    long int nb;

    i = 0;
    while(av[i])
    {
        nb = ft_atoi(av[i]);
        if(nb > LONG_MAX || nb < LONG_MIN)
            return (1);
        i++;
    }
    return (0);
}


int invalideCheck(char **av)
{
    if (digitalCheck(av))
        return (1);
    if(dupCheck(av))
        return (1);
    if(exceedlimit(av))
        return (1);
    return (0);
}

int countWord(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(str[i])
    {
        while(str[i] == ' ')
            i++;
        if(str[i])
            count++;
        while(str[i] != ' ' && str[i])
            i++;
    }
    return (count);
}

char **SplitToStr(char *str)
{
    char **nb_str;
    int i = 0;
    int len;
    int j = 1;
    int k;
    int count_word = countWord(str);
    
    //Allocate 2 more strings, the first string set to \0 to be the same as the first argement as the name a.out
    nb_str = (char **)malloc((count_word + 2) * sizeof(char *));
    if (nb_str == NULL)
        return (NULL);
    /*nb_str[0] = malloc(sizeof(char));
    if (nb_str[0] == NULL)
        return (NULL);*/
    nb_str[0] = NULL;
    while(str[i])
    {
        k = 0;
        len = 0;
        // Skip leading spaces
        while(str[i] == ' ')
            i++;
        // Calculate the length of the current word
        while(str[i + len] != ' ' && str[i + len])
            len++;
        // Allocate memory for the current word
        nb_str[j] = (char *)malloc((len + 1)* sizeof(char)); 
        if (nb_str[j] == NULL) // Free previously allocated memory before returning NULL
        {
            while( j > 1)
                free(nb_str[--j]);
            free(nb_str);// Free the pointer
            return NULL;
        }
        // Copy the current word into nb_str
        while(str[i] != ' ' && str[i])
            nb_str[j][k++] = str[i++];
        nb_str[j][k] = '\0';// Null-terminate the string
        j++;// Move to the next word
    }
    nb_str[j] = NULL;// Null-terminate the array of strings
    return (nb_str);
}

int main(int argc, char **av)
{
    int i = 1;

    if (argc == 1 || (argc == 2 && av[1][0] == '\0'))
        return (1);
    if (argc == 2)
        av = SplitToStr(av[1]);// split the argement to strings"
    while(av[i])
    {
        printf("%s\n",av[i]);
        i++;
    }
    if (invalideCheck(av))// check the strings are valide 
    {
        printf("Error\n");
          return (1);
    }
}

