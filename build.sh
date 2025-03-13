clang \
    sisyphus.c -o sisyphus.out \
    -std=c99 \
    -Wall \
    -Werror \
    -Wextra \
    -Wno-typedef-redefinition \
    -Wno-error=typedef-redefinition \
    $(pkg-config --cflags gtk4) \
    $(pkg-config --libs gtk4)
