#include "minishell.h"

int ft_espacio_antes(const char *cadena, int pos_caracter)
{
    if (pos_caracter > 0 && cadena[pos_caracter - 1] == ' ')
        return 1;
    return 0;
}

int ft_espacio_despues(const char *cadena, int len, int pos_caracter)
{
    if (pos_caracter < len - 1 && cadena[pos_caracter + 1] == ' ')
        return 1;
    return 0;
}

char *ft_agregar_espacios(const char *cadena, int len, int pos_caracter, int espacio_antes, int espacio_despues)
{
    int new_len;
	char *nueva_cadena;

	new_len = len;
    if (espacio_antes && espacio_despues)
	{
        new_len += 2;
    } 
	else
	{
        new_len += 1;
    }

    nueva_cadena = (char *)malloc(new_len + 1);

    if (nueva_cadena == NULL)
	{
        printf("Error al asignar memoria.\n");
        return NULL;
    }

    int i = 0, j = 0;
    while (i <= len)
	{
        if (i == pos_caracter)
		{
            if (espacio_antes && espacio_despues)
			{
                nueva_cadena[j++] = ' ';
                nueva_cadena[j] = cadena[i];
            }
			else if (espacio_antes)
			{
                nueva_cadena[j++] = ' ';
                nueva_cadena[j] = cadena[i];
            } else
			{
                nueva_cadena[j] = cadena[i];
            }
        }
		else
		{
            nueva_cadena[j] = cadena[i];
        }
        i++;
        j++;
    }

    return nueva_cadena;
}

void ft_modificar_cadena(char *cadena, int len, int pos_caracter)
{
	int espacio_antes;
    int espacio_despues;
	char *nueva_cadena;

	espacio_antes = ft_espacio_antes(cadena, pos_caracter);
    espacio_despues = ft_espacio_despues(cadena, len, pos_caracter);

    nueva_cadena = ft_agregar_espacios(cadena, len, pos_caracter, espacio_antes, espacio_despues);

    if (nueva_cadena != NULL)
	{
        printf("Cadena después de la modificación: %s\n", nueva_cadena);
        free(cadena);
        cadena = nueva_cadena;
    }
}