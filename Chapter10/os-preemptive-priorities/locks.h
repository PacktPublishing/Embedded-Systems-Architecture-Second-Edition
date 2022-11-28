/*
 *
 * Embedded System Architecture - Second Edition
 * Copyright (c) 2018-2022 Packt
 *
 * Author: Daniele Lacamera <root@danielinux.net>
 *
 * MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 */
#ifndef LOCKS_H_INCLUDED
#define LOCKS_H_INCLUDED
#define MAX_LISTENERS 4

struct semaphore {
    uint32_t value;
    uint8_t listeners[MAX_LISTENERS];
};

typedef struct semaphore semaphore;
typedef semaphore mutex;

int sem_trywait(semaphore *s);
int sem_dopost(semaphore *s);

static inline int sem_init(semaphore *s, int val)
{
    int i;
    s->value = val;
    for (i = 0; i < MAX_LISTENERS; i++)
        s->listeners[i] = 0;
    return 0;
}

#define mutex_init(m) sem_init(m, 1)
#define mutex_trylock(m) sem_trywait(m)

#endif
