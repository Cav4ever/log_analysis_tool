#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *inFp;
    FILE *outFp;
    char str[64];    
    char outfileName[64];
    int data1, data2, data3;
    int ret;
    int count = 0;

    if (2 != argc) {
        printf("usage: ./a.out inFileName.\n");
        exit(1);
    }
    memset(str, 0, sizeof(str) / sizeof(char));
    memset(outfileName, 0, sizeof(outfileName) / sizeof(char));

    inFp = fopen(argv[1], "r");
    sprintf(outfileName, "%s_out", argv[1]);
    outFp = fopen(outfileName, "w");

    while (NULL != fgets(str, 64, inFp)) {
        ret = sscanf(str,"%d %d %d",&data1, &data2, &data3);
        if (0 == ret) {
            if (0 != count) {
                fprintf(outFp, "%d\n", count);
                count = 0;
            }
            fprintf(outFp, "%s\n", str);
        } else {
            if (data3 == 1) {
                if (0 != count) {
                    fprintf(outFp, "%d\n", count);
                    count = 0;
                }
                fprintf(outFp, "%d\n", data2);
            } else if (data3 == 0) {
                count += data2;
            }
        }
        memset(str, 0, sizeof(str) / sizeof(char));
    }
    if (0 != count) {
        fprintf(outFp, "%d\n", count);
    }

    fclose(inFp);
    fclose(outFp);
    return 0;
}