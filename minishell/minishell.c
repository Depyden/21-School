/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_v23.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lregenar <lregenar@student>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:46:37 by sverkart          #+#    #+#             */
/*   Updated: 2021/04/02 15:16:20 by lregenar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct			s_variable
{
	char				**arvar;
	char				**fvar;
}						t_variable;

typedef struct			s_instruct
{
	char				basis;
	char				**arg;
	char				**name;
	char				**flag;
	char				*instrct;
	char				**spaces;
	struct s_instruct	*next;
}						t_instruct;

typedef struct			s_info
{
	int					*rdr_date;
	char				***date;
	char				**cmd_env;
	char				**cmd_export;
	t_variable			*basis;	
	t_instruct			*instrct;
	t_instruct			**cm_date;
}						t_info;

int						g_n;
int 					g_qm;
int						g_src;
int						g_flag;
int						g_sign;
int						g_point;
int						g_flag_n;
int						g_command_signal;
char					*g_var;
char					*g_line;
char 					**g_env;
char					*g_first;
char					*g_line_pipe;
char					*g_print_err;
char					*g_command_pwd;
char					*g_echo_home;


/*
** _____________________prototype utils_______________________________________
*/																			//
int						get_next_line(char **line);
void					ft_putstr(char *str); 								//
char					*ft_strjoin_free(char *s1, char *s2); 				//
char					*ft_strjoin_non_free(char *s1, char *s2); 			//
int						ft_strlen(char *str);								//
int						ft_strcmp(char *str1, char *str2);					//
char					**ft_split(char const *s, char c); 					//
size_t					ft_strlcpy(char *dest, char *src, size_t size); 	//
char					*ft_strdup(const char *s1); 						//
char					**ft_realloc_mass(char **arr, char *str);			//
int						ft_arrlen(char **str);								//
void					ft_free(char **str);								//
void					ft_putstr_fd(char *s, int fd); 						//
int						ft_sign(char n, char *line);						//	
int						ft_sign_in_arr(char **date, char *sign);			//	
int						ft_isalnum(int n); 									//
int						ft_isalpha(int n); 									//
int						ft_isdigit(int n); 									//
char					*ft_reduction_arr(char *str, int n);				//
void					ft_lstadd_back(t_instruct **lst, t_instruct *new); 	//
char					*ft_substr(char *s,  int start, int len);			//
/*																			//
** _____________________prototype srcs______________________________________//
*/
/*
** _____________________main functions________________________________________
*/
void					clear_malloc();
void					read_input(t_info *inf);
void					ft_error(char *str, t_info *inf);
void					write_in_file(t_instruct *instrct, char *line);
void					errno_error(char *com_name, errno_t error_num);
/*
** _____________________parsing input line____________________________________
*/
void					line_parsing(char *line, t_info *inf);
char					**line_split_into_words(char *line, char ***spaces);
int						line_parse_by_command(char **line, t_info *inf,
						char **spaces);
char					*inplace_env(char *word, char **env, int *j);
char					**parser_env(char **env);
char					*modify_word(char *word, char **env, char **lll);
void					line_check(char **line);
int						line_skip_quote(int i, char *line);
/*
** _____________________initialization of structures and lists________________
*/
void					ft_start_zero(t_info *inf);
void					init_struct_base(t_info *inf);
t_instruct				*init_list_command(t_instruct *new);
//____________________________________________________________________________
/*
** commands (srcs/commands)
*/
void					implement_command(t_instruct *instrct, t_info *inf);
int						cd_command(t_instruct *instrct, t_info *inf);
void					pwd_command(t_instruct *comm);
void					echo_command(t_instruct *instrct);
void					env_command(char **env, t_instruct *instrct);
void					export_command(t_info *inf, t_instruct *instrct);
void					export_com_here(t_info *inf, t_instruct *instrct, int i);
int						export_equal_args(char **arg);
char					**export_add_args(char **env, char *value);
char					**export_change_env(char **env, char *value);
int						export_check_args(char **env, char *value);
void					unset_command(t_info *p, t_instruct *comm);
void					exit_command(t_info *inf, t_instruct *comm);
void					not_found();
void					redirection_command(t_instruct *instrct);
int						ft_atoi(const char *str);
/*
** extarnal command
*/
void					external_command(t_instruct *instrct, char **env);
void					file_command(t_instruct *instrct, char **env);
void					fork_redirect(char *file_name, char *flag, char **date);
void					fork_run(t_instruct *instrct, char **date, char **env);
void					run_forks(int flag, t_instruct *instrct, char **date, char **env);
int						check_stat(t_instruct *instrct, char *name,
						int name_flag);
char					*relative_path(char *path);

/*
** NEW FOR PIPES
*/
char					**external_mass(t_instruct *comm, char **env);
void					run_commands(t_info *inf);
void					clear_mass_com(t_info *inf, int count);
int						size_pipe_in_line(t_instruct *com);
void					init_mass_command(t_info *inf, int count);
t_instruct				*put_param_in_mass(t_instruct *com, t_info *inf);
void					pipe_commands(t_info *inf, int size);
void					pipe_redirect_fork(int file, char **date,
						t_instruct *cm_date, t_info *inf);
int						if_internal_command(t_instruct *instrct);
int						get_fd(t_instruct *instrct);

//=====================================================================================
void		sighandler(int signum);
int			ft_is_a_directory(char *line);
char		*ft_str_slash(char *line, int c);
int			ft_strncmp(char *str1,  char *str2, int n);
int			ft_sign_n(char n, char *line, int j);
//=====================================================================================

//////////// cd_command.c  
static void	change_location(char **current_workdir, t_info *inf) //
{
	int 	i;
	int 	j;
	char	*pwd;
	
	
	j = 0;
	pwd = "OLDPWD";
	//printf("current_workdir = %s\n", current_workdir[0]);
	while(j < 2)
	{
		i = 0;
		while (inf->cmd_env[i] && ft_strcmp(inf->cmd_env[i], pwd) != 0)
			i++;
				
		if (!(inf->cmd_env[i]))
		{
			inf->cmd_env = ft_realloc_mass(inf->cmd_env, pwd);
			inf->cmd_env = ft_realloc_mass(inf->cmd_env, "");
		}
		free(inf->cmd_env[++i]);
		inf->cmd_env[i] = ft_strdup(*current_workdir);
		free(*current_workdir);
		*current_workdir = getcwd(NULL, 10);
		pwd = "PWD";
		j++;
	}
}

static char	*removing(t_instruct *comm)
{
	char	*path;
	int		len;

	path = NULL;
	len = ft_strlen(comm->arg[0]);
	if (ft_strcmp(&comm->arg[0][len - 1], " ") == 0)
	{
		if (!(path = (char *)malloc(sizeof(char) * len)))
		{	
			ft_putstr_fd("Malloc error\n", 0);
			exit (12);
		}
		ft_strlcpy(path, comm->arg[0], len);
	}
	else
		path = ft_strdup(comm->arg[0]);
	return(path);
}

int	cd_error(t_instruct *instrct, errno_t error_num, char **current_workdir, char **path) //
{
	g_print_err = "1";	
	free(*current_workdir);	
	if (error_num != 0)
	{
		free(*path);		
		errno_error(instrct->instrct, error_num);
	}
	else
	{
		free(*path);
		ft_putstr_fd("cd: No such file or directory\n", 0);
	}
	return (1);
}

 int	cleaning(char *current_workdir, char *path, t_instruct *instrct)
{
	free(path);
	free(current_workdir);
	write_in_file(instrct, ft_strdup(""));
	g_print_err = "0";
	return (0);
}

int			cd_command(t_instruct *comm, t_info *p) //
{
	char		*path;
	char		*current_workdir;
	int			arr_len;
	int			i;
	

	i = 0;
	errno = 0;
	arr_len = ft_arrlen(comm->arg);
	current_workdir = getcwd(NULL, 10);
	//printf("current_workdir = %s\n", current_workdir);	
	path = NULL;
	if (arr_len == 0)
	{
		while (p->cmd_env[i] && ft_strcmp(p->cmd_env[i], "HOME") != 0)
			i++;
		path = p->cmd_env[i] ? ft_strdup(p->cmd_env[++i]) : ft_strdup(current_workdir);	
	}
	else if (arr_len > 1)
	{
		return (cd_error(comm, errno, &current_workdir, &path));
	}
	else
		path = removing(comm);
	if (chdir(path) != 0)
		return (cd_error(comm, errno, &current_workdir, &path));
	else
		change_location(&current_workdir, p);
	return (cleaning(current_workdir, path, comm));
}
////////////
////////////  curr_err_command.c  
void	not_found(void) //
{
	char *s;

	s = ft_strdup("command not found: ");
	s = ft_strjoin_free(s, g_print_err);
	ft_putstr(s);
	free(s);
	//g_print_err = "0";
}
////////////
////////////   unset_command.c  
char  **create_new_env(t_info *p, t_instruct *comm) //
{
	int  i;
	int  j;
	char **new;

	if (!(new = (char **)malloc(sizeof(char *) + 1)))
	{	
		ft_putstr_fd("1Problem in Malloc\n", 0);
		exit (12);
	}
	new[0] = NULL;
	i = 0;
	while (p->cmd_env[i])
	{
		j = -1;
		while (comm->arg[++j])
			if (ft_strcmp(p->cmd_env[i], comm->arg[j]) == 0)
				break ;
		if (comm->arg[j] != NULL)
			i += 2;
		else
		{
			new = ft_realloc_mass(new, p->cmd_env[i++]);
			new = ft_realloc_mass(new, p->cmd_env[i++]);
		}
	}
	return (new);
}
/*
** Функция для пересоздания массива переменных окружения env
*/
void		unset_command(t_info *p, t_instruct *comm) // убрал чтобы повторить поведение unset
{
	char	**new;

	new = create_new_env(p, comm);
	ft_free(p->cmd_env);
	p->cmd_env = NULL;
	p->cmd_env = new;
	g_print_err = "0";
}
////////////
////////////  redirect_command.c   
static void	child(t_instruct *comm, int *fd) //
{
	char *my_line;

	dup2(get_fd(comm), fd[1]);
	//printf("777\n");	
	dup2(fd[1], 0);
	close(fd[0]);
	/*
	while (get_next_line(&my_line) > 0) // ???
	{
		//printf("!!!!!!!!!!my_line = %s\n", my_line);
		write(1, my_line, ft_strlen(my_line));
		write(1, "\n", 1);	
		free(my_line);
	}*/
	close(fd[1]);
	signal(SIGINT, exit);
	signal(SIGQUIT, exit);
	exit(1);
}

void	redirection_command(t_instruct *comm) //
{
	int		fd[2];
	pid_t	pid;
	int		status;


	pipe(fd);
	g_command_signal = 2;
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		//exit(1);	
		child(comm, fd);		
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		close(fd[1]);
		close(fd[0]);
		g_command_signal = 0;
	}
}
////////////
////////////  pwd_command.c
static void pwd_implement(t_instruct *comm) //
{
	char *p;
	char *out;
	
	out = ft_strdup("");
	errno = 0;
	if ((p = getcwd(NULL, 10)) == NULL)
		errno_error(comm->instrct, errno);
	else
	{
		free(out);
		out = ft_strdup(p);
		out = ft_strjoin_free(out, "\n");
	}
	free(p);
	write_in_file(comm, out);
}
void	pwd_command(t_instruct *comm) //
{	
	g_print_err = "0";
	if (comm->arg[0] == NULL)
		pwd_implement(comm);
	else
	{
		g_print_err = "1";
		ft_putstr_fd("pwd: Too many arguments\n", 0);
		return ;
	}	
}
////////////
////////////  file_command.c    
char		*new_str(char *old_path, char *curr_pwd, int i) //
{
	char *new_path;

	new_path = ft_strdup(curr_pwd);
	free(curr_pwd);
	new_path = ft_strjoin_free(new_path, "/");
	new_path = ft_strjoin_free(new_path, &old_path[i]);
	return (new_path);
}
char		*double_dot(char *path, char *curr_pwd)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(curr_pwd) - 1;
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
		{
			while (curr_pwd[j] != '/')
				j--;
			curr_pwd[j] = '\0';
			j--;
			i += 3;
			continue ;
		}
		else if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] != '/')
			return (NULL);
		else
			break ;
	}

	return (new_str(path, curr_pwd, i));
}
char		*join_path(char *old_path, char *curr_pwd, int f) // добавление к пути название файла
{
	char *new_path;

	new_path = ft_strdup(curr_pwd);
	//printf("new_path = %s f = %d\n", new_path, f);
	//printf("old_path = %s\n", old_path);
	free(curr_pwd);
	if (f == 1)
		new_path = ft_strjoin_free(new_path, &old_path[1]);
	else
	{
		new_path = ft_strjoin_free(new_path, "/");
		new_path = ft_strjoin_free(new_path, old_path);
	}
	free(old_path);
	//printf("2 new_path = %s f = %d\n", new_path, f);	
	return (new_path);
}

char		*relative_path(char *path) //
{
	char *curr_pwd;
	int flag;
	int j;

	flag = 0;
	j = ft_strlen(path);
	//printf("-l j = %d\n", j);
	//printf("-l path = |%s|\n", path);
	while (path[flag] != '\0' && (path[flag] == '.' || path[flag] == '/'))
	{
		if (path[flag] == '.' && path[flag+1] == '\0')
		{
			//printf("1/1 -l\n");
			g_flag = 1;	
			return (NULL);
		}
		else if (path[flag] == '.' && path[flag+1] == '.' && path[flag+2] == '.')
			break ;
		flag++;
	}
	/*
	if (!(ft_is_a_directory(path)))
	{
		g_flag = 1;
		printf("1/2 -l\n");
		return (NULL);	
	}*/
	flag = 0;
	//printf("1/3 -l\n");
	//printf("1/3 -l path = %s\n", path);
	if (!(curr_pwd = getcwd(NULL, 10)))
		return (NULL);	
	if (path[0] == '.' && path[1] == '.')
		return (double_dot(path, curr_pwd));
	else if (path[0] == '.' && path[1] == '/')
		flag = 1;
	return (join_path(path, curr_pwd, flag));
}
//g_var = (7)17171671(7)171671

// #define ENOENT 2 /* No such file or directory */
int ft_other_error(char *str, int n)
{
	int i;

	if (!str)
		return (n);
	//printf("start n = %d\n", n);
	//printf("start str = %s\n", str);
	i = 0;
	while (str[i] != '\0')
	{
		if ((ft_strcmp(str, "<") == 0) || (ft_strcmp(str, "<<") == 0))
		{
			n = 2;
			g_src = 1;	
		}
		else if (ft_strcmp(str, "<<<") == 0)
		{
			n = 2;
			g_src = -1;				
		}
		i++;
	}
	//printf("end n = %d\n", n);
	return (n);
}

