# Huffman Coding Text File Compression and Decompression

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)

## Introduction

Welcome to our minor project repository! This project is focused on implementing a lossless compression and decompression program for text files using the Huffman Coding algorithm. Huffman Coding is a widely used data compression technique that assigns variable-length codes to input characters, with shorter codes for more frequent characters. This leads to efficient text file compression while ensuring no loss of data during decompression.

Our program is written in C and provides a simple yet effective way to compress and decompress text files. This README will guide you through the features and usage of our program.

## Features

- **Lossless Compression:** Our program guarantees that the decompressed text will be identical to the original, ensuring no data loss during the compression and decompression process.

- **Efficient Huffman Coding:** The program employs the Huffman Coding algorithm to achieve optimal compression, with shorter codes for more frequently occurring characters.

- **User-Friendly Interface:** We've designed a simple command-line interface that makes it easy to compress and decompress text files.

- **Portability:** The program is written in C, ensuring it can be run on various platforms without any issues.

## How It Works

The program works by constructing a Huffman tree based on the frequency of characters in the input text file. It then encodes the characters with shorter codes for frequently occurring characters and longer codes for less frequent ones. During decompression, the original text is reconstructed by traversing the Huffman tree.
