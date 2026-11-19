# Simple Encryption Using XOR

COMP 211 Checkoff 3 · Aki Bhabad

For this checkoff I explored how the XOR operator (`^` in C) can encrypt and decrypt a message, and why simple XOR encryption is not secure.

## What I explored

**The key is a list of instructions for each bit.** XOR goes through the message bit by bit:

- key bit 0 = leave that bit alone
- key bit 1 = flip that bit

Encrypting is `cipher = plain ^ key`. Decrypting is the exact same step, `plain = cipher ^ key`, because you just flip back the exact bits that got flipped.

**Why the same key undoes itself:** two rules.

- `k ^ k = 0`
- `x ^ 0 = x`

So `(p ^ k) ^ k = p ^ (k ^ k) = p ^ 0 = p`.

**Why AND and OR don't work:** to decrypt, every cipher has to point back to exactly one plain message. AND forces a bit to 0 whenever the key bit is 0, and OR forces a bit to 1 whenever the key bit is 1, so you can't tell what the original bit was. XOR never forces a bit to a fixed value. Each bit is kept or flipped, and both can be undone by applying the same key again.

## Most interesting discoveries

1. **One function does both jobs.** `xor_crypt` encrypts the first time you call it and decrypts the second time, which is why it's called "crypt."
2. **Patterns leak through.** In my output, `"ll"` in "Hello" became `46 46` and `"11"` in "211" became `1B 1B`. The same letter with the same key always gives the same byte.
3. **It's easy to break.**
   - A 1-byte key only has 2^8 = 256 possibilities, so a computer can try every key almost instantly.
   - If you know just one letter, you get the key: if `62` is `'H'`, then `0x48 ^ 0x62 = 0x2A`, which is the key.
4. **XOR isn't the weak part, the key is.** A key that is completely random, as long as the message, and never reused (a one-time pad) is mathematically impossible to break. The catch is you need a secret key as big as everything you send, so it isn't practical.

## Code

`XOR.c` encrypts the string `"Hello COMP 211"` with the key `0x2A`, prints the encrypted bytes in hex, then decrypts it back.

### How to run

```bash
gcc -Wall -o xor XOR.c
./xor
```

### Output

```
Original:  Hello COMP 211
Key:       0x2A
Encrypted: 62 4F 46 46 45 0A 69 65 67 7A 0A 18 1B 1B
Decrypted: Hello COMP 211
```

## Presentation

My slides are in [`slides.pdf`](slides.pdf).

## Resources

- My AI exploration chat: https://claude.ai/share/40d911d1-b27d-4452-8005-820c3f3bf375
- XOR cipher (Wikipedia): https://en.wikipedia.org/wiki/XOR_cipher
- One-time pad (Wikipedia): https://en.wikipedia.org/wiki/One-time_pad
- Bitwise operators, *Dive Into Systems* (COMP 211 textbook): https://diveintosystems.org/book/C4-Binary/bitwise.html