int			check_stat(t_instruct *comm, char *name, int name_flag) //[]
{
	int			fd;
	int			flag;
	struct stat	buff;

	flag = 0;
	//printf("name = %s\n", name);
	if ((fd = open(name, O_RDONLY)) == -1)
	{
		//printf("g_var = %s\n", g_var);
		//printf("name_flag = %d\n", name_flag);	
		if (g_var[0] != '\0')
		{
			if (g_var[0] == 'A' && (g_var[1] == '2' || g_var[1] == 'A'))
			{
				name_flag = 2;
				//printf("name_flag = 2\n");				
				g_var = ft_substr(g_var, 2, ft_strlen(g_var));			
			}
			/*
			else if (g_var[0] == 'B')
			{
				name_flag = 2;
				//g_print_err = "0";
				//printf("B!!!\n");			
				g_var = ft_substr(g_var, 1, ft_strlen(g_var));				
			}*/
			else
			{
				//printf("name_flag = 1\n");
				name_flag = 1;
				g_var = ft_substr(g_var, 1, ft_strlen(g_var));								
			}
		}
		if (name_flag == 1)
		{
			g_print_err = "127";		
			errno = -5;
			//printf("5/1 -l\n");
		}
		else if (name_flag == 2)
		{
			//g_print_err = "127";		
			errno = -5;
			//printf("5/1 -l\n");
		}
		else
		{
			g_print_err = "1";
			//printf("5/2 -l\n");			
		}
		//printf("comm->instrct = %s\n", comm->instrct);		
		//printf("7 -l errno = %d\n", errno);
		//printf("g_var = %s\n", g_var);		
		//if (g_var[0] == '2' || g_var[0] == '3' || g_var[0] == 'A')
		//	g_var = ft_reduction_arr(g_var, 1);
		//printf("g_var = %s\n", g_var);
		//printf("? errno= %d\n", errno);
		//printf("? g_print_err= %s\n", g_print_err);		
		//printf("? name= %s\n", name);
		if (!name && errno == 14)
			errno = 21;
		else if (g_n == 1)
		{
			g_print_err = "0";
			g_n = 2;
		}
		errno = ft_other_error(name, errno);
		errno_error(comm->instrct, errno);
		return (flag = (-1));
	}
	fstat(fd, &buff);
	if ((buff.st_mode & S_IRWXU) == (S_IXUSR) ||
	(buff.st_mode & S_IRWXU) == (S_IXUSR + S_IWUSR) ||
	(buff.st_mode & S_IRWXU) == (S_IXUSR + S_IRUSR) ||
	(buff.st_mode & S_IRWXU) == (S_IXUSR + S_IRUSR + S_IWUSR))
		flag = 1;
	close(fd);
	return (flag);
}
////////////
////////////   external_fork_command.c   
void	run_forks(int flag, t_instruct *comm, char **date, char **env) //
{
	int i;

	i = 0;
	if (flag == 1)
	{
		if (comm->name[i] == NULL)
		{
			fork_run(comm, date, env);
		}
		else if (comm->name[i] != NULL)
		{
			fork_redirect(comm->name[i], comm->flag[i], date);
			i++;
		}
	}
	else
	{
		//printf("errno = %d\n", errno);
		//printf("g_print_err = %s\n", g_print_err);		
		if (g_src == 1) // 2      /* No such file or directory */
		{
			g_src = 0;
			g_print_err = "1";
			errno = 2;
			//errno_error(comm->instrct, errno);
			return ;
		}
		else if (g_src == -1)
		{
			g_src = 0;
			g_print_err = "0";
			errno_error(comm->instrct, errno);
			return ;
		}		
		else
			g_print_err = "127";
		if (g_flag == 1)
		{
			g_flag = 0;
			g_print_err = "126";
		}
		if (flag == 0)
		{
			if (errno == 0)
			{
				g_print_err = "126";	
				errno = 13;							
			}	
			else
				errno = -5;
			errno_error(comm->instrct, errno);
		}
	}
	//printf("8 -l\n");
}
/*
** Запуск дочернего процесса без редиректов
*/
void	fork_run(t_instruct *comm, char **date, char **env) //
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	errno = 0;
	pid = fork();
	//printf("777\n");
	if (pid == 0)
	{
		//printf("1 777\n");
		//printf("date[0] = %s\n", date[1]);
		execve(date[0], date, env); // env был
	}
	else if (pid == -1)
	{
		//printf("2 777\n");
		errno_error(comm->instrct, errno);		
	}
	else
	{
		//printf("3 777\n");	
		wpid = waitpid(pid, &status, WUNTRACED);		
	}	
	if (status && (	g_command_signal == 7))
		g_print_err = "1";
	kill(pid, SIGKILL);
}
/*
** Запуск дочернего процесса с учетом редиректа
*/
void	choose_side(pid_t cpid, int *pipefd, char **date, int fd, int is_right) //
{
	int status;

	close(pipefd[is_right]);
	pipefd[is_right] = fd;
	if (cpid == 0)
	{
		dup2(pipefd[is_right], is_right);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(date[0], date, NULL);
	}
	else
	{
		if (is_right == 1)
			close(pipefd[0]);
		else
			close(pipefd[1]);
		waitpid(cpid, &status, WUNTRACED);
	}
}
void	fork_redirect(char *file_name, char *flag, char **date) //
{
	pid_t	cpid;
	int		fd;
	int		pipefd[2];

	if (ft_strcmp(flag, ">") == 0)
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	else if (ft_strcmp(flag, ">>") == 0)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0664);
	else if (ft_strcmp(flag, "<") == 0)
		fd = open(file_name, O_RDONLY);
	cpid = fork();
	pipe(pipefd);
	if (ft_strcmp(flag, ">") == 0 || ft_strcmp(flag, ">>") == 0)
		choose_side(cpid, pipefd, date, fd, 1);
	else if (ft_strcmp(flag, "<") == 0)
		choose_side(cpid, pipefd, date, fd, 0);
}
////////////
////////////  external_command.c  

static char	*command_path(char *name, char **env)
{
	int		i;
	int		j;
	char	**path;

	//printf("name = |%s|\n", name);	
	if (name[0] == '.' && !name[1])
	{
		g_qm = 1;
		return (name);		
	}
	else if (name[0] == '.' && name[1] == '.' && !name[2])
	{
		g_qm = 2;
		return (name);		
	}
	i = 0;
	while (env[i] && ft_strcmp(env[i], "PATH") != 0)
		i++;
	if (env[i] && env[++i])
	{
		path = ft_split(env[i], ':');
		j = -1;
		while (path[++j])
		{
			//printf("1 - path[j] = %s\n", path[j]);			
			path[j] = ft_strjoin_free(path[j], "/");
			path[j] = ft_strjoin_free(path[j], name);
			//printf("2 - path[j] = %s\n", path[j]);
			//printf("j = %d\n", j);
			if (open(path[j], O_RDONLY) != -1)
			{
				free(name);
				name = ft_strdup(path[j]);
				break ;
			}
		}
		ft_free(path);
	}
	//printf("end command_path = %s\n", name);
	return (name);
}

static char	**arg_creation(t_instruct *comm)
{
	char	**date;
	int		i;

	i = 0;
	if (!(date = (char **)malloc(sizeof(char *) + 1)))
	{	
		ft_putstr_fd("2Problem in Malloc\n", 0);
		exit (12);
	}
	date[0] = NULL;
	date = ft_realloc_mass(date, comm->instrct);
	while (comm->arg[i])
	{

		date = ft_realloc_mass(date, comm->arg[i++]);
		//printf("date[i] = |%s|\n", date[i]);			
	}
	//printf("777\n");
	return (date);
}
static void	current_path(char **date, int *name_flag, char **env)
{
	*name_flag = 0;
	if (date[0][0] == '/')
		*name_flag = 0;
	else if (ft_sign('/', date[0]))
	{
		date[0] = relative_path(date[0]);
		//printf("2 -l\n");
		//printf("3 -l date[0] =%s\n", date[0]);
		//printf("g_flag = %d\n", g_flag);
	}
	else
	{
		//printf("current_path date[0] = %s\n", date[0]);		
		date[0] = command_path(date[0], env);
		//printf("current_path date[0] = %s\n", date[0]);			
		*name_flag = 1;
	}
}

void ft_mb_dir2(char *str)
{
	int i;

	i = 0;
	if (str[0] == '/')
	{
		while (str[i] != '\0')
		{
			if (str[i] != '/')
				break ;
			else if (str[i] == '/' && str[i+1] == ' ' && str[i+2] == '\0')
			{
				g_qm = 3;
				g_flag = 1;
			}				
			i++;
		}
	}
}

void ft_mb_dir(char *str)
{
	int i;

	//printf("str = %s\n", str);
	if (!str)
		return ;
	if (str[0] == '/' || str[0] == '.')
	{
	i = 0;		
		while (str[i] != '\0')
		{
			if (str[i] != '/' && str[i] != '.')
				break ;
			if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '\0')
			{
				g_qm = 3;
				g_flag = 1;		
			}
			else if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '.' && str[i+3] == '\0')
			{
				g_qm = 3;
				g_flag = 1;				
			}
			else if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '.' && str[i+3] == '/' && str[i+4] == ' ' && str[i+5] == '\0')
			{
				g_qm = 3;
				g_flag = 1;				
			}
			else if (str[i] == '.' && str[i+1] == '/' && str[i+2] == '\0')
			{
				g_qm = 3;
				g_flag = 1;				
			}
			else if (str[i] == '.' && str[i+1] == '/' && str[i+2] == ' ' && str[i+3] == '\0')
			{
				g_qm = 3;
				g_flag = 1;				
			}
			else if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '.' && str[i+3] == '.')
				break ;				
			i++;
		}		
	}
	if (g_qm != 3)
		ft_mb_dir2(str);
}

void	external_command(t_instruct *instrct, char **env)
{
	char		**date;
	int			name_flag;
	int			flag;

	//printf("instrct= |%s|\n", instrct->instrct);
	date = arg_creation(instrct);
	//printf("date[0] = |%s|\n", date[0]);
	//printf("date[1] = |%s|\n", date[1]);
	
	current_path(date, &name_flag, env);
	//printf("errno = %d\n", errno);
	ft_mb_dir(date[0]);
	//printf("4 -l date[0] = %d\n", name_flag);
	g_point = 1;
	g_print_err = "0"; //  (ls=0) 
	if (g_qm == 1)
	{
		flag = -1;
		g_qm = 0;
		errno_error(date[0], -1);		
	}
	else if (g_qm == 2)
	{
		flag = -1;
		g_qm = 0;
		errno_error(date[0], -5);		
	}
	else if (g_qm == 3)
	{
		g_qm = 0;
		flag = -1;	
		errno_error(date[0], 21);
	}
	else
		flag = check_stat(instrct, date[0], name_flag);
	//printf("flag = %d\n", flag);
	//printf("8 -l\n");
	run_forks(flag, instrct, date, env);
	errno = 0;
	ft_free(date);
}
char	**external_mass(t_instruct *comm, char **env)
{

	char	**date;
	int		name_flag;
	int		flag;

	date = arg_creation(comm);
	current_path(date, &name_flag, env);
	g_point = 1;
	g_print_err = "0";
	flag = check_stat(comm, date[0], name_flag);
	//g_print_err = "0";	
	return (date);
}
////////////
////////////  new.c  

void	ft_bzero(void *s, size_t n)
{
	char *str;

	str = s;
	while (n)
	{
		n--;
		str[n] = 0;
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*buf;

	if ((n && SIZE_MAX / n < size) || (size && SIZE_MAX / size < n))
		return (NULL);
	if (!(buf = (void *)malloc(size * n)))
		return (NULL);
	ft_bzero(buf, size * n);
	return (buf);
}

int	ft_putchar(int c)
{
	unsigned char uc;

	uc = (unsigned char)c;
	if (!(write(1, &uc, 1)))
		return (0);
	return (1);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
int	free_args(char ***args)
{
	int		i;

	i = 0;
	while (*args && (*args)[i])
		free((*args)[i++]);
	free(*args);
	*args = NULL;
	return (0);
}
static void	insertion_sort(char ***array, int size)
{
	int		i;
	int		i_tmp;
	char	*str_tmp;

	i = 1;
	while (i < size)
	{
		if (ft_strcmp((*array)[i - 1], (*array)[i]) > 0)
		{
			str_tmp = (*array)[i];
			i_tmp = i;
			while (i_tmp > 0 && ft_strcmp((*array)[i_tmp - 1], str_tmp) > 0)
			{
				(*array)[i_tmp] = (*array)[i_tmp - 1];
				i_tmp--;
			}
			(*array)[i_tmp] = str_tmp;
		}
		i++;
	}
}
char	**get_envs(char **envp)
{
	int			i;
	int			j;
	char		**env_vars;

	j = ft_arrlen(envp);
	if (!(env_vars = (char **)ft_calloc(sizeof(char *), j + 100)))
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		env_vars[j] = ft_strdup("");
		env_vars[j] = ft_strjoin_free(env_vars[j], envp[i++]);
		env_vars[j] = ft_strjoin_free(env_vars[j], "=");
		env_vars[j] = ft_strjoin_free(env_vars[j], envp[i++]);
		j++;
	}
	return (env_vars);
}
static void	print_env(char **env)
{
	int		i;
	int		size;
	char	*cur_str;

	i = 0;
	size = ft_arrlen(env);
	g_env = get_envs(env);
	size = ft_arrlen(g_env);
	insertion_sort(&g_env, size);
	while (i < size)
	{
		write(1, "declare -x ", 11);
		cur_str = g_env[i++];
		while (*cur_str)
		{
			ft_putchar(*cur_str);
			if (*cur_str == '=')
				ft_putchar('\"');
			cur_str++;
		}
		write(1, "\"\n", 2);
	}
	free_args(&g_env);
}
void		export_command(t_info *inf, t_instruct *instrct)
{
	int		i;
	int		size;
	char	*tmp;
	int		exp;
	
	i = 0;
	if (!instrct->arg[0])
		return (print_env(inf->cmd_env));
	size = ft_arrlen(instrct->arg);
	if (instrct->arg[0][0] != ' ')
	{
		while (i < size)
		{
			if (!(ft_isalpha(instrct->arg[i][0]) || instrct->arg[i][0] == '_'))
			{
				ft_putstr_fd("minishell: export: not a valid identifier\n", 0);
				g_print_err = "1";
				i++;
				continue;
			}
			export_com_here(inf, instrct, i++);
			g_print_err = "0";
		}
	}
}

////////////
////////////  export_command_help.c   
/*
** Проверяем аргумент в массиве env
*/
int			export_check_args(char **env, char *value)
{
	int		i;
	char	*temp;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	temp = ft_strdup(value);
	ft_putstr_fd("Export_check_args:\n", 0);
	ft_putstr_fd(temp, 0);
	ft_putstr_fd("\n", 0);
	value[i] = '=';
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], temp) == 0)
		{
			free(temp);
			ft_putstr_fd("Return 1\n", 0);
			return (1);
		}
		i++;
	}
	free(temp);
	ft_putstr_fd("Return 0\n", 0);
	return (0);
}
/*
** Меняем существующий аргумент
*/
char		**export_change_env(char **env, char *value)
{
	int		i;
	char	*temp_name;
	char	*temp_value;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	temp_name = ft_strdup(value);
	temp_value = ft_strdup(&value[++i]);
	ft_putstr_fd(temp_name, 0);
	ft_putstr_fd(temp_value, 0);
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i], temp_name) == 0)
		{
			ft_putstr_fd(env[i], 0);
			free(env[++i]);
			env[i] = NULL;
			env[i] = ft_strdup(temp_value);
			ft_putstr_fd(env[i], 0);
			break ;
		}
		i++;
	}
	free(temp_name);
	free(temp_value);
	return (env);
}
/*
** 	Добавляем аргумент в конец env
*/
char		**export_add_args(char **env, char *value)
{
	int		i;
	char	*temp_name;
	char	*temp_value;

	i = 0;
	while (value[i] != '=')
		i++;
	value[i] = '\0';
	temp_name = ft_strdup(value);
	i++;
	temp_value = ft_strdup(&value[i]);
	ft_putstr_fd(temp_name, 0);
	ft_putstr_fd(temp_value, 0);
	ft_putstr_fd("\n", 0);
	env = ft_realloc_mass(env, temp_name);
	env = ft_realloc_mass(env, temp_value);
	free(temp_name);
	free(temp_value);
	return (env);
}
/*
** Проверка на правильный аргумент
*/
int			export_equal_args(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] == '=')
			return (1);
		i++;
	}
	return (0);
}
void		export_com_here(t_info *inf, t_instruct *instrct, int i)
{
	int		j;

	j = 0;
	while (instrct->arg[i][j] && instrct->arg[i][j] != '=')
		j++;
	if (instrct->arg[i][j] != '\0')
	{
		if (export_check_args(inf->cmd_env, instrct->arg[i]) == 1)
		{
			ft_putstr_fd("Export_change_env\n", 0);
			inf->cmd_env = export_change_env(inf->cmd_env, instrct->arg[i]);
		}
		else
		{
			ft_putstr_fd("Export_add_args\n", 0);
			inf->cmd_env = export_add_args(inf->cmd_env, instrct->arg[i]);
		}	
	}
	else
	{
		ft_putstr_fd("ft_realloc_mass\n", 0);
		inf->cmd_export = ft_realloc_mass(inf->cmd_export, instrct->arg[i]);
	}
}
////////////
////////////  command_helper.c   
/*
int		ft_atoi(const char *str)
{
	int s;
	int nbr;

	nbr = 0;
	s = 1;
	while (*str == '\t' || *str == '\v' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
	{
		s = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 10 * nbr + (*str - '0');
		if (nbr < 0 && nbr != -2147483648)
			return (s == -1 ? 0 : -1);
		str++;
	}
	return (nbr * s);
}*/

