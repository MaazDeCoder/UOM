# Secure Text Encoding and Decoding System with Multi-Layer Transformation
##  Overview
This project implements a customizable text encoding and decoding system that applies multiple reversible transformation layers to secure message transmission. The program is written in C++ and allows users to encode messages using several configurable techniques and decode them through password-based authentication.

---
##  Features
###  Security Features
- Password-based authentication using hashed verification
- Metadata encryption derived from password hash
- Layered encoding to increase obfuscation strength
  
###  Encoding Techniques
- **Shift Cipher:** Caesar cipher with configurable shift amount (1-9)
- **Block Reversal:** Split text into blocks and reverse each block
- **String Reversal:** Reverse the entire message
- **ASCII Conversion:** Convert characters at odd indices to ASCII values
- **Steganography:** Insert noise characters (!) to hide the message

###  Operation Modes
- **Basic Mode:** Uses default settings and password only
- **Advanced Mode:** Allows full customization of all encoding parameters

---
##  System Architecture Overview
```
Encoder & Decoder System
├── Core Functions
│   ├── Encoding Pipeline
│   │   ├── Shift Cipher
│   │   ├── Block Reversal
│   │   ├── String Reversal
│   │   ├── ASCII Conversion
│   │   └── Steganography
│   └── Decoding Pipeline (Reverse order)
├── Security Layer
│   ├── Password Hashing
│   └── Metadata Encryption
└── User Interface
    ├── Interactive Prompts
    └── Error Handling
```

###  Encoding Pipeline Flow

> Input Text → Shift Cipher → Block Reversal → String Reversal → ASCII Conversion → Steganography → Final Output <br>

###  Decoding Pipeline Flow

> Encoded Text → Remove Steganography → Parse ASCII Values → Reverse String → Block Reversal → Shift Decipher → Original Text

### Prerequisites
- C++ compiler supporting C++11 or later (GCC, MinGW, MSVC, Clang)
- Terminal or command-line interface
- Basic understanding of console input/output

  
---
##  Usage Guide
### Encoding a Message
1. Run the program
2. Select option `1` (Encode a message)
3. Choose mode:
    - `1` Basic Mode: Uses default settings
    - `2` Advanced Mode: Customize each encoding step
4. Enter password
5. For Advanced Mode, configure:
    - Shift Cipher amount (1-9)
    - Block reversal size (1-9)
    - String reversal (Y/N)
    - ASCII conversion (Y/N)
    - Steganography (Y/N)
6. Enter your message
7. Receive encoded output with metadata

### Decoding a Message
1. Run the program
2. Select option 2 (Decode a message)
3. Paste the encoded message (including metadata)
4. Enter the correct password
5. Receive decoded original message
---
## Example Session
- ### Encoding
```plaintext
====================================================
            Encoder & Decoder -- by Maaz Ali
====================================================

Choose an operation:
 1. Encode a message
 2. Decode a message
 0. Exit
 Select: 1

Enter a message to encode
Message: Hello World!

Select Mode
1. Basic Mode (password only)
2. Advanced Mode (fully customizable)
Select: 2

Enter password:
Password: secret123

Apply Shift Cipher? [Y/N]
 Select: Y

Enter shift amount
 Amount: 3

Apply Reverse Entire String? [Y/N]
 Select: Y

Apply Block Reversal? [Y/N]
 Select: Y

Enter block size
 Size: 4

Apply ASCII conversion on even index? [Y/N]
 Select: Y

Apply Stegnography? [Y/N]
 Select: N

Result: i9h:x7g7y6!!p2093466619||u{111}g{36}r{35}Z{114}K{104}o{111}

```

- ### Decoding
``` plaintext
====================================================
            Encoder & Decoder -- by Maaz Ali
====================================================

Choose an operation:
 1. Encode a message
 2. Decode a message
 0. Exit
 Select: 2

Enter a message to encode
Message: i9h:x7g7y6!!p2093466619||u{111}g{36}r{35}Z{114}K{104}o{111}

Enter password:
Password: secret123

Result: Hello World!

```

---
##  Technical Details

### Encoding Format
- #### Complete Format
> Encoded Format: ENCRYPTED_METADATA!!pHASH||ENCODED_TEXT <br>
- #### Metadata Structure
> Metadata Format: c{shift}b{block}r{reverse}a{ascii}s{steg}

### Character Range Handling
- All transformations work within printable ASCII range (32-126)
- Automatic wrap-around for shift operations
- Special characters are preserved through encoding/decoding

###  Security Considerations
- Multiple encoding layers provide basic obfuscation
- Password protection prevents unauthorized decoding
- Metadata encryption hides encoding parameters
  
---

##  Quick Reference
### Command Summary
Option | Description
---| ---|
`1` |	Encode a message |
`2` |	Decode a message |
`0`	| Exit program |

### Encoding Parameters
Parameter |	Range |	Description |
---| ---| ---|
Shift Cipher |	1-9 |	Character shift amount
Block Size |	1-9	| Size of blocks to reverse
String Reversal	| Y/N |	Reverse entire string
ASCII Conversion |	Y/N	| Convert odd indices to ASCII
Steganography |	Y/N	| Add noise characters

### Common Error Messages
- >  Error: Wrong password! Access denied. - Incorrect password during decoding
- >  Invalid input! Please enter a number. - Non-numeric input
- >  Please enter Y or N - Invalid yes/no response

---
##  Author
### Maaz Ali
University Of Malakand Project - Encoding/Decoding System

