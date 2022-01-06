/*
 *  Bounded buffer skeleton for Sieve of Erathosthenes primes program
 *  Based on Operating Systems: Three Easy Pieces by R. Arpaci-Dusseau and A. Arpaci-Dusseau
 * 
 *  This example uses locks and a condition to synchronize a child thread and
 *  the parent.  The child generates matricies and the parent computes the
 *  average when the matrix is ready for processing.
 *
 *  Wes J. Lloyd
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>
#include "buffer.h"

/**
 * Initialize bounded buffer
 **/
void initbuff(int nslots, buffer_t *buff, char * n)
{
  // initialize all elements defined in buffer struct
  buff->buffer = (int*)malloc(sizeof(int) * nslots);
  buff->maxSlots = nslots;
  buff->use_ptr = 0;
  buff->fill_ptr = 0;
  buff->count = 0;
  buff->name = n;
  pthread_mutex_init(&(buff->mutex), NULL);
  pthread_cond_init(&(buff->cond), NULL);
}

/**
 * Release memory allocated to buffer.
 **/
void freebuff(int nslots, buffer_t *buff, char * n)
{
  free(buff->buffer);
}

/**
 * Load value into bounded buffer.
 **/ 
void put(int value, buffer_t *buff)
{
  pthread_mutex_lock(&(buff->mutex)); // p1
  while (buff->count == buff->maxSlots) // p2
    pthread_cond_wait(&(buff->cond), &(buff->mutex)); // p3

  // put
  buff->buffer[buff->fill_ptr] = value;
  buff->fill_ptr = (buff->fill_ptr + 1) % buff->maxSlots;
  buff->count++;

  pthread_cond_signal(&(buff->cond)); // p5
  pthread_mutex_unlock(&(buff->mutex)); // p6
}

/**
 * Retrieve a value from the bounded buffer
 **/
int get(buffer_t *buff)
{
  pthread_mutex_lock(&(buff->mutex)); // c1
  while (buff->count == 0) // c2
    pthread_cond_wait(&(buff->cond), &(buff->mutex)); // c3

  // get
  int tmp = buff->buffer[buff->use_ptr];
  buff->use_ptr = (buff->use_ptr + 1) % buff->maxSlots;
  buff->count--;

  pthread_cond_signal(&(buff->cond)); // c5
  pthread_mutex_unlock(&(buff->mutex)); // c6
  return tmp;
}

