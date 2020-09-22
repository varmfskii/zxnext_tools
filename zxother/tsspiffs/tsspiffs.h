
#pragma once

// #define TSF_CHECK_BLANK             // to test block after erase
// #define TSF_CHECK_EXIST_ON_CREATE   // to look for existing filename when file is created

#ifndef min
#define min(x,y) ((x) < (y) ? (x) : (y))
#endif
#ifndef max
#define max(x,y) ((x) > (y) ? (x) : (y))
#endif

// enums
enum
{
 TSF_MAGIC = ((uint32_t)0x78E15CA3)
};

typedef enum
{
  TSF_RES_OK = 0,
  TSF_RES_FS_ERROR,
  TSF_RES_FILE_NOT_FOUND,
  TSF_RES_FILE_EXISTS,
  TSF_RES_MODE_ERROR,
  TSF_RES_BULK_FULL,
  TSF_RES_NOT_BLANK,
  TSF_RES_NO_MORE_FILES
} TSF_RESULT;

typedef enum
{
  TSF_CHUNK_HEAD = 0x00,
  TSF_CHUNK_BODY = 0x01,
  TSF_CHUNK_FREE = 0xFF
} TSF_CHUNK_TYPE;

typedef enum
{
  TSF_MODE_READ   = 0x01,
  TSF_MODE_WRITE  = 0x02,
  TSF_MODE_CREATE = 0x04,
  TSF_MODE_CREATE_WRITE = TSF_MODE_CREATE | TSF_MODE_WRITE,
} TSF_MODE;

typedef enum
{
  TSF_LIST_NEXT = 0,
  TSF_LIST_START
} TSF_LIST;

// types
typedef TSF_RESULT (*tsf_read_t)(uint32_t, void*, uint32_t);
typedef TSF_RESULT (*tsf_write_t)(uint32_t, const void*, uint32_t);
typedef TSF_RESULT (*tsf_erase_t)(uint32_t);

#ifdef _MSC_VER
#pragma pack(1)
#endif

typedef struct
{
  uint32_t magic;
  uint16_t next_chunk;
  uint8_t type;
} TSF_CHUNK;

typedef struct
{
  uint32_t size;
  uint8_t fnlen;
} TSF_HDR;

typedef struct
{
  uint32_t bulk_start;          // start address in flash IC
  uint32_t bulk_size;           // size of the TSF
  uint32_t block_size;          // erase block size
  uint16_t last_written_chunk;  // for wear levelling

  tsf_read_t  hal_read_func;
  tsf_write_t hal_write_func;
  tsf_erase_t hal_erase_func;

  uint8_t *buf;
  uint16_t buf_size;
} TSF_CONFIG;

typedef struct
{
  uint32_t free;
  uint16_t chunks_number;
  uint16_t files_number;
  TSF_CONFIG *cfg;
} TSF_VOLUME;

typedef struct
{
  uint32_t addr;             // first chunk address
  uint32_t size;             // file size
  uint32_t seek;             // current pointer
  uint32_t chunk_addr;       // current chunk address
  uint32_t chunk_offset;     // current offset in chunk
  uint32_t prev_chunk_addr;  // previous chunk address
  uint16_t next_chunk;       // next chunk
  uint8_t mode;
  TSF_VOLUME *vol;
} TSF_FILE;

typedef struct
{
  uint32_t size;
} TSF_FILE_STAT;

#ifdef _MSC_VER
#pragma pack()
#endif

// functions
// file operations
TSF_RESULT tsf_open(TSF_VOLUME*, TSF_FILE*, const char*, uint8_t);
TSF_RESULT tsf_read(TSF_FILE*, void*, uint32_t);
TSF_RESULT tsf_write(TSF_FILE*, const void*, uint32_t);
TSF_RESULT tsf_close(TSF_FILE*);
TSF_RESULT tsf_seek(TSF_FILE*, uint32_t);
TSF_RESULT tsf_delete(TSF_VOLUME*, const char*);
TSF_RESULT tsf_stat(TSF_VOLUME*, TSF_FILE_STAT*, const char*);
TSF_RESULT tsf_list(TSF_VOLUME*, uint8_t);

// volume operations
TSF_RESULT tsf_mount(TSF_CONFIG*, TSF_VOLUME*);
TSF_RESULT tsf_format(TSF_CONFIG*);
TSF_RESULT tsf_check(TSF_CONFIG*);

// auxilliary functions
TSF_RESULT tsf_init_chunk(TSF_CONFIG*, uint32_t);
TSF_RESULT tsf_check_blank(TSF_CONFIG*, uint32_t, uint32_t);
TSF_RESULT tsf_search(TSF_VOLUME*, uint32_t*, const char*);
TSF_RESULT tsf_open_for_read(TSF_FILE*, const char*);
TSF_RESULT tsf_create(TSF_FILE*, const char*);
TSF_RESULT tsf_take_new_chunk(TSF_VOLUME*, uint8_t, uint32_t*);
TSF_RESULT tsf_vol_stat(TSF_VOLUME*);
TSF_RESULT tsf_read_int(TSF_FILE*, void*, uint32_t);
