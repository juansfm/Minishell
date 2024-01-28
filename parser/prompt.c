#include "minishell.h"

void	ft_prompt(void)
{
	ft_putstr_fd(RED "⠀⠀⠀⣠⡿⠟⠛⠉⠉⠙⠿⣦⠀\n", 1);
	ft_putstr_fd("⠀⢰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣄⡀\n", 1);
	ft_putstr_fd("⢠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣶⣤⣀⡀\n", 1);
	ft_putstr_fd("⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠙⠒⠲⠦⢤⣄⣀⣀⡀⠀⠀\n", 1);
	ft_putstr_fd("⠘⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠓⠶⠦⣤⣀⣀\n", 1);
	ft_putstr_fd("⠀⠈⠳⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠒⠶⢦⣄\n", 1);
	ft_putstr_fd("⠀⠀⠀⠈⠳⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠈⠙⢶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡿⢦⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠟⠁⠀⠀⠈⠉⠑⠲⢤⣀⡀⠈⠻⣇⠀⣷⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⢷⡖⠚⠻⣧⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⢻⡄\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡧⠀⠀⠀⣿\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠗⠒⠤⣀⠀⠀⠀⠀⠀⠀⢰⠏⠀⠀⠀⢰⡏⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠚⠛⠛⠛⠛⠛⠆⠀⠀⢀⡿⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣄⠙⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡾⠁\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣷⣄⡙⠷⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠀⠀⠀⢀⡾⠁\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⡛⢿⣶⣤⣉⡉⠉⠉⠉⠉⠉⠙⠛⠿⢿⣟⡛⠛⠛⠚⠋⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢳⡄⠙⢧⡈⠉⠓⠲⣦⣄⡀⠀⠀⠀⠀⠈⠙⠳⢦⣀⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣦⠀⠙⣦⡀⠀⠀⠙⢿⣶⣄⡀⠀⠀⠀⠀⠀⠈⠛⠦⣄⡀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⣄⠈⠻⣦⡀⠀⠀⠈⠻⣿⡓⠶⢤⣄⡀⠀⠀⠀⠀⠉⠓⠦⣄\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣦⡀⠙⣿⠶⣄⡀⠀⠈⠻⢦⡀⠀⠉⠙⠒⠦⣤⣄⡀⠀⠈⠙⣆\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢷⣄⣾⠀⠈⠛⢦⡀⠀⠀⠙⢦⡀⠀⠀⠀⠀⠈⠙⠓⠦⣤⡼⠃\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⠀⠀⠀⠀⠙⢶⣄⠀⠀⠻⡄⠀⠀\n", 1);
	ft_putstr_fd("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠳⣦⣠⠇⠀⠀\n" RESET, 1);
}

// char	*ft_expand_all(t_general *g_data, char *cmd)
// {
// 	int		dollar_pos;
// 	int		i;
// 	char	*string_restruc;
// 	char	*word_exchange;
// 	char	*extract_word;

// 	i = 0;
// 	dollar_pos = -1;
// 	string_restruc = ft_strdup("");
// 	word_exchange = NULL;
// 	while (cmd[i])
// 	{
// 		ft_if_is_quote(cmd[i], g_data);
// 		if (ft_char_is_dollar(cmd[i], g_data) == 0)
// 			dollar_pos = i;
// 		if (dollar_pos == -1)
// 		{
// 			string_restruc = ft_charjoin_free(string_restruc, cmd[i]);
// 			i++;
// 		}
// 		else
// 		{
// 			extract_word = ft_extract_word(cmd, dollar_pos);
// 			i++;
// 			if (ft_strcmp(extract_word, "?") == 0)
// 			{
// 				word_exchange = ft_itoa(g_data->status);
// 				string_restruc = ft_strjoin_free(string_restruc,
// 						word_exchange);
// 				free(word_exchange);
// 				i++;
// 			}
// 			else if (!(*extract_word)
// 				|| (ft_char_reserved(extract_word[0]) == 1))
// 			{
// 				string_restruc = ft_charjoin_free(string_restruc, '$');
// 				i++;
// 			}
// 			else
// 			{
// 				word_exchange = ft_get_word_exchange(g_data, extract_word);
// 				string_restruc = ft_strjoin_free(string_restruc, word_exchange);
// 				i += ft_strlen(extract_word);
// 				free(word_exchange);
// 			}
// 			free(extract_word);
// 		}
// 		dollar_pos = -1;
// 	}
// 	g_data->quote_double = 0;
// 	g_data->quote_simple = 0;
// 	free(cmd);
// 	return (string_restruc);
// }

// char	*ft_process_dollar(t_general *g_data, char *cmd, int *i, char *string_restruc)
// {
//     int		dollar_pos;
//     char	*word_exchange;
//     char	*extract_word;

//     dollar_pos = *i;
//     extract_word = ft_extract_word(cmd, dollar_pos);
//     (*i)++;
//     if (ft_strcmp(extract_word, "?") == 0)
//     {
//         word_exchange = ft_itoa(g_data->status);
//         string_restruc = ft_strjoin_free(string_restruc, word_exchange);
//         free(word_exchange);
//         (*i)++;
//     }
//     else if (!(*extract_word) || (ft_char_reserved(extract_word[0]) == 1))
//     {
//         string_restruc = ft_charjoin_free(string_restruc, '$');
//         (*i)++;
//     }
//     else
//     {
//         word_exchange = ft_get_word_exchange(g_data, extract_word);
//         string_restruc = ft_strjoin_free(string_restruc, word_exchange);
//         (*i) += ft_strlen(extract_word);
//         free(word_exchange);
//     }
//     free(extract_word);
//     return string_restruc;
// }