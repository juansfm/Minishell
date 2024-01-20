#include "minishell.h"

//funcion que comprueba si existe la variable de entorno que le paso

//falta comprobar esta funcion extract_word

//esta funcion es para sacar la palabra que le mandare al execve,
//este me mirara, recibo la pos de donde esta el dollar
char *ft_extract_word(char *str, int pos_dolar, int *pos)//pos es donde esta el dolar 
{
    int start;
    int end;
    char *word;
    int fin;

    word = NULL;
    fin = 0;
    start = pos_dolar;
    end = start + 1;
    if(str[end] && ft_isdigit(str[end]))
    {
       // word = //lamar al execve con el dolar y el numero solamente
       fin = 1;
    }
    while (str[end] && (fin == 0))
    {
        if(!ft_isalnum(str[end]))
        {
            end--;
            break;
        }
        end++;
    }
    word = ft_substr(str, start + 1, end - start);
    *pos = end;
    return (word);//esta palabra es la que va a ir al execve sin dolar
}

//la funcion devuelve la posicion donde esta el primer dolar o menos 1 si no lo encuentra(dolar valido)
//ahora esta modificada para que se le pase la posicion desde donde comienza a buscar
int ft_encontrar_dolar(char *cadena, int inicio)
{
    int i;
    int comilla_simple;
    int comilla_doble;

    i = inicio;
    comilla_simple = 0;
    comilla_doble = 0;
    while (cadena[i])
    {
        if (cadena[i] == '\"')
            comilla_doble = (comilla_doble + 1) % 2;
        else if (cadena[i] == '\'')
        {
            if (comilla_doble == 0)
                comilla_simple = (comilla_simple + 1) % 2;
        }
        else if (cadena[i] == '$' && comilla_simple == 0)
            return (i);
        i++;
    }
    return (-1);
}

//si la funcion busca_caracter encuentra el caracter que le paso, devuelve la posicion donde esta el dolar
//esta funcion es solo una parte de otra funcion, esto me guarda en una cadena todo hasta donde esta el dolar

//queremos que esta funcion nos sirva para coger desde ubicaciones dadas 

char *ft_cpy_part(char *str, int *pos, int num_chars)
{
    int start;
    char *dest;

    start = *pos;
    if (num_chars > 0)
        dest = ft_substr(str, start, num_chars);
    else
        dest = ft_strdup(""); // return an empty string instead of NULL
    printf("\033[0;34m");
    printf("\nAqui copiamos: %s\n", dest);
    printf("\033[0m");
    *pos = start + num_chars;
    return (dest);//esta cadena sera tanto para reservar la palabra que hay antes de $
    // como para reservar la palabra que hay despues de la extraccion del $
}

char *ft_remodelar_cadena(char *split_tokens, char *palabra_dolar, char *word_exchange, int pos_dolar)
{
    char *cadena_a_trozos = NULL;
    char *palabra_a_cambiar = NULL;
    char *cadena_parte_final = NULL;
    int pos = 0;

    printf("\ncacahuete verde: %s\n", palabra_dolar);
    cadena_a_trozos = ft_cpy_part(split_tokens, &pos, pos_dolar);
    palabra_a_cambiar = ft_cpy_part(split_tokens, &pos, ft_strlen(palabra_dolar) + 1);
    printf("La palabra a cambiar: %s\n", palabra_a_cambiar);
    cadena_parte_final = ft_cpy_part(split_tokens, &pos, ft_strlen(split_tokens) - pos);
    printf("La cadena parte final: %s\n", cadena_parte_final);
    if(cadena_a_trozos != NULL)
        cadena_a_trozos = ft_strjoin(cadena_a_trozos, word_exchange);
    else
        cadena_a_trozos = ft_strdup(word_exchange);
    printf("\033[0;35m");
    printf("\nunion principio con palabra modificada: %s\n",cadena_a_trozos);
    printf("\033[0m");
    cadena_a_trozos = ft_strjoin(cadena_a_trozos, cadena_parte_final);
    return (cadena_a_trozos);
}

