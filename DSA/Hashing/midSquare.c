#include <stdio.h>
#include <math.h>

// Function to calculate the number of digits in an integer
int numDigits(int number) {
    int digits = 0;
    while (number != 0) {
        number /= 10;
        digits++;
    }
    return digits;
}

// Mid-square hashing function
int midSquareHash(int key, int tableSize) {
    // Step 1: Square the key
    long long squaredKey = (long long)key * (long long)key;

    // Convert squared key to string to extract middle digits
    char squaredKeyStr[20];
    sprintf(squaredKeyStr, "%lld", squaredKey);

    // Calculate the length of the squared key string
    int squaredKeyLength = numDigits(squaredKey);

    // Step 2: Extract middle digits
    int midLength = squaredKeyLength / 2;
    int tableSizeDigits = numDigits(tableSize);
    int start_index = midLength - (tableSizeDigits / 2);
    char middleDigits[10];

    // Extract the middle digits
    for (int i = 0; i < tableSizeDigits; i++) {
        middleDigits[i] = squaredKeyStr[start_index + i];
    }
    middleDigits[tableSizeDigits] = '\0';

    // Convert middle digits back to integer
    int hashValue = atoi(middleDigits);

    // Step 3: Map to the table size
    return hashValue % tableSize;
}

int main() {
    int key = 1234;
    int tableSize = 1000;
    printf("Hash value: %d\n", midSquareHash(key, tableSize));
    return 0;
}



/*
Certainly! Let's break down the given segment of code step-by-step to understand its purpose and logic:

### Segment of Code

```c
int midLength = squaredKeyLength / 2;
int tableSizeDigits = numDigits(tableSize);
int start_index = midLength - (tableSizeDigits / 2);
char middleDigits[10];
```

### Explanation

1. **Calculating `midLength`**:
   ```c
   int midLength = squaredKeyLength / 2;
   ```
   - `squaredKeyLength` is the number of digits in the squared key. 
   - By dividing `squaredKeyLength` by 2, `midLength` gets the index of the middle of the squared key string.
   - This is essentially finding the midpoint of the squared key, which will help in locating the middle digits.

2. **Calculating `tableSizeDigits`**:
   ```c
   int tableSizeDigits = numDigits(tableSize);
   ```
   - `tableSizeDigits` is the number of digits in the hash table size.
   - This helps determine how many digits we need to extract from the middle of the squared key.
   - For example, if `tableSize` is 1000, `tableSizeDigits` would be 4.

3. **Calculating `start_index`**:
   ```c
   int start_index = midLength - (tableSizeDigits / 2);
   ```
   - `midLength` gives us the midpoint of the squared key.
   - `tableSizeDigits / 2` gives us half the number of digits in the table size.
   - `start_index` is calculated by subtracting half the number of digits of the table size from the midpoint of the squared key.
   - This effectively finds the starting index from which to extract the middle digits.
   - For example, if `midLength` is 3 (indicating the middle of a 7-digit squared key) and `tableSizeDigits` is 4, then `start_index` would be `3 - 2 = 1`. This means the extraction should start from index 1.

4. **Declaring `middleDigits` Array**:
   ```c
   char middleDigits[10];
   ```
   - This array is used to store the extracted middle digits as a string.
   - The size of 10 is chosen to be large enough to accommodate the middle digits and the null terminator.

### Example

Let's take an example to illustrate the logic:

- **Key**: 1234
- **Squared Key**: 1234^2 = 1522756 (7 digits)
- **Hash Table Size**: 1000 (4 digits)

1. **Calculate `squaredKeyLength`**:
   - Squared key (1522756) has 7 digits.
   - `squaredKeyLength = 7`

2. **Calculate `midLength`**:
   - `midLength = 7 / 2 = 3` (integer division)

3. **Calculate `tableSizeDigits`**:
   - Hash table size (1000) has 4 digits.
   - `tableSizeDigits = 4`

4. **Calculate `start_index`**:
   - `start_index = 3 - (4 / 2) = 3 - 2 = 1`

5. **Extracting Middle Digits**:
   - Starting from index 1, we need to extract 4 digits.
   - Squared key: 1522756
   - Middle digits extracted: 5227

By carefully determining `start_index`, the code ensures that the middle portion of the squared key is extracted to form the hash value, which helps in distributing keys more uniformly across the hash table.

### Summary

- `midLength` finds the midpoint of the squared key.
- `tableSizeDigits` determines the number of digits needed for the hash value.
- `start_index` identifies where to start extracting the middle digits.
- `middleDigits` stores the extracted middle digits as a string before converting them to an integer for the final hash value. 

This process helps in generating a hash value that is well-distributed, reducing the likelihood of collisions in the hash table.
*/