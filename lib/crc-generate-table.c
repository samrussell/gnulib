#include <stdio.h>

unsigned long crc_table[256];

// taken from RFC 1952
void make_crc_table(int bits)
{
    unsigned long c;

    int n, k;
    for (n = 0; n < 256; n++) {
        c = (unsigned long) n;
        for (k = 0; k < bits; k++) {
            if (c & 1) {
                c = 0xedb88320L ^ (c >> 1);
            } else {
                c = c >> 1;
            }
        }
        crc_table[n] = c;
    }
}

void print_crc_table(int bits) {
    make_crc_table(bits);

    printf("  {");

    for (int i = 0; i < 256; i++){
        if ((i % 6) == 0) {
            printf("\n   ");
        }
        if (i != 255) {
            printf(" 0x%08X,", crc_table[i]);
        }
        else {
            printf(" 0x%08X\n", crc_table[i]);
        }
    }

    printf("  }");
}

int main(int argc, char* argv[]){
    printf("static const uint32_t crc32_sliceby8_table[][256] = {\n");
    for (int i=8; i <= 64; i += 8) {
        print_crc_table(i);
        if (i < 64) {
            printf(",");
        }
        printf("\n");
    }
    printf("};\n");
}
