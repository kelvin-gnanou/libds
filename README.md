# libds - Data Structures in C

[![Status](https://img.shields.io/badge/status-in%20development-orange)]()
[![Language](https://img.shields.io/badge/language-C11-blue)]()
[![License](https://img.shields.io/badge/license-MIT-green)]()
[![Focus](https://img.shields.io/badge/focus-data%20structures%20%26%20algorithms-purple)]()

> A C11 project that implements classic integer data structures. It is organized as a reusable static library, with a separate interactive demo and test suite. The project is under active development; its API and documentation may change.

## Contents

- [Features](#features)
- [Project status and scope](#project-status-and-scope)
- [Architecture](#architecture)
- [Requirements](#requirements)
- [Build configurations](#build-configurations)
- [Run the demo](#run-the-demo)
- [Tests](#tests)
- [Public API](#public-api)
- [Internal implementation](#internal-implementation)
- [Memory and error behavior](#memory-and-error-behavior)
- [Install and uninstall](#install-and-uninstall)
- [Use from another C project](#use-from-another-c-project)
- [Known limitations](#known-limitations)
- [Contributing](#contributing)
- [License](#license)

## Features

The library currently provides:

- an integer stack (LIFO);
- an integer queue (FIFO);
- a singly linked list of integers;
- an integer binary search tree;
- a graph whose vertices are identified by integer indices and whose edges can be directed or undirected.

The library is built as `libds.a`. The interactive demonstration program and unit tests are separate executables and are not included in the library archive.

## Project status and scope

This is an educational project becoming a reusable library. It currently targets C11 and supports the five structures listed above. It is not yet a stable, versioned release: public contracts, edge-case behavior, and installation support are still being refined.

The library stores `int` values in the stack, queue, list, and tree. Graph vertices are represented by indices from zero to the graph's configured size minus one. It has no third-party runtime dependencies.

## Architecture

```text
include/ds/       Public headers installed for library users
src/              Library implementation
examples/include/ Private declarations used by the demo
examples/src/     Interactive demo and structure demonstrations
tests/            Unit tests
build/<mode>/     Generated objects, library, and executables
Makefile          Build, test, install, uninstall, and cleanup targets
```

`include/ds/ds.h` is the umbrella header. Consumers can include it to access all public structure headers. The installed public headers retain the `ds/` namespace, for example `#include <ds/stack.h>`.

## Requirements

- GNU Make;
- a C11-compatible compiler (the Makefile uses `cc` by default; set `CC=clang` or `CC=gcc` to choose another compiler);
- an archiver such as `ar` for creating the static library;
- the `install` utility for the Makefile's install and uninstall targets.

Check the tools with:

```sh
make --version
cc --version
```

## Build configurations

Build the static library and demo with the default debug configuration:

```sh
make
```

Select a configuration with `BUILD`:

```sh
make BUILD=debug       # debug symbols, no optimization
make BUILD=release     # optimized build
make BUILD=sanitize    # AddressSanitizer and UndefinedBehaviorSanitizer
```

Each configuration has its own output directory, so its object files are not reused by another configuration. Generated files are placed under `build/<mode>/`:

```text
build/<mode>/lib/libds.a
build/<mode>/bin/ds-demo
build/<mode>/bin/ds-tests
```

Useful build targets:

| Command | Action |
|---|---|
| `make` or `make all` | Build the library and demo |
| `make library` | Build only `libds.a` |
| `make demo` | Build only the interactive demo (and its library dependency) |
| `make test` | Build and run the test suite |
| `make check` | Alias for `make test` |
| `make clean` | Remove artifacts for the selected `BUILD` mode |
| `make clean-all` | Remove the complete build directory |
| `make help` | Show all Makefile targets and configurable variables |

Compiler and linker options can be supplied through the standard Make variables, for example `make CC=clang CFLAGS='-std=c11 -O2'`.

## Run the demo

Build and launch the interactive menu with:

```sh
make run
```

The demo lets you choose a stack, queue, linked list, binary search tree, or graph demonstration. `make` builds the demo but does not launch it.

## Tests

Build and run the current unit test suite with:

```sh
make test
```

Run it with AddressSanitizer and UndefinedBehaviorSanitizer using:

```sh
make BUILD=sanitize test
```

The tests use C `assert()` checks and cover common operations for each structure. They do not yet constitute exhaustive validation of allocation failures, all invalid inputs, or every graph edge case.

## Public API

The **public API** is the set of declarations in the installed headers under `include/ds/`. These functions are intended to be called by applications that link against `libds.a`.

| Structure | Header | Public operations |
|---|---|---|
| Stack | `ds/stack.h` | `ds_stack_create`, `ds_stack_destroy`, `ds_stack_empty`, `ds_stack_size`, `ds_stack_push`, `ds_stack_pop` |
| Queue | `ds/queue.h` | `ds_queue_create`, `ds_queue_destroy`, `ds_queue_empty`, `ds_queue_size`, `ds_queue_enqueue`, `ds_queue_dequeue` |
| Linked list | `ds/list.h` | `ds_list_create`, `ds_list_destroy`, `ds_list_empty`, `ds_list_size`, `ds_list_push_front`, `ds_list_push_back`, `ds_list_pop_front`, `ds_list_pop_back`, `ds_list_remove_first`, `ds_list_remove_last` |
| Binary search tree | `ds/tree.h` | `ds_tree_create`, `ds_tree_destroy`, `ds_tree_insert`, `ds_tree_contain`, `ds_tree_size`, `ds_tree_height` |
| Graph | `ds/graph.h` | `ds_graph_create`, `ds_graph_destroy`, `ds_graph_size`, `ds_graph_insert` |

The umbrella header is:

```c
#include <ds/ds.h>
```

### Public `clear` operations

There are currently **no public `*_clear()` functions** in the headers. Applications cannot call `ds_stack_clear()`, `ds_queue_clear()`, `ds_list_clear()`, or `ds_tree_clear()` through the supported public API. To release a structure and its contents, call its public `*_destroy()` function; the handle is set to `NULL`.

The `clear` helpers currently present in the stack, queue, list, and tree implementation files are internal `static` functions. They release nodes as part of destruction and are not exported library functions. A future API change may expose public clear operations, but that requires adding declarations and defining their public contracts first.

## Internal implementation

The **internal implementation** consists of the source files in `src/`, private structure layouts, and `static` helper functions. These are implementation details: applications should include `ds/...` public headers and should not depend on private structs or source-level helpers.

In particular, `ds_stack_clear`, `ds_queue_clear`, `ds_list_clear`, and `ds_tree_clear` are file-local helpers. The graph implementation also has a private edge insertion helper. The declarations in `examples/include/examples.h` belong only to the demonstration program; they are not part of the library API.

## Memory and error behavior

- Create functions return a structure handle, or `NULL` if allocation fails.
- Insert and mutation functions that can fail return `bool`.
- Pop and dequeue operations accept an optional output pointer for the removed value; consult the corresponding header for the exact contract.
- Destroy functions take a pointer to the handle, release owned allocations, and set the handle to `NULL`.
- Values are stored by value as `int`; callers do not transfer ownership of separate value allocations.

The `ds_status` enumeration is defined in `include/ds/status.h`, but it is intentionally not included by the umbrella header `ds/ds.h` and is not used by the current public functions. Adopting it would require redesigning several function return types and signatures. That API refactor is deferred until a more stable release; for now, operations report failure with `bool` or `NULL`, and callers cannot distinguish detailed error causes.

The API documentation is still being completed. In particular, applications should review the public headers for the current behavior of null arguments and optional output pointers. Thread-safety guarantees have not been specified; callers should synchronize access when sharing mutable structures between threads.

## Install and uninstall

Install the library, public headers, and project documentation under `/usr/local`:

```sh
make library
sudo make install
```

The files are installed to:

```text
/usr/local/lib/libds.a
/usr/local/include/ds/*.h
/usr/local/share/doc/ds/README.md
/usr/local/share/doc/ds/LICENSE
```

To install under a user-owned prefix, for example `$HOME/.local`, use:

```sh
make install PREFIX="$HOME/.local"
```

To stage files for packaging without writing to the system, use `DESTDIR`:

```sh
make install DESTDIR=/tmp/ds-package
```

Pass the same `PREFIX`, `LIBDIR`, `INCLUDEDIR`, `DOCDIR`, and `DESTDIR` values when uninstalling as were used for installation. For the default system installation:

```sh
sudo make uninstall
```

The uninstall target removes the library, this project's public headers, and its installed README and license. It attempts to remove the project's empty include and documentation directories, but leaves non-empty shared directories in place.

## Use from another C project

After a default `/usr/local` install, a client can include the public API and link the static library:

```c
#include <ds/ds.h>

int main(void) {
    ds_stack_t stack = ds_stack_create();
    if (stack == NULL) {
        return 1;
    }

    (void)ds_stack_push(stack, 42);
    ds_stack_destroy(&stack);
    return 0;
}
```

For a client whose source files are in the current directory, the requested short form is:

```sh
clang *.c -lds -o my-program
```

This relies on the compiler and linker searching `/usr/local/include` and `/usr/local/lib` by default, which is common but platform-dependent. If those paths are not searched, specify them explicitly:

```sh
clang -I/usr/local/include *.c -L/usr/local/lib -lds -o my-program
```

For a custom prefix, use that prefix's include and library directories, for example:

```sh
clang -I"$HOME/.local/include" *.c -L"$HOME/.local/lib" -lds -o my-program
```

## Known limitations

- Containers currently store integers only; there is no generic element or callback interface.
- The graph uses fixed, numeric vertex indices; named vertices, edge removal, traversal, and path algorithms are not provided.
- The tree is an unbalanced binary search tree, so its worst-case operation depth can be linear.
- Duplicate values are documented as ignored for the tree; duplicate-edge and self-loop semantics for graphs still need a complete public contract.
- Public `clear` operations and structured status-code errors are not yet available.
- The project does not yet publish a stable versioned ABI, shared library, package metadata, or a `pkg-config` file.

## Contributing

Contributions are welcome. Before proposing a change:

1. Make a focused change and update relevant public-header documentation.
2. Add or update tests for the behavior being changed.
3. Run `make clean && make test`; when relevant, also run `make BUILD=sanitize test`.
4. Update this README if build, installation, public API, or supported behavior changes.

## License

This project is distributed under the MIT License. See [LICENSE](LICENSE) for the full text.
