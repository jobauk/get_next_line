_This project has been created as part of the 42 curriculum by jaukes._

## Description

`get_next_line(int fd)` reads text from a file descriptor one line at a time. The returned line includes the newline when there is one. The caller must free each line. The function returns `NULL` when there is nothing left to read or an error occurs.

The normal/mandatory version may only read from a single open file descriptor at a time. The bonus version can read from an indefinite amount of file descriptors at a time. Re-using a file descriptor (e.g. reading half the file, closing the fd, and then opening a new file that gets the same fd) is undefined behaviour and will yield weird results.

## Instructions

To use these functions compile your source files along with the `*.c` files in this repository. Compile using:

```sh
cc -Wall -Wextra -Werror -DBUFFER_SIZE=42 \
    $YOUR_FILES get_next_line.c get_next_line_utils.c
```

You may omit `-DBUFFER_SIZE`. This will use a default buffer size of `1024` bytes.

To run a demo you can:

```sh
cc -Wall -Wextra -Werror -DBUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c -o demo
printf 'first\n\nlast' > demo.txt
./demo demo.txt
```

For the bonus it prints the
descriptor next to each line so you can see the reads alternate.

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line_bonus.c get_next_line_utils_bonus.c -o demo_bonus
printf 'A1\nA2\n' > first.txt
printf 'B1\n\nB3' > second.txt
./demo_bonus first.txt second.txt
```

## Algorithm

The read buffer keeps track of how many bytes were read and where to resume on the next call. When the buffer runs out, `read()` fills it with up to `BUFFER_SIZE` bytes. The function builds the line one byte at a time until it finds a newline or reaches EOF. Any bytes after the newline stay in the buffer for the next call.

The line starts with room for 128 bytes and grows by about half whenever it needs more space. This avoids allocating for every byte which is wildly inefficient. Once the line is complete it `\0` terminates the string and returns it.

The normal version uses a single variable to hold the state while the bonus version uses a linked list where every `t_state` has a pointer to the next. Each active descriptor gets a node with its own buffer and read position. The function looks up the node once per call. The node is freed when it detects EOF or an error.

## Resources

I used the man pages. AI was used to confirm my thoughts about re-used file descriptors.
