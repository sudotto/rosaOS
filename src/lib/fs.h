#ifndef FS
#define FS

#define FILE_SIZE 24576
#define HEAD_SIZE 72
#define DATA_SIZE FILE_SIZE - HEAD_SIZE

// SINGULAR FILES

typedef struct {
	char name[32];
	char desc[32];
	int psector;
	char data[DATA_SIZE];    // total info is 48 * 512 bytes (48 sectors)
	int sector;
} File;                                                    // files on disk get translated to struct to make it easy

File new_file(char* name, char* desc);
int open_file(File* file);
int close_file(File* file);

// MULTIPLE FILES

int end_of_files();

#endif
