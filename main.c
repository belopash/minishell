#include "get_next_line.h"
#include "libft.h"

typedef struct        s_fd
{
    int                 input;
    int                 output;
}                       t_fd;


void ft_execute(char **argv, char **env)
{
    //ft_putendl_fd("tut", 1);
    execve(ft_strjoin("/bin/", argv[0]), &argv[0], env);
    //ft_putendl_fd("tut2", 1);
}


char **ft_create_array(t_list *list)
{
    int i;
    char **argv;
    i = 0;
    argv = (char **)malloc(sizeof(char*) * (ft_lstsize(list) + 1));
    while (list)
    {
        argv[i] = list->content;
        list = list->next;
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

void ft_lst_print(t_list *list)
{
    while (list)
    {
        ft_putendl_fd(list->content, 1);
        list = list->next;
    }
}

char *ft_together(t_list *list)
{
    char *var = "";
    while (list)
    {
        var = ft_strjoin(var, list->content);
        var = ft_strjoin(var, " ");
        list = list->next;
    }
    return (var);
}


char *ft_search_env(int *i, char *line, char **env)
{
    char *var;
    int j;
    
    var = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    j = 0;
    while(line[*i] != ' ' && line[*i] != '$' && line[*i] != '"' && line[*i] != '\'' && line[*i] != ';' && line[*i])
    {
        var[j] = line[*i];
        j++;
        (*i)++;
    }
    int k = 0;
 
        while (env[k])
        {
            if (!ft_strncmp(env[k], var, j))
            {
                if (env[k][j] == '=')
                    return(ft_strdup(env[k] + j + 1));
            }
            k++;
        }
    return (ft_strdup(""));
}

int ft_parsing(char *line, char **env)
{
    char *content;
    t_list *list;
    int i;
    int j;
    
    t_fd fd;
    
    fd = (t_fd){0, 1};
    content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    list = NULL;
    i = 0;
    j = 0;
    while(line[i])
    {
        
        if (line[i] == ';')
        {
            if (j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            ft_putendl_fd(ft_together(list), 1);
            //ft_execute(ft_create_array(list), env);
            //system(ft_together(list));
            ft_putendl_fd("///////////////", 1);
            list = NULL;
            i++;
            continue ;
        }
        
        if (line[i] == '|')
        {
            if (j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            ft_putendl_fd(ft_together(list), 1);
            
            
            
            int fd_p[2];
            pipe(fd_p);
            fd.input = fd_p[0];
            fd.output = fd_p[1];
            
            int pid;
            pid = fork();
            if (pid == 0)
            {
                dup2(fd_p[1], 1);
                close(fd_p[0]);
                ft_execute(ft_create_array(list), env);
                close(fd_p[1]);
            }
            else
            {
                dup2(fd_p[0], 0);
                close(fd_p[1]);
                int status;
                wait(&status);
                close(fd_p[0]);
            }
            
            
            
            
            
            //ft_execute(ft_create_array(list), env);
            //system(ft_together(list));
            ft_putendl_fd("///////////////", 1);
            list = NULL;
            i++;
            continue ;
        }
        
        if (line[i] == '>')
        {
            if (j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            ft_putendl_fd(ft_together(list), 1);
            //ft_execute(ft_create_array(list), env);
           // system(ft_together(list));
            ft_putendl_fd("///////////////", 1);
            list = NULL;
            i++;
            continue ;
        }
        
        if (line[i] == '<')
        {
            if (j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            ft_putendl_fd(ft_together(list), 1);
             //ft_execute(ft_create_array(list), env);
            //system(ft_together(list));
            ft_putendl_fd("///////////////", 1);
            list = NULL;
            i++;
            continue ;
        }
        
        
        if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
            {
                i++;
                char *tmp;
                tmp = ft_search_env(&i, line, env);
                while (tmp[0])
                {
                    content[j] = tmp[0];
                    tmp++;
                    j++;
                }
                if ((line[i] == ' ' || line[i] == '\0') && j > 0)
                {
                    content[j] = '\0';
                    ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                    j = 0;
                }
                continue ;
            }
            
        if (line[i] == '"')
        {
            i++;
            while (line[i] != '"' && line[i])
            {
                if (line[i] == '$' && line[i + 1] != '\\' && line[i + 1] != ' ' && line[i + 1] != '\'' && line[i + 1] != '"' && line[i + 1] != '\0')
                {
                    i++;
                    char *tmp;
                    tmp = ft_search_env(&i, line, env);
                    while (tmp[0])
                    {
                        content[j] = tmp[0];
                        tmp++;
                        j++;
                    }
                    continue ;
                }
                if (line[i] == '\\' &&(line[i+1] == 'n'))
                {
                    i += 2;
                    content[j] = '\n';
                    j++;
                    continue ;
                }
                if (line[i] == '\\' && (line[i+1] == '\\' || line[i+1] == '\'' || line[i+1] == '"' || line[i+1] == '$'))
                    i++;
                
                content[j] = line[i];
                j++;
                i++;
            }
            if (line[i] == '"')
                i++;
            if ((line[i] == ' ' || line[i] == '\0') && j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            continue ;
        }
        
        if (line[i] == '\'')
        {
            i++;
            while (line[i] != '\'' && line[i])
            {
                if (line[i] == '\\' &&(line[i+1] == 'n'))
                {
                    i += 2;
                    content[j] = '\n';
                    j++;
                    continue ;
                }
                if (line[i] == '\\' && (line[i+1] == '\\'))
                    i++;
                content[j] = line[i];
                j++;
                i++;
            }
            if (line[i] == '\'')
                i++;
            if ((line[i] == ' ' || line[i] == '\0') && j > 0)
            {
                content[j] = '\0';
                ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
                j = 0;
            }
            continue ;
        }
        
        if (line[i] == ' ')
        {
            i++;
            continue ;
        }
      
        
        if (line[i] == '\\')
            i++;
        
        content[j] = line[i];
        j++;
        i++;
        if ((line[i] == ' ' || line[i] == '\0') && j > 0)
        {
            content[j] = '\0';
            ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
            j = 0;
        }
    }
    //ft_lst_print(list);
    ft_putendl_fd(ft_together(list), 1);
    ft_execute(ft_create_array(list), env);
    //system(ft_together(list));
    
    ft_putendl_fd("///////////////", 1);
    return(0);
}


int ft_minishell(char **env)
{
    char *line;
    line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    
    while(1)
    {
        write(1, "\e[1;34mminishell\e[0m$>", 23);
        int r = get_next_line(0, &line);
        if (r == 0)
        {
            continue;
        }
        if (!ft_strncmp(line, "exit", 4))
        {
            free(line);
            exit(0);
        }
        system(line);
        
        int pid;
        pid = fork();
        if (pid == 0)
        {
            ft_parsing(line, env);
        }
        else
        {
            int status;
            wait(&status);
        }
        
    }
    
    free(line);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    ft_minishell(env);
    return (0);
}
