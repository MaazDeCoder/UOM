#include <iostream>
#include <string>

using namespace std;

/* ===========================================================================================
    PROJECT: Secure Text Encoding and Decoding System with Multi-Layer Transformation
    COURSE: Programming Fundamentals (PF)

    This program demonstrates core PF concepts:
    - Input/Output operations
    - Variables and Data Types
    - Control Structures (if/else + loops)
    - Functions and Modular Programming
    - String Manipulation
    - ASCII-based Character Processing
    - Basic Encryption Logic
=========================================================================================== */

// ----------------------------------------------- FUNCTION DECLARATIONS ------------------------------------------------ //

// Helper Functions
bool askYesNo(string output_message);
int askInt(string output_message, int min, int max);

// Common Functions
string blockReversal(string text, int blockSize);
string reverseString(string text);
int hashPassword(string password);

// Encoding Pipeline
string encodeShiftCipherText(string text, int shift_cipher);
string encodedApplyASCII(string text);
string encodedStegnography(string text);
string encodedMetadata(int encoded_password_hash, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography);
string encoding(string text, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography);
string encoderInterface(string text, int mode);

// Decoding Pipeline
string decodedStegnography(string text);
string decodedApplyASCII(string text);
string decodedShiftCipherText(string text, int shift_cipher);
string decodeMetadata(string encrypted_metadata, int hash_password);
string decoding(string text, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography);
string decoderInterface(string encoded_message);

// Main Application Interface
string mainApp();

// Program entry point
int main()
{
    cout << "====================================================" << endl;
    cout << "            Encoder & Decoder -- by Maaz Ali" << endl;
    cout << "====================================================" << endl;

    string output = mainApp();
    if (!output.empty())
    {
        cout << "Result: " << output << endl;
    }

    return 0;
}

/* ===========================================================================================
    SECTION 1: HELPER FUNCTIONS
    (PF Topics: Functions, Loops, Conditions)
=========================================================================================== */

