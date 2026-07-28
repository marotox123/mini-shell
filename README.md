# mini-shell

Prosty shell napisany w C — projekt do nauki programowania systemowego w Linuksie (procesy, `fork`/`execv`, zarządzanie pamięcią, parsowanie tekstu).

## Funkcje

- Prompt w stylu `user@host /sciezka>`
- Wbudowane komendy:
  - `help` — lista dostępnych komend
  - `clear` — czyści ekran
  - `pwd` — wypisuje bieżący katalog
  - `cd <ścieżka>` — zmiana katalogu
  - `..` — skrót do `cd ..`
  - `ls [ścieżka]` — listowanie zawartości katalogu
  - `echo <argumenty>` — wypisuje argumenty
  - `exit` — wyjście z shella
- Uruchamianie plików wykonywalnych przez `./nazwa_programu` (fork + execv)
- Dynamicznie rosnący bufor linii wejściowej (bez sztywnego limitu długości polecenia)

## Budowanie

```sh
make
```

albo ręcznie, bez Makefile:

```sh
gcc -Wall -Wextra -o program main.c cd.c echo.c ls.c runelf.c utils.c
```

## Uruchomienie

```sh
./program
```

## Struktura projektu

Każda wbudowana komenda ma własną parę plików `.c`/`.h`:

```
main.c      – pętla główna, prompt, dispatch komend
utils.c/.h  – parser argumentów, pomocnicze funkcje
cd.c/.h     – komenda cd
echo.c/.h   – komenda echo
ls.c/.h     – komenda ls
runelf.c/.h – uruchamianie zewnętrznych plików wykonywalnych
```

## Znane ograniczenia

Projekt powstał w celach edukacyjnych, więc świadomie ma kilka uproszczeń:

- Parser argumentów (`ArgumentParser` w `utils.c`) alokuje tablicę `argv` na sztywno **64 wskaźniki** — polecenie z więcej niż 64 argumentami spowoduje wyjście poza alokowaną pamięć.
- Brak obsługi cudzysłowów/escapowania — `echo "a b"` zostanie rozbite na dwa argumenty.
- Brak przeszukiwania `PATH` — programy zewnętrzne trzeba uruchamiać z prefiksem `./`.
- Brak potoków (`|`) i przekierowań (`>`, `<`).
- Brak obsługi sygnałów (np. Ctrl+C przerywa cały shell, a nie tylko bieżące polecenie).

## Licencja

Projekt hobbystyczny/edukacyjny — używaj dowolnie.
