/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpires <kpires@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:30:50 by kpires            #+#    #+#             */
/*   Updated: 2024/11/25 14:30:50 by kpires           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../icl/minishell.h"

int	g_status; // Variable globale pour stocker le statut du shell

// Fonction pour gérer le signal SIGINT (Ctrl+C)
void	handle_sigint(int sig)
{
    if (sig == SIGINT) // Vérifie si le signal reçu est SIGINT
    {
        g_status = 130; // Définit le statut global à 130 (code de sortie pour interruption)
        ioctl(STDIN_FILENO, TIOCSTI, "\n"); // Simule l'entrée d'un caractère de nouvelle ligne
        rl_replace_line("", 0); // Remplace la ligne actuelle par une chaîne vide
        rl_on_new_line(); // Déplace le curseur à une nouvelle ligne
    }
}