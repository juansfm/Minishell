#include "minishell.h"
/*

int ft_espacio_antes(char *cadena, int pos_caracter)
{
    if (pos_caracter > 0 && cadena[pos_caracter - 1] == ' ')
        return 0;
    return 1;
}

int ft_espacio_despues(char *cadena, int *len, int pos_caracter)
{
    if (pos_caracter < ((*len) - 1) && cadena[pos_caracter + 1] == ' ')
        return 0;
    return 1;
}
int ft_change_len(int *espacios_ad, int *len)
{
    if (espacios_ad[0] && espacios_ad[1])
        return ((*len) + 2);
    else if (espacios_ad[0] || espacios_ad[1])
        return ((*len) + 1);
    return *len;

    
}*/
/*
char *ft_agregar_espacios(char *cadena, int *len, int pos_caracter, int *espacios_ad)
{
    int new_len;
	char *nueva_cadena;
    int i;
    int j;
    
    nueva_cadena = NULL;
    new_len = ft_change_len(espacios_ad, len);
    nueva_cadena = malloc(sizeof(char) * (new_len + 1));
    if (nueva_cadena == NULL)
	{
        printf("Error al asignar memoria.\n");
        return NULL;
    }
    i = 0;
    j = 0;
    printf("\n\nHola estamos dentro agregar espacios\n\n");
    while (i <= new_len)
	{
        if (i == pos_caracter)
		{
            if ((espacios_ad[0] == 1) && (espacios_ad[1] == 1))
			{
                nueva_cadena[j++] = ' ';
                nueva_cadena[j] = cadena[i];
                
            }
			else if (espacios_ad[0] == 1)
			{
                nueva_cadena[j++] = ' ';
                nueva_cadena[j] = cadena[i];
            }
            else if (espacios_ad[1] == 1)
                nueva_cadena[j] = cadena[i];
        }
		else
            nueva_cadena[j] = cadena[i];
        i++;
        j++;
    }
    printf("la nueva cadena es: %s\n", nueva_cadena);
    return nueva_cadena;
}


int count_pipes_without_quotes(char *cadena)
{
    int count;
    int in_quotes;

    in_quotes = 0;
    count = 0;
    while (*cadena)
    {
        if (*cadena == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (*cadena == '|' && !in_quotes)
        {
            count++;
        }
        cadena++;
    }
    return count;
}

int is_pipe_outside_quotes(const char *cadena, int index)
{
    int in_quotes;

    in_quotes = 0;
    while (index--)
    {
        if (*cadena == '"')
        {
            in_quotes = !in_quotes;
        }
        cadena++;
    }
    return (*cadena == '|' && !in_quotes);
}

void add_spaces(t_modify *params, int index)
{
    char *cadena;
    int len;
    int *j;
    char *temp;

    cadena = params->cadena;
    len = params->len;
    j = params->j;
    temp = params->temp;
    if ((index > 0 && cadena[index - 1] != ' ') || (index < len - 1 && cadena[index + 1] != ' '))
    {
        if (index > 0 && cadena[index - 1] != ' ')
        {
            temp[(*j)++] = ' ';
        }
        temp[(*j)++] = '|';
        if (index < len - 1 && cadena[index + 1] != ' ')
        {
            temp[(*j)++] = ' ';
        }
    }
    else
    {
        temp[(*j)++] = ' ';
        temp[(*j)++] = '|';
        temp[(*j)++] = ' ';
    }
}

char *modify_string(t_general g_data)
{
    int pipes;
    int in_quotes;
    
    pipes = count_pipes_without_quotes(cadena);
    g_data->len = ft_strlen(cadena);
    if (pipes == 0)
    {
        return ft_strdup(cadena); // No hay pipes fuera de comillas
    }

    temp = malloc(sizeof(char) * (len + pipes * 2 + 1)); // Asumiendo que cada pipe necesita dos espacios

    if (temp == NULL)
    {
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    params = {cadena, len, 0, temp};

    in_quotes = 0;
    while (*cadena)
    {
        if (*cadena == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (is_pipe_outside_quotes(cadena, params.j - temp))
        {
            add_spaces(&params, params.j - temp);
        }
        else
        {
            temp[params.j - temp] = *cadena;
            params.j++;
        }
        cadena++;
    }

    temp[params.j - temp] = '\0';
    return temp;
}*/