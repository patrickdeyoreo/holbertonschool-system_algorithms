#ifndef __HUFFMAN_H_
#define __HUFFMAN_H_

#include <errno.h>
#include <stdio.h>

#include "../heap/heap.h"

#define CHAR_TABLE_SIZE (1 << (sizeof(char) * 8))
#define FREQ_TABLE_SIZE CHAR_TABLE_SIZE

typedef char char_table_t[CHAR_TABLE_SIZE];
typedef size_t freq_table_t[FREQ_TABLE_SIZE];

extern char *program_invocation_name;
extern char *program_invocation_short_name;

int huffman(char mode, char *ifilename, char *ofilename);
int huffman_compress(FILE *istream, FILE *ostream);
int huffman_decompress(FILE *istream, FILE *ostream);
char_table_t *char_table(void);
freq_table_t *freq_table(void);
int freq_table_read(FILE *istream);
int freq_table_write(FILE *ostream);

#endif /* __HUFFMAN_H_ */