// Ask user a yes/no question and return boolean response
bool askYesNo(string output_message)
{
    char choice;
    while (true)
    {
        cout << "\n"
             << output_message << " [Y/N] \n Select : ";
        cin >> choice;
        if (choice == 'Y' or choice == 'y')
        {
            return true;
        }
        else if (choice == 'N' or choice == 'n')
        {
            return false;
        }
        else
        {
            cout << "Please enter Y or N" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Ask user for an integer within a specified range
int askInt(string output_message, int min, int max)
{
    int value;
    while (true)
    {
        cout << "\n"
             << output_message;
        cin >> value;

        if (value < min or value > max)
        {
            cout << "Please enter number between " << min << " and " << max << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else
        {
            return value;
        }
    }
}

/* ===========================================================================================
    SECTION 2: Common Functions
    (PF Topics: Functions, Control Structures, Character Manipulation, String Manipulation)
=========================================================================================== */

// Reverse blocks of text based on specified block size
string blockReversal(string text, int blockSize)
{
    if (blockSize <= 0 or blockSize >= text.length())
        return text;
    string output;
    int textLength = text.length();

    for (int i = 0; i < textLength; i += blockSize)
    {
        string block;

        // Extract block
        for (int j = 0; j < blockSize && (i + j) < textLength; j++)
        {
            block += text[i + j];
        }

        // Reverse block and append to output
        for (int k = block.length() - 1; k >= 0; k--)
        {
            output += block[k];
        }
    }
    return output;
}

// Reverse the entire string
string reverseString(string text)
{

    string output = "";
    for (int i = text.length() - 1; i >= 0; i--)
    {
        output += text[i];
    }

    return output;
}

// Generate password hash
int hashPassword(string password)
{
    int h = 0;
    for (char ch : password)
    {
        h = h * 42 + (int)ch;
    }
    return h;
}

/* ===========================================================================================
    SECTION 3: ENCODING PIPELINE
    (PF Topics: Functions, String Manipulation, Control Structures)
=========================================================================================== */

// Shift cipher encoding - shifts characters by specified amount within printable ASCII range
string encodeShiftCipherText(string text, int shift_cipher)
{
    string output = "";
    int range_size = 95;

    for (char ch : text)
    {
        int original_offset = ch - 32;
        int new_offset = (original_offset + shift_cipher) % range_size;
        char shifted = new_offset + 32;
        output += shifted;
    }
    return output;
}

// Apply ASCII conversion on even indexed characters
string encodedApplyASCII(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (i % 2 == 0)
        {
            output += text[i];
        }
        else
        {
            output += "{" + to_string((int)text[i]) + "}";
        }
    }
    return output;
}

// Apply stegnography by inserting '!' before every character at even indices
string encodedStegnography(string text)
{
    string output = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (i % 2 == 0)
        {
            output += "!";
        }
        output += text[i];
    }
    return output;
}

// Generate encoded metadata string
string encodedMetadata(int encoded_password_hash, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography)
{

    string metadata = "";
    metadata += "c";
    metadata += to_string(shift_cipher);
    metadata += "b";
    metadata += to_string(blocksize);
    metadata += "r";
    metadata += reverse_string ? "1" : "0";
    metadata += "a";
    metadata += apply_ascii ? "1" : "0";
    metadata += "s";
    metadata += apply_stegnography ? "1" : "0";

    string hash_string = to_string(encoded_password_hash);
    int key = 0;
    for (char ch : hash_string)
    {
        key = key + ch;
    }

    key = key % 26;

    if (key == 0)
    {
        key = 13;
    }

    string encrypted_metadata = "";
    for (char ch : metadata)
    {
        char encrypted_char = ch + key;

        if (encrypted_char > 126)
        {
            encrypted_char = 33 + (encrypted_char - 127);
        }
        encrypted_metadata += encrypted_char;
    }
    encrypted_metadata += "!!p" + to_string(encoded_password_hash);
    return encrypted_metadata;
}

// Generate fully encoded text based on selected transformations
string encoding(string text, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography)
{
    string encoded_text;

    encoded_text = text;
    if (shift_cipher != 0)
    {
        encoded_text = encodeShiftCipherText(encoded_text, shift_cipher);
    }
    if (blocksize > 0)
    {
        encoded_text = blockReversal(encoded_text, blocksize);
    }
    if (reverse_string)
    {
        encoded_text = reverseString(encoded_text);
    }
    if (apply_ascii)
    {
        encoded_text = encodedApplyASCII(encoded_text);
    }
    if (apply_stegnography)
    {
        encoded_text = encodedStegnography(encoded_text);
    }

    return encoded_text;
}

// Interface for encoding text with user-defined settings
string encoderInterface(string text, int mode)
{
    // Default
    int shift_cipher = 3;
    bool reverseEntireString = true;
    bool ASCII_on_even_index = true;
    bool encryptedmetadata = true;
    bool applyStegnography = false;
    int blockSize = 0;
    string password, encoded_metadata, encoded_text, result;

    cout << "\nEnter password: \nPassword: ";
    cin >> password;

    // Advanced mode
    if (mode == 2)
    {
        if (askYesNo("Apply Shift Cipher?"))
        {
            shift_cipher = askInt("Enter shift amount \n Amount: ", 1, 9);
        }
        else
        {
            shift_cipher = 0;
        }
        reverseEntireString = askYesNo("Apply Reverse Entire String?");

        if (askYesNo("Apply Block Reversal?"))
        {
            blockSize = askInt("Enter block size \n Size: ", 1, 9);
        }

        ASCII_on_even_index = askYesNo("Apply ASCII conversion on even index?");
        applyStegnography = askYesNo("Apply Stegnography?");
    }
    int encoded_password_hash = hashPassword(password);
    encoded_metadata = encodedMetadata(encoded_password_hash, shift_cipher, blockSize, reverseEntireString, ASCII_on_even_index, applyStegnography);
    encoded_text = encoding(text, shift_cipher, blockSize, reverseEntireString, ASCII_on_even_index, applyStegnography);
    result = encoded_metadata + "||" + encoded_text;
    return result;
}

/* ===========================================================================================
    SECTION 4: DECODING PIPELINE
    (PF Topics: Loops, Functions, Conditions, Character Manipulation)
=========================================================================================== */

// Remove stegnography by skipping every third character
string decodedStegnography(string text)
{
    string output;
    for (int i = 0; i < text.length(); i++)
    {
        if (i % 3 == 0)
        {
            continue;
        }
        else
        {
            output += text[i];
        }
    }
    return output;
}

// Decode ASCII encoded segments back to characters
string decodedApplyASCII(string text)
{
    string output = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == '{')
        {
            string num = "";
            int start = i;
            i++;
            while (i < text.length() && text[i] != '}')
            {
                num += text[i];
                i++;
            }
            bool properlyClosed = (i < text.length() && text[i] == '}');
            if (properlyClosed && !num.empty())
            {
                // if properly formatted and numeric
                bool isNumber = true;
                for (char ch : num)
                {
                    if (!isdigit(ch))
                    {
                        isNumber = false;
                        break;
                    }
                }
                if (isNumber)
                {
                    output += char(stoi(num));
                }
                else
                {
                    output += text.substr(start, i - start + 1);
                }
            }
            else
            {
                output += text.substr(start, (i < text.length() ? i - start + 1 : text.length() - start));
            }
        }
        else
        {
            output += text[i];
        }
    }
    return output;
}

// Reverse shift cipher to retrieve original text
string decodedShiftCipherText(string text, int shift_cipher)
{
    string output;
    int range_size = 95;

    for (char ch : text)
    {
        int original_offset = ch - 32;
        int new_offset = (original_offset - shift_cipher + range_size) % range_size;
        char shifted = new_offset + 32;
        output += shifted;
    }
    return output;
}

