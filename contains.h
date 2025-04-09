#ifndef CONTAINS_H
#define CONTAINS_H

int contains(void *el, void *a, int layers, size_t nmem, size_t width, int (*match)(void *, void *));
int streq(char *s0, char **s1);

#endif /* CONTAINS_H */
