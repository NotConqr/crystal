#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

// Configuration
bool cleanUPD = true;
std::string server = "https://raw.githubusercontent.com/NotConqr/crystal/refs/heads/main/crystal.cpp";
std::string Remote_Version = "https://raw.githubusercontent.com/NotConqr/crystal/refs/heads/main/V_";

// Function Declarations
void Title(const std::string& title);
void wait(int sec);
void upd();
void getfile();
std::string getLocalVersion();
void saveLocalVersion(const std::string& version);

// Functions

void getfile() {
    // Remove any previous executable
    std::remove("crystals");

    // Download the updated source file
    std::string download_cmd = "curl -o crystalSRC.cpp " + server;
    if (system(download_cmd.c_str()) != 0) {
        std::cerr << "Failed to download code from the server!" << std::endl;
        return;
    }

    // Compile the downloaded file
    std::string compile_cmd = "g++ crystalSRC.cpp -o crystals";
    if (system(compile_cmd.c_str()) != 0) {
        std::cerr << "Failed to compile code!" << std::endl;
        std::remove("crystalSRC.cpp"); // Clean up source file on error
        return;
    }

    // Remove the source file after compilation if cleanup is enabled
    if (cleanUPD) {
        std::remove("crystalSRC.cpp");
    }
}

void upd() {
    // Command to download the remote version file
    std::string cmdsv = "curl -o ver.txt " + Remote_Version;
    if (system(cmdsv.c_str()) != 0) {
        std::cerr << "Can't Download Version File" << std::endl;
        return;
    }

    // Read local and remote versions
    std::string local_version = getLocalVersion();
    std::ifstream Version_File("ver.txt");
    std::string remote_version;

    if (Version_File) {
        std::getline(Version_File, remote_version);
        Version_File.close();

        // Compare versions
        if (local_version == remote_version) {
            std::cout << "You are using the latest version: " << local_version << std::endl;
        } else {
            std::cout << "A new version is available: " << remote_version << std::endl;
            std::cout << "Current version: " << local_version << std::endl;
            std::cout << "Downloading New Version" << std::endl;
            getfile();

            // Only update the local version file if the download and compilation succeed
            std::ifstream checkFile("crystals");
            if (checkFile.good()) {
                saveLocalVersion(remote_version);
            }
        }
    } else {
        std::cerr << "Could not open version file." << std::endl;
    }

    // Clean up the version file if enabled
    if (cleanUPD) {
        std::remove("ver.txt");
    }
}

std::string getLocalVersion() {
    std::ifstream local_version_file("local_version.txt");
    std::string version;

    if (local_version_file) {
        std::getline(local_version_file, version);
        local_version_file.close();
    } else {
        // If the version file doesn't exist, return an initial version
        version = "CY.0.2";
        saveLocalVersion(version); // Write initial version to the file
    }

    return version;
}

void saveLocalVersion(const std::string& version) {
    std::ofstream local_version_file("local_version.txt");
    if (local_version_file) {
        local_version_file << version;
        local_version_file.close();
    }
}

void wait(int sec) {
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

void Title(const std::string& title) {
    #ifdef _WIN32
    SetConsoleTitle(title.c_str());
    #else
    std::cout << "\033]0;" << title << "\007";
    #endif
}

// Main function
int main() {
    std::string version = getLocalVersion();
    Title("Crystal - " + version);
    upd();
    std::cout << "Done." << std::endl;
    wait(5);
    return 0;
}
