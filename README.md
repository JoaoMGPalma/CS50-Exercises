# CS50 Projects: C & Python Implementation (Lectures 1 - 6)

This is a collection of the low-level systems and algorithmic work I did during Harvard’s CS50. I’ve refactored these to be **completely independent**—I stripped out the `cs50.h` library and replaced it with standard C and Python built-ins. 

It was a great exercise in moving from "classroom code" to "real-world code" where you can't rely on helper libraries to handle things like input or string management for you.

---

## 🚀 Technical Highlights

If you're looking through this for a role, here is the stuff that actually matters:

* **Manual Memory Management (C):** Projects like `recover.c` and `dictionary.c` are where I really got comfortable with the heap and stack. I’m handling pointers, malloc, and freeing memory manually to ensure zero leaks.
* **Algorithmic Efficiency:** My `speller` implementation uses a custom **Hash Table**. I went with a $O(1)$ average lookup time, which is exactly what you need when you're checking 140,000+ words in a fraction of a second.
* **Forensics & Bit-Level Logic:** In `recover.c`, I’m parsing raw binary data and using bitwise masks (`&`) to find JPEG headers. It’s a deep dive into how data is actually stored on a disk.
* **Polyglot Logic:** I implemented the `readability` and `credit` logic in both C and Python. It shows I can solve the problem regardless of which language I'm using.

---

## 📂 Project Directory

### 💳 [credit.py](credit.py)
* **What it does:** Validates credit card numbers using **Luhn’s Algorithm**.
* **The "Win":** I used purely mathematical logic to peel off digits rather than converting everything to strings. It’s much faster and cleaner.

### 🌳 [inheritance.c](inheritance.c)
* **What it does:** Simulates blood type inheritance across generations.
* **The "Win":** This was my deep dive into **recursion** and nested data structures.

### 📚 [readability.c](readability.c) & [readability.py](readability.py)
* **What it does:** Calculates the Coleman-Liau index to grade the difficulty of a text.
* **The "Win":** A straightforward example of parsing character streams and handling multi-language logic.

### 📷 [recover.c](recover.c)
* **What it does:** Recovers "deleted" JPEGs from a raw forensic image.
* **The "Win":** No libraries used—just raw C, `fread`, and hexadecimal signature matching.

### 📖 [speller-dictionary.c](speller-dictionary.c)
* **What it does:** A lightning-fast spell checker.
* **The "Win":** Implemented a Hash Table with linked-list collision handling from scratch.

### 🔊 [volume.c](volume.c)
* **What it does:** Adjusts the volume of WAV files by scaling raw audio samples.
* **The "Win):** Demonstrates how to preserve a 44-byte binary header while manipulating the 16-bit audio data that follows.

---

> **Note:** The C files here are standard `gcc` compatible and have zero external dependencies. The Python files are built for Python 3.10+.
