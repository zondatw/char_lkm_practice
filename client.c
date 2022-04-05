#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 256
#define DIRVER_PATH "/dev/charlkm"

static char recvMessage[MSG_SIZE];

int main() {
    printf("===== Character driver client =====\n");

    int ret, fd;
    char sendMessage[MSG_SIZE];

    fd = open(DIRVER_PATH, O_RDWR);
    if (fd < 0) {
        perror("Open driver fail");
        return errno;
    }

    printf("Enter string to send to the character driver:\n");
    scanf("%[^\n]%*c", sendMessage);

    printf("Ready send [%s] to character driver\n", sendMessage);
    ret = write(fd, sendMessage, strlen(sendMessage));
    if (ret < 0) {
        perror("Send message to character dirver fail");
        return errno;
    }

    printf("Press ENTER to read message from character driver\n");
    getchar();

    printf("Ready read message from character driver\n");
    ret = read(fd, recvMessage, MSG_SIZE);
    if (ret < 0) {
        perror("Read message from character dirver fail");
        return errno;
    }

    printf("Read message [%s]\n", recvMessage);

    printf("Bye!!\n");
    return 0;
}
