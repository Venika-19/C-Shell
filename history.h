#ifndef __HISTORY_H
#define __HISTORY_H

void history();

void add_comm();

void init_hist_q();

struct q {
    struct q *next;
    struct q *prev;
    char name[4096];
    int after;
};

struct q *hist_head;

#endif