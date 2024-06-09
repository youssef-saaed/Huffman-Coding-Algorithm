# Huffman Coding Algorithm in C

This repository contains a C implementation of the Huffman coding algorithm, which is an efficient method for lossless data compression. The code constructs a Huffman tree based on the frequency of characters in a given message and generates a unique binary code for each character, minimizing the overall space required to store the message.

## Features

- **Dynamic Memory Allocation**: Efficient use of memory through dynamic allocation and deallocation.
- **Min-Heap Structure**: Utilization of a min-heap structure to build the Huffman tree in optimal time.
- **Bit-Level Operations**: Functions to display the message in bits before and after encoding to demonstrate the compression.

## Compilation and Execution

To compile the program, use the following command:

```sh
gcc -o HuffmanCodeAlgorithm HuffmanCodeAlgorithm.c
```

To run the program, execute the compiled binary:

```sh
./HuffmanCodeAlgorithm
```

## Usage

Upon execution, the program will prompt the user to enter a message that needs to be compressed. After input, the program will display the Huffman codes for each character, the original message in bits, and the compressed message in bits along with the storage size comparison.

## Code Structure

- `Node`: A structure representing a node in the Huffman tree.
- `MinHeap`: A structure representing a min-heap used to build the Huffman tree.
- `Pair`: A structure representing a key-code pair for each character.
- `HuffmanCodeAlgorithm`: The main function that orchestrates the reading of the message, construction of the Huffman tree, and encoding of the message.

## Functions

- `ReadMessage`: Reads the message to be compressed from the user.
- `CharFreqArrConstructor`: Constructs an array of characters and their corresponding frequencies from the message.
- `NewNode`, `NewMinHeap`, `NewPair`: Constructors for the `Node`, `MinHeap`, and `Pair` structures.
- `FreeMinHeap`, `FreePair`, `FreeBinaryTree`: Destructors for the `MinHeap`, `Pair`, and binary tree structures.
- `SwapNodes`: Swaps two nodes in the min-heap.
- `InsertInMinHeap`, `ExtractMin`: Functions to insert into and extract the minimum value from the min-heap.
- `HuffmanTree`: Constructs the Huffman tree from the character frequencies.
- `ProduceHuffmanCode`: Generates the Huffman codes for each character.
- `PrintBitsBeforeEncoding`, `PrintBitsAfterEncoding`: Functions to print the message in bits before and after encoding.

## Contributing

Contributions to improve the efficiency or readability of the code are welcome. Please feel free to fork the repository, make changes, and submit a pull request.

## License

This project is open-source and available under the [MIT License](LICENSE).
