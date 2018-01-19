# Simpletron
From the apprentice Lab 10.10 (maybe).

The requirements given are as follows.
![requirements](requirements.jpg)

However I have also added in a stack which grows up from the bottom of the memory. I have also added a call and return opcode and a memory dump opcode for debugging, and added instructions to implement a simplistic printing function.

## New Instructions

| Instruction | Human Readable Description | 
| --- | --- | 
| 12xx | WRITE the Accumulator contents to stdout |
| 22xx | PUSH the Accumulator to the stack |
| 23xx | POP from stack to accumulator |
| 24xx | CALL subroutine at the memory location currently in the accumulator. The current `programCounter` is pushed to the stack |
| 25xx | RETurn from subroutine to the memory location popped from the stack. |
| 99xx | DUMP memory to stdout |
| 50xx | LOAD Literal __xx__ into accumulator |
| 51xx | LOAD from Address in accumulator, into the accumulator |

## Considerations

1. The `CALL` and `RET` instructions rely on the `programCounter` to be the next item in the stack. Each subroutine must therefore ensure that there is a `POP` for every `PUSH` performed.
2. The 100 words of memory are not used to hold the program code, there is a separate program memory for this.

## Build and Run

The project uses cmake, so to make use:

```bash
> mkdir build
> cd build
> cmake ..
> make
```

To run tests:
```bash 
> ./tests/simpletron_test
```

To run as normal:
```bash
> ./src/simpletron
```

To enable debug messages run with debug as the argument
```bash
> ./src/simpletron debug 
```