# Project Workflow

As mentioned in the overview, as long as we can:

1. Compile your program via `make`,
2. Run your program as described, and
3. Successfully compress + uncompress a file,

you are absolutely free to implement the project any way you think is best.

However, here are some suggestions just in case you feel a bit lost.

---

## **Suggested Development Process**

Before doing anything, it's a good idea to create your `compress.cpp` and `uncompress.cpp` with `main()` functions and get your project files to the point where you can compile successfully with `make` (even though the `compress` and `uncompress` executables don't do anything yet). Once things are compiling:

- Start working on `compress`
- Once it's working reasonably well, start working on `uncompress`
- Use print statements, `gdb`, etc. to make sure things are implemented correctly

---

## *Suggested Control Flow for `compress`*

1. Parse the command line arguments and throw an error if the user runs your program incorrectly
2. Open the input file for reading
3. Read bytes from the file and count the number of occurrences of each byte value
4. Use the byte counts to construct a Huffman coding tree. Each unique byte with a non-zero count will be a leaf node
5. Open the output file for writing
6. Write enough information (a "file header") to the output file to enable the coding tree to be reconstructed when read by `uncompress`
7. Move back to the beginning of the input file
8. Using the Huffman coding tree, translate each byte into its code, and append these bits to the output file (after the header)
9. Close the input and output files (note: this is handled for you; see Design Notes)

---

## *Suggested Control Flow for `uncompress`*

1. Open the input file for reading
2. Read the file header and reconstruct the Huffman coding tree
3. Open the output file for writing
4. Decode bits from the input file into bytes using the Huffman tree and write them to the output file
5. Close the input and output files (handled for you; see Design Notes)

---

## **Potential Development Process**

If you use the structure provided in the starter code, a reasonable development process could be:

1. Create `compress.cpp` and `uncompress.cpp` with `main()` functions that don't do anything yet  
   - Use these to test components step-by-step

2. Create `HCTree.cpp` and add skeletons for functions needed  
   - Refer to `HCTree.h` to match the function signatures

3. Implement `HCTree::build` to construct the Huffman Tree from frequencies  
   - Use `gdb` or print statements to trace and verify

4. Implement the `HCTree` destructor

5. Implement `HCTree::encode` to encode a symbol

6. Implement `HCTree::decode`

7. Piece everything together in `compress.cpp` and `uncompress.cpp` according to control flows  
   - Implement and test one step at a time  
   - Refer to “Design Notes” for recommendations on the file header format

---

## **Map Out *Your* Ideal Approach**

The above steps are just suggestions. Everyone works differently.

Before writing a single line of code:

- Read through this guide
- Make sure you fully understand the project requirements
- Map out how *you personally* want to approach the problem

You’re allowed (and encouraged) to deviate or iterate on your roadmap as needed.

---

**TL;DR:**  
**Do not write a single line of code** until you have mapped out your approach!  
Chat with a tutor during Lab Hours if you want feedback on your plan! 😊
