#ifndef GETTOKEN_H
#define GETTOKEN_H

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS };

extern int gettoken(void);

extern int tokentype; 			/* type of last token */
extern char token[MAXTOKEN];		/* last token string */

#endif	/* GETTOKEN_H */
