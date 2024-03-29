/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/03/29 13:53:28 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_here_doc(char *delimiter)
{
	char *line;
	char *here_doc_content = NULL;

	init_signal_handlers();

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
					  "by end-of-file (wanted `%s')\n",
					  delimiter);
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (here_doc_content == NULL)
			here_doc_content = strdup(line);
		else
		{
			char *temp = malloc(strlen(here_doc_content) + strlen(line) + 2);
			sprintf(temp, "%s\n%s", here_doc_content, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}
	printf("\nContenu du here_doc :\n%s\n", here_doc_content);
	free(here_doc_content);
	exit(0);
}

void	fork_here_doc(char *delimiter)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		handle_here_doc(delimiter);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		ft_printf("The child process has finished\n");
	}
	else
	{
		perror("Error:\nduring fork_here_doc");
		exit(EXIT_FAILURE);
	}
}

void	handle_sigint_here_doc(int sig)
{
	(void)sig;
	exit(0);
}

void syntax_analyse(t_token *tokens)
{
	t_token *current;

	current = tokens;
	signal(SIGINT, handle_sigint_here_doc);
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			//handle_here_doc(current->value);
			fork_here_doc(current->value);
		}
		current = current->next;
	}
}