////////////
////////////  exit_command.c
int		ft_atoi(const char *str)
{
	int		i;
	int		n;
	long	nb;

	n = 1;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			n = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb * n > 2147483647)
			return (-1);
		if (nb * n < -2147483648)
			return (0);
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	return (nb * n);
}
void		exit_command(t_info *inf, t_instruct *comm)
{
	int exit_status;
	
	exit_status = 0;
	if (comm->arg[0] != NULL)
	{
		if (comm->arg[1] != NULL)
		{
			if (ft_isdigit(comm->arg[1][0]) == 0)
			{
				g_print_err = "1";
				ft_putstr("exit\n");
				ft_putstr_fd("exit: too many arguments\n", 0);				
				return ;
			}
			else
			{
				g_print_err = "1";
				ft_putstr("exit\nexit: ");
				ft_putstr(comm->arg[0]);
			}
		}	
		else
			ft_putstr("exit\n");
		exit_status = ft_atoi(comm->arg[0]);			
		if (ft_isdigit(comm->arg[0][0]) == 0)
		{
			ft_putstr("exit: ");
			ft_putstr(comm->arg[0]);				
			ft_putstr_fd(": numeric argument required\n", 0);	
			exit_status = 255;								
		}
		else if ((ft_isdigit(comm->arg[0][0]) == 1) && (ft_atoi(comm->arg[0]) == -1))
		{
			ft_putstr("exit: ");
			ft_putstr(comm->arg[0]);				
			ft_putstr_fd(": numeric argument required\n", 0);	
			exit_status = 255;								
		}		
	}
	else
		ft_putstr("exit\n");
	clear_malloc(inf);
	ft_free(inf->cmd_env);
	exit(exit_status);
}
////////////
////////////  env_command.c
/*
** Функция для печати переменных окружения
*/
void		env_command(char **env, t_instruct *instrct)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup("");
	if (instrct->arg[0] != NULL)
	{
		g_print_err = "127";
		ft_putstr_fd("env: ", 0);
		write(1, instrct->arg[0], ft_strlen(instrct->arg[0]));
		ft_putstr_fd(": No such file or directory\n", 0);
		return ;
	}
	else
		while (env[i])
		{
			line = ft_strjoin_free(line, env[i++]);
			line = ft_strjoin_free(line, "=");
			line = ft_strjoin_free(line, env[i++]);
			line = ft_strjoin_free(line, "\n");
		}
	write_in_file(instrct, line);
	g_print_err = "0";
}
////////////
////////////   echo_command.c  
/*
** Проверяет на наличие -n флагов
*/
static int			check_n(char **str, int *flag)
{
	int		i;

	i = 0;
	*flag = 0;
	while (str[i])
	{
		//printf("str[i] = %s\n", str[i]);
		if (ft_strcmp("-n", str[i]) == 0)
		{
			*flag = 1;
			g_flag_n++;
			i++;
		}
		else
			break ;
	}
	return (i);
}
int ft_echo_i(int i)
{
	//printf(" = %s\n", g_line);
	//printf("g_line[0] = |%c|\n", g_line[0]);
	i = 0;
	while(g_line[i] != '\0')
	{
		if (g_line[i] == '2')
			break ;
		i++;
	}
	if (g_line[i] == '2' && g_line[i] != '\0')
	{
		g_line = ft_reduction_arr(g_line, i);
		g_line = ft_reduction_arr(g_line, i-1);
	}
	i = 0;
	if (g_line[0] == '9' &&  g_line[1] != '2')
	{
		g_line = ft_substr(g_line, 1, ft_strlen(g_line));
		if (g_line[0] == '1')
			g_line = ft_substr(g_line, 1, ft_strlen(g_line));			
		i = -6;		
	}
	else if (g_line[0] == '8' &&  g_line[1] != '2')
	{
		g_line = ft_substr(g_line, 1, ft_strlen(g_line));
		if (g_line[0] == '1')
			g_line = ft_substr(g_line, 1, ft_strlen(g_line));			
		i = -7;		
	}
	else if ((g_line[0] == '2' && g_line[0] == '1') && g_line[1])
	{
		if (g_line[1] == '9' && g_line[0] != '2')
		{
			g_line = ft_substr(g_line, 2, ft_strlen(g_line));
			i = -6;
			printf("7");
		}
		else if (g_line[1] == '8'  && g_line[0] != '2' && g_line[2] != '2')
		{
			g_line = ft_substr(g_line, 2, ft_strlen(g_line));
			i = -7;
			printf("77");
		}
		else
		{
			g_line = ft_substr(g_line, 2, ft_strlen(g_line));
			i = -6;
			printf("777");
		}
	}
	if (i == 0 || g_line[0] == '2')
		g_line = ft_substr(g_line, 1, ft_strlen(g_line));
	//printf("i = %d\n", i);
	//printf(" = %s\n", g_line);
	//printf("после g_line[0] = |%c|\n", g_line[0]);
	//printf("g_print_err = %s\n", g_print_err);
	return (i);
}
void		echo_command(t_instruct *instrct) // echoecho
{
	char	*line;
	char	*part;
	int		flag;
	int		i;
	char 	*tmp;
	int 	m;

	m = 0;
	i = 0;
	i = i + check_n(instrct->arg, &flag);
	//printf("i = %d\n", i);
	line = ft_strdup("");
	//printf("g_print_err = %s\n", g_print_err);
	while (instrct->arg[i])
	{
		//printf("instrct->arg[i] = |%s|\n", instrct->arg[i]);
		//printf("instrct->spaces[i] = |%s|\n", instrct->spaces[i]);
		//printf("i = %d\n", i);
		/*
		if (((m = ft_strcmp(instrct->spaces[i], " ")) == 0) && g_flag_n > 0)// ???
		{
			g_flag_n--;
			free(instrct->spaces[i]);
			instrct->spaces[i] = ft_strdup("");
		}*/
		//printf("1 line = |%s|\n", line);		
		part = ft_strjoin_non_free(instrct->arg[i], instrct->spaces[i]);
		//printf("part = |%s|\n", part);
		line = ft_strjoin_free(line, part);
		//printf("2 line = |%s|\n", line);
		free(part);
		i++;
	}
	//i = 0;
	//printf("g_src = %d\n", g_src);
	//printf("g_point = %d\n", g_point);
	//printf("g_src = %d\n", g_src);
	//printf("end line = |%s|\n", line);
	//printf("g_print_err = %s\n", g_print_err);
	//printf("g_line = %s\n", g_line);
	//printf("g_var = %s\n", g_var);
	//printf("g_line_pipe = %s\n", g_line_pipe);
	/*
	8 - echo $?
	9 - echo
	*/	

	if ((i = ft_strlen(g_line)) > 0)
	{
		i = ft_echo_i(i);
		//printf("g_print_err = %s\n", g_print_err);	
	}
	//printf("i = %d\n", i);
	if (i == -7)
	{
		if (line[0] == '0' && line[1] != ' ')
		{
			//printf("777\n");
			tmp = ft_substr(line, 1, ft_strlen(line));
			tmp = ft_strjoin_non_free(" ", tmp);
		}
		else if (line[0] == '0')
			tmp = ft_substr(line, 1, ft_strlen(line));
		else if (line[0] == '1' && line[1] == '2')
			tmp = ft_substr(line, 3, ft_strlen(line));
		free(line);
		line = ft_strjoin_non_free(g_print_err, tmp);
		//printf("tmp = %s\n", tmp);
		//printf("line = %s\n", line);
		if (tmp)
			free(tmp);
	}
// l ;echo $? ; echo $? ;l; echo $? | echo $? ; ./././././. ; $? ;  $?;  $?; echo $?
	g_print_err = "0";
	//printf("на выходе line = %s\n", line);
	if (flag == 0)
	{
		line = ft_strjoin_free(line, "\n");		
	}
	write_in_file(instrct, line);
}

////////////
////////////   implement_command.c
/* Выполняем требуемую команду, согласно тому, что лежит в instrct */


void	implement_command(t_instruct *instrct, t_info *inf)
{
	//printf("here - 3\n");
	if (ft_strcmp(instrct->instrct, "$?") == 0)
		not_found();	
	else if (ft_strcmp(instrct->instrct, "echo") == 0)
		echo_command(instrct);
	else if (ft_strcmp(instrct->instrct, "cd") == 0)
		cd_command(instrct, inf);
	else if (ft_strcmp(instrct->instrct, "pwd") == 0)
		pwd_command(instrct);
	else if (ft_strcmp(instrct->instrct, "clear") == 0)
	{
		ft_putstr("\033[2J");
		ft_putstr("\033[0;0f");
	}	
	else if (ft_strcmp(instrct->instrct, "exit") == 0)
		exit_command(inf, instrct);
	else if (ft_strcmp(instrct->instrct, "export") == 0)
		export_command(inf, instrct);
	else if (ft_strcmp(instrct->instrct, "unset") == 0)
		unset_command(inf, instrct);
	else if (ft_strcmp(instrct->instrct, "env") == 0)
		env_command(inf->cmd_env, instrct);
	else if (ft_strcmp(instrct->instrct, ">") == 0)
		redirection_command(instrct);
	else
		external_command(instrct, inf->cmd_env);
}

int		if_internal_command(t_instruct *instrct)
{
	return (ft_strcmp(instrct->instrct, "echo") == 0 ||
		ft_strcmp(instrct->instrct, "cd") == 0 ||
		ft_strcmp(instrct->instrct, "pwd") == 0 ||
		ft_strcmp(instrct->instrct, "exit") == 0 ||
		ft_strcmp(instrct->instrct, "export") == 0 ||
		ft_strcmp(instrct->instrct, "unset") == 0 ||
		ft_strcmp(instrct->instrct, "env") == 0 ||
		ft_strcmp(instrct->instrct, "$?") == 0 ||
		ft_strcmp(instrct->instrct, ">") == 0);
}

////////////
//=====================================================================================
//=====================================================================================
//////////// parser_env.c    
/*
** Функция для парсинга переменных окружения в структуру variable
*/
char		**parser_env(char **env)
{
	char	**new_env;
	int		i;
	int		j;
	char	*temp;

	if (!(new_env = (char **)malloc(sizeof(char *) * (ft_arrlen(env) + 1))))
		return (NULL);
	new_env[0] = NULL;
	i = -1;
	while (env[++i])
	{
		j = 0;
		if (g_sign == 1)
			g_sign = 2;	
		while (env[i][j] != '='  && env[i][j] != '\0')
			j++;
		if (env[i][j] == '=')
		{
			//printf("env[%d] = %s\n", i, env[i]);	
			env[i][j] = '\0';
			//printf("i = %d | j = %d\n", i, j);		
			temp = ft_strdup(env[i]);
			new_env = ft_realloc_mass(new_env, temp);
			//printf("1 new_env = %s\n", new_env[i]);
			free(temp);
			temp = ft_strdup(&env[i][++j]);
			new_env = ft_realloc_mass(new_env, temp);
			//printf("2 new_env[i] = %s\n", new_env[i]);
			free(temp);			
		}
		else
		{
			while (env[i][j] != '='  && env[i][j] != '\0')
				j++;
			temp = ft_strdup(env[i]);
			new_env = ft_realloc_mass(new_env, temp);
			free(temp);
		}
	}
	return (new_env);
}
////////////
////////////   modify_word.c
/*
** __________________________________________________________________
** Убирает из слова слеш, заменяет переменные среды и убирает кавычки
** __________________________________________________________________
*/
/*
** Убирает кавычки
** Если в кавычках есть переменная среды, он ее заменяет
*/
char	*delete_quotes(char *oldline, int *i, char **env, char qt) // zxc
{
	char	*line;
	int		j;
	int		m;
	char *tmp;
	int 	l;
	
	j = *i;
	line = ft_strdup(oldline);
	free(oldline);
	//printf("1a |%s|\n", line);
	//printf("qt === |%c|\n", qt);
	
	//if (line[0] != '\'' || line[0] != '\"')
	//	line = ft_str_slash(line, 0);	
	l = (ft_sign_n('\'', line, 0));
	m = (ft_sign_n('\"', line, 0));
	//printf("!!!l == |%d|\n", l);	
	//printf("!!!m == |%d|\n", m);	
	//printf("!!!g_qm == |%d|\n", g_qm);
	// g_qm == 0	- нет кавычек
	// g_qm == -1	- работаем над одинарными кавычками
	// g_qm == -2	- работаем над двойными кавычками
	if (l == m)
		g_qm = 0;
	else if (l == -1 && m != -1)
		g_qm = -2;
	else if (m == -1 && l != -1)
		g_qm = -1;
	else if (m > l|| l > m)
	{
		if (m > l)
			g_qm = -1;		
		else if (l > m)
			g_qm = -2;
	}
	//printf("!!!g_qm == |%d|\n", g_qm);
	line = ft_reduction_arr(line, *i); // убирает первую кавычку
	//printf("line == |%s|\n", line);
	//printf("g_print_err = |%s|\n", g_print_err);
	while (line[j])
	{	
		if (line[j] == '\\' && (line[j + 1] == qt) && (g_qm != -1)) // если \" и работа 
		{
			//printf("1-1 |%s| j = %d\n", line, j);			
			line = ft_reduction_arr(line, j++);
			//j--;
			//printf("1-2 |%s| j = %d\n", line, j);		
		}
		else if (line[j] == '\\' && (line[j + 1] == '\\') && (g_qm != -1)) // если \" и работа 
		{
			//printf("pr-1 |%s| j = %d\n", line, j);
			line = ft_reduction_arr(line, j);
			j++;
			//printf("pr-1 |%s| j = %d\n", line, j);
		}			
		else if (line[j] == '\\' && (line[j + 1] == '$'  && (g_qm != -1)))
		{
			//printf("2-1 |%s| j = %d\n", line, j);			
			line = ft_reduction_arr(line, j++);
			//printf("2-1 |%s| j = %d\n", line, j);				
		}
		else if (line[j] == '$' && (line[j + 1] == '?') && (g_qm != -1))
		{
			//printf("3-1 |%s| j = %d\n", line, j);
			line = inplace_env(line, env, &j);
			//printf("3-1 |%s| j = %d\n", line, j);
		}
		else if (line[j] == '$' && (ft_isalnum(line[j + 1]) && (g_qm != -1)))
		{
			//printf("4-1 |%s| j = %d\n", line, j);
			line = inplace_env(line, env, &j);
			//printf("4-1 |%s| j = %d\n", line, j);
		}
		else if (line[j] == qt)
		{
			//printf("5-1 line|%d| = %c\n line = %s\n", j, qt, line);
			line = ft_reduction_arr(line, j);
			//printf("5-1 line|%d| = %c\n line = %s\n", j, qt, line);
			break ;
		}
		else
			j++;
		//printf("2-4 |%d|\n", j);
	}
	*i = j;
	g_qm = 0;
	//printf("end |%s|\n", line);	
	return (line);
}

