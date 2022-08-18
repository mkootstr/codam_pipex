/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/23 19:24:38 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/08/18 15:35:40 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[], char *envp[])
{
	//input checken
	//parsen
	//errors
}

void	pipex(linked list, char *envp[])
{
	int end[2];
	pid_t	child1;
	pid_t	child2;

	while (linked list niet op einde)
	{
		//pipe
		//fork
		//if child one function(linked list)
		//pipe
		//fork
		//if child two function(linked list)
		close(end[0]);
		close(end[1]);
		waitpid(child1);
		waitpid(child2);
	}
}
//ERROR MANAGEMENT
	//arg hoeveelheid checken maar ook of valid is met die pipes
	//moet nl altijd groter dan 4 maar als bonus moet ie groter dan 5
	//dus checken of tweede argument here_doc is en dan pas input minimum vaststellen
	//file met custom errors en nummers maken voor alles wat errnum niet doet

	//INPUT PARSEN
	//checken voor here_doc en dan naar andere parser
	//voor bonus denk ik alles opslaan in argc sized struct
	//dan per pointer splitten
	//een pipe tegelijk splitten voor bonus
	//pas verder parsen en freeen als proces klaar is
	//twee structs aanmaken voor de twee commands en infile outfile
	//misschien outfile los als ik het beetje begrijp
	//eerste arg als losse char* opslaan
	//de rest in array voor flags en arguments

	//EEN PIPE SPECIFIEKER PARSEN
	//commands zoeken in PATH van environment
	//nog ff kijken hoe de fuck dat werkt
	//opslaan in die twee structs

	//PIPEN EN FORKEN (pijpen en fucken is beetje grappig ik ben 12)
	//wordt dus ingewikkeld
	//hoe werkt freeen met mother en child process? Met fork=0 of fork=1 als condition misschien
	//iig execve met path en arguments uit struct en environment

	//dan wanneer klaar shit freeen process stoppen opnieuw forken tot einde

	//bonus nog ff kijken wat die dubbele haakjes zijn
	//moet vgm heel ander proces voor komen uwu