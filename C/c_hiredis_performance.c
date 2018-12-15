#include <hiredis/hiredis.h>
#include <stdio.h>
#include <time.h>

#define NANO_IN_SEC 1000000000
#define NBR_CALL 1000000

int time_calculate(struct timespec begin, struct timespec end, int nbr) {
  long long delta = (end.tv_sec * NANO_IN_SEC + end.tv_nsec) -
                    (begin.tv_sec * NANO_IN_SEC + begin.tv_nsec);
  return (int)(nbr / (delta / (double)NANO_IN_SEC));
}

int main(void) {
  struct timespec begin = {0};
  struct timespec end = {0};
  printf("Connecting...\n");
  redisContext *redis = redisConnect("localhost", 6379);
  if (redis->err) {
    puts(redis->errstr);
    char *p = redis->errstr;
    while (*p)
      printf("%x ", (int)(*p++));
    printf("\n");
  } else {
    puts("Connected!");
    clock_gettime(CLOCK_MONOTONIC, &begin);
    for (int i = 0; i < NBR_CALL; i++)
      redisAppendCommand(redis, "SET foo bar");
    for (int i = 0; i < NBR_CALL; i++) {
      redisReply *reply;
      redisGetReply(redis, (void **)&reply);
      freeReplyObject(reply);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    puts("Done");
  }
  printf("> %d c/sec\n", time_calculate(begin, end, NBR_CALL));
}
