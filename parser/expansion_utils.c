#include "minishell.h"

//funcion que comprueba si existe la variable de entorno que le paso

//falta comprobar esta funcion extract_word
char *ft_extract_word(char *str, int *pos) //esta funcion es para sacar la palabra que le mandare al execve, este me mirara
{
    int start;
    int end;
    char *word;
    int fin;

    word = NULL;
    fin = 0;
    start = *pos;
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
            break;
        }
        end++;
    }
    word = ft_substr(str, start + 1, end - start);
    *pos = end;
    return (word);//esta palabra es la que va a ir al execve
}


//ahora esta moduificada para que se le pase la posicion desde donde comienza a buscar
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
    int i;
    char *dest;

	start = *pos;
    dest = ft_substr(str, start, num_chars);
    dest[i] = '\0';
    *pos = start + num_chars;
    return (dest);//esta cadena sera tanto para reservar la palabra que hay antes de $
    // como para reservar la palabra que hay despues de la extraccion del $
}

void funcion_que_lo_lleva_todo(char *cadena)
{
    //char *cadena;donde lo queremos meter
    //while (ft_encontrar_dolar(cadena) != -1)

        //ft_encuentra_dolar(cadena, pos);
        //word_expansion = ft_extract_word(cadena, &pos);
        //funcion que manda word_expansion al execve 
        //var_a_expandir =el valor de lo que haya llegado del execve, si es null me
        //reserva_antes = ft_cpy_part(cadena, cadena, &pos, num_chars);
        //reserva_despues = ft_cpy_part(cadena, cadena, &pos, num_chars);
        //join = ft_strjoin(reserva_antes, var_a_expandir);
        //join = ft_strjoin(join, reserva_despues);

}
//despues de esta funcion tengo la funcion que me devuelve el significado de la palabra que tenia dolar
//tras esa funcion tengo que pegar la palabra a la cadena que me dejo la funcion cpy_part, tras juntarlo tengo que
// pegarle lo que venga despues de la palabra sacsada de $lo que sea

//[listo]1 - la funcion busca carcacter hay que añadirle que si esta entre comillas simples no lo haga, pero para eso hay que ver si hay algunas comillas aabiertas antes de la
//[listo]2 - si encuentra el caracter llama a la funcion extrae_word[listo]
//3 - la funcion extrae_word llamara a la funcion que mira variables de entorno[aun no]
//4 - da igual lo que salga ese valor ha de ser sustituido por la palabra extraida de la funcion extrae_word[aun no]
//[listo]5 - llama se llama a la funcion que copia todo hasta antes del dolar, se reserva[listo?]
//[listo]6 - se crea una nueva cadena con el tamaño de la union de la cadena reservada y la palabra extraida
//[listo]7 - se crea una nueva cadena con el tamaño de la union y lo que haya detras de la cadena extraida
//[mirarlo]obviamente hay que ir limpiando las cadenas que se han ido fusionando, esto es un paso que va por que va dentro de todo el proceso
//8 - si se vuelve a pasar la funcion busca_caracter y no encuentra nada, se copia lo que quede de la cadena original
