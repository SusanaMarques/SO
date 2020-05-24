#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int myprint(char *s)
{
    const char *end = s;
    while (*end++)
        ;
    write(1, s, end - s - 1);
    return end - s - 1;
}

//Função que faz parsing de uma linha
int parse_linha(char *buff, char **str)
{
    char *tok;
    tok = strtok(buff, " ");

    
        str[0] = strdup(tok);
        tok = strtok(NULL, "");
        if(tok){
        str[1] = strdup(tok);
       
        }
    return 1;
}

//Função que faz parsing do argumento
int parse_arg(char *buff, char **str)
{
   
    char *tok;

    //aponta para o segundo elemento do buffer
    char* str2 = &(buff[1]);

    tok = strtok(str2,"\"");
    tok = strtok(str2, "|");
   
    
    int i; 

    for (i = 0; tok; i++)
    {
        if(sizeof(str)<i){ 
        str=realloc(str,sizeof(str)+sizeof(char**)*5);}

        str[i] = strdup(tok);
        
        tok = strtok(NULL, "|");
           
      
    }

    return i;
    
   
}



ssize_t readln(int fd, void *buff, size_t n)
{
    char c = ' ';
    size_t s = 0, r = 1;
    char *temp = (char *)buff;

    while ((s < n) && r && (c != '\n'))
    {

        r = read(fd, &c, 1);

        if (r && (c != '\n'))
        {
            temp[s] = c;
            s++;
        }
    }
    temp[s] = 0;
    if (s == 0 && temp[s] == '\n')
        return -1;

    return s;
}



void exec(char *args){
    int i=0;
    char **str = malloc(sizeof(char **)*5);
    i=parse_arg(args,str);
    myprint(str[0]);
    myprint(str[1]);
    myprint(str[2]);
     myprint(str[3]);

    return ;
}

int shell()
{
    char *buff = malloc(150);
    while (1)
    {
        myprint("argus$ ");
        if (readln(0, buff, 150))
        {

            char **args = malloc(sizeof(char **));
            parse_linha(buff, args);
            if (!strcmp(args[0], "tempo-inactividade") && args[1])
            {
                //tempo inatividade
                myprint("inac\n");
            }
            else if (!strcmp(args[0], "tempo-execucao") && args[1])
            {
                //tempo execucao
                myprint("texec\n");
            }
            else if (!strcmp(args[0], "executar") && args[1])
            {
                //exec
                //myprint(args[1]);
                exec(args[1]);
                
            }
            else if (!strcmp(args[0], "listar"))
            {
                //list
                myprint("list\n");
            }
            else if (!strcmp(args[0], "terminar") && args[1])
            {
                //kill
                myprint("term\n");
            }
            else if (!strcmp(args[0], "historico"))
            {
                //history
                myprint("his\n");
            }
            else if (!strcmp(args[0], "ajuda"))
            {
                
                myprint("\e[1mtempo-inactividade\e[0m segs\n");
                myprint("\e[1mtempo-execucao\e[0m segs\n");
                myprint("\e[1mexecutar\e[0m p1 | p2 ... | pn\n");
                myprint("\e[1mlistar\e[0m\n");
                myprint("\e[1mterminar\e[0m tarefa\n");
                myprint("\e[1mhistorico\e[0m\n");
            }
            else
            {
                myprint("Comando invalido! Insira \e[4majuda\e[24m para obter ajuda.\e[0m");
            }
            free(args);
        }
        else
        {
            myprint("\e[1mComando invalido! Insira \e[4majuda\e[24m para obter ajuda.\e[0m");
        }
        myprint("\n");
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        return shell();
    }
    else
    {
        if (!strcmp(argv[1], "-i"))
        {
            //tempo-inatividade
              myprint("inac\n");
        }
        else if (!strcmp(argv[1], "-m"))
        {
            //tempo execucao
                myprint("texec\n");
          
        }
        else if (!strcmp(argv[1], "-e"))
        {
            //exec
                myprint("exec\n");
        }
        else if (!strcmp(argv[1], "-l"))
        {
            //list))
                 myprint("list\n");
        }
        else if (!strcmp(argv[1], "-t"))
        {
            //kill
              myprint("term\n");
        }
        else if (!strcmp(argv[1], "-r"))
        {
            //history
              myprint("his\n");
        }
        else if (!strcmp(argv[1], "-h"))
        {
            //help))
            myprint("\e[1margus\e[0m segs\n");
             myprint("\e[1m-i\e[0m segs\n");
                myprint("\e[1m-m\e[0m segs\n");
                myprint("\e[1m-e\e[0m p1 | p2 ... | pn\n");
                myprint("\e[1m-l\e[0m\n");
                myprint("\e[1m-t\e[0m tarefa\n");
                myprint("\e[1m-r\e[0m\n");
        }
        else
        {
            myprint("\e[1mComando invalido! Insira \e[4majuda\e[24m para obter ajuda.\e[0m");
        }
        printf("\n");
    }

    return 0;
}
