# GeoSolitaire.ai - Solitaire Management System

A C++ project simulating a simplified digital solitaire game using geometric shape cards, where the card strength is defined by the area of the shape. The system organizes incoming cards into the minimum number of piles under specific placement rules and extracts the Longest Increasing Subsequence (LIS) of the card strengths as part of its strategic backend.

---

## Problem Description

GeoSolitaire.ai replaces number-based cards with geometric shapes — squares, rectangles, and triangles — where each card's strength is its shape's area.

Cards arrive sequentially and must be organized into piles following these rules:

- A card can be placed on top of an existing pile only if its strength (area) is **at most** the top card of that pile.
- Alternatively, create a new pile for the incoming card.

The goal is to minimize the number of piles.

Additionally, the system must compute a valid **Longest Increasing Subsequence (LIS)** of card strengths (areas) from the sequence of cards seen so far, aiding the development of automated players.

---

## Design Specifications

### Classes

- **Card (Abstract Base Class)**
  - Represents a card with virtual methods to compute area.
  - Overloads comparison operators to compare cards by area.
  - Overloads stream insertion (`<<`) and extraction (`>>`) operators for I/O.
  - Derived classes: `Square`, `Rectangle`, `Triangle`, each implementing area calculation.

- **CardOrganizer**
  - Manages piles and card placement.
  - Methods:
    - `void addCard(Card*)`: Inserts a card into a suitable pile or creates a new pile.
    - `size_t getPileCount() const`: Returns the current minimum number of piles.
    - `std::vector<Card*> getLIS() const`: Returns a valid Longest Increasing Subsequence of cards based on area.

---

## Input Format

- The first line contains `q` — the number of queries.
- Each of the next `q` lines is one of the following:
  
  **Add Card Query:**
-1 SHAPE param1 [param2]
```
- For `SQUARE`: `1 SQUARE edge`
For `RECTANGLE`: `1 RECTANGLE length breadth`
For `TRIANGLE`: `1 TRIANGLE base height`
```

**Pile Count Query:**
- Prints the current minimum number of piles.

**LIS Query:**
- Prints a valid Longest Increasing Subsequence of cards encountered so far.

---

## Output Format

- For **Pile Count Query (2)**: Print a single integer — the current minimum number of piles.
- For **LIS Query (3)**:
- First, print the size `n` of a valid LIS.
- Then print `n` lines, each describing a card in the LIS, using the same format as input (shape and parameters).
- Use `\n` (newline) instead of `std::endl` for output to avoid TLE.

---

## Constraints

- `1 <= q <= 10^5`
- Card areas are integers and do not exceed `10^9`.
- Number of LIS queries (`3`) does not exceed 10^3.

---



