/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:15:40 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 17:18:40 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

# include "prototypes.h"
# include "structs.h"
# include "../ft_printf/includes/core.h"
# include "../libft/libft.h"

# define BUILTINS_COUNT 6

# define ERROR_GNL "Read error.\n"
# define ERROR_MALLOC "Memory error.\n"
# define ERROR_EXEC "Error on fork.\n"
# define ERROR_CMD_NOT_FOUND "Command not found.\n"
# define ERROR_PERMISSION_DENIED "Permission denied.\n"
# define ERROR_INVALID_ARGUMENT "Invalid argument.\n"
# define ERROR_TOO_MANY_SYMLINK "Too many symbolic links\n"

#endif
