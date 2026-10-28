#include <stdio.h>
#include <math.h>
#include <locale.h>

#define N 5
#define M 3
#define K 2
#define L 1.0f
#define EPS 1e-6f

typedef struct {
    const char* name;
    float x[N];
} Series;

typedef struct {
    int time;
    int type;
    float value;
} Incident;

static const char* state_name(int s) {
    if (s < 0) return "СНИЖЕНИЕ";
    if (s > 0) return "РОСТ";
    return "НОРМА";
}

static int state_q(float q, float limit) {
    if (q < -limit - EPS) return -1;
    if (q > limit + EPS) return  1;
    return 0;
}

int main() {
    setlocale(LC_CTYPE, "RUS");

    Series series[M] = {
        { "API",{ 43.7f, 44.2f, 44.7f, 50.6f, 51.1f } },
        { "GPU",{ 53.8f, 57.2f, 55.2f, 53.2f, 51.2f } },
        { "WEB",{ 32.0f, 31.3f, 30.6f, 35.2f, 34.5f } },
    };
    int times[N] = { 1, 2, 3, 4, 5 };

    printf("Производный показатель Q[i] = X[i] - X[i-%d], L = %.1f\n\n", K, L);
    for (int c = 0; c < M; c++) {
        printf("Компонент %s:\n", series[c].name);
        for (int i = K; i < N; i++) {
            float q = series[c].x[i] - series[c].x[i - K];
            int st = state_q(q, L);
            printf("  t=%d  X[i]=%.2f  X[i-k]=%.2f  Q=%.2f  %s\n",
                times[i], series[c].x[i], series[c].x[i - K],
                q, state_name(st));
        }
        printf("\n");
    }


    return 0;
}