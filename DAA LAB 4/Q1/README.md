# Application of Sorting-I

## Problem Statement

Assume that we are given `n` pairs of items as input, where the first item is a number and the second item is one of three colours: **Red, Blue, or Yellow**.

The items are already sorted by number.

Design an **O(n)** algorithm to sort the items by colour in the order:

**Red → Blue → Yellow**

while maintaining the sorted order of numbers among items having the same colour.

By choosing a proper input representation, write a C program to validate the algorithm.

---

## Aim

To sort a set of number-colour pairs by colour in the order **Red, Blue, Yellow** while preserving the original sorted order of numbers within each colour, using **O(n)** time.

---

## Key Idea

Since the input is **already sorted by number**, we do not need to perform another comparison-based sorting operation.

We can use **three separate arrays**:

- `red[]` — stores numbers whose colour is Red.
- `blue[]` — stores numbers whose colour is Blue.
- `yellow[]` — stores numbers whose colour is Yellow.

We scan the input exactly once.

Because the input numbers are already sorted, numbers inserted into each colour array will automatically remain sorted.

Finally, we concatenate:

```text
Red + Blue + Yellow
```

This gives the required ordering.

---

## Algorithm

### Step-by-Step

1. Create three arrays:
   - `red[]`
   - `blue[]`
   - `yellow[]`

2. Initialize three indices:
   ```text
   r = 0
   b = 0
   y = 0
   ```

3. Traverse the input array from left to right.

4. For every pair `(number, colour)`:
   - If the colour is **Red**, store the number in `red[]`.
   - If the colour is **Blue**, store the number in `blue[]`.
   - If the colour is **Yellow**, store the number in `yellow[]`.

5. Since the original input is sorted by number, each of the three arrays is automatically sorted.

6. Copy all elements of `red[]` into the output array.

7. Copy all elements of `blue[]` after the red elements.

8. Copy all elements of `yellow[]` after the blue elements.

9. The resulting array is sorted by:
   ```text
   Red → Blue → Yellow
   ```
   while preserving the numerical order within each colour.

---

## Pseudocode

```text
ALGORITHM SortByColour(A, n)

    Create arrays red, blue, yellow

    r ← 0
    b ← 0
    y ← 0

    FOR i ← 0 TO n - 1

        IF A[i].colour = RED
            red[r] ← A[i].number
            r ← r + 1

        ELSE IF A[i].colour = BLUE
            blue[b] ← A[i].number
            b ← b + 1

        ELSE
            yellow[y] ← A[i].number
            y ← y + 1

    index ← 0

    FOR i ← 0 TO r - 1
        output[index] ← (red[i], RED)
        index ← index + 1

    FOR i ← 0 TO b - 1
        output[index] ← (blue[i], BLUE)
        index ← index + 1

    FOR i ← 0 TO y - 1
        output[index] ← (yellow[i], YELLOW)
        index ← index + 1

    RETURN output
```

---

## Why Does It Work?

The input is already sorted by number.

For example:

```text
(10, Blue)
(20, Red)
(30, Blue)
(40, Yellow)
(50, Red)
(60, Yellow)
```

While scanning from left to right:

```text
Red:    20, 50
Blue:   10, 30
Yellow: 40, 60
```

Each colour array remains sorted because the numbers were encountered in increasing order.

After concatenation:

```text
(20, Red)
(50, Red)
(10, Blue)
(30, Blue)
(40, Yellow)
(60, Yellow)
```

The colours are correctly grouped:

```text
Red → Blue → Yellow
```

and the numbers within each colour remain sorted.

---

## Correctness

### Invariant

After processing the first `i` input elements:

- `red[]` contains exactly the Red elements among the first `i` elements, in increasing numerical order.
- `blue[]` contains exactly the Blue elements among the first `i` elements, in increasing numerical order.
- `yellow[]` contains exactly the Yellow elements among the first `i` elements, in increasing numerical order.

### Initialization

Before processing any element, all three arrays are empty.

Therefore, the invariant is true.

### Maintenance

When a new element is processed, it is appended to the array corresponding to its colour.

Since the original input is sorted by number, the new number is greater than or equal to the previously stored numbers.