int ft_slash(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '/')
		{
			while (line[i] == '/')
				i++;
			if (line[i] == '\0')
				return (0);			
		}
		i++;
	}
	return (1);
}

char *ft_test(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '$' && str[i] != '?')
			return (str);
		else if (str[i] == '$' && str[i+1] == '?')
			g_n = 1;
		i++;
	}
	return (str);
}
char	*modify_word(char *word, char **env, char **lll)
{
	int		i;
	char	*line;
	char	qt;

	i = 0;
	line = ft_strdup(word);
	if ((line[0] == '.' && !line[1]) || (line[0] == '.' && line[1] == '.' && !line[2]))
		g_qm = 40;
	//printf("[[]] start = |%s|\n", line);
	line = ft_test(line);
	//printf("g_print_err = %s\n", g_print_err);
	//printf("[[]] start = |%s|, g_qm = %d\n ", line, g_qm);
	i = 0;	
	if (g_qm != 40)
	{
		while (line[i])
		{
			qt = line[i];
			if (ft_sign(line[i], "\"\'"))
			{
				line = delete_quotes(line, &i, env, qt);			
			}
			else if (line[i] == '\\' && line[i + 1])
			{
				line = ft_reduction_arr(line, i);
				i++;
			}
			else if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
			{
				line = inplace_env(line, env, &i);
			}
			else
				i++;
		}
	}
	else
		g_qm = 0;	
	//printf("[[]] finish = |%c|\n", lll[0][1]);
	if (lll[0][0] == '\'' && lll[0][1] == '\'' && lll[0][2] == '\0')
		line = ft_strdup(" ");
	else if (lll[0][0] == '\"' && lll[0][1] == '\"' && lll[0][2] == '\0')
		line = ft_strdup(" ");		
	else if (!(ft_slash(line)))
		line = ft_strjoin_non_free(line, " ");
	//printf("line == |%s|\n", line);	
	//printf("[[]] start = |%s|, g_qm = %d\n ", line, g_qm);
	return (line);
}
////////////
////////////   line_split_into_words.c  
/*
** ____________________________________________
**           Создает массив пробелов
** ____________________________________________
*/
int			line_count_spaces(char *line, char ***spaces)
{
	int		i;
	char	*word;

	i = 0;	
	while (ft_sign(line[i], " \t"))
		i++;
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
	{	
		ft_putstr_fd("6Problem in Malloc\n", 0);
		exit (12);
	}
	word[i] = '\0';
	i = 0;
	while (ft_sign(line[i], " \t"))
	{
		word[i] = line[i];
		i++;
	}
	*spaces = ft_realloc_mass(*spaces, word);
	free(word);
	return (i);
}
/*
** ____________________________________________
**        Пропускает всё, что в кавычках
** ____________________________________________
**   - Если символ, поданый на вход - кавычка,
**     вернет индекс закрывающей кавычки;
*/
// надо дописать различия между кавычками

int			line_skip_quote(int i, char *line)
{
	char	qt;

	qt = line[i]; // номер элемента строки
	//printf(" = %d\n", i);
	//printf(" = %c\n", qt);
	if (ft_sign(line[i], "\"\'")) // проверка на ' и "
	{
		//printf(" = %d\n", i);
		i++;
		while (line[i])
		{
			//if (line[i] == '\\' && line[i + 1] == '\"')
			//	i = i + 2;
			//else
			if (line[i] == qt)
				return (i);
			else
				i++;
		}
	}
	return (i);
}
int			count_word_len(char *line)
{
	int		i;
	int		j;
	int n = 0;

	i = 0;
	//printf(" start count_word_len = |%s|\n", line);
	while (line[i])
	{
		//printf("1;i = %d\n", i);
		if ((j = line_skip_quote(i, line)) != i) // если различается перва и след кавычка
		{
			//printf("1;i = %d\n", i);			
			//printf("1cw_line = %s j = %d\n", line, j);
			while(i != j)
			{
				if (line[i] == '\\' && line[n+1] != '$')
				{
					i = j;
					//printf("1 here\n");
					break ;
				}
				i++;
			}
			//printf("2cw_line = %s j = %d\n", line, j);
			if (line[i] == '\'' || line[i] == '\"')
			{					
				i = j+1;
			//	printf("2 here\n");
				return (i);								
			}
			//printf("1-2;j = %d\n", j);
		}
		else if (line[i] == '\\' && line[i+1] == '\0')
		{
			//printf("3cw_line  = %s\n", line);
			i++;
			break ;			
		}
		else if (line[i] == '\\')
		{
			i = ((line[i + 1] != '\'') ? i + 2 : i + 1);
			//printf("4cw_line  = %d\n", i);			
		}
		else if (i == 0 && ft_sign(line[i], ";|><"))
		{
			if (ft_sign(line[i], "|"))
				g_print_err = "0";
			i++;
			if (ft_sign(line[i - 1], "><"))
				while (ft_sign(line[i], "><"))
					i++;
			//printf("5cw_line  = %d\n", i);	
			return (i);
		}
		else if (ft_sign(line[i], " \t;|><"))
		{
			//printf("6cw_line  = %d\n", i);			
			return (i);
		}	
		else
			i++;
		//printf("6;i = %d\n", i);
	}
	//printf("FINISH;i = %d\n", i);
	//printf("finish count_word_len = |%s|\n", line);
	return (i);
}

/*
** ____________________________________________
**    Разбивает строку на слова и возвращает
**           двумерный массив слов
** ____________________________________________
*/

char		**line_split_into_words(char *line, char ***spaces)
{
	char	**date;
	char	*word;
	int		i;
	int		len;

	i = 0;
	//printf("line_split_into_words = |%s|\n", line);
	if (!(date = (char **)malloc(sizeof(char *))))
	{	
		ft_putstr_fd("7-1 Problem in Malloc\n", 0);
		exit (12);
	}
	if (!(*spaces = (char **)malloc(sizeof(char *))))
	{	
		ft_putstr_fd("7-2 Problem in Malloc\n", 0);
		exit (12);
	}
	date[0] = NULL;
	*spaces[0] = NULL;
	while (ft_sign(line[i], " \t"))
		i++;
	while (line[i])
	{
		//printf("i = %d\n", i);	
		len = count_word_len(&line[i]);
		//printf("line = %s\n", line);
		//printf("i = %d\n", i);		
		//printf("len = %d\n", len);
		word = ft_substr(line, i, len);
		//printf("word = |%s|\n", word);	
		i += len;
		date = ft_realloc_mass(date, word);
		free(word);
		i += line_count_spaces(&line[i], spaces);
		//printf("i = %d\n", i);	
	}
	free(line);
	return (date);
}
////////////
////////////   line_parsing.c  
/*
** _________________________________________________
**            Парсинг входной строки.
** _________________________________________________
** На выходе лист с командами, флагами и аргументами
*/

int ft_one_or_two_err(char *str)
{
	int i;
	int n;

	//printf("str = %s\n", str);
	if (!str[0])
		return (-1);
	n = 0;
	i = 0;		
	while (str[i] != '\0') // ls; ;
	{
		if (str[i] != ';' && str[i] != '|' && str[i] != ' ')
			n = 1;
		else if (str[i] == ';' && str[i+1] != ';' && n == 0)
			return (1);
		else if (str[i] == ';' && str[i+1] == ';')
			return (2);
		else if (str[i] == '|' && str[i+1] != '|' && n == 0)
			return (3);
		else if (str[i] == ';' && str[i+1] == ' ' && n == 1)
		{
			i++;
			while (str[i] != '\0')
			{
				if (str[i] != ';' && str[i] != '|' && str[i] != ' ')
					return (-1);
				else if (str[i] == '|')
					break ;				
				else if (str[i] == ';')
					return (1);
				i++;
			}
		}			
		else if (str[i] == '|' && str[i+1] != '|' && n == 1)
		{
			if (str[i+1] == '\0')
				return (3);
			i++;
			while (str[i] != '\0')
			{
				if (str[i] != ';' && str[i] != '|' && str[i] != ' ')
					return (-1);
				else if (str[i] == ';')
					break ;
				else if (str[i+1] == '\0')
					return (3);
				i++;
			}
		}
		else if (str[i] == '|' && str[i+1] == '|')
			return (4);
		i++;
	}
	return (-1);
}

void		line_structure_parse(char **date, char **spaces, t_info *inf, int j)
{
	int i;

	i = 0;
	if (j > 0)
	{
		g_print_err = "258";
		inf->basis->arvar = ft_realloc_mass(inf->basis->arvar, "\'");		
		if (j == 1)
			ft_error("syntax error near unexpected token `;'", inf);
		else if (j == 2)
			ft_error("syntax error near unexpected token `;;'", inf);
		else if (j == 3)
			ft_error("syntax error near unexpected token `|'", inf);
		else if (j == 4)
			ft_error("syntax error near unexpected token `||'", inf);
	}
	while (date[i])
	{
		if (ft_strcmp(";", date[i]) == 0)
			inf->basis->fvar = ft_realloc_mass(inf->basis->fvar, date[i++]);
		else if (ft_strcmp("|", date[i]) == 0)
			inf->basis->fvar = ft_realloc_mass(inf->basis->fvar, date[i++]);
		else
			i += line_parse_by_command(&date[i], inf, spaces);
	}
}

int ft_quantity_echo(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'e' && line[i+1] == 'c' && line[i+2] == 'h' && line[i+3] == 'o')
			return (1);
		i++;
	}
	return (0);
}

int ft_check_echo(char *line)
{
	int i;

	i = 0;
	if ((i = ft_sign(';' ,line) == 0) && (i = ft_sign('|' ,line) == 0))
	{
		//printf("not ';' and not '|'\n");
		return (1);
	}
	if ((i = ft_quantity_echo(line)) == 0)
	{
		//printf("not \"echo\"\n");
		return (1);
	}
	while(line[i] != '\0')
	{
		if (line[i] == '$' && line[i+1] == '?')
			return (0);
		i++;
	}
	return (1);
}

char *ft_strecho(char *line)
{
	int i;
	char *str;

	str = ft_strdup("");
	i = 0;
	while(line[i] != '\0')
	{
		if (line[i] == ';')
			str = ft_strjoin_free(str, "1");
		else if (line[i] == '|')
		{
			str = ft_strjoin_free(str, "2");			
		}
		else if (line[i] == '$' && line[i+1] == '?')
		{
			str = ft_strjoin_free(str, "7");
			i++;
		}			
		else if (line[i] == 'e' && line[i+1] == 'c' && line[i+2] == 'h' && line[i+3] == 'o')
		{
			str = ft_strjoin_free(str, "6");
			i += 3;
		}
		i++;
	}
	return (str);
}

/*
4 - $?
8 - echo $?
9 - echo
*/


char *ft_newtmp(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '2')
		{
			if (str[i])
				str = ft_reduction_arr(str, i);			
			if (str[i-1])
				str = ft_reduction_arr(str, i-1);
			if (str[i-2])
				str = ft_reduction_arr(str, i-2);
		}
		i++;
	}
	return (str);
}

char *ft_strecho2(char *str)
{
	int i;
	char *tmp;

	tmp = ft_strdup("");
	i = 0 ;
	while (str[i] != '\0')
	{
		if (str[i] == '6' && str[i+1] == '7')
		{
			tmp = ft_strjoin_free(tmp, "8");
			i++;
			if (str[i+1] == '2' || str[i+1] == '1')
			{
				if (str[i+1] == '1')
					tmp = ft_strjoin_free(tmp, "1");
				else if (str[i+1] == '2')
					tmp = ft_strjoin_free(tmp, "2");
				i++;
			}
		}
		else if (str[i] == '6' && str[i+1] != '7')
			tmp = ft_strjoin_free(tmp, "9");		
		i++;
	}
	//printf("tmp = %s\n", tmp);
	//tmp = ft_newtmp(tmp);
	//printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);
}
//g_var = (7)17171671(7)171671
void ft_code_var(char *str)
{
	int i;

	i = 0;
	//printf("str = %s\n", str);
	g_var = ft_strdup("A");
	while(str[i] != '\0')
	{
		if (str[i] == '6' && str[i+1] == '7')
		{
			g_var = ft_strjoin_free(g_var, "A");			
			i++;			
		}
		else if (str[i] == '7')
			g_var = ft_strjoin_free(g_var, "2");
		else if (str[i] == '1' && str[i+1] == '1')
		{
			g_var = ft_strjoin_free(g_var, "3");
			i++;		
		}
		i++;
	}
	//printf("g_var = %s\n", g_var);	
}

void ft_start_echo(char *str) // p[]
{
	int i;

	i = 0;
	if ((i = ft_check_echo(str)) != 0)
		return ;
	str = ft_strecho(str);
	g_line_pipe = ft_strdup(str);
	//printf("1 str - %s\n", str);	
	ft_code_var(str);



	str = ft_strecho2(str);
	//printf("2 str - %s\n", str);	
	g_line = ft_strdup(str);
	free(str);
}

