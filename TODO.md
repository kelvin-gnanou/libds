# Roadmap

This file tracks the work needed to move the project from an educational C11 implementation toward a stable, reusable library. Completed items describe repository changes; they do not by themselves mean that the behavior has been fully validated on every platform.

## Features

- [ ] Add an iterator to allow users to traverse the data structure.
- [ ] Support generic data types using `void *` instead of `int`.
- [ ] Add a custom data comparator
- [ ] Implement tree balancing to prevent the tree from degenerating into a linked list.
- [ ] verify intallation's files before uninstall


## Completed repository work

- [x] Separate public headers (`include/ds/`), library sources (`src/`), tests (`tests/`), and demo sources/headers (`examples/src/`, `examples/include/`).
- [x] Add Make targets for the static library, demo, tests, debug/release/sanitizer build modes, and cleanup.
- [x] Add automatic header dependency generation and separate build output by configuration.
- [x] Add `install` and `uninstall` targets with configurable `PREFIX`, installation directories, and `DESTDIR` staging.
- [x] Document build commands, installation, linking, current API, internal clear helpers, and known limitations in `README.md`.
- [x] Ignore generated C build, coverage, profiling, editor, and operating-system files.

- [x] Exercise install and uninstall with a temporary `DESTDIR`; confirm only the expected files are created and removed.

## 1. Validate installation and library consumption

- [ ] Compile and link a small independent C program against the staged `libds.a` and installed public headers.
- [ ] Verify the documented `clang *.c -lds` command on the intended development environment; document explicit `-I`/`-L` flags where default search paths differ.
- [ ] Check installation and uninstall behavior with a custom `PREFIX` and matching directory overrides.

## 2. Stabilize the public API

- [ ] Document the behavior of every public function for null handles, invalid indices, empty containers, and optional output pointers.
- [ ] Decide whether stack, queue, list, and tree should expose public `ds_*_clear()` operations. The current `ds_*_clear` functions are private `static` helpers used by destruction and are not callable by library users.
- [ ] Decide whether to activate the `ds_status` error type or retain the current `bool`/`NULL` failure reporting; remove or complete the placeholder header accordingly.
- [ ] Document ownership, lifetime, copied-handle behavior, and thread-safety expectations.
- [ ] Define graph behavior for duplicate edges, self-loops, invalid vertices, and edge insertion failure.
- [ ] Reconcile all public API documentation and examples with declarations in `include/ds/*.h`.

## 3. Strengthen implementation and validation

- [ ] Expand tests for empty/single-element structures, repeated mutation cycles, invalid arguments, and allocation-failure paths where practical.
- [ ] Run the complete test suite in debug, release, and sanitizer configurations.
- [ ] Investigate GCC `-fanalyzer`'s possible null dereference warning in `ds_queue_dequeue()` (reported through `ds_queue_clear()`); verify the queue invariants and add a guard or regression test if needed.
- [ ] Run AddressSanitizer and UndefinedBehaviorSanitizer in an environment where LeakSanitizer works. In this environment, `make BUILD=sanitize test` fails in LeakSanitizer; `ASAN_OPTIONS=detect_leaks=0 make BUILD=sanitize test` passes but disables leak detection, so memory leaks remain unverified.
- [ ] Validate builds with both GCC and Clang.
- [ ] Review graph insertion for transactional behavior when adding an undirected edge fails partway through.
- [ ] Review tree recursion depth and document worst-case complexity for the unbalanced tree.
- [ ] Verify public headers are self-contained and that an external program can include the umbrella header.

## 4. Prepare distribution documentation

- [ ] Choose and document a versioning policy before publishing a stable release.
- [ ] Add CI for compiler builds and tests once the supported compiler/platform matrix is chosen.
- [ ] Consider generating a `pkg-config` file to simplify consumer compiler and linker flags.
- [ ] Add focused files under `docs/` when the material outgrows the README: API contracts, architecture, development/testing, and integration examples.
- [ ] Keep `README.md` as the project overview and quick start; do not create empty documentation files that duplicate it.

## Release readiness

A first stable release should wait until the public API is documented and internally consistent, staged installation and external linking have been verified, the test suite passes in the supported configurations, and the README matches the shipped behavior.
