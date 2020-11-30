/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                   Extrae                                  *
 *              Instrumentation package for parallel applications            *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 2.1      *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

#include "pthread_redirect.h"

int (*pthread_create_real)(pthread_t*,const pthread_attr_t*,void *(*) (void *),void*) = NULL;
int (*pthread_join_real)(pthread_t,void**) = NULL;
int (*pthread_detach_real)(pthread_t) = NULL;
void (*pthread_exit_real)(void*) = NULL;
int (*pthread_barrier_wait_real)(pthread_barrier_t *barrier) = NULL;

int (*pthread_mutex_lock_real)(pthread_mutex_t*) = NULL;
int (*pthread_mutex_trylock_real)(pthread_mutex_t*) = NULL;
int (*pthread_mutex_timedlock_real)(pthread_mutex_t*,const struct timespec *) = NULL;
int (*pthread_mutex_unlock_real)(pthread_mutex_t*) = NULL;

int (*pthread_cond_broadcast_real)(pthread_cond_t*) = NULL;
int (*pthread_cond_timedwait_real)(pthread_cond_t*,pthread_mutex_t*,const struct timespec *) = NULL;
int (*pthread_cond_signal_real)(pthread_cond_t*) = NULL;
int (*pthread_cond_wait_real)(pthread_cond_t*,pthread_mutex_t*) = NULL;

int (*pthread_rwlock_rdlock_real)(pthread_rwlock_t *) = NULL;
int (*pthread_rwlock_tryrdlock_real)(pthread_rwlock_t *) = NULL;
int (*pthread_rwlock_timedrdlock_real)(pthread_rwlock_t *, const struct timespec *) = NULL;
int (*pthread_rwlock_wrlock_real)(pthread_rwlock_t *) = NULL;
int (*pthread_rwlock_trywrlock_real)(pthread_rwlock_t *) = NULL;
int (*pthread_rwlock_timedwrlock_real)(pthread_rwlock_t *, const struct timespec *) = NULL;
int (*pthread_rwlock_unlock_real)(pthread_rwlock_t *) = NULL;

