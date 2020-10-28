// HelloCpp.App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;



string sayHello(string phrase)
{
    return phrase + "Nayshh!!! \n";
}

void WriteToFile()
{
    ofstream myfile;
    myfile.open("example.txt");
    myfile << "Writing this to a file.\n";
    myfile.close();
}

void ReadFile()
{
    const char* fileName = "300434064523500002585_420875503.sbd";
    FILE* stream;

    errno_t err;
    int32_t fileSize;

    uint8_t val_u8;
    uint32_t val_u32;

    err = fopen_s(&stream, fileName, "rb");

    if (err != 0)
    {
        printf("%s: Cannot open file\n", fileName);
        return;
    }

    fseek(stream, 0L, SEEK_END);
    fileSize = ftell(stream);
    rewind(stream);


    int bytesRemaining = fileSize - ftell(stream);

    while (bytesRemaining > 1)
    {
        fread(&val_u32, sizeof(val_u32), 1, stream);

        int32_t timeOfDay = (val_u32 >> 0) & 0x7FF;
        int32_t interval = (val_u32 >> 11) & 0x7FF;
        int32_t measurementCnt = (val_u32 >> 22) & 0x1F;
        int32_t deltaType = (val_u32 >> 27) & 0x3;
        int32_t precision = (val_u32 >> 29) & 0x7;

        cout << timeOfDay << " " << interval << " " << measurementCnt << " " << deltaType << " " << precision << "\n";

        // MeasurementCh_t* pCh = &measurementSet.channel[ch_idx];

        bytesRemaining = fileSize - ftell(stream);
    }

    fread(&val_u8, sizeof(val_u8), 1, stream);
    uint8_t batteryCV = val_u8;

    cout << batteryCV << " <-- battery \n";

    if (stream)
    {
        err = fclose(stream);
        if (err == 0)
        {
            //printf("The file " + fileName + " was closed\n");
        }
        else
        {
            //printf("The file " + fileName + " was not closed\n");
        }
    }

}

void Test()
{
    string result = sayHello("Hello I say! \n");
    cout << result;
    cout << "Hello World!\n";
    cout << "Nice Cpp Jul!\n";


    int age = 25;
    age = 26;
    float weight = 65.5;
    double balance = 123456.7;
    char gender = 'f';
    string username = "CodeBeauty";
    bool isTodaySunny = false;
    string colors[10] = {};
    string names[] = { "Vlad", "Faith", "Julius" };

    cout << names[0];

    cin >> colors[0];

    /*
      bool isTodaySunny = false;
      bool isTodayWeekend = false;

      if (isTodayWeekend && isTodaySunny) {
         cout << "Go to park" << endl;
      }
      else {
         cout << "Go to Work" << endl;
      }
    */
}


void PointerTest()
{
    // int a = 5;
    // point *b = &a; --> declar a pointer.. pointer to address of a.
    // int c = *b;   --> get value at...
    cout << "32 BIT: Pointers! \n";

    int a = 5;
    int* b = &a;
    int c = *b;

    cout << c;
    cout << "\n";
}

int main()
{

    PointerTest();

    ReadFile();
    WriteToFile();

    system("pause>0");
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
