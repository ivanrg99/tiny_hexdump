#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct file_contents {
	uint8_t *data;
	size_t size;
} file_contents;

file_contents
read_file(const char *path)
{
	file_contents res;
	FILE *f = fopen(path, "rb");
	if (f == NULL) {
		fprintf(stderr, "Error reading file %s", path);
		exit(1);
	}
	fseek(f, 0, SEEK_END);
	size_t f_size = ftell(f);
	fseek(f, 0, SEEK_SET);
	res.data = (uint8_t *) malloc(f_size);
	fread(res.data, f_size, 1, f);
	res.size = f_size;
	fclose(f);
	return res;
}

void
print_contents(file_contents * contents)
{
	int32_t offset = 0;
	printf("%08X0\t", offset);
	for (size_t i = 1; i <= contents->size; i++) {
		printf("%02X ", *contents->data++);
		if (i % 16 == 0) {
			printf("\n%08X0\t", ++offset);
		}
	}
	printf("\n");
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: hexdump <file>\n");
		exit(0);
	}
	file_contents contents = read_file(argv[1]);
	print_contents(&contents);
	free(contents.data - contents.size);
	return 0;
}
