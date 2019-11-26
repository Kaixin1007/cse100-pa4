#include <fstream>
#include <iostream>

using namespace std;

class FileUtils {
  public:
    /* Check if a given data file is valid */
    static bool isValidFile(string fileName) {
        ifstream in;
        in.open(fileName, ios::binary);

        // Check if input file was actually opened
        if (!in.is_open()) {
            cout << "Invalid input file. No file was opened. Please try "
                    "again.\n";
            return false;
        }

        in.close();
        return true;
    }
};
