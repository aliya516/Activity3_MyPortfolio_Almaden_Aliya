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

struct Node
{
    huffmanNode* node;
    Node* next;
    Node(huffmanNode* n) : node(n), next(NULL) {}
};

class HuffmanTree
{
private:
    void enqueue(huffmanNode* node, int priority);
    huffmanNode* dequeue();
    void setCode(huffmanNode* root, string code, string codes[]);
    bool isempty();

public:
    huffmanNode* root;
    Node* Front;
    HuffmanTree() : Front(NULL) {}

    huffmanNode* buildTree(char chars[], int freqs[], int sizes);
    void getCodes(huffmanNode* root, string code, string codes[]);
};

void HuffmanTree::enqueue(huffmanNode* node, int priority)
{
    Node* newNode = new Node(node);

    if (Front == NULL || priority < Front->node->frequency)
    {
        newNode->next = Front;
        Front = newNode;
    }
    else
    {
        Node* current = Front;
        while (current->next != NULL && priority >= current->next->node->frequency)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

huffmanNode* HuffmanTree::dequeue()
{
    if (isempty())
    {
        cout << "Queue is empty.\n" << endl;
        return NULL;
    }
    else
    {
        Node* Temp = Front;
        Front = Front->next;

        huffmanNode* node = Temp->node;
        delete Temp;
        return node;
    }
}

huffmanNode* HuffmanTree::buildTree(char chars[], int freqs[], int sizes)
{

    for (int i = 0; i < sizes; ++i)
    {
        enqueue(new huffmanNode(chars[i], freqs[i]), freqs[i]);
    }

    while (!isempty())
    {
        huffmanNode* left = dequeue();

        if (isempty())
        {
            return left;
        }

        huffmanNode* right = dequeue();

        int combinedFrequency = left->frequency + right->frequency;
        huffmanNode* newNode = new huffmanNode('\0', combinedFrequency);
        newNode->left = left;
        newNode->right = right;

        enqueue(newNode, combinedFrequency);
    }
    return NULL;
}

void HuffmanTree::setCode(huffmanNode* root, string code, string codes[])
{
    if (root == NULL)
        return;
    if (root->character != '\0')
    {
        codes[static_cast<unsigned char>(root->character)] = code;
    }
    setCode(root->left, code + "0", codes);
    setCode(root->right, code + "1", codes);
}

void HuffmanTree::getCodes(huffmanNode* root, string code, string codes[])
{
    setCode(root, code, codes);
}

bool HuffmanTree::isempty()
{
    return (Front == NULL);
}

string compress(string text, string codes[])
{
    string compressedData = "";
    for (char ch : text)
    {
        compressedData += codes[static_cast<unsigned char>(ch)];
    }
    return compressedData;
}

void writeBit(ofstream& output, int bit)
{
    static char buffer = 0;
    static int count = 0;

    buffer |= (bit << (7 - count));
    count++;

    if (count == 8)
    {
        output.put(buffer);
        buffer = 0;
        count = 0;
    }
}

void saveHuffmanTree(huffmanNode* root, ofstream& output)
{
    if (root == NULL)
        return;

    output << root->character << root->frequency;

    saveHuffmanTree(root->left, output);
    saveHuffmanTree(root->right, output);
}

int main()
{
    string rawFile = "sample.txt";
    string compFile = "compressed file.huff";

    ifstream inputFileCheck(rawFile);
    if (!inputFileCheck.is_open())
    {
        cout << "Error: Cannot find sample.txt file." << endl;
        return 1;
    }
    inputFileCheck.close();

    ifstream input(rawFile);
    string text((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());


    const int MAX_CHAR = 256;
    char chars[MAX_CHAR];
    int freqs[MAX_CHAR] = {0};
    int sizes = 0;

    for (char ch : text)
    {
        if (freqs[static_cast<unsigned char>(ch)] == 0)
        {
            chars[sizes++] = ch;
        }
        freqs[static_cast<unsigned char>(ch)]++;
    }

    string processedText = "";
    bool previousSpace = false;
    for (char ch : text)
    {
        if (ch == ' ')
        {
            if (!previousSpace)
            {
                processedText += "~";
                previousSpace = true;
            }
        }
        else
        {
            processedText += ch;
            previousSpace = false;
        }
    }

    HuffmanTree H;
    H.root = H.buildTree(chars, freqs, sizes);
    string codes[MAX_CHAR] = {};
    H.getCodes(H.root, "", codes);


    string compData = compress(text, codes);


    ofstream output(compFile, ios::binary);
    saveHuffmanTree(H.root, output);
    output << "\n";


    for (char bit : compData)
    {
        int bitValue = bit - '0';
        writeBit(output, bitValue);
    }

    output.close();
    input.close();

    cout << "\nText compressed successfully!" << endl;
    cout << "Output file: compressed.huff"<< endl;
    return 0;
}
