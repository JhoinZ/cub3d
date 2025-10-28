/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsaffiri <fsaffiri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:07:42 by fsaffiri          #+#    #+#             */
/*   Updated: 2025/10/28 12:10:10 by fsaffiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* int	main(char **av, int ac)
{
	t_tools	tools;

	ft_full_parsing(av, ac, &tools);
	ft_init_player_vectors(&tools);
	ft_setup_mlx_and_game(&tools);
	ft_run_game_loop(&tools);
	return (0);
} */

int main(int ac, char **av)
{
    t_tools tools;

    // 1. Fase Parsing Completa
    // Se questa funzione ritorna, il parsing è corretto e i dati sono in 'tools'.
    ft_full_parsing(av, ac, &tools); 
    
    // -------------------------------------------------------------------
    // FASE DI TEST: Qui fermiamo il programma per verificare i dati parsati
    // -------------------------------------------------------------------

    printf("\n✅ Successo del Parsing:\n");
    printf("Configurazione e Mappa validate. Dati del giocatore:\n");
    printf("- Posizione Iniziale: (X=%.2f, Y=%.2f)\n", tools.player.pos_x, tools.player.pos_y);
    printf("- Direzione Vettore: (dir_x=%.2f, dir_y=%.2f)\n", tools.player.dir_x, tools.player.dir_y);
    printf("- Piano Telecamera: (plane_x=%.2f, plane_y=%.2f)\n", tools.player.plane_x, tools.player.plane_y);
    printf("\nPronto per avviare il motore grafico (MiniLibX).\n");

    // Pulizia di tutta la memoria allocata nel parsing (senza MLX)
    // Usiamo ft_free_all per liberare map_grid e i path delle texture.
	ft_free_mem(&tools);
    return (0);
}
