/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:51:39 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/11 18:51:42 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

//*******ANSI escape sequences for bold text colors *//

# define    RST "\033[0m"           // Reset to default color
# define    RED "\033[1;31m"        // Bold Red
# define    G   "\033[1;32m"        // Bold Green
# define    Y   "\033[1;33m"        // Bold Yellow
# define    B   "\033[1;34m"        // Bold Blue                
# define    M   "\033[1;35m"        // Bold Magenta
# define    C   "\033[1;36m"        // Bold Cyan
# define    W   "\033[1;37m"        // Bold White



//write macro
#define DEBUG_MODE 0


//*************** enums **********************//


//philo states

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING,
    TAKE_FIRST_FORK,
    TAKE_SECOND_FORK,
    DIED,
}           t_philo_status;





typedef enum e_opcode
{
    LOCK,
    UNLOCK,
    INIT,
    DESTROY,
    CREATE,
    JOIN,
    DETACH,
}   t_opcode;


typedef enum e_time_code
{
    SECOND,
    MILLISECOND,
    MICROSECOND,
}   t_time_code;


//*************** structures **********************//

typedef pthread_mutex_t t_mtx;

typedef struct s_table t_table;



//*******FORK *//
typedef struct s_fork
{
    t_mtx   fork;
    int     fork_id;
}           t_fork;



//*******PHILO *//
typedef struct s_philo
{
    int         id;
    long        meals_counter;
    bool        full;
    long        last_meal_time;
    t_fork      *first_fork;
    t_fork      *second_fork;
    pthread_t   thread_id;
    t_table     *table;
}               t_philo;


//*******TABLE *//
struct s_table
{
    long    philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    nbr_limit_meals;
    long    start_simulation;
    bool    end_simulation;
    bool    all_threads_ready;
    t_mtx   table_mutex;
    t_mtx   write_lock;
    t_fork  *forks;
    t_philo *philos;
};




//*********PROTOTYPES*******


//****************utils *************/
void    error_exit(const char *error);
long    gettime(t_time_code time_code);
void    precise_usleep(long usec, t_table *table);



//****************parsing *************/
void parse_input(t_table *table, char **av);




//***************write *************/
write_status(t_philo_status status, t_philo *philo, bool debug);

//****************init *************/
void data_init(t_table *table);


//****************safe_functions *************/
void *safe_malloc(size_t bytes);
void safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
                        void *data, t_opcode opcode);
void safe_mutex_handle(t_mtx *mutex, t_opcode opcode);




//****************synchro_utils *************/
void wait_all_threads(t_table *table);


//****************getters_setters *************/
void set_bool(t_mtx *mtx, bool *dest, bool value);
bool get_bool(t_mtx *mtx, bool *value);
void set_long(t_mtx *mtx, long *dest, long value);
long get_long(t_mtx *mtx, long *value);
bool simulation_finished(t_table *table);