#include "boxes.h"
#include <stdio.h>
#include <stdlib.h>

static char _buffer[1024];
static int _currentChar = 0;
static int _charsNumber = 0;
static FILE *_inputFile, *_outputFile;

static inline int _read() {
    if (_charsNumber < 0) {
        exit(1);
    }
    if (!_charsNumber || _currentChar == _charsNumber) {
        _charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), _inputFile);
        _currentChar = 0;
    }
    if (_charsNumber <= 0) {
        return -1;
    }
    return _buffer[_currentChar++];
}

static inline int _readInt() {
    int x;
    scanf("%d", &x);
    return x;
}

int main() {
	_inputFile = fopen("boxes.in", "rb");
	_outputFile = fopen("boxes.out", "w");

    int N, K, L, i;
    N = _readInt();
    K = _readInt();
    L = _readInt();

    int *p = (int*)malloc(sizeof(int) * (unsigned int)N);

    for (i = 0; i < N; i++) {
        p[i] = _readInt();
    }

    printf("%lld\n", delivery(N, K, L, p));
    return 0;
}
