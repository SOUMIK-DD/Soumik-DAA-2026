# Defective Coin Problem – Divide and Conquer

## Problem Statement

There are `n` coins. All coins have the same weight except possibly one coin which may be lighter than the others.

Using a balance weighing scale, we need to find the defective (lighter) coin if it exists. If all coins have the same weight, we should report that no defective coin exists.

The algorithm should use the **Divide and Conquer** approach and run in:

**O(log₂ n + c)** time.

---

## Approach

The main idea is to divide the coins into two equal groups and compare their total weights.

### Cases

1. **Left group is lighter**

   The defective coin must be in the left group.

2. **Right group is lighter**

   The defective coin must be in the right group.

3. **Both groups have equal weight**

   Neither group contains a lighter coin. Therefore, if there is a defective coin, it must be among the remaining unweighed coins.

The process is repeated recursively until only one possible coin remains.

---

## Divide and Conquer

For `n` coins:

```text
n
↓
n/2
↓
n/4
↓
n/8
↓
...
↓
1
