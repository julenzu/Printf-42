*This project has been created as part of the 42 curriculum by jzuazo.*

# ft_printf

## Description

**ft_printf** is a re-implementation of the C standard library function `printf()`. The project is an introduction to **variadic functions** in C (`<stdarg.h>`): how a function can receive an unknown number of arguments and how to walk through them with `va_start`, `va_arg` and `va_end`. It also pushes towards a well-structured, easily extensible code base, since each conversion is handled by its own small function.

As with the original `printf()`, `ft_printf()` returns the total number of characters written to standard output. The buffer management of the original `printf()` is intentionally **not** reproduced: output is written directly with `write(2)`.

### Supported conversions

| Specifier | Description                                                   |
|-----------|---------------------------------------------------------------|
| `%c`      | A single character                                            |
| `%s`      | A string (prints `(null)` if the pointer is `NULL`)           |
| `%p`      | A `void *` pointer in hexadecimal (prints `(nil)` if `NULL`)  |
| `%d`      | A signed decimal integer (base 10)                            |
| `%i`      | A signed integer (base 10)                                    |
| `%u`      | An unsigned decimal integer (base 10)                         |
| `%x`      | An unsigned integer in lowercase hexadecimal (base 16)        |
| `%X`      | An unsigned integer in uppercase hexadecimal (base 16)        |
| `%%`      | A literal percent sign                                        |

### Project structure

```
.
├── Makefile
├── README.md
├── ft_printf.h        # Prototypes and required includes
├── ft_printf.c        # ft_printf() main loop and conversion dispatcher
├── ft_print_char.c    # %c (and the base write primitive used everywhere)
├── ft_print_str.c     # %s
├── ft_print_nbr.c     # %d, %i, %u
└── ft_print_hex.c     # %x, %X, %p
```

## Instructions

### Compilation

The project is compiled with `cc` and the flags `-Wall -Wextra -Werror`. The library is created with `ar` (never `libtool`) in the root of the repository.

```bash
make            # builds libftprintf.a
make clean      # removes the object files
make fclean     # removes the object files and libftprintf.a
make re         # fclean + all
```

The Makefile does not relink: running `make` twice does nothing the second time if no file has changed.

### Usage

Include the header in your code and link against the library:

```c
#include "ft_printf.h"

int main(void)
{
    int len;

    len = ft_printf("Hello %s! %d + %i = %u\n", "world", 40, 2, 42U);
    ft_printf("hex: %x / %X, ptr: %p, percent: %%, char: %c\n",
              255, 255, &len, 'A');
    ft_printf("printed %d characters\n", len);
    return (0);
}
```

```bash
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o test
./test
```

### Testing against the original

Since `ft_printf()` must behave like `printf()`, a simple way to check it is to print the same thing with both functions and compare both the output and the returned value:

```c
int a = printf("%s|%d|%x|%p\n", "abc", -42, 3735928559u, (void *)0);
int b = ft_printf("%s|%d|%x|%p\n", "abc", -42, 3735928559u, (void *)0);
// a and b must be equal and both lines must be identical
```

## Algorithm and data structure

### Overall approach

`ft_printf()` performs a **single linear pass** over the format string:

1. Initialise the argument list with `va_start`.
2. Walk the format string character by character.
3. If the character is `%` and is followed by another character, hand the next character to a dispatcher (`ft_conversion_type`), which reads the matching argument with `va_arg` and calls the right printing function. Two characters are consumed (`%` and the specifier).
4. Otherwise, print the character as it is.
5. Accumulate the number of bytes written by every call and return the total after `va_end`.

If the format pointer is `NULL`, the function returns `-1`.

### Why a dispatcher with one function per conversion

The mandatory part only requires nine conversions and no flags, width or precision, so a simple `if / else if` chain is the clearest and most readable option. Each branch calls a small, single-purpose function that **returns the number of characters it printed**. This has several benefits:

- The return value of `ft_printf()` is obtained by summing the return values, with no global state and no counter passed by pointer.
- Every function is short, independent and easy to test, and fits the Norme (function length, number of parameters).
- Adding a new conversion means writing one function and adding one branch.
- `%x` and `%X` share a single function, `ft_print_hex()`, which receives the digit set as a parameter (`"0123456789abcdef"` or `"0123456789ABCDEF"`). `%p` reuses it too, simply prefixing `0x`.

### Number printing: recursion instead of buffers

Numbers are printed **recursively**: to print `n` in base `b`, first print `n / b` (if `n >= b`) and then the last digit `n % b`. The digits come out in the right order without reversing anything, and **no memory is allocated** (no `malloc`, no temporary string, no array), so there is nothing to free and no possibility of leaks.

Some details worth noting:

- **`%d` / `%i`**: if the number is negative, `-` is printed and the value is converted to `long` before being negated. This is what makes `INT_MIN` work, since `-INT_MIN` does not fit in an `int`.
- **`%u`**: reuses the same decimal routine as `%d`, taking an `unsigned int`.
- **`%x` / `%X`**: take an `unsigned int`, passed to `ft_print_hex()` as an `unsigned long`.
- **`%p`**: the pointer is cast to `unsigned long` (wide enough to hold an address on 64-bit systems) and printed in lowercase hexadecimal prefixed by `0x`. A `NULL` pointer prints `(nil)`, matching glibc behaviour.
- **`%s`**: a `NULL` string prints `(null)`, matching glibc behaviour.
- **`%c`**: the argument is read as `int` (default argument promotion) and written as a single byte.

### Data structures

No custom data structure is needed. The only "structures" involved are:

- `va_list`, to traverse the variable arguments. It is created once in `ft_printf()` and passed to the dispatcher.
- A plain string holding the digit set for hexadecimal conversions, used as a lookup table (`base[n % 16]`).

This deliberately minimal design follows the subject's requirement of not reimplementing the original buffer management, and keeps the code simple, allocation-free and robust. If bonus features (flags `-0.# +`, width, precision) were added, the natural evolution would be a small parsing step filling a struct of flags before dispatching the conversion.

## Resources

### References

- `man 3 printf` – behaviour of the original function and its conversions.
- `man 3 stdarg` – `va_start`, `va_arg`, `va_copy` and `va_end`.
- Kernighan & Ritchie, *The C Programming Language* (2nd edition).

### Use of AI

In line with the project's AI guidelines, all the library code was written by me.
AI was used only to help structure this `README.md`. I reviewed the result
and I am able to explain every part of it.