char	**ft_reduction_arr2(char **str, int n, int m, int len)
{
	char	**arr;
	int		l;

	if (n == m)
		l = 1;
	else
		l = m - n + 1;
	if (!(arr = (char **)malloc(sizeof(char *) * (len + 1 - l))))
		return (NULL);
	l = 0;
	n--;
	while (l != n)
	{
		arr[l] = str[l];
		l++;
	}
	//m--;
	while (str[m])
	{
		arr[l++] = str[m++];
	}
	arr[l] = NULL;
	free(str);
	return (arr);
}
int ft_strlen_arr(char **spr)
{
	int i;

	i = 0;
	while (spr[i] != 0)
		i++;
	return (i);
}
int ft_what_is_it(char *str)
{
	int i;
	
	i = 0;
	//printf("st str = %s\n" , str);	
	while (str[i] != '\0')
	{
		if (str[i] == ';' || str[i] == '|' || str[i] == '\\')	
			return (1);		
		else
			i++;
	}
	//printf("end str = %s\n" , str);	
	return (0);
}
char *ft_correct_str(char *str, int n)
{
	char *tmp;
	
	if (n == 1)
		tmp = ft_strdup(".");
	else if (n == 2)
		tmp = ft_strdup("/");
	else if (n == 2)
		tmp = ft_strdup("..");
	free(str);
	//printf("str = %s\n" , str);	
	return (tmp);
}
char **ft_for_cd_point(char **spr, int i)
{
	int n;
	int m;
	int len;
	n = i;
	char *tmp;
/////

//printf("star\n");
//	printf("spr[%d] = %s\n", i-1, spr[i-1]);
///////
	tmp = ft_strdup(spr[i-1]);
	len = ft_strlen_arr(spr);
	m = 0;
	while (spr[i] != 0)
	{
		if ((ft_strcmp(spr[i], ".") != 0) )
		{
			//printf("1spr[%d] = %s\n", i, spr[i]);
			if (!(ft_what_is_it(spr[i])))  
			{
				if (ft_strcmp(tmp, "..") == 0)
					spr[i] = ft_correct_str(spr[i], 3);
				else
					spr[i] = ft_correct_str(spr[i], 1);
				m = i-1;
			}	
			else
			{
				m = i-1;
				break ;							
			}
		}
		i++;
	}
	if (spr[i] == 0)
		m = i - 1;
	//printf("n = %d | m = %d | ln = %d\n", n, m, len);			
	if (m != 0)
		spr = ft_reduction_arr2(spr, n, m, len);
	/*
	if (ft_strcmp(tmp, "..") == 0)
	{
		free(spr[1]);
		spr[1] = ft_strdup(tmp);
	}*/
	i = 0;
	free(tmp);
	/////////////
	//printf("end\n");
	/*
	while (spr[i] != 0)
	{
		printf("spr[%d] = %s\n", i, spr[i]);
		i++;
	}*/
	//////////////
	return (spr);
}
char **ft_for_cd_slash(char **spr, int i)
{
	int n;
	int m;
	int len;

	len = ft_strlen_arr(spr);
	n = i;
	m = 0;
	while (spr[i] != 0)
	{
		if (ft_strcmp(spr[i], ".") != 0)
		{
			//printf("1spr[%d] = %s\n", i, spr[i]);
			if (!(ft_what_is_it(spr[i])))
			{
				spr[i] = ft_correct_str(spr[i], 2);
				m = i-1;
			}	
			else
			{
				m = i-1;
				break ;							
			}
		}
		i++;
	}
	if (spr[i] == 0)
		m = i - 1;
	if (m != 0)
	{
		spr = ft_reduction_arr2(spr, n, m, len);		
	}
	//printf("n = %d | m = %d | ln = %d\n", n, m, len);
	return (spr);
}
int ft_only_slash(char *str)
{
	int i;
	
	i = 0;
	//printf("st slash = %s\n" , str);	
	while (str[i] != '\0')
	{		
		if (str[i] != '/')	
			return (1);	
		else if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '\0')
			return (0);
		else if (str[i] == '/' && str[i+1] == '.' && str[i+2] == '.' && str[i+3] == '\0')
			return (0);
		else if (str[i] == '/')
			i++;				
		else
			i++;
	}
	//printf("end str slash = %s\n" , str);	
	return (0);
}
int ft_one_or_zero(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '.' && str[i] != '/')
			return (1);
		else if (str[0] != '.')
			return (1);
		else if (str[i] == '.' && str[i+1] == '.' && str[i+2] == '.')
			return (1);		
		i++;
	}
	return (0);
}
int ft_only_point(char *str)
{
	int i;
	
	i = 0;
	//printf("st point = %s\n" , str);
	if (ft_one_or_zero(str) == 1)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == '.' && str[i+1] == '/')
			i++;
		else if (str[i] == '.' && str[i+1] == '/' && str[i+2] == '.')
			i += 2;
		else if (str[i] == '.' && str[i+1] == '.' && str[i+2] == '/')
			i += 2;
		else if (str[i] == '.' && str[i+1] == '.' && str[i+2] == '/' && str[i+3] == '.')
			i += 3;
		else if (str[i] == '.' && str[i+1] == '.' && str[i+2] == '/' && str[i+3] == '.' && str[i+4] == '.')
			i += 4;
		else
			i++;
	}
	//printf("end st point = %s\n" , str);	
	return (0);
}
char **ft_for_cd(char **spr)
{
	int i;

	i = 0;
	if (!spr)
		return (NULL);
	while (spr[i] != 0)
	{
		//printf("start spr[%d] = %s\n", i, spr[i]);
		if (ft_strcmp(spr[i], "cd") == 0)
		{
			if (spr[i+1] == 0)
				return (spr);
			if (spr[i] == 0)
				break ;
			if (ft_only_point(spr[i+1]) == 0)			
			{
				if (ft_strcmp(spr[i+1], "..") != 0)
					spr[i+1] = ft_correct_str(spr[i+1], 1);
				if (spr[i+2] == 0)
					return (spr);
				spr = ft_for_cd_point(spr, i+2);
				//break ;						
			}
			else if (ft_only_slash(spr[i+1]) == 0)			
			{
				spr[i+1] = ft_correct_str(spr[i+1], 2);
				if (spr[i+2] == 0)
					return (spr);
				spr = ft_for_cd_slash(spr, i+2);
				//break ;						
			}		
		}
		i++;
	}
	return (spr);
}
//

/*
пробегает по строке и ищет пробелы
вычисляет сколько надо отрезать и куда добавить
отрезает и рекурсирует и бежит дальше
пропускает кавычки если только те не слитные
*/

char	*ft_reduction_arr1(char *str, int n, int m, int len)
{
	char	*arr;
	int		l;

	l = m - n;
	if (!(arr = (char *)malloc(sizeof(char *) * (len - l))))
		return (NULL);
	l = 0;
	n -= 1;
	while (l != n)
	{
		arr[l] = str[l];
		l++;		
	}
	m--;
	while (str[m])
		arr[l++] = str[m++];
	arr[l] = '\0';
	free(str);
	return (arr);
}
char *ft_space(char *str, int i)
{
	int j;
	int n;
	int len;
	int m;

	len = ft_strlen(str);
	j = 0;
	n = 0;
	m = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (m == 0)
				m = 1;
			else if (m == 1)
				m = 0;
		}
		if (str[i] == ' ' && str[i+1] == ' ' && m == 0)
		{
			j = i+1;
			while (str[i] != '\0' && str[i] == ' ')
				i++;
			n = i;
			str = ft_reduction_arr1(str, j, n, len);
			break ;
		}
		i++;
	}
	//printf("len [%d]\n", len);
	//printf("j[%d]\n", j);
	//printf("n[%d]\n", n);
	//printf("str[%d] = %c\n", i, str[i]);
	//tmp = ft_strdup(str);
	//printf("str = |%s|\n", str);	
	//free(str);
	//printf(" = |%s|\n", str);
	if (len != i)
		str = ft_space(str, 0);
	return (str);
}
int ft_str(char *str)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (k == 1 && str[i] == '\"')
			return (-1);
		else if (k == 2 && str[i] == '\'')
			return (-2);					
		else if (str[i] == '\'')
		{
			if (k == 1)
				k = 0;
			else
				k = 1;
		}
		else if (str[i] == '\"')
		{
			if (k == 2)
				k = 0;
			else
				k = 2;			
		}
		i++;
	}
	return (0);
}
char *ft_quotation_mark(char *str, int i, int len)
{
	int j;
	int n;
	char m;

	j = 0;
	n = 0;
	//printf("len = %d\n", len);
	while(str[i] != '\0')
	{
		if (((((str[i] == '\'' && str[i+1] == '\'') ||\
			(str[i] == '\"' && str[i+1] == '\"')))) && len == 0)
		{
			m = str[i];
			j = i+1;
			while (str[i] != '\0' && str[i] == m)
				i++;
			n = i;
			str = ft_reduction_arr1(str, j, n, ft_strlen(str));
			break ;
		}
		i++;
	}
	//printf("len [%d]\n", len);
	//printf("j[%d]\n", j);
	//printf("n[%d]\n", n);
	//printf("str[%d] = %c\n", i, str[i]);
	//tmp = ft_strdup(str);
	//printf("str = |%s|\n", str);	
	//free(str);
	//printf(" = |%s|\n", str);
	if (ft_strlen(str) != i)
		str = ft_quotation_mark(str, 0, len);
	return (str);
}
char	*ft_reduction_arr3(char *str, int m, int n) 
{
	char	*spr;
	int		l;

	if (!(spr = (char *)malloc(sizeof(char *) * (ft_strlen(str) - 1))))
		return (NULL);
	l = 0;
	while (l != m)
	{
		spr[l] = str[l];
		l++;
	}
	m++;
	while (m != n)
	{
		spr[l] = str[m];
		l++;
		m++;
	}
	n++;
	while(str[n] != '\0')
	{
		spr[l] = str[n];
		l++;
		n++;
	}
	//l++;	
	spr[l] = '\0';
	free(str);
	return (spr);
}
char *ft_qmark2(char *str, int i, int len)
{
	int n;
	int m;
	char ch;

	n = 0;
	m = 0;
	while(str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && len == 0)
		{
			ch = str[i];
			m = i;
			i++;
			while (str[i] != '\0' && str[i] != ch && str[i] != ' ' && str[i] != '\\' && str[i] != '$' )
			{
				if (ch == '\'' && (str[i] == ';' || str[i] == '|'))
					break ;
				i++;
			}	
			if (str[i] == ' ')
				break ;
			else if (str[i] == ch)
				n = i;
			break ;
		}
		i++;
	}
	//printf("m [%d]\n", m);
	//printf("n [%d]\n", n);
	//printf("str[%d] = |%c|\n", i, str[i]);
	//tmp = ft_strdup(str);
	//printf("str = |%s|\n", str);	
	//free(str);
	//printf(" = |%s|\n", str);	
	if (m != 0 && n == 0)
		str = ft_qmark2(str, m+1, len);
	else if (m != 0 && n != 0)
	{
		str = ft_reduction_arr3(str, m, n);
		//m +=3;
		n-=1;
		str = ft_qmark2(str, n, len);
	}	

	return (str);
}
char *ft_replacement(char *str, int i)
{
	char *tmp1;
	char *tmp2;

	while(str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' &&\
			str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 4;
			while (str[i] == ' ' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;				
			if (str[i] == '$' && str[i+1] == '0')
			{
				tmp1 = ft_substr(str, 0, i);
				tmp1 = ft_strjoin_free(tmp1, "MINISHELL");
				tmp2 = ft_substr(str, i+2, ft_strlen(str));
				free(str);
				str = ft_strjoin_free(tmp1, tmp2);
				free(tmp2);
			}
			else if (str[i] == '$' && (ft_isdigit(str[i+1]) == 1))
			{
				tmp1 = ft_substr(str, 0, i);
				tmp2 = ft_substr(str, i+2, ft_strlen(str));
				free(str);
				str = ft_strjoin_free(tmp1, tmp2);
				free(tmp2);
				if (!str[i])
					return (str);			
			}
		}
		i++;
	}
	return (str);
}


char *ft_echo_tld(char *str, int i, int j)
{
	char *tmp1;
	char *tmp2;

	if (j < 0)
		return (str);
	while(str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' &&\
			str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 4;
			while (str[i] == ' ' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;				
			if (str[i] == '~')
			{
				tmp1 = ft_substr(str, 0, i);
				tmp1 = ft_strjoin_free(tmp1, g_echo_home);
				tmp2 = ft_substr(str, i + 1, ft_strlen(str));
				free(str);
				str = ft_strjoin_free(tmp1, tmp2);
				free(tmp2);
				if (!str[i])
					return (str);	
			}
		}
		i++;
	}
	return (str);
}
char *ft_cd_tld(char *str, int i, int j)
{
	char *tmp1;
	char *tmp2;

	if (j < 0)
		return (str);
	while(str[i] != '\0')
	{
		if (str[i] == 'c' && str[i+1] == 'd' && str[i+2] == ' ')
		{
			i += 2;
			while (str[i] == ' ' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;				
			if (str[i] == '~')
			{
				tmp1 = ft_substr(str, 0, i);
				tmp1 = ft_strjoin_free(tmp1, g_echo_home);
				tmp2 = ft_substr(str, i + 1, ft_strlen(str));
				free(str);
				str = ft_strjoin_free(tmp1, tmp2);
				free(tmp2);
				if (!str[i])
					return (str);			
			}
		}
		i++;
	}
	return (str);
}
char *ft_cd_minus(char *str, int i, int j)
{
	char *tmp1;
	char *tmp2;

	if (j < 0)
		return (str);
	while(str[i] != '\0')
	{
		if (str[i] == 'c' && str[i+1] == 'd' && str[i+2] == ' ')
		{
			i += 2;
			while (str[i] == ' ' && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				break ;				
			if (str[i] == '-')
			{
				tmp1 = ft_substr(str, 0, i);
				tmp1 = ft_strjoin_free(tmp1, "$OLDPWD; echo $OLDPWD");
				tmp2 = ft_substr(str, i + 1, ft_strlen(str));
				free(str);
				str = ft_strjoin_free(tmp1, tmp2);
				free(tmp2);
				if (!str[i])
					return (str);			
			}
		}
		i++;
	}
	return (str);
}
int ft_tdl_test1(char *str, char ch, int i)
{
	i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i] != '\0' && str[i] != ch)
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' && str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 4;
			while (str[i] == ' ' && str[i] != '\0' && str[i] != ch && str[i] != '~')
				i++;
			if (str[i] == '~' || str[i] == '\0')
				return (-1);
			else if (str[i] == ch)
				return (i+1);
		}
		i++;
	}
	return (i);
}
int ft_tdl_test2(char *str, char ch, int i, char n)
{
	if (str[i] == '\0' || str[i+1] == '\0')
		return (-1);
	i++;
	while (str[i] != '\0' && str[i] != ch)
	{
		if (str[i] == 'c' && str[i+1] == 'd' && str[i+2] == ' ')
		{
			i += 2;
			while (str[i] == ' ' && str[i] != '\0' &&\
				str[i] != ch && str[i] != n)
				i++;
			if (str[i] == n || str[i] == '\0')
				return (-1);
			else if (str[i] == ch)
				return (i+1);
		}
		i++;
	}
	return (i);
}
int ft_tld_echo(char *str)
{
	int i;
	int k;

//	printf("6\n");
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if ((k = ft_tdl_test1(str, str[i], i)) < 0)
				return (-1);
			else
				i++;
		}
		i++;
	}
	return (k);
}
int ft_tld_cd(char *str, char m)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if ((k = ft_tdl_test2(str, str[i], i, m)) < 0)
				return (-1);
			else
				i++;
		}
		i++;
	}
	return (k);
}

void		line_parsing(char *line, t_info *inf)
{
	char	**date;
	char	**spaces;
	int 	i;

	line = ft_echo_tld(line, 0, ft_tld_echo(line));
	line = ft_cd_tld(line, 0, ft_tld_cd(line, '~'));
	line = ft_cd_minus(line, 0, ft_tld_cd(line, '-'));
	line = ft_space(line, 0);
	line = ft_quotation_mark(line, 0, ft_str(line));
	line = ft_qmark2(line, 0, ft_str(line));
	line = ft_replacement(line, 0);

	//printf("до line = %s\n", line);
	//printf("после len line = |%s|\n", line);
	init_struct_base(inf);  // выделили память
	line_check(&line);
	//printf("date[0] = |%s|\n", date[0]);
	//printf("date[1] = |%s|\n", date[1]);
	//printf("date[2] = |%s|\n", date[2]);
	ft_start_echo(line);
	i = ft_one_or_two_err(line);
	//printf("line = |%s|\n", line);	
	//printf("g_print_err = |%s|\n", g_print_err);	
	if (g_command_signal == 8)
		return ;
	date = line_split_into_words(line, &spaces);
	date = ft_for_cd(date);
	//printf("date[0] = |%s|\n", date[0]);	
	//printf("date[1] = |%s|\n", date[1]);
	//printf("date[2] = |%s|\n", date[2]);		
	line_structure_parse(date, spaces, inf, i);
	//printf("date[0] = |%s|\n", date[0]);
	//printf("date[1] = |%s|\n", date[1]);
	//printf("date[2] = |%s|\n", date[2]);	
	ft_free(date);
	ft_free(spaces);
}
////////////
////////////  line_parse_into_commands.c  