void GetpthreadHookPoints (int rank)
{
// #if defined(PIC)

	/* Obtain @ for pthread_create */
	pthread_create_real =
		(int(*)(pthread_t*,const pthread_attr_t*,void *(*) (void *),void*))
		dlsym (RTLD_NEXT, "pthread_create");
	if (pthread_create_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_create in DSOs!!\n");

	/* Obtain @ for pthread_join */
	pthread_join_real =
		(int(*)(pthread_t,void**)) dlsym (RTLD_NEXT, "pthread_join");
	if (pthread_join_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_join in DSOs!!\n");

	/* Obtain @ for pthread_barrier_wait */
	pthread_barrier_wait_real =
		(int(*)(pthread_barrier_t *)) dlsym (RTLD_NEXT, "pthread_barrier_wait");
	if (pthread_barrier_wait_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_barrier_wait in DSOs!!\n");

	/* Obtain @ for pthread_detach */
	pthread_detach_real = (int(*)(pthread_t)) dlsym (RTLD_NEXT, "pthread_detach");
	if (pthread_detach_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_detach in DSOs!!\n");

	/* Obtain @ for pthread_exit */
	pthread_exit_real = (void(*)(void*)) dlsym (RTLD_NEXT, "pthread_exit");
	if (pthread_exit_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_exit in DSOs!!\n");

	/* Obtain @ for pthread_mutex_lock */
	pthread_mutex_lock_real = (int(*)(pthread_mutex_t*)) dlsym (RTLD_NEXT, "pthread_mutex_lock");
	if (pthread_mutex_lock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_lock in DSOs!!\n");
	
	/* Obtain @ for pthread_mutex_unlock */
	pthread_mutex_unlock_real = (int(*)(pthread_mutex_t*)) dlsym (RTLD_NEXT, "pthread_mutex_unlock");
	if (pthread_mutex_unlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_unlock in DSOs!!\n");
	
	/* Obtain @ for pthread_mutex_trylock */
	pthread_mutex_trylock_real = (int(*)(pthread_mutex_t*)) dlsym (RTLD_NEXT, "pthread_mutex_trylock");
	if (pthread_mutex_trylock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_trylock in DSOs!!\n");

	/* Obtain @ for pthread_mutex_timedlock */
	pthread_mutex_timedlock_real = (int(*)(pthread_mutex_t*,const struct timespec*)) dlsym (RTLD_NEXT, "pthread_mutex_timedlock");
	if (pthread_mutex_timedlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_mutex_timedlock in DSOs!!\n");

	/* Obtain @ for pthread_cond_signal */
	pthread_cond_signal_real = (int(*)(pthread_cond_t*)) dlsym (RTLD_NEXT, "pthread_cond_signal");
	if (pthread_cond_signal_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_cond_signal in DSOs!!\n");
	
	/* Obtain @ for pthread_cond_broadcast */
	pthread_cond_broadcast_real = (int(*)(pthread_cond_t*)) dlsym (RTLD_NEXT, "pthread_cond_broadcast");
	if (pthread_cond_broadcast_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_cond_broadcast in DSOs!!\n");
	
	/* Obtain @ for pthread_cond_wait */
	pthread_cond_wait_real = (int(*)(pthread_cond_t*,pthread_mutex_t*)) dlsym (RTLD_NEXT, "pthread_cond_wait");
	if (pthread_cond_wait_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_cond_wait in DSOs!!\n");
	
	/* Obtain @ for pthread_cond_timedwait */
	pthread_cond_timedwait_real = (int(*)(pthread_cond_t*,pthread_mutex_t*,const struct timespec*)) dlsym (RTLD_NEXT, "pthread_cond_timedwait");
	if (pthread_cond_timedwait_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_cond_timedwait in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_rdlock */
	pthread_rwlock_rdlock_real = (int(*)(pthread_rwlock_t*)) dlsym (RTLD_NEXT, "pthread_rwlock_rdlock");
	if (pthread_rwlock_rdlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_rdlock in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_tryrdlock */
	pthread_rwlock_tryrdlock_real = (int(*)(pthread_rwlock_t*)) dlsym (RTLD_NEXT, "pthread_rwlock_tryrdlock");
	if (pthread_rwlock_tryrdlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_tryrdlock in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_timedrdlock */
	pthread_rwlock_timedrdlock_real = (int(*)(pthread_rwlock_t *, const struct timespec *)) dlsym (RTLD_NEXT, "pthread_rwlock_timedrdlock");
	if (pthread_rwlock_timedrdlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_timedrdlock in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_rwlock */
	pthread_rwlock_wrlock_real = (int(*)(pthread_rwlock_t*)) dlsym (RTLD_NEXT, "pthread_rwlock_wrlock");
	if (pthread_rwlock_wrlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_wrlock in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_tryrwlock */
	pthread_rwlock_trywrlock_real = (int(*)(pthread_rwlock_t*)) dlsym (RTLD_NEXT, "pthread_rwlock_trywrlock");
	if (pthread_rwlock_trywrlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_trywrlock in DSOs!!\n");
	
	/* Obtain @ for pthread_rwlock_timedrwlock */
	pthread_rwlock_timedwrlock_real = (int(*)(pthread_rwlock_t *, const struct timespec *)) dlsym (RTLD_NEXT, "pthread_rwlock_timedwrlock");
	if (pthread_rwlock_timedwrlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_timedwrlock in DSOs!!\n");

	/* Obtain @ for pthread_rwlock_unlock */
	pthread_rwlock_unlock_real = (int(*)(pthread_rwlock_t*)) dlsym (RTLD_NEXT, "pthread_rwlock_unlock");
	if (pthread_rwlock_unlock_real == NULL && rank == 0)
		fprintf (stderr, "Unable to find pthread_rwlock_unlock in DSOs!!\n");
// #else
	// fprintf (stderr, "Warning! pthread instrumentation requires linking with shared library!\n");
// #endif /* PIC */
}

void mtx_rw_wrlock_caller(pthread_rwlock_t* lock, char* name, char const * caller_name) {
    pthread_rwlock_wrlock_real(lock);

    char cur_host_name[100];
    cur_host_name[99] = '\0';
    gethostname(cur_host_name, 99);

    //fprintf(stderr, "DEBUG_LOCK\t%s OS_TID:%ld\t%s\tmtx_rw_wrlock\t%s\n", cur_host_name, syscall(SYS_gettid), name, caller_name);
}

void mtx_rw_rdlock_caller(pthread_rwlock_t* lock, char* name, char const * caller_name) {
    pthread_rwlock_rdlock_real(lock);

    char cur_host_name[100];
    cur_host_name[99] = '\0';
    gethostname(cur_host_name, 99);

    //fprintf(stderr, "DEBUG_LOCK\t%s OS_TID:%ld\t%s\tmtx_rw_rdlock\t%s\n", cur_host_name, syscall(SYS_gettid), name, caller_name);
}

void mtx_rw_unlock_caller(pthread_rwlock_t* lock, char* name, char const * caller_name) {
    pthread_rwlock_unlock_real(lock);

    char cur_host_name[100];
    cur_host_name[99] = '\0';
    gethostname(cur_host_name, 99);

    //fprintf(stderr, "DEBUG_LOCK\t%s OS_TID:%ld\t%s\tmtx_rw_unlock\t%s\n", cur_host_name, syscall(SYS_gettid), name, caller_name);
}