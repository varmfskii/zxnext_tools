#pragma once

void parse_args(int, char*[]);
void init_hdr();
void pack_blocks();
void load_ini(char*);
void load_files();
void save_spg(char*);
void unpack_spg(char*);
char *strlwr(char *);