// Decode metadata using password hash
string decodeMetadata(string encrypted_metadata, int hash_password)
{

    string hash_string = to_string(hash_password);
    int key = 0;
    for (char ch : hash_string)
        key = key + ch;

    key = key % 26;

    if (key == 0)
        key = 13;

    string decrypted_metadata = "";
    for (char ch : encrypted_metadata)
    {
        char decrypted_char = ch - key;

        if (decrypted_char < 33)
        {
            decrypted_char = 127 - (33 - decrypted_char);
        }
        decrypted_metadata += decrypted_char;
    }
    return decrypted_metadata;
}

// Full decoding pipeline applying transformations in reverse order
string decoding(string text, int shift_cipher, int blocksize, bool reverse_string, bool apply_ascii, bool apply_stegnography)
{

    string decoded_text = text;
    if (apply_stegnography)
    {
        decoded_text = decodedStegnography(decoded_text);
    }
    if (apply_ascii)
    {
        decoded_text = decodedApplyASCII(decoded_text);
    }
    if (reverse_string)
    {
        decoded_text = reverseString(decoded_text);
    }
    if (blocksize > 0)
    {
        decoded_text = blockReversal(decoded_text, blocksize);
    }
    if (shift_cipher != 0)
    {
        decoded_text = decodedShiftCipherText(decoded_text, shift_cipher);
    }
    return decoded_text;
}

// Interface for decoding text with password verification
string decoderInterface(string encoded_message)
{
    string password;
    cout << "\nEnter password: \nPassword: ";
    cin >> password;
    int entered_hash = hashPassword(password);
    int hash_start = encoded_message.find("!!p");
    int hash_end = encoded_message.find("||", hash_start + 3);
    string stored_hash_str = encoded_message.substr(hash_start + 3, hash_end - hash_start - 3);
    int stored_hash = stoi(stored_hash_str);

    // Verify password
    if (entered_hash != stored_hash)
    {
        return "Error: Wrong password! Access denied.";
    }
    string encoded_metadata = encoded_message.substr(0, encoded_message.find("!!p"));
    int text_start = encoded_message.find("||") + 2;
    string encoded_text = encoded_message.substr(text_start);

    string decode_metadata = decodeMetadata(encoded_metadata, entered_hash);

    int shift_cipher, blocksize;
    bool reverse_string, apply_ascii, apply_stegnography;

    shift_cipher = (int)(decode_metadata[decode_metadata.find("c") + 1] - '0');
    blocksize = (int)(decode_metadata[decode_metadata.find("b") + 1] - '0');
    reverse_string = (bool)(decode_metadata[decode_metadata.find("r") + 1] - '0');
    apply_ascii = (bool)(decode_metadata[decode_metadata.find("a") + 1] - '0');
    apply_stegnography = (bool)(decode_metadata[decode_metadata.find("s") + 1] - '0');

    string decoded_message = decoding(encoded_text, shift_cipher, blocksize, reverse_string, apply_ascii, apply_stegnography);

    return decoded_message;
}

/* ===========================================================================================
    SECTION 5: MAIN PROGRAM CONTROL FLOW
    (PF Topics: Input/Output, Control Structures, Functions)
=========================================================================================== */

// Main application interface
string mainApp()
{
    int choice;
    int mode = -1;
    string text, encoded_text, decoded_text;

    cout << "\nChoose an operation: \n 1. Encode a message \n 2. Decode a message \n 0. Exit\n Select: ";
    if (!(cin >> choice))
    {
        cout << "Invalid input! Please enter a number." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return mainApp();
    }

    if (choice == 0)
    {
        cout << "Good Bye!" << endl;
        return "";
    }
    else if (choice == 1)
    {
        cout << "\nEnter a message to encode \nMessage: ";
        cin.clear();
        cin.ignore(10000, '\n');
        getline(cin, text);
        while (true)
        {
            cout << "\nSelect Mode \n1. Basic Mode (password only) \n2. Advanced Mode (fully customizable) \nSelect: ";
            cin >> mode;
            cin.clear();
            cin.ignore(10000, '\n');

            if (mode != 1 && mode != 2)
            {
                cout << "Invalid Number entered!" << endl;
                cin.ignore();
                continue;
            }
            encoded_text = encoderInterface(text, mode);
            return encoded_text;
        }
    }
    else if (choice == 2)
    {
        cout << "\nEnter a message to decode \nMessage: ";
        cin.clear();
        cin.ignore(10000, '\n');
        getline(cin, text);

        decoded_text = decoderInterface(text);
        return decoded_text;
    }
    else
    {
        cout << "Invalid number entered!" << endl
             << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        return mainApp();
    }
}
