#include <fcntl.h>
#include "../utils/list.h"

CharCharList get_history() {
    int fd = open("/tmp/.shellout_history", O_CREAT | O_RDONLY, 0664);
    CharCharList charCharList = new_charcharlist(10);
    CharList charList = new_charlist(10);
    char buffer;
    while (read(fd, &buffer, 1)) {
        if (buffer == 10) {
            if (charList.size) {
                append_charcharlist(&charCharList, charList);
                charList = new_charlist(10);
            }
        } else
            append_charlist(&charList, buffer);
    }
    if (charList.size) {
        append_charcharlist(&charCharList, charList);
    }
    close(fd);
    return charCharList;
}

void set_history(CharCharList *charCharList) {
    int fd = open("/tmp/.shellout_history", O_CREAT | O_WRONLY | O_TRUNC, 0664);
    char buffer;
    CharList charList;
    for (int i = 0; i < charCharList->size; ++i) {
        charList = index_charcharlist(charCharList, i);
        for (int j = 0; j < charList.size; ++j) {
            buffer = index_charlist(&charList, j);
            write(fd, &buffer, 1);
        }
        if (i + 1 != charCharList->size) {
            buffer = '\n';
            write(fd, &buffer, 1);
        }
    }
    close(fd);
}