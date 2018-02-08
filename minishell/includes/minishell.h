/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:15:40 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:21:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>

# include "prototypes.h"
# include "structs.h"
# include "../ft_printf/includes/core.h"
# include "../libft/libft.h"

# define BUILTINS_COUNT 6

# define ERROR_GNL "Une erreur est survenue lors de la lecture.\n"
# define ERROR_MALLOC "Une erreur de mémoire est survenue.\n"
# define ERROR_EXEC "Une erreur est survenue lors du lancement du processus.\n"
# define ERROR_CMD_NOT_FOUND "Commande non trouvée.\n"

#endif
