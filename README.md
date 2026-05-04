# 🧮 Fraction Calculator: Mixed Numbers & Simplification

> A C++ program designed to process and calculate mixed-number fractions. It reads user input containing optional integral parts, performs arithmetic operations, and returns results in their simplest reduced form.

## ⚙️ The Challenge
The program must handle "Proper Fractions with optional integral parts" using a specific input format (e.g., `Integral | Numerator/Denominator`). The core logic involves:
1. **Parsing**: Extracting values separated by the vertical bar (`|`) and forward slash (`/`).
2. **Conversion**: Transforming mixed numbers into improper fractions for calculation.
3. **Reduction**: Implementing the **Greatest Common Divisor (GCD)** algorithm to ensure all results are displayed in the simplest form.
4. **Formatting**: Converting improper results back into mixed numbers for the final output.

## ✨ Features
- **Mixed Number Support**: Handles fractions with or without an leading whole number (e.g., `0 | 2/3` or `2 | 3/4`).
- **Comprehensive Arithmetic**: Calculates both the **Sum** and the **Product** of two given fractions.
- **Simplest Form Logic**: Automatically reduces fractions (e.g., `2/4` becomes `1/2`).
- **Strict I/O Constraints**: Exclusively uses `cin` and `cout`, avoiding legacy C functions like `printf` or `scanf`.

## 🎨 Example Interaction
- **Input**: `2 | 3/4` and `3 | 5/6`
- **Sum Output**: `2(3/4) + 3(5/6) = 6(7/12)`
- **Product Output**: `2(3/4) x 3(5/6) = 10(13/24)`

## 🛠️ Tech Stack
- **Language**: C++
- **Libraries**: `<iostream>` (for `cin`/`cout`), `<string>`, and `<limits>`.
- **Constraints**: No C-style I/O functions allowed.

## 🚀 How to Run

### Compilation
```bash
g++ addDriver.cpp addFunctions.cpp -o [your_file_name].exe
```
