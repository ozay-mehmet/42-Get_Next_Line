*This project has been created as part of the 42 curriculum by mozay.*

# 🚀 Get Next Line

---

## 📄 Description
`get_next_line` is a C function that reads and returns the next line from a given file descriptor each time it is called. Its main objective is to provide a reliable way to read files line by line, regardless of the file's size or the length of its lines. The function dynamically allocates memory for each line, ensuring that even extremely long lines are handled correctly without buffer overflows or memory leaks.

Key features and behaviors:
- Reads from any file descriptor (such as files, standard input, or pipes).
- Returns each line including the newline character (`\n`) if present, or the last line if it does not end with a newline.
- Manages an internal buffer ("stash") to store leftover data between calls, so no data is lost between reads.
- Handles arbitrary buffer sizes, as defined by the `BUFFER_SIZE` macro.
- The bonus version supports reading from multiple file descriptors simultaneously, maintaining separate buffers for each.

This project is a fundamental exercise in the 42 curriculum, teaching students about low-level file I/O, dynamic memory management, and robust error handling in C. It also encourages writing clean, modular code and understanding the importance of resource management in systems programming.

---

## ⚙️ Instructions

### Compilation
- **Mandatory version:**
  ```sh
  gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o gnl
  ```
- **Bonus version:**
  ```sh
  gcc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
  ```

### Usage Example
```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void) {
    int fd = open("file.txt", O_RDONLY);
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```
- Call `get_next_line(fd)` in a loop to read each line.
- Free each returned string after use.

---

## 🧠 Algorithm Explanation & Justification
The function uses a static buffer ("stash") to store unread data between calls. It reads chunks from the file descriptor, appends them to the stash, and extracts lines one by one. This minimizes system calls and efficiently handles lines of any length. The bonus version keeps a separate stash for each file descriptor, enabling concurrent reads. This approach is chosen for its balance of performance, memory efficiency, and correctness.

---

## 📚 Resources
- POSIX [`read(2)`](https://man7.org/linux/man-pages/man2/read.2.html) manual page
- Standard C library documentation (`malloc`, `free`, string functions)
- 42 subject PDF for Get Next Line

---

## 🤖 AI Usage
- AI was used to help write and improve the README, draft documentation, summarize project requirements, and clarify algorithm explanations.