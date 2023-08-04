int main(int argc, char **argv)
{
	int i;
	(void) argv;
	i = 4 + (400 / argc);
	printf("%i",i);
	return(i);
}