/*
** Проверяет, корректны ли перенаправления и нет ли после них разделителя
*/
void ft_g_red_errr(int z, t_info *inf)
{
	g_print_err = "258";
	if (z == 1)
		ft_error("syntax error near unexpected token `newline'", inf);
	else if (z == 2)
		ft_error("2syntax error near unexpected token `;'", inf);
	else if (z == 3)
		ft_error("syntax error near unexpected token `|'", inf);
	else if (z == 4)
		ft_error("syntax error near unexpected token `>'", inf);
	else if (z == 5)
		ft_error("syntax error near unexpected token `>>'", inf);
	else if (z == 6)
		ft_error("syntax error near unexpected token `<'", inf);	
	else if (z == 7)
		ft_error("syntax error near unexpected token `<<'", inf);
	else if (z == 8)
		ft_error("syntax error near unexpected token `<<<'", inf);
	else if (z == 9)
		ft_error("syntax error near unexpected token `<>'", inf);	
	ft_error("syntax error near unexpected token `<' or(and) `>'", inf);
}
void ft_greater_red_err(char **line, t_info *inf, int i)
{
	i++;
	if (!line[i])
		ft_g_red_errr(1, inf);
	else if (line[i][0] == ';')
		ft_g_red_errr(2, inf);
	else if (line[i][0] == '|')
		ft_g_red_errr(3, inf);
	else if (line[i][0] == '>')
	{
		if (line[i][1] != '>' )
			ft_g_red_errr(4, inf);
		else if (line[i][1] == '>')
			ft_g_red_errr(5, inf);
	}
}
void ft_less_red_err(char **line, t_info *inf, int i)
{
	i++;
	if (!line[i])
		ft_g_red_errr(1, inf);
	else if (line[i][0] == ';')
		ft_g_red_errr(2, inf);
	else if (line[i][0] == '|')
		ft_g_red_errr(3, inf);
	else if (line[i][0] == '<')
	{
		if (line[i][1] != '<')
			ft_g_red_errr(6, inf);
		else if (line[i][1] == '<' && line[i][2] != '<')
			ft_g_red_errr(7, inf);
		else if (line[i][1] == '<' && line[i][2] == '<')
			ft_g_red_errr(8, inf);
	}
}
void ft_equality_plus_minus(char **line, int i, t_info *inf, char ch)
{
	int len;
	int j;

	//printf("777\n");
	j = 0;
	len = ft_strlen(line[i]) - 1;
	while (len > 0)
	{
		if (line[i][len] == ch)
			j++;
		len--;
	}
	//printf("j = %d ch = %c  line[i][j] = %c\n", j, ch, line[i][j]);	
	if (j == 1 && ch == '<')
		j = 6;
	else if ((j == 2 && ch == '<') || (j > 3 && ch == '>'))
		j = 7;
	else if ((j == 2 && ch == '>') || (j == 3 && ch == '>') || (j > 3 && ch == '<'))
		j = 5;
	else if (j == 3 && ch == '<')
		j = 4;
	//printf("j = %d\n", j);	
	ft_g_red_errr(j, inf);
}
void ft_mb_err(char **line, int i, t_info *inf)
{
	int j;
	int flag_minus;
	int flag_plus;

	flag_plus = 0;
	flag_minus = 0;
	j = 0;
	while (line[i][j] != 0)
	{
		if (line[i][j] == '>')
			flag_plus++;
		else if (line[i][j] == '<')
			flag_minus++;
		j++;
	}
	j--;
	//printf("flag_plus = %d flag_minus = %d  line[i][j] = %c\n", flag_plus, flag_minus, line[i][j]);
	if (flag_plus > 0 && flag_minus > 0 && (line[i][j] == '>' || line[i][j] == '<'))
	{
		if (flag_plus != flag_minus)
			ft_g_red_errr(0, inf);
		else if (flag_plus == flag_minus)
			ft_equality_plus_minus(line, i, inf, line[i][j]);
	}
	//printf("777\n");
}
void	error_redirections(char **line, int i, t_info *inf)
{
	int j;

	j = 0;
	if (line[i][0] == '>' && line[i][1] == '\0')
		ft_greater_red_err(line, inf, i);
	else if (line[i][0] == '>' && line[i][1] == '>' && line[i][2] == '\0')
		ft_greater_red_err(line, inf, i);
	else if (line[i][0] == '>' && line[i][1] == '>' && line[i][2] == '>' && line[i][3] == '\0')
		ft_g_red_errr(4, inf);		
	else if (line[i][0] == '>' && line[i][1] == '>' && line[i][2] == '>' && line[i][3] == '>')
	{
		while (line[i][j] != '\0' && line[i][j] == '>')
			j++;		
		if (line[i][j] == '\0'|| line[i][j] == '<')
			ft_g_red_errr(5, inf);
	}
	else if ((ft_strcmp(line[i], "<")  == 0) && line[i][j+1] == '\0')
		ft_less_red_err(line, inf, i);
	else if ((ft_strcmp(line[i], "<<")  == 0) && line[i][j+2] == '\0')
		ft_less_red_err(line, inf, i);
	else if ((ft_strcmp(line[i], "<<<")  == 0) && line[i][j+3] == '\0')
		ft_less_red_err(line, inf, i);
	else if (ft_strcmp(line[i], "<<<<")  == 0)
		ft_g_red_errr(6, inf);
	else if (ft_strcmp(line[i], "<<<<<")  == 0)
		ft_g_red_errr(7, inf);
	else if (line[i][0] == '<' && line[i][1] == '<' && line[i][2] == '<' && line[i][3] == '<' && line[i][4] == '<' && line[i][5] == '<')
	{
		while (line[i][j] != '\0' && line[i][j] == '<')
			j++;		
		if (line[i][j] == '\0' || line[i][j] == '>')
			ft_g_red_errr(8, inf);
	}
	ft_mb_err(line, i, inf);
}
/*
** _______________________________________________________
** Парсинг входного двумерного массива в структуру команды
** _______________________________________________________
*/

void	fill_com_args(char *line, t_instruct *new, char *spaces)
{
	if (!(new->instrct))
	{
		new->instrct = ft_strdup(line);	
		//printf("!!new->instrct= |%s|\n", new->instrct);
		//printf("!!new->spaces = |%s|\n", new->spaces[0]);
		//printf("!!new->arg = |%s|\n", new->arg[0]);
	}
	else
	{
		
		if ((ft_strcmp(new->arg[0], "") == 0) && (ft_strcmp(new->spaces[0], " ") == 0))
		{
			free(new->spaces[0]);
			new->spaces[0] = ft_strdup("");
			new->spaces = ft_realloc_mass(new->spaces, spaces);
			new->arg = ft_realloc_mass(new->arg, line);
			//printf("1\n");
			//printf("1new->spaces = |%s|\n", new->spaces[0]);
			//printf("1new->arg = |%s|\n", new->arg[0]);
		}
		else
		{
			new->spaces = ft_realloc_mass(new->spaces, spaces);
			new->arg = ft_realloc_mass(new->arg, line);
			//printf("3-1new->spaces = |%s|\n", new->spaces[0]);
			//printf("3-1new->arg = |%s|\n", new->arg[0]);
			//printf("3-2new->spaces = |%s|\n", new->spaces[1]);
			//printf("3-2new->arg = |%s|\n", new->arg[1]);
			//printf("-----\n");
		}
	}
}

int		fill_structure(char **line, t_instruct *new, t_info *inf, char **spaces)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((ft_strcmp(";", line[i]) == 0 || ft_strcmp("|", line[i]) == 0))
		{
			//printf("1= fill_structure = %s\n", line[i]);
			new->basis = line[i][0];
			break ;
		}
		if (line[i][0] == '>' || line[i][0] == '<')
		{
			//printf("2/1= fill_structure = %s\n", line[i]);
			new->flag = ft_realloc_mass(new->flag, line[i]);
			error_redirections(line, i++, inf);
			new->name = ft_realloc_mass(new->name, line[i++]);
			//printf("2/2= fill_structure = %s\n", line[i]);
		}
		else
		{
			//printf("3= fill_structure = %s\n", line[i]);
			line[i] = modify_word(line[i], inf->cmd_env, line);
			fill_com_args(line[i], new, spaces[i]);
			i++;
		}
	}
	return (i);
}

int		line_parse_by_command(char **line, t_info *inf, char **spaces)
{
	int			i;
	t_instruct	*new;

	new = NULL;
	if (!(new = init_list_command(new)))
		ft_error("Allocation problem!", inf);
	free(new->instrct);
	new->instrct = NULL;
	//printf("line[0] = %s\n", line[0]);
	//printf("line[1] = %s\n", line[1]);
	//printf("line[2] = %s\n", line[2]);
	i = fill_structure(line, new, inf, spaces);
	if (!(line[i]))
		new->basis = '\0';
	if (!(new->instrct))
	{
		//printf("line[%d] = %s line[%d] = %s\n", i, line[i], i-1, line[i-1]);
		new->instrct = ft_strdup(">");
	}
	inf->basis->arvar = ft_realloc_mass(inf->basis->arvar, new->instrct);
	ft_lstadd_back(&(inf->instrct), new);
	//printf("echo 7 >> p|echo 6 >> p\n");
	//printf("line[0] = %s\n", line[0]);
	//printf("line[1] = %s\n", line[1]);
	//printf("line[2] = %s\n", line[2]);
	return (i);
}
////////////
////////////  line_check.c   
int ft_is_a_directory(char *line)
{
	int		fl;	
	int		i;

	i = 0;
	fl = 0;	
	while (line[i] == ' ')
		i++;
	if (line[i] == '/' || line[i] == '.')
	{
		while (line[i] != '\0')
		{
			if ((line[i] == '.') && (line[i+1] == '.') && (line[i+2] == '.'))
			{
				fl = 7;
				break ;				
			}		
			while (line[i] == '.')
				i++;
			while (line[i] == '/')
				i++;				
			if (line[i] != '/' && line[i] != '.' && line[i] != '\0' && (line[i] != ' '))
			{
				fl = 7;
				break ;
			}
			while (((line[i] == '.') && (line[i+1] == '/')) || ((line[i] == '/') && (line[i+1] == '.')))
				i += 2;
			while (((line[i] == '.') && (line[i+1] == '.') && (line[i+2] == '/')) || ((line[i] == '.') && (line[i+1] == '.') && (line[i+2] == '/')))
				i += 3;
			if ((line[i] == '.') && (line[i+1] == '.') && (line[i+2] == '.'))
			{
				fl = 7;
				break ;				
			}			
			if ((line[i] == '\0') ||  (line[i] == ' '))
				break ;
			i++;
		}
	}
	if (fl == 0)
		return (1);
	return (0);
}

/*
** ____________________________________________
**  Проверяет строку на закрытие кавычек или \
** ____________________________________________
**   - Если в строке есть незакрытая кавычка или
**     пустой слэш, то читаем дальше
**
**         line_check - основная функция
** - Создаем процесс-ребенок, в нем проходимся
**   по строке (through_line), если встречаем
**   незакрытую кавычку, читаем дальше (if_not_closed),
**   передаем дописанную строку родителю
** - В родителе принимаем новую строку (read_new_line)
*/

void		if_not_closed(int *i, char **newline, char *message, char symb)
{
	char *line;
	char *new;

	if (!(symb))
	{
		signal(SIGINT, exit);
		signal(SIGQUIT, exit);				
		ft_putstr(message);
		ft_putstr("> ");

		get_next_line(&line);
		//printf("line = |%s| strlen=%d\n", line, ft_strlen(line));		
		new = ft_strdup(*newline);
		//printf("line = |%s| strlen=%d\n", new, ft_strlen(new));
		free(*newline);
		//free(newline);	
		*newline = ft_strjoin_non_free(new, line);
		//printf("newline = |%p|\n", newline);
		free(line);
		free(new);
		//printf("g_flag = %d\n", g_flag);
		if (g_flag == 3)
		{
			g_flag = 0;
			*i = -1;			
		}
	}
}

char *ft_str_slash(char *line, int c) // откорректировать с какого именно момента будет считываться слеш
{	
	char *str;
	int len;	
	int i;
	int j;

	i = c;
	//printf("ft_str_slash = |%s|\n", line);
	len = 0;	
	while (line[c] != '\"' && line[c] != '\0')
	{
		if (line[c] == '\\' && line[c+1] == '\\')
		{
			c++;
			len++;
		}
		c++;
	}
	len = ft_strlen(line) - len;
	//printf("len = %d\n", len);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len] = '\0';
	//printf("line = |%s|\n", line);
	j = 0;
	while(i > j)
	{
		str[j] = line[j];
		j++;
	}
	while (c > j)
	{
		if ((line[i] == '\\') && (line[i+1] == '\\'))
			i++;
		str[j] = line[i];
		j++;
		i++;
	}
	while (len > j)
	{
		str[j] = line[i];
		j++;
		i++;
	}
	free(line);
	//printf("FINISH ft_str_slash= %s\n", str);
	return (str);
}
int	ft_sign_n(char n, char *line, int j) //
{
	while (line[j])
	{
		if (line[j] == n)
			return (j);
		j++;
	}
	return (-1);
}
int ft_quantity(char n, char *line, int i)
{
	int j;

	j = 0;
	while (line[i])
	{
		if (line[i] == n)
			j++;
		i++;
	}
	return (j);
}
char *ft_newline(char *line)
{
	int k = 0;
	int m;
	int n;
	int i;
	int j;
	//int fl = ft_strlen(line);

	n = ft_sign_n('\'', line, 0);
	//printf("одинарная кавычка эл n= %d\n", n);
	m = ft_sign_n('\"', line, 0);
	//printf("двойная кавычка эл m= %d\n", m);
	i = ft_quantity('\'', line, 0);
	//printf("ft_quantity i = %d\n", i);
	j = ft_quantity('\"', line, 0);
	//printf("ft_quantity j = %d\n", j);
	if (n == -1 && m != -1)
	{
		m++;
		//line = ft_str_slash(line, m);
		//printf("нет одинарных кавычек, но есть двойная\nm=%d\n", m);
		if (j % 2 != 0 && j == 1)
		{	
			line = ft_strjoin_non_free(line, "\"");
			//printf("надо дописать двойную кавычку\n");			
		}	
	}
	else if (m == -1 && n != -1)
	{
		//printf("нет двойных кавычек, но есть одинарная\nn=%d\n", n);
		if (i % 2 != 0)
		{
			line = ft_strjoin_non_free(line, "\'");
			//printf("надо дописать одинарную кавычку\n");			
		}
	}
	else if (m > n || n > m)
	{
		//printf("1 - зашел\n");
		while(line[k] != '\0')
		{
			if (line[k] == '\'')
			{
				//printf("2 - зашел\n");
				k++;
				while (line[k] != '\'' && line[k] != '\0')
					k++;
				if (line[k] == '\0')
				{
					line = ft_strjoin_non_free(line, "\'");
					//printf("надо дописать одинарную кавычку\n");
					break ;					
				}
			}
			else if (line[k] == '\"')
			{
				//printf("3 - зашел\n");
				k++;
				//line = ft_str_slash(line, k);		
				while (line[k] != '\"' && line[k] != '\0')
					k++;
				if (line[k] == '\0')
				{
					line = ft_strjoin_non_free(line, "\"");
					//printf("надо дописать двойную кавычку\n");
					break ;	
				}
			}
			k++;
		}
	}
	return (line);
}
char *ft_echo_n(char *str, int i)
{
	char *tmp;
	int j;

	while (str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' && str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 4;
			while (str[i] == ' ')
				i++;
			if (str[i] == '-' && str[i+1] == 'n' && (str[i+2] == 'n' || str[i+2] == ' '))
			{
				tmp = ft_substr(str, 0, i + 2);
				i += 1;
				j = i;
				while (str[i] == 'n')
					i++;
				str = ft_substr(str, i, ft_strlen(str));
				str = ft_strjoin_free(tmp, str);
				//printf("str = |%s|\n", str);		
				if (str[j] != '\0')
					str = ft_echo_n(str, j);
				break ;
			}
		}
		i++;
	}
	return (str);
}
int ft_uuu(char *str)
{
	int i;
	int j;
	int n;

	n = 0;
	j = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			j = -1;
		else if (str[i] == ' ' && str[i+1] == '-' && str[i+2] == '-' && str[i+3] == 'n')
			n = -1;
		i++;
	}
	if (j < 0 && n < 0)
		return (1);
	return (0);
}
char *ft_space_n(char *str, int i)
{
	char *tmp;
	int j;

	while (str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' && str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 5;
			if (str[i] == '-' && str[i+1] == 'n')
			{
				while (str[i] != '\0' && str[i] != '|' && str[i] != ';')
					i++;
				j = i;
				i--;									
				while (str[i] == ' ')
					i--;
				tmp = ft_substr(str, 0, i+1);
				str = ft_substr(str, j, ft_strlen(str));			
				str = ft_strjoin_free(tmp, str);
				if (str[i] != '\0')
					str = ft_space_n(str, i);
				break ;
			}
		}
		i++;
	}
	return (str);
}
char *ft_double_n(char *str, int i)
{
	char *tmp;
	int j;
	int m;

	m = -1;
	while (str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' && str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 5;
			if (str[i] == '-' && str[i+1] == 'n')
			{
				i += 2;
				j = i+1;
				while (str[i] != '\0' && str[i] != ';' && str[i] != '|' && (str[i] == ' ' || str[i] == '-' || str[i] == 'n'))
				{
					if (str[i] == '-' && str[i+1] == 'n' && str[i+2] != ' ' )
					{
						m = i;
						i++;
						while (str[i] == 'n')
							i++;
						if (str[i] != ' ' && str[i] != '\0' && str[i] != ';' && str[i] != '|')
							i = m;
						break ;
					}
					else if (str[i] == '-' && str[i+1] == 'n' && str[i+2] == ' ' )
					{
						i++;
						while (str[i] == 'n' || str[i] == '-' || str[i] == ' ')
							i++;
						i--;
						break ;
					}
					else if (str[i] == '-' && str[i+1] != 'n')
					{
						i--;
						break ;
					}
					else if (str[i] == 'n')
					{
						i--;
						break ;
					}
					i++;
				}
				if (str[i] == '|')
					tmp = ft_substr(str, 0, j-1);
				else
					tmp = ft_substr(str, 0, j); // ???	
				str = ft_substr(str, i, ft_strlen(str));
				str = ft_strjoin_free(tmp, str);	
				if (str[j-1] != '\0')
					str = ft_double_n(str, j);
				break ;
			}
		}
		i++;
	}
	return (str);
}
int ft_nnn(char *str, int i)
{
	while(str[i] != '\0')
	{
		if (str[i] == 'e' && str[i+1] == 'c' && str[i+2] == 'h' && str[i+3] == 'o' && str[i+4] == ' ')
		{
			i += 4;		
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				break ;					
			if (str[i] == '-' && str[i+1] == 'n')
				return (1);
		}
		i++;
	}
	return (0);
}

