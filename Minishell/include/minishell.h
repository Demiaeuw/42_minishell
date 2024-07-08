/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acabarba <acabarba@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:43:41 by acabarba          #+#    #+#             */
/*   Updated: 2024/07/08 16:50:09 by acabarba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>	// write
# include <stdlib.h>    // malloc, free, exit, getenv
# include <stdio.h>     // printf
# include <unistd.h>    // write, access, read, close, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty
# include <fcntl.h>     // open, O_* constants
# include <sys/types.h> // opendir, readdir, closedir, stat, lstat, fstat, wait, waitpid, wait3, wait4
# include <sys/stat.h>  // stat, lstat, fstat
# include <dirent.h>    // opendir, readdir, closedir
# include <string.h>    // strerror
# include <errno.h>     // perror
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/ioctl.h> // ioctl
# include <termios.h>   // tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <unistd.h>    // ttyname, ttyslot
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include "../utils/libft/libft.h"
# include "../utils/ft_printf/includes/ft_printf.h"
# include "../utils/gnl/get_next_line.h"

int		main(void);

//00
void	main_error(void (*f)());

#endif