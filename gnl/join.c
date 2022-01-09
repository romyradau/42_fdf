
char	*my_strjoin(char	*pot, char	*buf)
{
	size_t	len;
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (pot == NULL)
		pot = my_substr("", 0, 0);
	len = my_strlen(i, pot) + my_strlen(j, buf);
	newstr = my_calloc((len + 1), sizeof(char));
	if (newstr == NULL)
		return (NULL);
	while (pot[i] != '\0')
	{
		newstr[i] = pot[i];
		i++;
	}
	while (i < len)
		newstr[i++] = buf[j++];
	if (pot != NULL)
		my_free(&pot);
	return (newstr);
}

int	main()
{
	char	*1;
	char	*2;

	1 = "does this work";
	2 = "i hope so";
	my_strjoin(1, 2);
}