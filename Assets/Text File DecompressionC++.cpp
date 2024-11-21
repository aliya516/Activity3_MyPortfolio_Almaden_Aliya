#include <iostream>
#include <fstream>

using namespace std;

struct huffmanNode
{
    char character;
    int frequency;
    huffmanNode* left;
    huffmanNode* right;
    huffmanNode(char c, int f) : character(c), frequency(f), left(NULL), right(NULL) {}
};

class HuffmanTree
{
private:
    int readBit(const string& compressedData, int bitIndex);

public:
    huffmanNode* root;
    HuffmanTree() : root(NULL) {}

    huffmanNode* reconstructHuffmanTree(ifstream& input);
    string decompress(const string& compressedData);
};

string HuffmanTree::decompress(const string& compressedData)
{
    string decompressedData = "";
    huffmanNode* current = root;
    int bitIndex = 0;

    while (bitIndex < compressedData.length() * 8)
    {
        int bitValue = readBit(compressedData, bitIndex);
        bitIndex++;

        if (bitValue == 0)
            current = current->left;
        else
            current = current->right;

        if (current->character != '\0')
        {

            if (current->character == '~')
                decompressedData += ' ';
            else
                decompressedData += current->character;

            current = root;
        }
    }

    return decompressedData;
}

huffmanNode* HuffmanTree::reconstructHuffmanTree(ifstream& input)
{
    char character;
    int frequency;


    input >> character;
    input >> frequency;


    if (character == '\0')
    {
        huffmanNode* internalNode = new huffmanNode(character, frequency);
        internalNode->left = reconstructHuffmanTree(input);
        internalNode->right = reconstructHuffmanTree(input);
        return internalNode;
    }
    else
    {

        return new huffmanNode(character, frequency);
    }
}

int HuffmanTree::readBit(const string& compressedData, int bitIndex)
{
    int byteIndex = bitIndex / 8;
    int offset = 7 - (bitIndex % 8);
    return (compressedData[byteIndex] >> offset) & 1;
}

int main()
{
    string compFile = "compressed file.huff";
    string decompressFile = "decompressed file.txt";


    ifstream input(compFile, ios::binary);
    if (!input.is_open())
    {
        cout << "Error opening " << compFile << " for reading." << endl;
        return 1;
    }


    HuffmanTree H;
    H.root = H.reconstructHuffmanTree(input);
    input.get();

    if (H.root == NULL)
    {
        cout << "Error: Failed to read Huffman tree information from the file." << endl;
        return 1;
    }

    string compressedBits((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    string decompressedData = H.decompress(compressedBits);

    ofstream decompressOutput(decompressFile);

    if (!decompressOutput.is_open())
    {
        cout << "Error opening " << decompressFile << " for writing." << endl;
        return 1;
    }

    decompressOutput << "Decompressed Data:\n" << decompressedData << endl;

    decompressOutput.close();

    cout << "Decompressed data has been saved to " << decompressFile << endl;

    input.close();

    return 0;
}
