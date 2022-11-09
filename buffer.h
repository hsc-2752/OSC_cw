#include <stdio.h>

struct Buffer* newBuffer();
void add(struct Buffer* b, struct process* p);
struct process* remove(struct Buffer* b);