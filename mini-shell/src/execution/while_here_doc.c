/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:43:37 by lauger            #+#    #+#             */
/*   Updated: 2024/05/09 14:04:26 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	handle_here_doc(t_minishell *shell, int i, char *delimiter)
{
	char		*line;
	char		*here_doc_content;
	char		*temp;
	size_t		len;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	here_doc_content = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (here_doc_content == NULL)
			here_doc_content = ft_strdup(line);
		else
		{
			len = ft_strlen(here_doc_content) + ft_strlen(line) + 2;
			temp = ft_calloc(len, 1);
			ft_strcpy(temp, here_doc_content);
			ft_strcat(temp, "\n");
			ft_strcat(temp, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}
	write_here_doc_in_file(here_doc_content,
		shell->redirect_array[i].infile.fd, shell);
	free_minishell(shell);
	exit(0);
}*/

char	*read_line(char *delimiter)
{
	char	*line;

	line = readline("gnegnegne > ");
	if (line == NULL || ft_strcmp(line, delimiter) == 0)
	{
		if (line != NULL)
			free(line);
		return (NULL);
	}
	return (line);
}

char	*update_here_doc_content(char *line, char *here_doc_content)
{
	size_t	len;
	char	*temp;

	if (here_doc_content == NULL)
		here_doc_content = ft_strdup(line);
	else
	{
		len = ft_strlen(here_doc_content) + ft_strlen(line) + 2;
		temp = ft_calloc(len, 1);
		ft_strcpy(temp, here_doc_content);
		ft_strcat(temp, "\n");
		ft_strcat(temp, line);
		free(here_doc_content);
		here_doc_content = temp;
	}
	free(line);
	return (here_doc_content);
}

static char	*read_and_process_line(char *delimiter, char *here_doc_content)
{
	char	*line;

	line = read_line(delimiter);
	if (line == NULL)
		return (NULL);
	here_doc_content = update_here_doc_content(line, here_doc_content);
	return (here_doc_content);
}

void	handle_here_doc(t_minishell *shell, t_file here_doc, char *delimiter)
{
	char	*here_doc_content;
	char	*temp;

	init_signal_handlers();
	signal(SIGINT, handle_sigint_here_doc);
	here_doc_content = NULL;
	while (1)
	{
		temp = read_and_process_line(delimiter, here_doc_content);
		if (temp == NULL)
		{
			free(temp);
			here_doc_content = ft_strjoin(here_doc_content, "\n");
			break ;
		}
		here_doc_content = temp;
	}
	write_here_doc_in_file(here_doc_content, here_doc.fd, shell);
	free_minishell(shell);
	shell->exit_status = 0;
	close(here_doc.fd);
	free(here_doc_content);
	exit(EXIT_SUCCESS);
}