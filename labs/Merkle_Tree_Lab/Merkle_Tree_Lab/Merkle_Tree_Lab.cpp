#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
using namespace std;

// Function to compute MD5 hash from string input
std::string compute_md5(const std::string& input) {
    HCRYPTPROV hProv = NULL;
    HCRYPTHASH hHash = NULL;
    BYTE rgbHash[16]; // MD5 hash size is 16 bytes
    DWORD cbHash = 16;
    CHAR rgbDigits[] = "0123456789abcdef";
    std::string hash_str;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed: " << GetLastError() << std::endl;
        return "";
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return "";
    }

    if (!CryptHashData(hHash, (BYTE*)input.c_str(), input.length(), 0)) {
        std::cerr << "CryptHashData failed: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return "";
    }

    if (!CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) {
        std::cerr << "CryptGetHashParam failed: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return "";
    }

    for (DWORD i = 0; i < cbHash; i++) {
        hash_str += rgbDigits[rgbHash[i] >> 4];
        hash_str += rgbDigits[rgbHash[i] & 0xf];
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return hash_str;
}

// Provided utility: split a message into fixed-size chunks
std::vector<std::string> chunk_input(const std::string& input, size_t chunk_size) {
    std::vector<std::string> chunks;
    for (size_t i = 0; i < input.length(); i += chunk_size) {
        chunks.push_back(input.substr(i, chunk_size));
    }
    return chunks;
}

std::string buildMerkleTree(const std::vector<std::string>& chunks) {
    vector<string> currentLevel;
    for (const auto& chunk : chunks)
        currentLevel.push_back(compute_md5(chunk));

    while (currentLevel.size() > 1)
    {
        if (currentLevel.size() % 2 != 0)
            currentLevel.push_back(currentLevel.back());

        vector<string> nextLevel;
        for (size_t index = 0; index < currentLevel.size(); index += 2)
        {
            string combined = currentLevel[index] + currentLevel[index + 1];
            nextLevel.push_back(compute_md5(combined));
        }
        currentLevel = nextLevel;
    }

    return currentLevel.empty() ? "" : currentLevel[0];
    return "";
}

bool verifyProof(const std::string& targetData, const std::vector<std::pair<std::string, std::string>>& proof, const std::string& expectedRoot) {
    string currentHash = compute_md5(targetData);

    for (const auto& p : proof)
    {
        const string& direction = p.first;
        const string& siblingHash = p.second;

        if (direction == "L")
            currentHash = compute_md5(siblingHash + currentHash);
        else if (direction == "R")
            currentHash = compute_md5(currentHash + siblingHash);
        else
            return false;
    }

    return currentHash == expectedRoot;
}

std::string readFileToString(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open " << filename << std::endl;
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

int main() {
    std::string cleanFile = "war_and_peace_clean.txt";
    std::string corruptFile = "war_and_peace_corrupted.txt";
    size_t chunkSize = 4096;

    std::cout << "=== Merkle Tree Integrity Check ===\n\n";

    // 1. Load clean file and chunk it
    std::string cleanData = readFileToString(cleanFile);
    auto cleanChunks = chunk_input(cleanData, chunkSize);
    std::cout << "Building Merkle tree for CLEAN file...\n";
    std::string cleanRoot = buildMerkleTree(cleanChunks);
    std::cout << "Clean Merkle Root: " << cleanRoot << "\n\n";

    // 2. Load corrupted file and chunk it
    std::string corruptData = readFileToString(corruptFile);
    auto corruptChunks = chunk_input(corruptData, chunkSize);
    std::cout << "Building Merkle tree for CORRUPTED file...\n";
    std::string corruptRoot = buildMerkleTree(corruptChunks);
    std::cout << "Corrupted Merkle Root: " << corruptRoot << "\n\n";

    // 3. Compare roots
    if (cleanRoot == corruptRoot)
        std::cout << "✅ No corruption detected (roots match).\n";
    else
        std::cout << "❌ Corruption detected! Roots differ.\n";

    // 4. Verify a proof for demonstration
    std::string targetData = corruptChunks.empty() ? "" : corruptChunks[0];
    std::vector<std::pair<std::string, std::string>> proof;  // would be generated
    bool valid = verifyProof(targetData, proof, cleanRoot);
    std::cout << "Verification result for first block: " << (valid ? "Valid" : "Invalid / Corrupt") << "\n";

    return 0;
}