Therefore, each colour array remains sorted.

### Termination

After all `n` elements have been processed, the three arrays contain all input elements grouped by colour and sorted by number within each group.

Concatenating them in the order:

```text
Red → Blue → Yellow
```

produces the required result.

Therefore, the algorithm is correct.

---

## Time Complexity Analysis

Let there be `n` input pairs.

### 1. Scanning the input

We visit every element exactly once:

```text
n operations
```

Therefore:

```text
O(n)
```

### 2. Copying Red elements

If there are `R` red elements:

```text
O(R)
```

### 3. Copying Blue elements

If there are `B` blue elements:

```text
O(B)
```

### 4. Copying Yellow elements

If there are `Y` yellow elements:

```text
O(Y)
```

Since every element has exactly one colour:

```text
R + B + Y = n
```

Therefore total work is:

```text
T(n) = O(n) + O(R) + O(B) + O(Y)

     = O(n) + O(R + B + Y)

     = O(n) + O(n)

     = O(n)
```





### Final Time Complexity

```text
Best Case    = O(n)
Average Case = O(n)
Worst Case   = O(n)
```

The complexity is **O(n)** in all cases because every element must be examined at least once.

---

## Space Complexity

We use three additional arrays and an output array.

In the worst case, all `n` elements may belong to one colour.

Therefore:

```text
red[] + blue[] + yellow[] = O(n)
```

and the output array also requires:

```text
O(n)
```

Hence:

```text
Space Complexity = O(n)
```

---

## C Program

```c
#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int number;
    char colour[10];
} Item;

int main() {
    int n;

    Item input[MAX];
    Item red[MAX], blue[MAX], yellow[MAX], output[MAX];

    int r = 0, b = 0, y = 0;
    int index = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("\nEnter the items in increasing order of number:\n");

    for (int i = 0; i < n; i++) {
        printf("Enter number and colour (Red/Blue/Yellow): ");
        scanf("%d %s", &input[i].number, input[i].colour);
    }

    /*
       Distribute elements into three arrays.
       Since input is already sorted by number,
       each array automatically remains sorted.
    */
    for (int i = 0; i < n; i++) {

        if (strcmp(input[i].colour, "Red") == 0) {
            red[r++] = input[i];
        }
        else if (strcmp(input[i].colour, "Blue") == 0) {
            blue[b++] = input[i];
        }
        else if (strcmp(input[i].colour, "Yellow") == 0) {
            yellow[y++] = input[i];
        }
        else {
            printf("Invalid colour: %s\n", input[i].colour);
            return 1;
        }
    }

    /* Copy Red elements */
    for (int i = 0; i < r; i++) {
        output[index++] = red[i];
    }

    /* Copy Blue elements */
    for (int i = 0; i < b; i++) {
        output[index++] = blue[i];
    }

    /* Copy Yellow elements */
    for (int i = 0; i < y; i++) {
        output[index++] = yellow[i];
    }

    printf("\nSorted by Colour:\n");

    for (int i = 0; i < n; i++) {
        printf("(%d, %s)\n",
               output[i].number,
               output[i].colour);
    }

    return 0;
}
```

---

## Sample Input

```text
Enter number of items: 8

Enter number and colour (Red/Blue/Yellow):
10 Blue
20 Red
30 Yellow
40 Blue
50 Red
60 Yellow
70 Red
80 Blue
```

## Sample Output

```text
Sorted by Colour:

(20, Red)
(50, Red)
(70, Red)
(10, Blue)
(40, Blue)
(80, Blue)
(30, Yellow)
(60, Yellow)
```

---

## Complexity Summary

| Operation | Complexity |
|---|---:|
| Scan input | O(n) |
| Store by colour | O(n) |
| Construct output | O(n) |
| **Total Time** | **O(n)** |
| **Space** | **O(n)** |

---

## Conclusion

The algorithm exploits the fact that the input is **already sorted by number**. Instead of sorting the elements again, it performs a single traversal and distributes the elements into three colour-specific arrays.

Finally, the arrays are concatenated in the order:

```text
Red → Blue → Yellow
```

Thus, the required ordering is achieved in **O(n) time**, while preserving the sorted numerical order within each colour.