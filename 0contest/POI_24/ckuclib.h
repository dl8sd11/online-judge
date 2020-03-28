namespace CK {
    const int MAXN = 1000006;
    int j;
    int e;
    int jendo[MAXN];
    int dwa[MAXN];
    int polowa[MAXN];
}

int dajn () {
    CK::j = rand() % 5;
    CK::e = rand() % 3;

    for (int i=0; i<CK::j; i++) {
        CK::jendo[i] = rand() % 100;
        CK::dwa[i] = rand() % 100;
        CK::polowa[i] = rand() % 100;
    }
    return CK::j;
}

int daje () {
    return CK::e;
}

int jedno (int k) {
    return CK::jendo[k-1];
}

int dwa (int k) {
    return CK::dwa[k-1];
}

int polowa (int k) {
    return CK::polowa[k-1];
}

void odpowiedz (int wynik) {
    cout << wynik << endl;
}

