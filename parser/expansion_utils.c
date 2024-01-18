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

char *ft_funcion_que_lo_lleva_todo(t_general *g_data, char *cmd)//esta funcion la llamare mas veces por si hay mas dolar
{
    int pos = 0;
    int pos_dolar = 0;
    char *palabra_dolar = NULL;
    char *word_exchange = NULL;
    char *cadena_ya_reestructurada = cmd;
    t_env *env = NULL; 

    while ((pos_dolar = ft_encontrar_dolar(cadena_ya_reestructurada, pos)) >= 0)
    {
        palabra_dolar = ft_extract_word(cadena_ya_reestructurada, pos_dolar, &pos);
        printf("\033[0;31m");
        printf("\nesta es la palabra que tiene el dolar: %s\n", palabra_dolar);
        printf("\033[0m");
        //llamo a la funcion que busca en el execve
        if(ft_env_search(g_data, palabra_dolar))
        {
            env = ft_env_search(g_data, palabra_dolar);
            ft_strdup(env->valor);
            word_exchange = ft_strdup(env->valor);
        }
        else
            word_exchange = "";
        cadena_ya_reestructurada = ft_remodelar_cadena(cadena_ya_reestructurada, palabra_dolar, word_exchange, pos_dolar);
        printf("\033[0;35m");
        printf("\nla cadena ya reestructurada: %s\n", cadena_ya_reestructurada);
        printf("\033[0m");
        pos = 0;
        //aqui mando la palabra al execve
        //word = funcion que llama al execve(palabra_dolar))
        //tres separar a cachos la cadena
    }
    return (cadena_ya_reestructurada);
}


/*copia de que lo lleva todo sin modificar
char *funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)//esta funcion la llamare mas veces por si hay mas dolar
{
    int pos = 0;
    int pos_dolar = 0;
    char *palabra_dolar = NULL;
    char *word_exchange = NULL;
    char *cadena_ya_reestructurada = NULL;
    g_data = NULL;

    pos_dolar = ft_encontrar_dolar(split_tokens, pos);//guarda la posicion del dolar
    if(pos_dolar < 0)
        return (split_tokens);
    palabra_dolar = ft_extract_word(split_tokens, pos_dolar, &pos);
    //pos actulizada al final de la palabra +1 si esk existe continuacion
    //word = funcion que llama al execve(palabra_dolar))
    //llamo a la funcion que busca en el execve
    word_exchange = "sustituto";
    cadena_ya_reestructurada = ft_remodelar_cadena(split_tokens, palabra_dolar, word_exchange, pos_dolar);
    printf("\033[0;35m");
    printf("\nla cadena ya reestructurada: %s\n", cadena_ya_reestructurada);
    printf("\033[0m");
    //aqui mando la palabra al execve
    //word = funcion que llama al execve(palabra_dolar))
    //tres separar a cachos la cadena
    return (cadena_ya_reestructurada);
}
*/
//de esta funcion hay que modificar que cuando haya algo detras de la funcion dolar 
/*char *funcion_que_lo_lleva_todo(t_general *g_data, char *split_tokens)
{
    char *cadena_a_trozos = NULL;
    char *palabra_dolar = NULL;
    char *palabra_a_cambiar = NULL;
    //char *cadena_parte_final = NULL;
    int pos = 0;
    int pos_dolar = 0;
    int num_chars = 0;

    g_data = NULL;
    printf("\033[0;35m");
    printf("\nvalor split token en funcion dentro de que lo lleva todo: %s\n", split_tokens);
    printf("\033[0m");

    pos_dolar = ft_encontrar_dolar(split_tokens, pos);
    printf("\nesta es la pos dolar tras salir(%i)\n", pos_dolar);
    if(pos_dolar < 0)
        return (split_tokens);
    palabra_dolar = ft_extract_word(split_tokens, pos_dolar);
    //aqui llamamos al execve con la palabra que nos devuelve la funcion extract_word
    printf("\033[0;31m");
    printf("\nesta es la palabra que tiene el dolar: %s\n", palabra_dolar);
    printf("\033[0m");
//hasta aqui hace solo un dolar por cadena, si hay varios dolar en una cadena no lo hace

    if(palabra_dolar != NULL)
    {
        //funcion que mira si existe la variable de entorno
        //si existe la variable de entorno, se sustituye por su valor
        printf("\nHEMOS ENCONTRADO DOLAR VALIDO\n");
        palabra_a_cambiar = "Sustituto";//esto se sustituye por el resultado de la funcionque mira si existe la variable de entorno
        if (palabra_a_cambiar != NULL)//si existe la variable de entorno
            num_chars = pos_dolar - pos;

            cadena_a_trozos = ft_cpy_part(split_tokens, &pos, num_chars);      //esto quiero que sea antes del dolar
            printf("\nla cadena a trozos: %s\n", cadena_a_trozos);
            printf("\npos tras copiar principio: %d\n", pos);
            num_chars = ft_strlen(palabra_a_cambiar);

            cadena_a_trozos = ft_strjoin(cadena_a_trozos, palabra_a_cambiar);
            printf("\033[0;35m");
            printf("\nunion principio con palabra modificada: %s\n",cadena_a_trozos);
            printf("\033[0m");
            //aqui tengo que unir la parte siguiente de la cadena que esta detras del dolar,previamente tendria que guardar esa info en algun lado
            //cadena_parte_final = ft_cpy_part(split_tokens, &pos, num_chars);      //esto quiero que sea despues del dolar
            //printf("\nla cadena a trozos otro cacho final: %s\n", cadena_parte_final);
            //cadena_a_trozos = ft_strjoin(cadena_a_trozos, cadena_parte_final);
            printf("\nla cadena a trozos juntitos final: %s\n", cadena_a_trozos);
        //else
            //la variable se sustituye por nada(dolar lo que sea desaparece)y se sigue con la cadena
        //lo que salga de aqui sera la cadena modificada en caso de $ valido o no
    }
    return (cadena_a_trozos);

}*/

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


//Partes de funcion expandir
//1-miro si hay dolar
//2-si lo hay, pregunto si puedo expandir,es decir que no este entre comillas simples
//3-si es un no, dejo la cadena como esta, y si no he terminado la cadena vuelvo a mirar si hay dolar
//4-si es un si, miro si lo que devuelve es un null o otra cosa
//5-si es un null tengo que rediseñar una n