#include "minishell.h"

//funcion que comprueba si existe la variable de entorno que le paso

//falta comprobar esta funcion extract_word
char *ft_extract_word(char *str, int *pos) //esta funcion es para sacar la palabra que le mandare al execve, este me mirara, recibo la pos de donde esta el dollar
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
            end--;
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

    i = 0;
	start = *pos;
    dest = ft_substr(str, start, num_chars);
    dest[i] = '\0';
    *pos = start + num_chars;
    return (dest);//esta cadena sera tanto para reservar la palabra que hay antes de $
    // como para reservar la palabra que hay despues de la extraccion del $
}


char *funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)
{
    char *cadena_a_trozos = NULL;
    char *palabra_dolar = NULL;
    char *palabra_a_cambiar = NULL;
    int pos = 0;
    int pos_dolar = 0;
    int num_chars = 0;
    g_data = NULL;

    printf("\033[0;35m");
    printf("\nvslor split token en funcion lleva todo: %s\n", split_tokens);
    printf("\033[0m");

    pos_dolar = ft_encontrar_dolar(split_tokens, pos);
    if(pos_dolar < 0)
        return (split_tokens);
    palabra_dolar = ft_extract_word(split_tokens, &pos_dolar);
    printf("\033[0;31m");
    printf("\nesta es la palabra que tiene el dolar: %s\n", palabra_dolar);
    printf("\033[0m");
//hasta aqui hace solo un dolar por cadena, si hay varios dolar en una cadena no lo hace

    if(palabra_dolar != NULL)
    {
        //funcion que mira si existe la variable de entorno
        //si existe la variable de entorno, se sustituye por su valor
        printf("\nestamso dentro if\n");
        palabra_a_cambiar = "cambio aqui";//esto se sustituye por el resultado de la funcionque mira si existe la variable de entorno
        if (palabra_a_cambiar != NULL)//si existe la variable de entorno
            num_chars = pos_dolar - pos;
            printf("\nnum_chars: %d\n", num_chars);
            cadena_a_trozos = ft_cpy_part(split_tokens, &pos, num_chars);      //esto quiero que sea antes del dolar
            printf("\nla cadena a trozos: %s\n", cadena_a_trozos);
            num_chars = ft_strlen(palabra_a_cambiar);
            printf("\nnum_chars: %d\n", num_chars);
            split_tokens = ft_strjoin(cadena_a_trozos, palabra_a_cambiar);
            printf("\nla cadena a trozos juntitos: %s\n", split_tokens);
            cadena_a_trozos = ft_cpy_part(split_tokens, &pos, num_chars);      //esto quiero que sea despues del dolar
            printf("\nla cadena a trozos otro cacho: %s\n", cadena_a_trozos);
            split_tokens = ft_strjoin(split_tokens, cadena_a_trozos);
            printf("\nla cadena a trozos juntitos final: %s\n", split_tokens);
        //else
            //la variable se sustituye por nada(dolar lo que sea desaparece)y se sigue con la cadena
        //lo que salga de aqui sera la cadena modificada en caso de $ valido o no
    }   
    return ("hay dolar");

}

//yo llamo a la funcion que lo lleva todo tras hacer limpia de comilla y tenerlo a cachitos, es decir 
//le entrarian varias cadenas por tanto hay que hacer un bucle que llame varias veces a la funcion

//quiero 

//despues de esta funcion tengo la funcion que me devuelve el significado de la palabra que tenia dolar
//tras esa funcion tengo que pegar la palabra a la cadena que me dejo la funcion cpy_part, tras juntarlo tengo que
// pegarle lo que venga despues de la palabra sacsada de $lo que sea

//[listo]1 - la funcion busca carcacter hay que añadirle que si esta entre comillas simples no lo haga, pero para eso hay que ver si hay algunas comillas aabiertas antes de la
//[listo]2 - si encuentra el caracter llama a la funcion extrae_word[listo]
//3 - la funcion extrae_word llamara a la funcion que mira variables de entorno[aun no]
//4 - da igual lo que salga ese valor ha de ser sustituido por la palabra extraida de la funcion extrae_word[aun no]
//[listo]5 - se llama a la funcion que copia todo hasta antes del dolar, se reserva[listo?]
//[listo]6 - se crea una nueva cadena con el tamaño de la union de la cadena reservada y la palabra extraida
//[listo]7 - se crea una nueva cadena con el tamaño de la union y lo que haya detras de la cadena extraida
//[mirarlo]obviamente hay que ir limpiando las cadenas que se han ido fusionando, esto es un paso que va por que va dentro de todo el proceso
//8 - si se vuelve a pasar la funcion busca_caracter y no encuentra nada, se copia lo que quede de la cadena original
