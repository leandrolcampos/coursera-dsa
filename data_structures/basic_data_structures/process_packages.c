/* ----------------------------------------------------------------------- *
 * 
 *   Author: Leandro Augusto Lacerda Campos <llacerdacampos@gmail.com>
 * 
 *   Data Structures and Algorithms Specialization,
 *   by University of California, San Diego, 
 *   and National Research University Higher School of Economics
 * 
 *   Course 2: Data Structures
 * 
 *   Solution for Network Packet Processing Simulation Problem
 * 
 * ----------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef size_t
#undef size_t
#endif

#define size_t unsigned int
#define time unsigned long

typedef struct Packet Packet;
struct Packet {
    time arrival;       /* time of arrival, in milliseconds */
    time processing;    /* processing time, in milliseconds */
    bool isdropped;     /* packet is dropped because network buffer is full */
    time start;         /* start time of processing, in milliseconds */
};

/* 
 * emalloc: allocates memory or print a message if an error occurs
 */
void *emalloc(size_t n)
{
    void *p;

    p = malloc(n);
    if (p == NULL) {
        printf("malloc of %u bytes failed\n", n);
        exit(1);
    }
    return p;
}

/* 
 * efree: deallocates the memory previously allocated or print a message if 
 * an error occurs
 */
void *efree(void *p)
{
    if (p == NULL) {
        printf("ptr points to NULL\n");
        exit(1);
    }
    free(p);
    return (p = NULL);
}

/*
 * processor: simulates the processing of network packets following the 
 * instruction of the problem (see the corresponding programming assignment 
 * file)
 */
time processor(Packet *base, size_t nel, size_t bufsiz)
{
    size_t clock;   /* processor clock */
    size_t cnt;     /* number of packets in the buffer */
    size_t bufidx;  /* last packet in the buffer */
    Packet *pkt;    /* current packet in the processor */
    size_t i;

    if (nel == 0)
        return 0;
    if (bufsiz == 0) {
        printf("the size of the buffer should be equal or greater than 1\n");
        exit(1);
    }
    clock = 0;
    cnt = 0;
    bufidx = 0;
    for (i = 0; i < nel; i++) {
        pkt = &base[i];
        if (!pkt->isdropped) {
            if (cnt == 0) { /* if the packet was not in the buffer */
                cnt++;
                clock = pkt->arrival;
                bufidx = i;
            }
            pkt->start = clock;
            clock += pkt->processing;
            /* update the buffer */
            while (++bufidx < nel && base[bufidx].arrival < clock) {
                if (cnt < bufsiz) /* put base[bufidx] in the buffer */
                    cnt++;
                else /* buffer is full */
                    base[bufidx].isdropped = true;
            }
            bufidx--;
            /* release a place in the buffer */
            cnt--;
        }
    }
    return clock;
}

int main()
{
    size_t s, n, i;
    Packet *packets;

    scanf("%u", &s);    /* size of the buffer */
    scanf("%u", &n);    /* number of incoming network packets */
    if (n == 0)
        exit(0);
    packets = emalloc(n * sizeof(*packets));
    for (i = 0; i < n; i++) {
        scanf("%lu", &packets[i].arrival);
        scanf("%lu", &packets[i].processing);
        packets[i].isdropped = false;
        packets[i].start = 0;
    }
    processor(packets, n, s);
    for (i = 0; i < n; i++) {
        if (packets[i].isdropped)
            printf("%d\n", -1);
        else
            printf("%lu\n", packets[i].start);
    }
    packets = efree(packets);
    return 0;
}