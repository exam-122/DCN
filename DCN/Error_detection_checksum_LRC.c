#include <stdio.h>


unsigned char calculateLRC(unsigned char *data, int length) {
    unsigned char lrc = 0;
    for (int i = 0; i < length; i++) {
        lrc += data[i];
    }
    lrc = (~lrc) + 1;
    return lrc;
}

void printBinary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 1);
    }
}

int main() {

    unsigned char dataToSend[] = {0x41, 0x42, 0x43, 0x44}; 
    int dataLength = sizeof(dataToSend) / sizeof(dataToSend[0]);

    unsigned char lrc = calculateLRC(dataToSend, dataLength);

  
    dataToSend[dataLength] = lrc;

  
    printf("Data with appended LRC (in binary):\n");
    for (int i = 0; i < dataLength + 1; i++) {
        printBinary(dataToSend[i]);
        printf(" ");
    }
    printf("\n");

    return 0;
}