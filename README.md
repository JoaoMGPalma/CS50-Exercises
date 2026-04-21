# CS50 Implementation Showcase: C & Python

This repository contains a collection of systems-level and algorithmic projects originally developed during Harvard’s CS50, now refactored for **maximum portability and independence**. By stripping away pedagogical libraries (like `cs50.h`), these implementations demonstrate a professional-grade grasp of the standard C library and Python's native capabilities.

---

## 🚀 Market-Valued Technical Highlights

In today's competitive landscape, this codebase demonstrates specific high-demand competencies:

* **Manual Memory Management (C):** Proficiency in the "Forensics" (`recover.c`) and "Data Structures" (`dictionary.c`) modules demonstrates a deep understanding of the heap and stack, pointer arithmetic, and the prevention of memory leaks—essential for high-performance systems engineering.
* **Algorithmic Efficiency:** The `speller` implementation utilizes a custom **Hash Table** with a $O(1)$ average lookup time, showcasing an ability to optimize for big-data scenarios where search speed is critical.
* **Bit-Level Forensics:** The `recover` utility demonstrates the ability to parse raw binary data and manipulate file headers, skills directly applicable to cybersecurity and data recovery roles.
* **Polyglot Logic:** By implementing the `readability` and `credit` logic in both C and Python, this repository showcases "logic-first" thinking—the ability to solve a problem regardless of the syntax.

---

## 📂 Project Directory

### 💳 [credit.py](credit.py)
* **Algorithm Mastery:** Implements **Luhn’s Algorithm** to validate credit card numbers.
* **Key Skill:** Uses mathematical logic rather than string manipulation to parse digits, demonstrating a focus on computational efficiency.

### 🌳 [inheritance.c](inheritance.c)
* **Recursive Logic:** Simulates genetic inheritance across multiple generations.
* **Key Skill:** Mastery of **recursive data structures** and dynamic memory allocation for nested "ancestor" nodes.

### 📚 [readability.c](readability.c) & [readability.py](readability.py)
* **Text Analysis:** Computes the **Coleman-Liau index** to determine the reading grade level of a text.
* **Key Skill:** Multi-language implementation and character-stream parsing.

### 📷 [recover.c](recover.c)
* **Digital Forensics:** Recovers deleted JPEGs from a raw memory card image by identifying **hexadecimal magic bytes**.
* **Key Skill:** Low-level File I/O and bitwise operations (`&` mask) to identify file signatures.

### 📖 [speller-dictionary.c](speller-dictionary.c)
* **High-Performance Data Structures:** A spell-checker that loads 140,000+ words into a **Hash Table** with linked-list collision handling.
* **Key Skill:** Designing custom data structures to minimize "Big O" time complexity.

### 🔊 [volume.c](volume.c)
* **Digital Signal Processing (DSP):** A utility that adjusts the volume of WAV files by scaling 16-bit audio samples.
* **Key Skill:** Binary file header preservation and handling of `int16_t` signed integers for raw audio processing.

---

> **Note on Portability:** All C files are compiled using standard `gcc` and do not require external dependencies. All Python files are compatible with Python 3.10+.