char		*through_line(char *line) // qwerty
{
	int j;
	int		i;
	char	*newline;
	char	*tmp;

	newline = ft_strdup(line);
	//printf("START_newline = |%s|\n", newline);
	newline = ft_newline(newline);
	i = 0;
	
	if ((j = ft_uuu(newline)) == 0)
	{
		if ((j = ft_nnn(newline, i)) > 0)
		{
			//printf("1 newline = %s\n", newline);
			newline = ft_echo_n(newline, i);
			//printf("2 newline = %s\n", newline);
			newline = ft_space_n(newline, i);
			//printf("3 newline = %s\n", newline);
			newline = ft_double_n(newline, i);
			//printf("4 newline = %s\n", newline);			
		}
	}
	//printf("FINAL_newline = |%s|\n", newline);
	while (newline[i])
	{
		if (newline[i] == '\\' && !(newline[i + 1]))
			if_not_closed(&i, &newline, "", '\0');
		else if (newline[i] == '\\' && (newline[i + 1] == '\\'))
			i++;
		/*
		else if (newline[i] == '|') 
		{
			//while (newline[++i] == ' ' || newline[++i] == '\t')
			i++;
			g_flag = 3;					
			if_not_closed(&i, &newline, "pipe", newline[i]);
		}*/
		i++;
	}
	//printf("g_print_err = |%s|\n", g_print_err);
	free(line);
	//printf("???newline = |%s|\n", newline);
	return (newline);
}

void		read_new_line(char **line, int *fd, int in)
{
	char	*stack;
	int		ret;
	char	buffer[12];

	dup2(fd[0], 0);
	close(fd[1]);
	free(*line);
	// = |%s|\n", *line);
	if (g_command_signal != 8)
	{
		stack = ft_strdup("");
		while ((ret = read(0, buffer, 10)) > 0)
		{
			buffer[ret] = '\0';
			stack = ft_strjoin_free(stack, buffer);
			if (ft_sign('\n', stack))
				break ;
		}
		//printf("ft_strlen(stack) = |%d|\n", ft_strlen(stack));		
		*line = ft_substr(stack, 0, ft_strlen(stack) - 1);
		//printf("read_new_line = |%s| strlen = %d\n", *line, ft_strlen(*line));		
		free(stack);
	}
	//printf("read_new_line = |%s|\n", *line);
	close(fd[0]);
	dup2(in, STDIN_FILENO);
	close(in);
}

void		line_check(char **line)
{
	char	*newline;
	pid_t	pid;
	int		status;
	int		fd[2];
	int		in;	
	//Функция dup() возвращает новый дескриптор файла, который полностью описывает (т.е. дуб­лирует) состояние файла,
	//связанного с handle. В случае успеха возвращается неотрицательная величина, а в противном случае —1.
	in = dup(STDIN_FILENO); // STDIN_FILENO -это стандартный номер дескриптора входного файла по умолчанию, равный 0 .
	pipe(fd); // канал
	pid = fork(); // процесс
	g_command_signal = 7;
	//printf("g_print_err = |%s|\n", g_print_err);
	if (pid == 0)
	{		
		newline = through_line(*line);
		//printf("newline = |%s|\n", newline);
		newline = ft_strjoin_free(newline, "\n");
		//printf("newline = |%s|\n", newline);
		dup2(fd[1], 1);
		close(fd[0]);
		ft_putstr(newline);
		//printf("newline = |%s|\n", newline);
		close(fd[1]);
		//free(newline);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		read_new_line(line, fd, in);
	}
}

////////////
////////////  line_inplace_env.c  

/*
** _________________________________________________________
** Расшифровывает переменную среды (из имени в ее значение);
** _________________________________________________________
** inplace_env - функция по расшифровке переменной среды
** - выделяет из строки имя переменной
** - отделяет конец строки (после переменной)
** - вызывает create_string
** - добавляет к полученной строке конец
**
** create_string - вспомогательная функция
** - находит в env соответствующее значение
** - записывает в строку ее начало (до переменной среды)
** - добавляет в нее расшифрованную переменную
*/

char		*create_string(int *j, char *word, char *name, char **env)
{
	int		tmp_j;
	char	*value;
	int		k;
	char	flag;

	k = 0;
	tmp_j = 0;
	flag = name[0];
	
	while (env[k] && ft_strcmp(env[k], name) != 0)
		k++;
	//printf("? env[%d] = %s\n", k, env[k]);
	free(name);
	if (!(value = (char *)malloc(sizeof(char) * (*j + 1))))
		return (NULL);
	while (tmp_j != *j)
	{
		value[tmp_j] = word[tmp_j];
		tmp_j++;
	}
	value[tmp_j] = '\0';
	//printf("? value = %s\n", value);		
	if (flag == '?')
	{
		value = ft_strjoin_free(value, g_print_err);
		//printf("2/1 - value = %s\n", value);				
	}
	else if (env[k] && env[++k])
	{
		value = ft_strjoin_free(value, env[k]);
		//printf("2/2 - value = %s\n", value);
	}
	return (value);
}

char		*inplace_env(char *word, char **env, int *j)
{
	int		k;
	char	*name;
	char	*end;
	char	flag;
	char	*value;

	//printf("word = %s\n", word);
	//printf("here\n");
	k = 0;
	name = ft_strdup(word + *j + 1);
	//printf("name = %s\n", name);
	flag = name[0];
	if (name[k] == '?')
		k++;
	else
		while (ft_isalnum(name[k]))
			k++;
	end = ft_strdup(name + k);
	//printf("end = %s\n", end);
	name[k] = '\0';
	value = create_string(j, word, name, env);
	//printf("value = %s\n", value);
	*j = ft_strlen(value);
	value = ft_strjoin_free(value, end);
	if (g_n == 1)
		g_first = value;
	//printf("end value = %s\n", value);
	//printf("g_pr= %s\n", g_print_err);
	//printf("g_n= %d\n", g_n);
	free(word);
	free(end);
	return (value);
}
////////////

void	clear_malloc(t_info *inf)
{
	t_instruct		*temp_com;

	g_point = 0;
	if (inf->instrct != NULL)
		while (inf->instrct)
		{
			temp_com = inf->instrct->next;
			ft_free(inf->instrct->name);
			ft_free(inf->instrct->flag);
			ft_free(inf->instrct->arg);
			ft_free(inf->instrct->spaces);
			free(inf->instrct->instrct);
			free(inf->instrct);
			inf->instrct = temp_com;
		}
	if (inf->basis != NULL)
	{
		ft_free(inf->basis->fvar);
		ft_free(inf->basis->arvar);
		free(inf->basis);
	}
}

void		ft_error(char *str, t_info *inf)
{
	//ft_putstr("Error: ");
	ft_putstr(str);
	ft_putstr("\n");
	clear_malloc(inf);
	read_input(inf);
}

/*
** Сообщение об ошибке от errno
*/
//  strerror(2)) =  No such file or directory
//  strerror(5)) =  command not found
//  strerror(14)) =  Bad address
//

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ch;
	char			c;

	c = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		ch = -n;
	}
	else
		ch = n;
	if (ch >= 10)
		ft_putnbr_fd(ch / 10, fd);
	c = (ch % 10) + 48;
	write(fd, &c, 1);
}

void		errno_error(char *com_name, errno_t error_num) //err
{
	char	*message;
	int i;

	//printf("7/1 -l\n");
	//printf("g_flag = %d\n", g_flag);
	//printf("com_name = %s\n", com_name);
	//printf("error_num = %d\n", error_num);
	if (com_name[0] == '0')
		message = ft_strjoin_non_free(g_print_err, ": ");
	else
		message = ft_strjoin_non_free(com_name, ": ");
	if (error_num == -5)
	{
		message = ft_strjoin_free(message, "command not found");
		//printf("g_print_err = |%s|\n", g_print_err);	
		//error_num = ft_putnbr_fd(g_print_err, 1);
	}
	else if (error_num == -1)
	{
		message = ft_strjoin_free(message, "filename argument required\n.: usage: . filename [arguments]");
		//printf("g_print_err = |%s|\n", g_print_err);	
		//error_num = ft_putnbr_fd(g_print_err, 1);
	}
	else if (g_flag == 1)
	{
		message = ft_strjoin_free(message, "is a directory");
	}
	else
		message = ft_strjoin_free(message, (char *)strerror(error_num));
	//printf("g_print_err = |%s|\n", g_print_err);
	message = ft_strjoin_free(message, "\n");
	ft_putstr_fd(message, 0);
	//g_print_err = "0"; // ?
	//errno = 0;
	//if (g_flag == 2)
	//	com_name = ft_strjoin_free(com_name, " ");
	free(message);
}


/*
** иницилизирует структуру variable (имя команды и разделитель)
*/

void		init_struct_base(t_info *inf)
{
	if (!(inf->basis = (t_variable *)malloc(sizeof(t_variable))) || !(inf->basis->fvar = (char **)malloc(sizeof(char *) + 1)) ||
		!(inf->basis->arvar = (char **)malloc(sizeof(char *) + 1)))
		ft_error("9Problem in malloc", inf);
	inf->basis->fvar[0] = NULL;
	inf->basis->arvar[0] = NULL;
}

/*
** иницилизирует структуру command (список)
*/

t_instruct	*init_list_command(t_instruct *new)
{
	if (!(new = (t_instruct *)malloc(sizeof(t_instruct))) ||
		!(new->name = (char **)malloc(sizeof(char *) + 1)) ||
		!(new->flag = (char **)malloc(sizeof(char *) + 1)) ||
		!(new->arg = (char **)malloc(sizeof(char *) + 1)) ||
		!(new->spaces = (char **)malloc(sizeof(char *) + 1)))
	{	
		ft_putstr_fd("10Problem in Malloc\n", 0);
		exit (12);
	}
	new->instrct = ft_strdup("");
	new->arg[0] = NULL;
	new->spaces[0] = NULL;
	new->name[0] = NULL;
	new->flag[0] = NULL;
	new->next = NULL;
	return (new);
}

int			size_pipe_in_line(t_instruct *com)
{
	int			size;
	t_instruct	*new;

	size = 1;
	new = com;
	while (new->basis == '|')
	{
		//printf("size = %d\n", size);		
		size++;
		if (new->next == NULL)
			break ;
		new = new->next;

	}
	return (size);
}

void		init_mass_command(t_info *inf, int count)
{
	inf->date = (char ***)malloc(sizeof(char **) * count);
	inf->cm_date = (t_instruct **)malloc(sizeof(t_instruct *) * count);
	inf->rdr_date = (int *)malloc(sizeof(int) * (count));
	if (!inf->date || !inf->cm_date || !inf->rdr_date)
	{
		errno_error("11Problem in Malloc", errno);
		exit(12);
	}
}

t_instruct	*put_param_in_mass(t_instruct *com, t_info *inf)
{
	int i;
	int flag;

	i = 0;
	flag = 1;
	while (flag == 1)
	{
		if (if_internal_command(com) == 0)
		{
			inf->date[i] = external_mass(com, inf->cmd_env);
			inf->cm_date[i] = NULL;
		}
		else
		{
			inf->date[i] = NULL;
			inf->cm_date[i] = com;
		}
		inf->rdr_date[i++] = get_fd(com);
		flag = 0;
		if (com->basis == '|')
		{
			g_print_err = "0";
			flag = 1;		
		}
		com = com->next;
	}
	//g_print_err = "0";
	//printf("g_print_err = %s\n", g_print_err);
	return (com);
}

void		clear_mass_com(t_info *inf, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (inf->date[i] != NULL)
			ft_free(inf->date[i]);
		else
			free(inf->date[i]);
		i++;
	}
	free(inf->date);
	free(inf->cm_date);
	free(inf->rdr_date);
}

void	run_commands(t_info *inf)
{
	int			count;
	t_instruct	*com;

	//printf("here - 1\n");	
	com = inf->instrct;
	if (com == NULL)
		return ;
	while (com)
	{
		if (com->basis == '|')
		{
			//g_print_err = "0";
			count = size_pipe_in_line(com);
			init_mass_command(inf, count);
			com = put_param_in_mass(com, inf);
			pipe_commands(inf, count);
			clear_mass_com(inf, count);
			
		}
		else
		{
			//printf("hesdfsdre - 2\n");
			//printf("inf->instrct = %p\n", com);
			implement_command(com, inf);
			com = com->next;
		}
	}

}

void	pipe_redirect_fork(int file, char **date, t_instruct *cm_date, t_info *inf)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	pid = fork();
	//printf("hi - 1\n");
	if (pid < 0)
	{
		errno_error("FORK", errno);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		//printf("hi - 2\n");
		dup2(file, fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (date != NULL)
			execve(date[0], date, inf->cmd_env);
		else
		{
			
			implement_command(cm_date, inf);
		}
		//printf("hi - 3\n");
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, &status, WUNTRACED);
	exit(0);
	//printf("hi - 4\n");
}

void	child_pipe_command(int prev_pipe, t_info *inf, int i, int *fd)
{
	
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (inf->rdr_date[i] != 0)
		pipe_redirect_fork(inf->rdr_date[i], inf->date[i], inf->cm_date[i], inf);		
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (inf->date[i] != NULL)
		execve(inf->date[i][0], inf->date[i], NULL);
	else
	{
		implement_command(inf->cm_date[i], inf);		
	}
	//printf("here - 3\n");
	g_line_pipe = "";
	exit(EXIT_SUCCESS);
}

