#include <stdio.h>
#include <string.h>

int foldingHash(int key, int partSize, int tableSize) {
    char keyStr[20];
    sprintf(keyStr, "%d", key);

    int keyLength = strlen(keyStr);
    int sum = 0;
    char partStr[partSize + 1];

    // Process each part
    for (int i = 0; i < keyLength; i += partSize) {
        // Extract part
        strncpy(partStr, keyStr + i, partSize);
        partStr[partSize] = '\0';
        
        // Convert part to integer and add to sum
        sum += atoi(partStr);
    }

    // Modulo operation to fit into hash table size
    return sum % tableSize;
}

int main() {
    int key = 987654321;
    int partSize = 3;
    int tableSize = 1000;

    int hashValue = foldingHash(key, partSize, tableSize);
    printf("Hash value: %d\n", hashValue);

    return 0;
}


/*
Hashing by folding is a method used to generate hash values from keys by dividing the key into equal-sized parts, processing these parts, and then combining them to form a hash value. This method is particularly useful for keys that are large or have a structure that can be naturally divided into parts, such as long integers or strings.

### Steps Involved in Hashing by Folding

1. **Divide the Key**: Split the key into equal-sized parts. If the key length is not a multiple of the part size, you may need to pad the key.
2. **Combine the Parts**: Sum or XOR the parts together to generate the hash value. Different folding techniques might use different ways to combine the parts.
3. **Modulo Operation**: Optionally, apply a modulo operation to fit the hash value into the desired hash table size.

### Types of Folding Methods

There are two common methods for combining the parts:

1. **Folding by Addition**: Sum all the parts together.
2. **Folding by XOR**: XOR all the parts together.

### Example of Folding by Addition

Let's consider a key represented as a long integer, and we will use folding by addition.

**Given**:
- Key: 987654321
- Part size: 3 digits
- Hash table size: 1000

**Steps**:

1. **Divide the Key**:
   - Split the key into parts of 3 digits each: 987, 654, 321.

2. **Combine the Parts**:
   - Sum the parts: \( 987 + 654 + 321 = 1962 \).

3. **Modulo Operation**:
   - Apply modulo operation to fit into hash table size: \( 1962 \mod 1000 = 962 \).

Thus, the hash value for the key 987654321 is 962.

### Code Example in C

Here is a C implementation of hashing by folding using the addition method:

```c
#include <stdio.h>
#include <string.h>

int foldingHash(int key, int partSize, int tableSize) {
    char keyStr[20];
    sprintf(keyStr, "%d", key);

    int keyLength = strlen(keyStr);
    int sum = 0;
    char partStr[partSize + 1];

    // Process each part
    for (int i = 0; i < keyLength; i += partSize) {
        // Extract part
        strncpy(partStr, keyStr + i, partSize);
        partStr[partSize] = '\0';
        
        // Convert part to integer and add to sum
        sum += atoi(partStr);
    }

    // Modulo operation to fit into hash table size
    return sum % tableSize;
}

int main() {
    int key = 987654321;
    int partSize = 3;
    int tableSize = 1000;

    int hashValue = foldingHash(key, partSize, tableSize);
    printf("Hash value: %d\n", hashValue);

    return 0;
}
```

### Explanation

1. **Convert Key to String**:
   - `sprintf(keyStr, "%d", key);` converts the integer key to a string.

2. **Divide the Key into Parts**:
   - Use a loop to iterate over the key string in steps of `partSize`.
   - `strncpy(partStr, keyStr + i, partSize);` extracts a part of the key.
   - `partStr[partSize] = '\0';` ensures the part is null-terminated.

3. **Sum the Parts**:
   - `sum += atoi(partStr);` converts the part to an integer and adds it to the sum.

4. **Modulo Operation**:
   - `return sum % tableSize;` ensures the hash value fits within the hash table size.

### Summary

Hashing by folding is a simple and effective technique for generating hash values, especially for structured keys. The key is divided into equal parts, and these parts are combined (by addition or XOR) to produce the hash value. The final hash value can be adjusted using a modulo operation to fit within the desired hash table size. This method helps in distributing keys more uniformly across the hash table, reducing collisions and improving performance.
*/