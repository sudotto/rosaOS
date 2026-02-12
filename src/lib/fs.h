#ifndef FS
#define FS

#define FS_START 10

#define FILE_SIZE 512 //24576
#define HEAD_SIZE 1 + 32 + 32 + 4
#define DATA_SIZE FILE_SIZE - HEAD_SIZE

// SINGULAR FILES

typedef struct {
	char init;
	char name[32];
	char desc[32];
	int psector;
	char data[DATA_SIZE];    // total info is 48 * 512 bytes (48 sectors)
	int sector;
} File;                                                    // files on disk get translated to struct to make it easy

void new_file(char* name, char* desc);
int open_file(File* file, char* filename);
int close_file(File* file);

// MULTIPLE FILES

int new_fs(); // init fs by zeroing the init flags of empty fentries
int search_fs(char* filename);
int end_of_fs();

#endif