void	pipe_commands(t_info *inf, int size)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	int		i;
	int		prev_pipe;

	i = 0;
	//printf("g_line_pipe = %s\n", g_line_pipe);
	if (g_line_pipe)
	{
		while (g_line_pipe[i] != '2' && g_line_pipe[i] != '\0' )
			i++;
		if (g_line_pipe[i] == '2' && g_line_pipe[i+1] == '1')
		{
			g_print_err = "127";
			g_line_pipe = ft_substr(g_line_pipe, i+1, ft_strlen(g_line_pipe));
		}
	}
	g_print_err = "0";
	i = 0;
	prev_pipe = dup(STDIN_FILENO);
	while (i < size)
	{
		if (i < size - 1)
			pipe(fd);
		pid = fork();
		if (pid < 0)
			errno_error("FORK", errno);
		else if (pid == 0)
		{
			child_pipe_command(prev_pipe, inf, i, fd);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);				
		}
			
		//printf("here - 3\n");
		//printf("pc =  g_line - %s\n", g_line);		
		//printf("test = %s\n", g_print_err);		
		close(prev_pipe);
		close(fd[1]);
		prev_pipe = fd[0];
		i++;
	}
}

/*
** Создает флаги режимов для открытия файла
*/

int		create_open_flag(char *flag)
{
	int open;

	if (ft_strcmp(flag, ">>") == 0)
		open = O_RDWR | O_CREAT | O_APPEND;
	else if (ft_strcmp(flag, ">") == 0)
		open = O_RDWR | O_CREAT | O_TRUNC;
	else
		open = O_RDONLY;
	return (open);
}

/*
** Вывод содержимого функций в файл или на печать
*/

void	fail_write_in_file(char *instrct, errno_t errno_num, char *line)
{
	g_print_err = "1";
	errno_error(instrct, errno_num);
	free(line);
	return ;
}

void	write_in_file(t_instruct *instrct, char *line)
{
	int flag;
	int i;
	int fd;

	i = -1;
	errno = 0;
	g_print_err = "0";
	//printf("v= |%s|\n", line);
	if (instrct->basis == '|')
		ft_putstr_fd(line, 1);
	else
	{
		if (instrct->flag[0] == NULL)
			ft_putstr_fd(line, 1);
		while (instrct->flag[++i])
		{
			flag = create_open_flag(instrct->flag[i]);
			if ((fd = open(instrct->name[i], flag, 0666)) == -1)
				return (fail_write_in_file(instrct->instrct, errno, line));
			ft_putstr_fd(line, fd);
			if (close(fd) == -1)
				return (fail_write_in_file(instrct->instrct, errno, line));
		}
	}
	free(line);
}

int		get_fd(t_instruct *instrct)
{
	int flag;
	int fd;

	if (instrct->flag[0] == NULL)
		return (0);
	flag = create_open_flag(instrct->flag[0]);
	if ((fd = open(instrct->name[0], flag, 0666)) == -1)
	{
		g_print_err = "1";
		errno_error(instrct->instrct, errno);
		return (-1);
	}
	return (fd);
}

char	*ft_reduction_arr(char *str, int n)
{
	char	*spr;
	int		m;

	if (!(spr = (char *)malloc(sizeof(char *) * (ft_strlen(str) + 1))))
	{	
		ft_putstr_fd("12Problem in Malloc\n", 0);
		exit (12);
	}
	m = 0;
	while (m != n)
	{
		spr[m] = str[m];
		m++;
	}
	n++;
	while (str[n])
	{
		spr[m++] = str[n++];
	}
	spr[m] = '\0';
	free(str);
	return (spr);
}

void	ft_free(char **str)
{
	int	n;

	n = 0;
	while (str[n])
		free(str[n++]);
	free(str);
}
int		ft_isalnum(int n) //
{
	if (n >= 48 && n <= 57)
		return (1);
	if (n >= 65 && n <= 90)
		return (1);
	if (n >= 97 && n <= 122)
		return (1);
	else
		return (0);
}
int		ft_isalpha(int n) //
{
	if (n >= 65 && n <= 90)
		return (1);
	if (n >= 97 && n <= 122)
		return (1);
	else
		return (0);
}
int		ft_isdigit(int n) // 
{
	if (n > 47 && n < 58)
		return (1);
	else
		return (0);
}
t_instruct	*ft_lstlast(t_instruct *lst) //
{
	t_instruct *past;

	past = lst;
	if (lst != 0)
	{
		while (past->next)
			past = past->next;
	}
	return (past);
}
void	ft_lstadd_back(t_instruct **lst, t_instruct *new) //
{
	t_instruct	*end;

	if (new != 0)
	{
		end = ft_lstlast(*lst);
		if (end != 0)
			end->next = new;
		else
			*lst = new;
		new->next = NULL;
	}
}
int	ft_arrlen(char **str) //
{
	int n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}
int	ft_sign(char n, char *line) //
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == n)
			return (1);
		i++;
	}
	return (0);
}
int	ft_sign_in_arr(char **date, char *sign) //
{
	int n;
	int m;

	n = 0;
	m = 0;
	while (date[n])
	{
		m = 0;
		while (date[n][m])
		{
			if (ft_sign(date[n][m], sign) == 0)
				return (0);
			m++;
		}
		n++;
	}
	return (1);
}
void	ft_putstr_fd(char *s, int fd) //
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
void	ft_putstr(char *str) //
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
char	**ft_realloc_mass(char **arr, char *str) //
{
	char	**spr;
	int		n;

	n = 0;
	if (!(spr = (char **)malloc(sizeof(char *) * (ft_arrlen(arr) + 2))))
	{	
		ft_putstr_fd("13Problem in Malloc\n", 0);
		exit (12);
	}
	while (arr[n] != NULL)
	{
		spr[n] = ft_strdup(arr[n]);
		n++;
	}
	spr[n++] = ft_strdup(str);
	spr[n] = NULL;
	n = 0;
	ft_free(arr);
	return (spr);
}
static void	*free_memory(char **spr) //
{
	int i;

	i = 0;
	while (spr[i])
	{
		free(spr[i]);
		i++;
	}
	free(spr);
	return (NULL);
}
static int	ft_words(const char *s, char c) //
{
	int words;
	int	i;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}
static int	ft_ch(char const *s, char c) //
{
	int i;

	i = 0;
	while (*s != c && s[i] != '\0')
		i++;
	return (i);
}
static char	**ft_split2(char const *s, char c, char **spr) //
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			if (!(spr[i] = (char *)malloc(sizeof(char) * (ft_ch(s, c) + 1))))
				return (free_memory(spr));
			while (*s != c && *s)
				spr[i][n++] = *s++;
			spr[i++][n] = '\0';
			n = 0;
		}
	}
	spr[i] = NULL;
	return (spr);
}
char		**ft_split(char const *s, char c) //
{
	char	**spr;
	int		words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	if (!(spr = (char **)malloc(sizeof(char *) * (words + 1))))
	{	
		ft_putstr_fd("15Problem in Malloc\n", 0);
		exit (12);
	}
	return (ft_split2(s, c, spr));
}
int		ft_strcmp(char *str1, char *str2) //
{
	unsigned char	*s1;
	unsigned char	*s2;
	int			i;

	if (!str1 || !str2)
		return (1);
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int		ft_strncmp(char *str1,  char *str2, int n)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (n > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strdup(const char *s1) //
{
	char	*str;
	int		n;

	if (!s1)
		return (NULL);
	n = 0;
	while (s1[n])
		n++;
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	n = 0;
	while (s1[n])
	{
		str[n] = s1[n];
		n++;
	}
	str[n] = '\0';
	return (str);
}
size_t	ft_strlcpy(char *dest, char *src, size_t size) //
{
	size_t	m;
	size_t	n;
	int		i;

	if (!src)
		return (0);
	i = 0;
	while (src[i] != '\0')
		i++;
	if (size <= 0)
		return (i);
	n = size - 1;
	m = 0;
	while (n > 0 && src[m] != '\0')
	{
		dest[m] = src[m];
		m++;
		n--;
	}
	dest[m] = '\0';
	return (i);
}
int		ft_strlen(char *str) //
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		i++;
	return (i);
}
char	*ft_substr(char *s,  int start, int len) //
{
	int	sub;
	int	m;
	char	*spr;

	//printf("ft_substr s=|%s| strart=%d len=%d\n", s, start, len);
	if (!s)
		return (NULL);
	m = 0;
	sub = ft_strlen(s);
	if (sub < start)
		len = 0;
	else
	{
		sub = sub - start;
		if (sub < len)
			len = sub;
	}
	if (!(spr = (char *)malloc(sizeof(char) * (len + 1))))
	{
		//printf(":<\n");
		return (NULL);		
	}
	while (m < len)
	{
		spr[m] = s[m + start];
		m++;
	}
	spr[m] = '\0';
	return (spr);
}
char	*ft_strjoin_free(char *s1, char *s2) //
{
	char			*spr;
	unsigned int	size;
	int				n;
	int				m;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (!(spr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	n = 0;
	m = 0;
	if (s1)
		while (s1[n])
		{
			spr[m] = s1[n];
			n++;
			m++;
		}
	n = 0;
	while (s2[n])
		spr[m++] = s2[n++];
	spr[size] = '\0';
	free((void *)s1);
	return (spr);
}
char	*ft_strjoin_non_free(char  *s1, char  *s2) //
{
	size_t	n;
	size_t	m;
	char	*spr;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1);
	m = ft_strlen(s2);
	if (!(spr = (char *)malloc(sizeof(char) * (n + m + 1))))
	{	
		ft_putstr_fd("19Problem in Malloc\n", 0);
		exit (12);
	}
	n = 0;
	while (s1[n])
	{
		spr[n] = s1[n];
		n++;
	}
	m = 0;
	while (s2[m])
	{
		spr[n + m] = s2[m];
		m++;
	}
	spr[n + m] = '\0';
	return (spr);
}

char	*push_line(char *remains)
{
	int		i;
	char	*array;

	i = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i] != '\n')
		i++;
	//printf("remains = |%s| i=%d\n", remains, i);		
	if (!(array = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (remains[i] && remains[i] != '\n')
	{
		array[i] = remains[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*cut_next_line(char *remains)
{
	int		i;
	int		j;
	char	*array;

	i = 0;
	j = 0;
	if (!remains)
		return (NULL);
	while (remains[i] && remains[i] != '\n')
		i++;
	if (!remains[i])
	{
		free(remains);
		return (NULL);
	}
	if (!(array = (char *)malloc(sizeof(char) * (ft_strlen(remains) - i + 1))))
		return (NULL);
	i++;
	while (remains[i])
	{
		array[j] = remains[i];
		i++;
		j++;
	}
	array[j] = '\0';
	free(remains);
	return (array);
}

/*
** Функция для обработки ctrl + D
*/

int		get_next_line(char **line)
{
	char		buf[32];
	static char	*str;
	int			i;

	i = 1;
	if (line == NULL)
		return (-1);
	while (buf[0] != '\n' && i != 0)
	{
		i = read(0, buf, 1);
		if (g_command_signal == 1)
			return (0);
		if (i == -1)
		{
			errno = 2;
			exit(1);
		}
		//printf("i = %d\n", i);
		buf[i] = '\0';
		str = ft_strjoin_free(str, buf);
		//printf(" str = %s  g_command_signal = %d\n", str, g_command_signal );
		if (i == 0 && str[0] == 0 && g_command_signal != 7)
		{
			if (g_command_signal == 2)
				exit(0);
			else
			{
				ft_putstr("exit\n"); 
				exit(0);				
			}
		}
		else
			i = 1;
	}
	*line = push_line(str);
	str = cut_next_line(str);
	return ((i == 0) ? 0 : 1);
}

/*
** Функция для получения path к текущей директории
*/

char		*get_pwd(char **env)
{
	int		i;
	int		j;
	char	*temp;
	char	*path;
	static int one = 0;

	i = -1;
	temp = ft_strdup("MINISHELL:");
	
	while (env[++i])
	{
		if (ft_strcmp(env[i], "PWD") == 0)
		{
			//free(temp);
			temp = ft_strjoin_free(temp, env[++i]);
			break ;
		}
	}
	temp = ft_strjoin_free(temp, ": <-> ");
	i = -1;
	while (env[++i])
	{
		if (ft_strcmp(env[i], "HOME") == 0)
		{
			g_echo_home =  ft_strdup(env[++i]);
			break ;
		}
	}
	g_var = "";
	return (temp);
}

/*
** Функция цикличного чтения строки
*/

void		read_input(t_info *inf)
{
	char	*line;

	while (1)
	{
		if (g_command_pwd)
			free(g_command_pwd);
		//printf("1\n");
		g_command_signal = 0;
		g_command_pwd = get_pwd(inf->cmd_env);
		//printf("2\n");
		ft_putstr(g_command_pwd);
		get_next_line(&line);
			
		//printf("3\n");
		line_parsing(line, inf);
		//printf("4\n");
		//printf("g_command_signal = %d\n", g_command_signal);
		if (g_command_signal != 8)
			run_commands(inf);
		//printf("5\n");
		clear_malloc(inf);
		//printf("6\n");
		g_flag_n = 0;
		g_line = "";
		g_sign = 1;
		//g_print_err = "0";
		//free(g_echo_home);
	}
}

/*
** Обработка сигнала на ctrl + C (SIGINT) и ctrl + \ (SIGQUIT)
*/

void  sighandler(int signum)
{
	if (g_command_signal == 7)
	{
		g_command_signal = 8;
		if (g_point == 1 && (signum == SIGQUIT))
		{
			if (g_sign != 2)
				ft_putstr("Quit: 3\n");		
			g_print_err = "131";
		}
		else if (signum == SIGINT)
		{
			if (g_point == 1)
			{
				if (g_sign != 2)
					ft_putstr("\n");
				g_print_err = "130";
			}
			else
			{
				if (g_sign != 2)
					ft_putstr("\n");
				if (g_sign != 2)
					ft_putstr(g_command_pwd);
			}
		}
		//else
		//	ft_putstr("\n"); 
		//return ;
	}
	else if (g_command_signal == 2)
	{
		g_command_signal = 1;
		if (g_sign != 2)		 
			ft_putstr("\n");
		//return ;
	}
	else if (signum == SIGINT && g_sign != 2)
	{
		if (write(STDOUT_FILENO, "\b\b  \n", 5) < 0)
			return ;
		if (g_point != 1)
		{
			ft_putstr(g_command_pwd);
			g_print_err = "1";
		}
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr("\b\b  \b\b");
	}
}
/*-------------------------------------------------------------------
** иницилизирует структуру inf
*/
void		ft_start_zero(t_info *inf)
{
	g_echo_home = "";
	g_flag_n = 0;
	g_first = "0";
	g_n = 0;
	g_sign = 0;
	g_src = 0;
	g_qm = 0;
	g_flag = 0;
	g_point = 0;
	g_command_signal = 0;
	g_print_err = "0";
	g_command_pwd = NULL;	
	inf->basis = NULL;
	inf->instrct = NULL;
	if (!(inf->cmd_export = (char **)malloc(sizeof(char *) + 1)))
		ft_error("22Problem in Malloc", inf);
	inf->cmd_export[0] = NULL;
}
//-------------------------------------------------------------------
// (void)argc; and (void)**argv; - делают арг типа void, чтобы компилятор не ругался



int			main(int argc, char **argv, char **env)
{
	t_info	inf;

	(void)argc;
	(void)**argv;
	ft_start_zero(&inf);
	inf.cmd_env = parser_env(env);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	int i = 0;
	while (env[i])
		i++;
	if (i > 20)
		g_sign = 2;
	//printf("g_sign = %d\n", g_sign);
	read_input(&inf);
	return (0);
}
