#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
  freopen("game.in", "w", stdout);
  srand(time(0));
  int T = 10;
  printf("%d\n", T);
  while(T --) {
    printf("20 %d\n", rand() & 1);
    for(int i = 1; i <= 20; i ++) {
      if(i & 1) {
        int th = rand();
        if(!(th & 1)) th ++;
        printf("%d ", th);
      } else {
        printf("%d ", rand());
      }
    }
    puts("");
  }
  return 0;
}
